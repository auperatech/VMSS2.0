# BoxVisualizerCalculator 

This node is provided as an available node for you to use. But in order to shed light on the detailed implementation of it and allow the user to customize based on their need, the source code is shared.

## Overview

`BoxVisualizerCalculator` is a component of the VMSS2.0 AI framework, responsible for visualizing the results of various machine learning models, including object detection, classification, segmentation, and landmark detection, directly on images. This visualization aids in interpreting the model's predictions by overlaying bounding boxes, segmentation masks, and landmark points on the input images.

## Initialization

The calculator is initialized with a set of options provided in a protocol buffer format. These options specify the type of input (detection, classification, segmentation, landmark), visual properties of the bounding boxes and text (such as color, thickness, font size), and other visualization parameters.

### Key Options

- `label_name_file`: Path to the file containing labels for detected classes.
- `input_type`: Specifies the type of input to visualize (detection, classification, segmentation, landmark).
- `box_color`, `text_color`: Colors for the bounding boxes and text labels.
- `box_thickness`, `text_size`, `font`: Visual properties for bounding boxes and text labels.
- `class_color`: Allows specifying different colors for different classes.
- `default_class_color`: Default color for classes not specifically mentioned in `class_color`.

## Features

- **Label Loading**: Ability to load labels from a specified file for annotation.
- **Bounding Box Visualization**: Draws bounding boxes around detected objects with class labels.
- **Segmentation Mask Overlay**: Applies segmentation masks on the image with adjustable opacity.
- **Landmark Visualization**: Marks detected landmarks on the image.
- **Custom Class Colors**: Supports custom colors for different classes.

## Usage

1. **Initialization**: The calculator must be initialized with the required options specifying how the visualization should be performed.

2. **Input Packet Reception**: After initialization, the calculator receives a packet containing either detections, classifications, segmentations, or landmarks along with the corresponding image.

3. **Visualization**: Based on the received packet, it overlays the relevant information (e.g., bounding boxes, segmentation masks, landmarks) on the image.

4. **Output**: The modified image, with the visualizations applied, is then passed downstream for further processing or output.

### Modifying the source code for your purpose

1. Here the proto file is given here as the file [box_visualizer.proto](box_visualizer.proto). Make your modifications to it
2. Copy the file to `/opt/aupera/protos/aup/avap/` and rebuild AVAP with 
    ```bash
    cd /opt/aupera/protos
    make clean
    make -j2
    make install
    ```
3. Modify the source code for [box_visualizer.cc](box_visualizer.cc) and [box_visualizer.h](box_visualizer.h) as necessary
4. run `make -j3 && make install` in the calculator folder.

