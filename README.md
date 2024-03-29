# Announcement: Aupera VMSS 2.0 - Free for AMD Contest Participants

Participants in the the [AMD Pervasive AI Developer Contest](https://www.hackster.io/contests/amd2023#challengeNav) can now access Aupera's powerful Video Machine-Learning Streaming Server (VMSS 2.0) completely for **free**!

<div align="center">
  <img src="visualizer.png" alt="vmss nodes sequence">
</div>

As the diagram above indicates, VMSS2.0 empowers AMD pervasive competitors to fulfill requirements of the competition and gives them a significant edge on this competition. We claim this because
1. VMSS2.0 has integrated a set of video input solutions.
2. It also provides a suite of powerful Vitis-AI based inference nodes.
3.  Additionally, there are various nodes that handles sending updated to web, email, sms, databases and more.
4.  And last but not least, it also allows users to rapidly and efficiently integrate their own C++ to build a full Robotics/Computer Vision pipeline.

Follow [this guide](./setup/K260_Kria_SOM) to install VMSS2.0 on SOM. This developer version empowers you to rapidly build complex Video AI applications without writing any code. 

## What is VMSS? 

VMSS is a software application that functions as a **V**ideo **M**achine-Learning **S**treaming **S**erver. Its primary purpose is to provide video analytic services to multiple video streams while efficiently utilizing multiple FPGA resources on a server system.

The latest version, VMSS 2.0, offers several features to create flexible ML pipelines. Instead of plugins, VMSS 2.0 has graph nodes that can have arbitrary types, back edges, and side packets. This allows for arbitrary (and even cyclical) graphs instead of just linear graphs. The graphical user interface of VMSS 2.0 helps users build, configure, and run ML pipelines easily. Customers can use Aupera's node toolkit or create their nodes with the aid of Aupera's node creation framework.

VMSS 2.0 allows packets to be synchronized across multiple streams, enabling stream-aware processing. Users can try any of the models on Xilinx Model Zoo (currently box detector and classifier models) with just a few mouse clicks. Additionally, VMSS 2.0 provides hardware abstraction to run ML pipelines on different platforms, allowing for quick adoption of new hardware. A web-application serves as the visual GUI for the server.

**Leverage VMSS 2.0 to:**

* Utilize available nodes for rapid pipeline construction.
* Get notifications via SMS, Email, HTTP API, MongoDB, and more.
* Create custom logic to process data within the pipeline exactly as you need.
* Access over 100+ models from AMD's Model Zoo for a wide range of applications.

## Build Video Applications Without Coding 

With VMSS installed on your target device, you can immediately leverage the available nodes to construct complex pipelines without any coding required. As illustrated below, nodes are categorized into Input, Logic/Apps (for ML Inference), Post Processing, and Output. Depending on your input source, a specific set of nodes is required to forward the appropriate packets to your logic node(s). Similarly, your output preferences determine the combination of nodes needed.

The above image indicates how different node categories connect and combine. You can select one or more options from each category to form a pipeline. Here's the process:

1. Choose Input Nodes: Select nodes that match your input source (video stream, file, etc.)
2. Add Logic Nodes: Use logic nodes to transform or analyze data. You can use them independently or in sequence.
3. Add PostProcessing (Optional): If your final output of choice requires post processing, choose the proper post processor. (e.g., visualization, to_json)
4. Choose nodes to finalize your results (e.g., output video, SMS, Email)
   
**NOTE:**  As shown above in the optional boxes, you have flexibility in how you connect components. For example:

- Use only a box detector: Ideal for simple object detection.
- Add a box tracker: Track objects across frames for more robust analysis.
- Link a detector directly to a classifier or landmark predictor: For immediate classification or landmark identification on cropped detections(for example feeding a crop of detectoed person to landmark predictor to identify the pose/joints).
- Insert a box tracker between detector and classifier/predictor: Track objects before classifying or predicting landmarks.

## Integrate your code easily by automatic boiler-plate generator

You can integrate your custom C++ logic into VMSS2.0 easily via producing boiler-plates, build and install directly on the platform. [Here is more info on this topic.](docs/basic_node_creation/README.md)

## **Resources**

Here are some key resources to get started with our VMSS 2.0 release for K260 Kria SOM:

* **Sneak Peek:** Get a first look at VMSS 2.0 in action with [our introductory video](https://youtu.be/KbzXKMxWZOw?si=rOYsU1yYClq-Pokr).

* **Setup:** Follow [these instructions](setup/K260_Kria_SOM/README.md) to set up the VMSS 2.0 docker on your SOM and leverage both the command line and our cloud AVAC.

* **Tutorial:** Follow [these instructions](./tutorial/K260_Kria_SOM/) to run a simple pipeline and learn about VMSS2.0 by progressively building a more complex pipeline. 

* **Running Examples:**  Learn to run examples through the VMSS 2.0 command-line interface with [this document](usage/K260_Kria_SOM/README.md).

* **Node (Calculator) Guide:** Learn what our suite of prebuilt nodes offer and learn about their specifications [in this document](docs/nodes/README.md).

* **Data Packet Guide:** Explore what packets are available in VMSS2.0 for communication between nodes [here](https://auperatech.github.io/VMSS2.0/packet_documentation/annotated.html).

* **Custom Logic:** Build your own custom logic and integrate it with VMSS 2.0 using [these instructions](docs/basic_node_creation/README.md). Also, check out open-sourced such as how to create a an inference node for a Vitis AI model zoo mode like [kp_predictor](calculators/kp_predictor) or modify some of our nodes like [box_visualizer](calculators/box_visualizer) and [to_json](calculators/to_json).

* **Cloud-Based UI Demo:**  Explore the capabilities of our cloud-based user interface for running RTSP-based examples [here](https://vmss.auperatechnologies.com/).

## Reporting Bugs

In case that you try our solution and find any bugs, please create and issue [here](https://github.com/auperatech/VMSS2.0/issues/new)

## Other supported platforms for VMSS2.0

VMSS 2.0 has been tested on the following list of hardware:
* KV260/KR260 (AMD)
* VCK5000 (AMD)
* U50 (AMD)
* V70 (AMD)
* SBC EdgeAI Box X7 (Planet Spark)
* V205 (Aupera)

For more information on these platforms, please check [this landing page](other_platforms.md).

If you have access to one of devices mentioned above, you may find the appropiate setup guide under [setup](https://github.com/auperatech/VMSS2.0/tree/main/docs)

If you don't have a compatible hardware, you can access VMSS 2.0 by signing up for a demo account via our website [VMSS2.0 here](https://vmss.auperatechnologies.com/).
