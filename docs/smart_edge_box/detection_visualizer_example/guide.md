This guide aims to provide an easy to follow example of creating custom nodes in VMSS 2.0

# Overview

Each node has the following components:
1. Node source code in C++
2. Options defined in proto

Also, it is important to know the following concepts:
1. Aupera's Video AI Parser (AVAP) for creating options
1. Aupera's Video AI Framework (AVAF) concepts that the source C++ code should follow
1. packets that are required for data communication between nodes

This guide will go through steps of creating a node that takes a JSON packet (`class JsonPacket`) that represents detections on a frame and visualizes them on image packet (`class ImagePacket`) and outputs said image packet. This procedure consists of the following steps:
1. Create custom options and update avap
2. Create node source code, build and install

This guide assumes that you are inside Aupera's VMSS docker for Smart-Edge-Box

# Creating Custom Options
Options are stored as protocol buffers format version 3. The avap build system is stored in the path `/opt/aupera/avaf/sdk_avaf_extra/protos/`. For this step lets create a new file and fill it up. [Open detection_visualizer.proto](detection_visualizer.proto) to see the file. The file should be in the directory `aup/avap` in the avap build system.

In order to build and install just go the directory of the avap build system and run the following:
```bash
cd /opt/aupera/avaf/sdk_avaf_extra/protos/
make clean
make -j4
make install
```

Now, avap includes the options required for the node. Note that for nodes that run inside the subgraph (running on device side) you need to take some extra steps. For that please [refer to this guide called basic_node_creation](../basic_node_creation/README.md).

# Creating the Code for Node
VMSS docker for Smart-Edge-Box has a utility to create a boilerplate for node source code. Run the following to generate the boilerplate to create [the boilerplate code](detection_visualizer_boilerplate.cc).
```bash
init_vmss_node.sh --vendor aupera --name-snake detection_visualizer --name-camel DetectionVisualizer --options-type DetectionVisualizerOptions --options-header detection_visualizer.pb.h
```
This will give this output:
```bash
Generating VERSION.mk...
Generating Makefile...
Generating detection_visualizer boiler plate ...
```
The following files will be generated considering ():
```bash
-rw-rw-rw- 1 nobody root  114 Dec 11 19:36 Makefile
-rw-rw-rw- 1 nobody root   90 Dec 11 19:36 VERSION.mk
-rw-rw-rw- 1 nobody root 1.3K Dec 11 19:37 detection_visualizer.cc
```

At this point you need to implement the functions defined in the boilerplate. [See the implemented code here](detection_visualizer.cc):
1. `fill_contract` sets the input and output packet types of the node. Input 0 is of type JSON packet, input 1 is of type ImagePacket. Output of 0 is of type image packet.
2. `initialize` needs to initialize the node. For this case, there are no initialization so just modify the return value.
3. `execute` runs on every frame or every time there are inputs available for the node