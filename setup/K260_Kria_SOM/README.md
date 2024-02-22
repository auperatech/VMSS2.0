# VMSS 2.0 Docker Installation Guide for KV260/KR260 Kria SOM with Ubuntu 22.04

This guide provides step-by-step instructions for installing VMSS 2.0 Docker for K26 on KV260 or KR260 Kria SOM, using the Kria Ubuntu Desktop 22.04 LTS Image. This tutorial has been tested on both KV260 and KR260 with the image flashed using Balena Etcher on a Windows 11 machine.

## Hardware/OS requirements

- Kria SOM (KV260 or KR260) with Kria Ubuntu Desktop 22.04 LTS Image.
- 32GB or more (We used 128GB SanDisk Extreme PLUS 200MB/s Read SD card.)
- Follow the initial setup instructions from Xilinx: [Setting up the SD Card Image](https://www.xilinx.com/products/som/kria/kv260-vision-starter-kit/kv260-getting-started-ubuntu/setting-up-the-sd-card-image.html).

## Installation Steps

### 1. System update
It is recommended to have the latest upgraded Ubuntu:
   ```bash
   sudo apt-get update
   sudo apt-get upgrade
   ```
***NOTE: This step may take several minutes. Follow the on-screen instructions, update kernels as required, and restart impacted services by selecting the corresponding checkboxes during the process. Specifically, for the on-screen prompt shown below, please select the option shown here***

<div align="center">
  <img src="kernel_update.jpg" alt="kernel_update">
</div>

After these steps, make sure that you perform a reboot on the system:
```bash
sudo reboot
```

### 2. Install Docker Image dependencies

VMSS 2.0 Docker Image requires the following dependencies to be installed on the host OS: `vitis-ai-runtime`, `bootgen-xlnx` as well as `kria-firmware-app`. Here is how you install these dependencies on the OS:

   ```bash
   sudo add-apt-repository -y ppa:xilinx-apps/ppa
   sudo apt-get install -y vitis-ai-runtime bootgen-xlnx
   cd ~/
   git clone --branch xlnx_rel_v2022.1 https://github.com/Xilinx/kria-apps-firmware.git
   cd kria-apps-firmware
   sudo make -C boards/ install
   cd ~/
   rm -rf kria-apps-firmware
   ```

You would also need to install docker engine. The following docker engine installation guide follows the guide [mentioned here](https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository)

#### Setup docker repository

   ```bash
   # Add Docker's official GPG key:
   sudo apt-get update
   sudo apt-get install ca-certificates curl
   sudo install -m 0755 -d /etc/apt/keyrings
   sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
   sudo chmod a+r /etc/apt/keyrings/docker.asc
   
   # Add the repository to Apt sources:
   echo \
     "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
     $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
     sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
   sudo apt-get update
   ```

#### Install docker packages
   ```bash
   sudo apt-get install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
   ```

#### Verify docker installation
   ```bash
   sudo docker run hello-world
   ```

### 3. Pull Docker image
VMSS is available throught the public docker repository `auperastor/kria-som-dev:latest`. You can pull the latest docker by `sudo docker pull auperastor/kria-som-dev:latest` on your Kria SOM device.

### 4. Start Docker

This docker ideally starts with a shared directory on host OS and the docker. For this reason first go the shared directory and then start the docker. Here is how:

```bash
cd <SHARED-DIR>;
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
    --volume="$HOME/.Xauthority:/root/.Xauthority:rw" \
    -v /tmp:/tmp \
    -v /dev:/dev \
    -v /sys:/sys \
    -v /etc/vart.conf:/etc/vart.conf \
    -v /lib/firmware/xilinx:/lib/firmware/xilinx \
    -v /run:/run \
    -v `pwd`:`pwd` \
    -w `pwd` \
    -e NFS_ABS_PATH=`pwd` \
    --name=<DOCKER-NAME> \
    -dit auperastor/kria-som-dev:latest bash
```

Note that `<SHARED-DIR>` is the directory that you share between host OS and docker. Also `<DOCKER-NAME>` is the name of the docker that you want to create. Now you can enter the docker:

```bash
sudo docker container exec -ti <DOCKER-NAME> bash
```

### 5. Execute Pipelines

Now before running the test pipeline, let's understand what we are about to run. `avaser` is VMMS's command that runs a graph/pipeline that you provide via `-c` argument. There are 3 pbtxt files that are required to pass to `avaser`:

##### Input `-i` : 
    comes after `-i` parameter and contains the same number of RTSP streams as the input_streams contained in your pipeline.pbtxt. 

##### Output `-o`: 
    comes after `-o` parameters and contains the same number of rtsp streams (or file passes) as the output_streams contained in your pipeline.pbtxt. 

##### Config `-c`: 
    comes after `-c` parameter and contains your pipeline definition (the list of nodes and connections). 

To learn more about VMSS please refer to our [user guide available here](https://auperatechvancouver.sharepoint.com/Shared%20Documents/Forms/AllItems.aspx?id=%2FShared%20Documents%2Freleases%2Fvmss2%2E0%5Favaf%5Favas%5Favac%2Fuser%5Fguides&p=true&ga=1).

It's time to run a test pipeline that runs a vehicle detector on a test RTSP video stream and watch the results on VLC(or any Video player that can run RTSP streams). First, let's navigate to the test directoy, then run the following command.


# TODO Update from here
```
cd /opt/aupera/vmss/test/box_detector_car/
```
Then let's run the pipeline. Before running this test pipeline, I highly recommed you change the output stream name defined in `output.pbtxt` by appending a unique name to the end of the stream name to avoid conflicts with other users that are trying to use the same name. If the name you define in outputbtxt is in use, the pipeline will crash. For instance, you can change the default address in `output.pbxt` to the following value by appedning your name:

```
"rtsp://vmss.auperatechnologies.com:554/car-som-out-your-name"
```

Finally, run this command:

```
avaser -i input.pbtxt -o output.pbtxt -c 1input_1output.pbtxt
```

Open VLC player on your computer and type the URL you passed to avaser as your `output.pbtxt` entry in VLC under `Media->Open Network Stream...`. You should be able to see bounding boxes overlayed around the cars in the scene. 

To illustrate the pipeline your just ran, please refer to the the following diagram: 
<div align="center">
  <img src="box_detector_visualizer.png" alt="following diagram">
</div>

In brief, all of the calculators used in your pipeline are shown above. All of these calculators can be reused to run different pipelines. For the users who may not be familiar with mux/demux, encode/decode, and filtering, to simply this further, you may think of the above diagram as a pipeline shown below where you can just copy and past the components that are summarized as `video_in` and `video_out` in any pipeline to achieve your goal.
<div align="center">
  <img src="simplified_graph.png" alt="simplified diagram">
</div>



