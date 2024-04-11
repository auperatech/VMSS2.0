# VMSS 2.0 Installation Guide for PlanetSpark SBC X7 Smart Edge AI Box

This guide provides step-by-step instructions for installing VMSS 2.0 on the PlanetSpark X7 Edge AI Box. 

## Prerequisites

- PlanetSpark X7 Edge AI Box 
- 16GB Micro SD Card
- USB-C to USB-A Data Cable
  
## Installation Steps



### 1. Flash Boot Image

- Download the [X7 2022.1 Boot Image](https://amd.vmaccel.com/object-store/v1/aup_releases/petalinux2022.1-SBC-X7.zip) and save it on your computer.
- Download the Balena Etcher to flash the SD Card. 
- Follow the instructions in the tool and select the downloaded image to flash onto your microSD card.

### 2. Power On the Device

- Insert the flashed SD Card from Step#1 into Slot#1 of the X7 box clearly printed as Slot #1.
- Connect to the internet via ethernet cable connection and connect the device to power and make sure you can power on the device. If you followed the steps correctly you should not see any red LED lights on the box.

### 3. Connect to the Device via Serial port

- With the USB-C to USB-A cable, insert a USB-C side into the PlanetSpark X7 Edge AI Box.
- Insert the USB-A side into a PC with serial port connection software such as Teraterm (windows) or MiniCom (Linux).
- In the serial port software set the connection settings to:
  - Speed (Baud Rate): 115200
  - Data: 8bit
  - Parity: none
  - Stop bits: 1 bit
  - Flow control: none
  
- In the serial connection terminal you should now see a login message, the default credentials are:
  - username: `root`
  - password: `root`

### 4. Connecting to Internet (Static IP or Dynamic IP)
- Follow one of the steps below to configure either a Static IP or Dynamic IP.

1. Static IP: If you want to force the device to have a specific IP, type these commands in the terminal:
  
    ```bash
    eeprom-cfg -w with_dhcp 0
    eeprom-cfg -w ip xxx.xxx.xxx.xxx
    ```
    
    Note: Replace xxx.xxx.xxx.xxx with your desired IP address.
    
    ```bash
    eeprom-cfg -w netmask 255.255.255.255
    eeprom-cfg -w gw 255.255.255.255
    eeprom-cfg -w dns 255.255.255.255
    ```
    Note: 255.255.255.255 will use defaults for your network. Only configure gateway (gw) if needed.
  
2. Dynamic IP: If you want the device to discover its IP through DHCP, type these commands in the terminal:
    ```bash
    eeprom-cfg -w with_dhcp 1
    ```

- Once you have setup either a Static IP or Dynamic IP, cold reboot the device.
- To see if your have internet connection after powerup type: 
```bash 
ifconfig 
```


### 5. Find the Device IP and Connect via SSH

- Use a third-party IP Scanner tool such as [Angry IP Scanner](https://angryip.org/) or through your router to find the X7 IP address 
- Once you have obtained the correct IP address login into the box via `ssh`: 
  
```bash
ssh root@<IP-Address>
```

The default login credentials are:
username: root
password: root


### 6. Install DRM Package and Requeset License Key

You must have a valid license key in order to use Aupera's software. In order to activate your license you must follow the steps stated below:

- Download the DRM package on the device by running the command below:
```bash
wget https://amd.vmaccel.com/object-store/v1/aup_releases/DRM-3.1.0-202310172335-md5-2ab483716a3cfb56beb18ab8a078e1a9.pkg
```
- Install DRM by running the following commands:

```bash
pkg-probe DRM-3.1.0 DRM-3.1.0-202310172335-md5-2ab483716a3cfb56beb18ab8a078e1a9.pkg
cd /D0/APP/DRM-3.1.0
chmod +x install
./install
```

### 7. Get the Device DNA Number and Ask Aupera for Credentials

- Run the following command to get the compressed file(xxx_dna.tar.gz) that contains the device's DNA
```bash
drm -d
```

- Send the xxx_dna.tar.gz to Aupera Technologies and ask for the DRM credentials for this
device.

- After getting the credential file xxx_lic.tar.gz, put it under '/D0/.drm' directory and run the following commands to activate the DRM.

```bash
cd /D0/.drm
drm -a
```

You should see a message printed on the terminal indicating succssefull activation of your device. Please contact Aupera Technologies if there is any issues with this step.

### 8. Install Required Runtime Libraries

- Download and install the libraries by running the following commands:

```bash
wget https://amd.vmaccel.com/object-store/v1/aup_releases/axstream-2022.1-5.0.3-202307201108-md5-5c98d05cd6992a5ea3c536449a3babb3.pkg
pkg-probe.sh axstream-2022.1-5.0.3 axstream-2022.1-5.0.3-202307201108-md5-5c98d05cd6992a5ea3c536449a3babb3.pkg
cd /D0/APP/axstream-2022.1-5.0.3
./install
```

### 9. Install VMSS Package 

- Download and install the VMSS package by running the following commands:

```bash
wget https://amd.vmaccel.com/object-store/v1/aup_releases/vmss-avaf-3.3.0-avas-3.1.0-202402091718-md5-90e31203f9fae832ff4f49bb7f9fe4a0.pkg
pkg-probe.sh ai_framework avmss-avaf-3.3.0-avas-3.1.0-202402091718-md5-90e31203f9fae832ff4f49bb7f9fe4a0.pkg
cd /D0/APP/ai_framework
./install
```

### 10. Login to VMSS Web APP and Add Your Device

Now you can add the device to your account on [VMSS Web APP](https://vmss.auperatechnologies.com/) under AI Host by rerieving it's DNA number and enter as the Serial Number. You can find the DNA number by running the following command:

```bash
drm -d
```
