# VMSS 2.0 Installation Guide for KV260/KR260 Kria SOM with Ubuntu 22.04

This guide provides step-by-step instructions for installing VMSS 2.0 on the KV260 or KR260 Kria SOM, using the Kria Ubuntu Desktop 22.04 LTS Image. This tutorial has been tested on both KV260 and KR260 with the image flashed using Balena Etcher on a Windows 11 machine.

## Prerequisites

- Kria SOM (KV260 or KR260) with Kria Ubuntu Desktop 22.04 LTS Image.
- 128GB SanDisk Extreme PLUS 200MB/s Read SD card.
- Follow the initial setup instructions from Xilinx: [Setting up the SD Card Image](https://www.xilinx.com/products/som/kria/kv260-vision-starter-kit/kv260-getting-started-ubuntu/setting-up-the-sd-card-image.html).

## Installation Steps

### 1. System Update
Start by updating your system packages. Open a terminal and run:
   ```bash
   sudo apt update
   sudo apt upgrade
   ```
***NOTE: This step takes several minutes. Follow the on-screen instructions, update kernels as required, and restart impacted services by selecting the corresponding checkboxes during the process.***  

### Reboot System
After updating, reboot your system to ensure all updates are applied.
```
sudo reboot
```

### 2. Download, Extract, & Install VMSS Package
Download the VMSS package for Ubuntu 22.04 using wget:

```
wget https://amd.vmaccel.com/object-store/v1/aup_releases/vmss_avaf3.2.0_k260_ubuntu22_md5sum927de12d5f5aeefd1224b72d0e052956.tar.gz
```

Once the download is complete check `md5sum` of downloaded package to match the number provided in the package name to ensure the download process was successful, then extract the package:

```
tar -xzvf vmss_k260_ubuntu22_vai2.5_md5sum4705079acb2d31979864a8c34d9a0e47.tar.gz vmss_final_package/
cd vmss_final_package/
./install.sh
```

### 3. Install Xilinx bootgen Tool and Verify DPU Availability

```
cd ~/
git clone --branch xlnx_rel_v2022.1 https://github.com/Xilinx/kria-apps-firmware.git
cd kria-apps-firmware
sudo make -C boards/ install
```

Now it's time to load one of the Apps you just installed using `xmutil` to load DPU drivers and get access to DPU. For our package we have included a model from AMD model zoo that was compiled for DPU `fingerprint = 0x101000016010407` , therefore, we will load the appropriate app that matches this DPU. To do so run the following commands:
```
sudo xmutil unloadapp
sudo xmutil loadapp kv260-benchmark-b4096
show_dpu
```

The `show_dpu` command should give you the following output:
```
device_core_id=0 device= 0 core = 0 fingerprint = 0x101000016010407 batch = 1 full_cu_name=DPUCZDX8G:DPUCZDX8G_1
```

*****NOTE:***** You may use any of the available K260 apps to use VMSS. VMSS does not depend on any specific DPU design. To run inference with VMSS, you must have your models compiled for the appropriate DPU that you have loaded in this step.



### 4. Run VMSS Example

VMSS framework runs a `Video Pipeline or Graph` that is described in your `pbtxt` file. Eeach pipeline/graph consits of a set of nodes that we refer to as `calculators`. You must have the calculator files that you need for your pipeline/graph available under the `/tmp/`. This utility script will create symbolic link that links your available calculators to the `/tmp` directory. Plesae make sure that all the required calculators are available before runnign `avaser` which runs your pipeline/graph. All the calculators in our pacakge should be available under `/opt/aupera/vmss/nodes/` now using this command you can choose to link `all` or a specific calculator. Let's link all the calculators by running the followinc command:

```
link_calculator all
```

Now before running the test pipeline, let's understand what we are about to run. `avaser` is VMMS's command that runs a graph/pipeline that you provide via `-c` argument. There are 3 pbtxt files that are required to pass to `avaser`: 

##### Input `-i` : 
    comes after `-i` parameter and contains the same number of RTSP streams as the input_streams contained in your pipeline.pbtxt. 

##### Output `-o`: 
    comes after `-o` parameters and contains the same number of rtsp streams (or file passes) as the output_streams contained in your pipeline.pbtxt. 

##### Config `-c`: 
    comes after `-c` parameter and contains your pipeline definition (the list of nodes and connections). 

To learn more about VMSS please refer to our [user guide available here](https://auperatechvancouver.sharepoint.com/Shared%20Documents/Forms/AllItems.aspx?id=%2FShared%20Documents%2Freleases%2Fvmss2%2E0%5Favaf%5Favas%5Favac%2Fuser%5Fguides&p=true&ga=1).

It's time to run a test pipeline that runs a vehicle detector on a test RTSP video stream and watch the results on VLC(or any Video player that can run RTSP streams). First, let's navigate to the test directoy, then run the following command.

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

To illustrate the pipeline your just ran, please refer to the the following diagram: ![following diagram](box_detector_visualizer.png):

In brief, all of the calculators used in your pipeline are shown above. All of these calculators can be reused to run different pipelines. For the users who may not be familiar with mux/demux, encode/decode, and filtering, to simply this further, you may think of the above diagram as a pipeline shown below where you can just copy and past the components that are summarized as `video_in` and `video_out` in any pipeline to achieve your goal.![simplified diagaram](simplified_graph.png):


