# VMSS 2.0 Docker Installation Guide for KV260/KR260 Kria SOM with Ubuntu 22.04

This guide provides step-by-step instructions for installing VMSS 2.0 Docker for K26 on KV260 or KR260 Kria SOM, using the [Kria Ubuntu Desktop 22.04 LTS Image](https://ubuntu.com/download/amd). This tutorial has been tested on both KV260 and KR260 with the image flashed using Balena Etcher on a Windows 11 machine.

## Hardware/OS Requirements

- Kria SOM (KV260 or KR260) with Kria Ubuntu Desktop 22.04 LTS Image.
- 32GB storage or more (We used 128GB SanDisk Extreme PLUS 200MB/s Read SD card).
- Follow the initial setup instructions from Xilinx: [Setting up the SD Card Image](https://www.xilinx.com/products/som/kria/kv260-vision-starter-kit/kv260-getting-started-ubuntu/setting-up-the-sd-card-image.html).

## Installation Steps

### 1. Download and Execute the Installation Script

Run the following command in your terminal to download and execute the installation script:

```bash
wget -qO aup_vmss_setup.sh https://raw.githubusercontent.com/auperatech/VMSS2.0/main/setup/K260_Kria_SOM/aup_vmss_setup.sh && bash aup_vmss_setup.sh
```
Follow the on-screen prompts to:

- Specify the full path of the shared directory for Docker container access. Leave blank to use the current directory.
- Enter the name for your Docker container. Leave blank to use the default name `vmss_docker`.

### 2. Accessing Your Docker Container
After the installation, you can access your Docker container's interactive bash session with the following command:

```bash
sudo docker container exec -ti vmss_docker bash
```
Replace `vmss_docker` with your specified container name if you did not use the default name when prompted for container name in the installation step.

Now that you have completed the installation you can follow our [tutorial](../../tutorial/K260_Kria_SOM/) to run examples and learn about VMSS2.0.

## Play with Aupera Web Cloud

VMSS2.0 utility consists of two major modules, Aupera Video AI Server(AVAS) and Aupera Video AI Client(AVAC). AVAS is the server that runs and manages various AI tasks, and AVAC is a web cloud application that allows users to use a friendly GUI to connect to AVAS. It only takes several simple steps to launch AVAS inside the docker and play with our AVAC after the docker is successfully built. Let's play!

**_NOTE: The following section assumes that you already entered the docker by the command listed above._**

**First, please run a single script to start AVAS.**

```bash
start.sh skip_check
```

**Then, with a single command to get the unique serial number(sn) of your device that we prepared.**

```bash
cat /opt/aupera/avas/etc/kria_som_sn.txt
```

**Next, create your own account and sign in to our Web Cloud.**

Sign up for an account at: [https://auperatechnologies.com](https://auperatechnologies.com/). 
Once you sign in with your new account, you will be asked to add a video stream. Please click the **Add Stream** button to add video streams you would like to use, or you could directly use the demo video streams we prepared for testing as listed below: 

```
rtsp://vmss.auperatechnologies.com:554/crowd
rtsp://vmss.auperatechnologies.com:554/car
rtsp://vmss.auperatechnologies.com:554/retail
rtsp://vmss.auperatechnologies.com:554/imagenet
rtsp://vmss.auperatechnologies.com:554/faces
```

**Last, add the device with the unique serial number and start running tasks.**

Go to the **AI Hosts** tab in the navigation bar. Click the **Add AI Host** button to add a host. 
Choose the **Add by Serial Number** tab, enter an AI Host Name of your choice, and enter the unique serial number from the last step in AI Host S/N input.

After device verification and the device is successful, you can go to the **AI Tasks** section to create your tasks and start to play!

**_NOTE: For a video and more detailed document to guide you through AVAC and creating tasks, please refer to_** 
[video guide](../../docs/avac/README.md)
[avac user guide document](../../docs/avac/README.md)

<!-- 

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

-->

