#!/bin/bash

# Exit script on error
set -e

export DEBIAN_FRONTEND=noninteractive

# Update system packages
echo "Updating system packages..."
sudo apt-get update

# Install 'bootgen'
echo "Installing bootgen..."
if ! dpkg -s bootgen-xlnx &>/dev/null; then
    sudo add-apt-repository -y ppa:xilinx-apps/ppa
    sudo apt-get install bootgen-xlnx -y
else
    echo "'bootgen-xlnx' is already installed."
fi

# Check for proper firmware installation
FIRMWARE_DIR="/lib/firmware/xilinx/kv260-smartcam/"
REQUIRED_FILES=("kv260-smartcam.bin" "kv260-smartcam.dtbo" "kv260-smartcam.xclbin" "shell.json")

echo "Checking for proper firmware installation..."
if [ -d "$FIRMWARE_DIR" ]; then
    MISSING_FILES=0
    for file in "${REQUIRED_FILES[@]}"; do
        if [ ! -f "${FIRMWARE_DIR}${file}" ]; then
            echo "Missing: ${file}"
            MISSING_FILES=1
        fi
    done
    if [ $MISSING_FILES -eq 1 ]; then
        echo "Firmware not properly installed. Missing files in ${FIRMWARE_DIR}"
        echo "Cloning and installing Kria Starter Kit Application Firmware..."
        git clone --branch xlnx_rel_v2022.1 https://github.com/Xilinx/kria-apps-firmware.git
        cd kria-apps-firmware/
        sudo make -C boards/ install
        cd ..
    else
        echo "Firmware is properly installed. Skipping firmware installation."
    fi
else
    echo "Firmware directory does not exist: ${FIRMWARE_DIR}"
    echo "Cloning and installing Kria Starter Kit Application Firmware..."
    git clone --branch xlnx_rel_v2022.1 https://github.com/Xilinx/kria-apps-firmware.git
    cd kria-apps-firmware/
    sudo make -C boards/ install
    cd ..
fi

# Function to check if app is already loaded
isAppLoaded() {
    loadedAppInfo=$(sudo xmutil listapps | grep kv260-smartcam)
    if [[ $loadedAppInfo == *"(0+0)                  0"* ]]; then
        echo 1
    else
        echo 0
    fi
}

# Check if the kv260-smartcam app is already loaded
if [[ $(isAppLoaded) -eq 1 ]]; then
    echo "kv260-smartcam is already loaded. Skipping loading step."
else
    echo "Loading kv260-smartcam..."
    sudo xmutil unloadapp || true
    sudo xmutil loadapp kv260-smartcam
fi

# Install dependencies for Docker
echo "Installing Docker dependencies..."
sudo apt-get install apt-transport-https ca-certificates curl software-properties-common -y

# Prepare and install Docker Engine
echo "Preparing and installing Docker Engine..."
if ! type docker &>/dev/null; then
    curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
    echo "deb [arch=arm64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
    sudo apt-get update
    sudo apt-get install -y docker-ce docker-ce-cli containerd.io
else
    echo "Docker is already installed."
fi

# Pull VMSS Docker Image
echo "Pulling VMSS Docker image..."
sudo docker pull auperastor/kria-som-dev:latest

echo -e "\nInstallation completed successfully. Creating a Docker container now...\n"

# Adding blank lines and ANSI color codes to make the prompts more visible
echo -e "Please provide the following information to configure your Docker container:\n"

printf "\033[1;33mEnter the shared directory path to be accessed by your Docker container (leave blank for current directory->[%s]):\033[0m " "$(pwd)"

# Function to validate the full path
validateFullPath() {
    if [[ "$1" = /* ]]; then
        echo "Valid full path."
    else
        echo -e "\033[0;31mThe provided path is not a full path. Please ensure it starts with '/'. Example: /home/ubuntu/shared\033[0m"
        return 1
    fi
}

# Loop until a valid full path is provided or the current directory is chosen
while true; do
    read -p "Path: " SHARED_DIR
    SHARED_DIR=${SHARED_DIR:-$(pwd)}
    if validateFullPath "$SHARED_DIR"; then
        break
    else
        echo "Please enter a valid full path."
    fi
done
echo

# Prompt for container name with enhanced visibility
echo -e "\033[1;33mEnter the container name (leave blank for default 'vmss_docker'):\033[0m"
read -p "Name: " DOCKER_NAME
DOCKER_NAME=${DOCKER_NAME:-"vmss_docker"}
echo

# Inform the user about the default values being used if necessary
if [ "$SHARED_DIR" == "$(pwd)" ]; then
    echo -e "\033[0;32mNo shared directory specified, using the current directory:\033[0m $SHARED_DIR\n"
fi

if [ "$DOCKER_NAME" == "vmss_docker" ]; then
    echo -e "\033[0;32mNo Docker container name specified, using the default name:\033[0m $DOCKER_NAME\n"
fi

# Create the shared directory if it doesn't exist and inform the user
if [ ! -d "$SHARED_DIR" ]; then
    echo "Shared directory does not exist, creating it for you at: $SHARED_DIR"
    mkdir -p "$SHARED_DIR"
fi

# Navigate to the shared directory
cd "$SHARED_DIR" || exit

# Check if a Docker container with the specified name already exists
while sudo docker ps -a --format '{{.Names}}' | grep -q "^${DOCKER_NAME}$"; do
    echo -e "\033[0;31mA Docker container named '$DOCKER_NAME' already exists.\033[0m"
    read -p "Would you like to (r)emove the existing container or (e)nter a new name? [r/e]: " response
    case "$response" in
        [rR])
            echo "Removing existing container..."
            sudo docker rm -f "$DOCKER_NAME"
            echo "Existing container removed. Proceeding with the creation of the new container."
            break
            ;;
        [eE])
            read -p "Please enter a new name for your Docker container: " NEW_NAME
            DOCKER_NAME=${NEW_NAME:-"vmss_docker"} # Use the entered new name or default to "vmss_docker" if input was blank
            ;;
        *)
            echo "Invalid response. Please answer with 'r' for remove or 'e' for enter a new name."
            ;;
    esac
done

# Proceed with Docker container creation using the final DOCKER_NAME
echo "Starting Docker container named $DOCKER_NAME in $SHARED_DIR..."
sudo docker run \
    --env="DISPLAY" \
    -h "aupera-docker" \
    --env="XDG_SESSION_TYPE" \
    --cap-add sys_admin \
    --cap-add NET_ADMIN \
    --cap-add NET_RAW \
    --network=host \
    --privileged=true \
    --hostname=general \
    -v /tmp:/tmp \
    -v /dev:/dev \
    -v /sys:/sys \
    -v /etc/vart.conf:/etc/vart.conf \
    -v /lib/firmware/xilinx:/lib/firmware/xilinx \
    -v /run:/run \
    -v "$SHARED_DIR":"$SHARED_DIR" \
    -w "$SHARED_DIR" \
    -e NFS_ABS_PATH="$SHARED_DIR" \
    --name="$DOCKER_NAME" \
    -dit auperastor/kria-som-dev:latest bash

echo "Container $DOCKER_NAME started successfully and can access $SHARED_DIR."

echo -e "\n\033[1;36mNow you can run your interactive bash session inside the Docker container by running:\033[0m"
echo -e "\033[0;32m    sudo docker container exec -ti $DOCKER_NAME bash\033[0m\n"
