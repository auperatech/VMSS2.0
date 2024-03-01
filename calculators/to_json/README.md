
# ToJsonCalculator Documentation

This node is provided as an available node for you to use. But in order to shed light on the detailed implementation of it and allow the user to customize based on their need, the source code is shared.

## Overview

`ToJsonCalculator` is a component of the VMSS2.0 AI framework, responsible for converting various machine learning model outputs, including object detection, classification, and segmentation results, into a JSON format. This conversion facilitates the easy handling, storage, and further processing of the model's predictions.

## Initialization

The calculator is initialized with options provided in a protocol buffer format. These options specify the type of input (detection, classification, segmentation), the network used for inference, and optionally, a file containing labels for detected classes.

### Key Options

- `label_name_file`: Path to the file containing labels for detected classes.
- `input_type`: Specifies the type of input to convert into JSON (detection, classification, segmentation).
- `network`: Specifies the name of the network that produced the inference results.

## Features

- **Label Loading**: Capability to load labels from a specified file for annotation in the JSON output.
- **Flexible Input Handling**: Supports input packets for detections, classifications, and segmentations, converting them into a standardized JSON format.
- **Network Specification**: Allows specifying the network used to obtain the inference results, enriching the JSON output with this context.

## Usage

1. **Initialization**: Initialize the calculator with the required options specifying the input type, network, and optionally, the path to a label file.

2. **Input Packet Reception**: After initialization, the calculator receives a packet containing detections, classifications, or segmentations.

3. **Conversion to JSON**: The received packet is converted into a JSON format, incorporating labels if specified, and adding additional context such as the network name and timestamp offsets.

4. **Output**: The resulting JSON object is then passed downstream for further processing, storage, or analysis.

### Modifying the source code for your purpose

1. Here the proto file is given here as the file [to_json.proto](to_json.proto). Make your modifications to it
2. Copy the file to `/opt/aupera/protos/aup/avap/` and rebuild AVAP with 
    ```bash
    cd /opt/aupera/protos
    make clean
    make -j2
    make install
    ```
3. Modify the source code for [to_json.cc](to_json.cc) and [to_json.h](to_json.h) as necessary
4. run `make -j3 && make install` in the calculator folder.

