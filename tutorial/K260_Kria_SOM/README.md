# Aupera VMSS2.0 Tutorial

Welcome to the Aupera VMSS2.0 Tutorial. This guide will walk you through setting up a face detection system that can run on RTSP streams, incorporating tracking and detection interval adjustments, changing input types, modifying output actions, and switching detection models.

## Table of Contents
- [Aupera VMSS2.0 Tutorial](#aupera-vmss20-tutorial)
  - [Table of Contents](#table-of-contents)
  - [Download Required Assets](#download-required-assets)
  - [Person Detection](#person-detection)
        - [Config `-c`:](#config--c)
        - [Input `-i` :](#input--i-)
        - [Output `-o`:](#output--o)
    - [Changing the Input to RTSP](#changing-the-input-to-rtsp)
  - [Reconfiguring the Pipeline to Run Face Detection](#reconfiguring-the-pipeline-to-run-face-detection)
  - [Adding a Tracker and Reducing Detection Interval](#adding-a-tracker-and-reducing-detection-interval)
  - [Changing Input from RTSP to USB](#changing-input-from-rtsp-to-usb)
  - [Modifying Output to Send SMS](#modifying-output-to-send-sms)
  - [Tips and Tricks](#tips-and-tricks)
    - [Test RTSP Streams](#test-rtsp-streams)
    - [Available Models](#available-models)

## Download Required Assets

Please make sure you have followed our [setup procedure](../../setup/K260_Kria_SOM/) and you have launched your own docker container before following the steps below. 

First, You need to download the required assets for this tutorial. Let's starting by downloading the required zipped for this tutorial and unzip it. 

```
wget https://amd.vmaccel.com/object-store/v1/aup_releases/k260_tutorial_assets_20240310.zip && unzip k260_tutorial_assets_20240310.zip
```
This will produce the following directory:
```
./assets
├── face_demo_82s.mp4
├── rtsp_facedetect-tracker_rtsp.pbtxt
├── rtsp_facedetect_rtsp.pbtxt
├── rtsp_persondetect_rtsp.pbtxt
├── usb_facedetect-tracker_rtsp.pbtxt
└── usb_facedetect-tracker_sms.pbtxt
```

## Person Detection
In this section, we will set up a person detector to run on a video file and view the results as bounding boxes drawn on the output video. To do so, we will use a video file in the assets for this totorial, a SSD based model provided by AMD, and finally we push the output to our public RTSP server and use a video player such as VLC to view the results.


Now, let's create our `input.pbtxt` and `output.pbtxt` files that are required for running a pipeline. For the input, we are using mp4 file `face_demo_82s.mp4`. Therefore, the path should be passed as `input_urls` as shown below: 

```
echo 'input_urls: "assets/face_demo_82s.mp4"' > input.pbtxt
```

For the output, we follow the same logic, but instead of saving the ouput in a file we are going to stream the results live by pushing the output to Aupera's public RTSP server. To do so, all you need to do is choose any unique arbitrary name and append to `rtsp://vmss.auperatechnologies.com:554/` and pass to to your `output_urls` as shown below

```
echo 'output_urls: "rtsp://vmss.auperatechnologies.com:554/your-output-name"' > output.pbtxt
```

***NOTE*** The RTSP server requires a unique stream to be used. Please change the "your-output-name" to your desired output name before proceeding to the next step. 

Finally, make sure you have a video player available to watch your output stream. We recommend using [VLC.](https://www.videolan.org/) Launche the video player and make sure you can run a test RTSP stream. You can use one of our test streams to verify this step. You may use any of the test streams listed [here](#test-rtsp-streams) to verify this.



***NOTE*** In VLC you can paste one of the streams above  `Media->Open Network Stream...` and press `Play`. 

Now that you have created your input and output files and verified you can watch an RTSP stream, you are ready to start this example. To run this example run the following command: 

```
avaser -i input.pbtxt -o output.pbtxt -c assets/rtsp_persondetect-tracker_rtsp.pbtxt
```

Upon running, you can watch the output stream using VLC or an alternative by using the link you set in your `output.pbtxt` (i.e `rtsp://vmss.auperatechnologies.com:554/your-output-name`). The output video should show a bounding box around each person.

In short, `avaser` is VMMS's command that runs a graph/pipeline. There are `3` pbtxt files that are required to pass to `avaser`:

##### Config `-c`: 
    expects a pipeline config file in `.pbtxt` format that contains your pipeline definition (the list of nodes and connections). 

##### Input `-i` : 
    expects your input(s) listed as pair(s) if `input_urls` and URL/File values passed a single `.pbtxt` file.

##### Output `-o`: 
    expects your output(s) listed as pair(s) if `output_urls` and URL/File values passed a single `.pbtxt` file.

### Changing the Input to RTSP

You can easily change the input stream to a live RTPS stream by changing the `input_urls`. For instance you can modify the previous `input.pbtxt` to run on a Mall RTSP stream by running the this command:

```
echo 'input_urls: "rtsp://vmss.auperatechnologies.com:554/crowd2"' > input.pbtxt
```

Now you can run the same `avaser` command you ran before by passing this new input input file:

```
avaser -i input.pbtxt -o output.pbtxt -c assets/rtsp_persondetect_rtsp.pbtxt
```

Now you can verify the new pipeline running on this new input by watching the address you set as your `output_urls` in `output.pbtxt` file.

## Reconfiguring the Pipeline to Run Face Detection 

In the previous step you were able to run a person detector model provided via AMD Vitis AI model zoo on two different sources of input (MP4 file and RTSP Stream). In this section, we are going to run the last pipeline you just ran but change the model from a person detector to a face detector. First, we will walk you through what's needed. Then we will explain the logic behind it futher.

In order to reconfigure the pipeline for this purpose you only need to modify the following 3 values in   `assets/rtsp_persondetect_rtsp.pbtxt` pipeline that you used in the previous step:

- [`ml_model_kernel_name`](https://github.com/auperatech/VMSS2.0/blob/ee5dff5b3479efb2d03464dcd49f66ac7b1f686e/tutorial/K260_Kria_SOM/assets/rtsp_persondetect_rtsp.pbtxt#L50): "densebox_320_320"
- [`detector_type`](https://github.com/auperatech/VMSS2.0/blob/ee5dff5b3479efb2d03464dcd49f66ac7b1f686e/tutorial/K260_Kria_SOM/assets/rtsp_persondetect_rtsp.pbtxt#L54): "FaceDetectDenseBox"
- [`total_classes`](https://github.com/auperatech/VMSS2.0/blob/ee5dff5b3479efb2d03464dcd49f66ac7b1f686e/tutorial/K260_Kria_SOM/assets/rtsp_persondetect_rtsp.pbtxt#L63): 2

Once you made the changes mentioned above, confirm your input and output urls as shown below:
```
root@general:/home/ubuntu# cat input.pbtxt
input_urls: "rtsp://vmss.auperatechnologies.com:554/crowd2"
root@general:/home/ubuntu# cat output.pbtxt
output_urls: "rtsp://vmss.auperatechnologies.com:554/your-output-name"
```
Then run the pipeline as shown before by running `avaser` and watch the results in your video player.
```
avaser -i input.pbtxt -o output.pbtxt -c assets/rtsp_persondetect_rtsp.pbtxt
```




[Check example here](./k260_kria_som_pbtxt.md#face-detection-on-rtsp-streams)

## Adding a Tracker and Reducing Detection Interval

Learn how to add a tracker to the face detection pipeline and reduce the detection interval for improved performance.

[Check example here](./k260_kria_som_pbtxt.md#adding-a-tracker-and-reducing-detection-interval)

## Changing Input from RTSP to USB

This section describes how to change the input source from an RTSP stream to a USB camera.

[Check example here](./k260_kria_som_pbtxt.md#changing-input-from-rtsp-to-usb)

## Modifying Output to Send SMS

Instructions on how to change the output of the detection system to send SMS alerts.

[Check example here](./k260_kria_som_pbtxt.md#modifying-output-to-send-sms)


## Tips and Tricks

### Test RTSP Streams

Here's a list of RTSP streams that you can use for testing:

| Stream Name | RTSP URL |
|-------------|----------|
| Cars Street View   | rtsp://vmss.auperatechnologies.com:554/car |
| Mall Surveilance View   | rtsp://vmss.auperatechnologies.com:554/crowd |
| Hallway   | rtsp://vmss.auperatechnologies.com:554/crowd2 |
| Compiled Subset of Imagenet Samples   | rtsp://vmss.auperatechnologies.com:554/imagenet |

### Available Models

| Model Kernel Name    | Description                       | Total Classes | TYPE | Download Link
|---------------|-----------------------------------|---------------| --------- | --------- |
| densebox_320_320 | face detector | 2  | FaceDetectDenseBox | [link](https://www.xilinx.com/bin/public/openDownload?filename=densebox_320_320-zcu102_zcu104_kv260-r2.5.0.tar.gz) |
| densebox_640_360 | face detector  | 2 | FaceDetectDenseBox | [link](https://www.xilinx.com/bin/public/openDownload?filename=densebox_640_360-zcu102_zcu104_kv260-r2.5.0.tar.gz) |
| ssd_pedestrian_pruned_0_97 | person detector | 2  | SSD  | [link](https://www.xilinx.com/bin/public/openDownload?filename=ssd_pedestrian_pruned_0_97-zcu102_zcu104_kv260-r2.5.0.tar.gz) |
| ssd_traffic_pruned_0_9 | vehicle detector | 4  | SSD  | [link](https://www.xilinx.com/bin/public/openDownload?filename=ssd_traffic_pruned_0_9-zcu102_zcu104_kv260-r2.5.0.tar.gz) |
| ssd_mobilenet_v2 | person + vehicle detector | 11 | SSD  | [link](https://www.xilinx.com/bin/public/openDownload?filename=ssd_mobilenet_v2-zcu102_zcu104_kv260-r2.5.0.tar.gz) |
| refinedet_baseline | person detector | 2  | RefineDet  | [link]() |
| yolov2_voc | VOC Dataset objects | 20  | YoloV2  | [link]() |
| yolov2_voc_pruned_0_66 | VOC Dataset objects | 20  | YoloV2  | [link]() |
| yolov3_voc | VOC Dataset objects | 20  | YoloV3  | [link]() |
| yolov3_bdd | person + vehicle detector | 10  | YoloV3  | [link]() |
| yolov3_adas_pruned_0_9 | person + vehicle detector | 10 | YoloV3  | [link]() |
| yolov3_voc_tf | VOC Dataset object | 20  | YoloV3  | [link]() |

- How to read from a file
- Saving detection results to a file
- Links to example projects and additional resources

Remember to replace placeholders (like RTSP URLs and model names) with actual data and add more detailed instructions and code snippets as needed. 
