# VMSS 2.0 Docker usage guide for KV260/KR260 Kria SOM with Ubuntu 22.04

If you have not created the docker container already, please take a look at [this guide](../../setup/K260_Kria_SOM/README.md) first.


### 1. Configuration, Input, Output

Before running the test pipeline, let's understand what we are about to run.  
`avaser` is VMMS's command that runs a graph/pipeline that you provide via `-c` argument. There are `3` pbtxt files that are required to pass to `avaser`:

##### Config `-c`: 
    comes after `-c` parameter and contains your pipeline definition (the list of nodes and connections). 

##### Input `-i` : 
    comes after `-i` parameter and contains the same number of RTSP streams as the input_streams contained in your pipeline.pbtxt

##### Output `-o`: 
    comes after `-o` parameter and contains the same number of rtsp streams (or file passes) as the output_streams contained in your pipeline.pbtxt


To learn more about VMSS please refer to our [user guide available here](https://auperatechvancouver.sharepoint.com/Shared%20Documents/Forms/AllItems.aspx?id=%2FShared%20Documents%2Freleases%2Fvmss2%2E0%5Favaf%5Favas%5Favac%2Fuser%5Fguides&p=true&ga=1).

It's time to run a test pipeline that runs a vehicle detector on a test RTSP video stream and watch the results on VLC(or any other video player that can run RTSP streams).

### 2. Execute Pipelines
First, let's navigate to the test directoy, then run the following command.
<!-- # TODO Update from here -->
```bash
cd /opt/aupera/vmss/test/box_detector_car/
```

Before running this test pipeline, we highly recommed you to change the output stream name defined in `output.pbtxt` by appending a unique name to the end of the stream name to avoid conflicts with other users that are trying to use the same name. If the name you define in `output.ptxt` is in use, the pipeline will crash. For instance, you can change the default address in `output.pbxt` to the following value by appedning your name:

```
"rtsp://vmss.auperatechnologies.com:554/car-som-out-your-name"
```

Finally, run this command:

```bash
avaser -c 1input_1output.pbtxt -i input.pbtxt -o output.pbtxt
```

You will be able to see some logs on the console once you issue the above command. Let's take a look at the output in the next step.

### 3. Visual Output

While the `avaser` is running, Open VLC player on your computer and follow `Media->Open Network Stream...`:
<div align="center">
  <img src="VLC-menu-NetStream.png" alt="VLC Menu">
</div>

In the window that pops up, type the URL you passed to `avaser` as output (in your `output.pbtxt` entry), for example:
<div align="center">
  <img src="VLC-URL.png" alt="VLC-URL">
</div>

You should be able to see the output stream on your screen.

### 3. Illustrate the Flow

To illustrate the sample pipeline you just ran, please refer to the the following diagram: 
<div align="center">
  <img src="box_detector_visualizer.png" alt="following diagram">
</div>

In summary, all of the calculators used in your pipeline are shown above. All of these calculators can be reused to run different pipelines. For the users who may not be familiar with `mux/demux`, `encode/decode`, and `filtering`, to simplify this further, you may think of the above diagram as a pipeline shown below where you can just copy and past the components that are summarized as `video_in` and `video_out` in any pipeline to achieve your goal.

<div align="center">
  <img src="simplified_graph.png" alt="simplified diagram">
</div>

