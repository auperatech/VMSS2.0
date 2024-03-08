# Aupera VMSS2.0 Tutorial

Welcome to the Aupera VMSS2.0 Tutorial. This guide will walk you through setting up a face detection system that can run on RTSP streams, incorporating tracking and detection interval adjustments, changing input types, modifying output actions, and switching detection models.

## Table of Contents
- [Aupera VMSS2.0 Tutorial](#aupera-vmss20-tutorial)
  - [Table of Contents](#table-of-contents)
  - [Face Detection on RTSP Streams](#face-detection-on-rtsp-streams)
    - [Test RTSP Streams](#test-rtsp-streams)
  - [Adding a Tracker and Reducing Detection Interval](#adding-a-tracker-and-reducing-detection-interval)
  - [Changing Input from RTSP to USB](#changing-input-from-rtsp-to-usb)
  - [Modifying Output to Send SMS](#modifying-output-to-send-sms)
  - [Switching to Person Detection and Model Selection](#switching-to-person-detection-and-model-selection)
    - [Available Models](#available-models)
  - [Tips and Tricks](#tips-and-tricks)

## Face Detection on RTSP Streams

In this section, we will set up a face detector to run on RTSP streams and visualize the results.

### Test RTSP Streams

Here's a list of RTSP streams that you can use for testing:

| Stream Name | RTSP URL |
|-------------|----------|
| Cars Street View   | rtsp://vmss.auperatechnologies.com:554/car |
| Mall Surveilance View   | rtsp://vmss.auperatechnologies.com:554/crowd |
| Compiled Subset of Imagenet Samples   | rtsp://vmss.auperatechnologies.com:554/imagenet |

## Adding a Tracker and Reducing Detection Interval

Learn how to add a tracker to the face detection pipeline and reduce the detection interval for improved performance.

## Changing Input from RTSP to USB

This section describes how to change the input source from an RTSP stream to a USB camera.

## Modifying Output to Send SMS

Instructions on how to change the output of the detection system to send SMS alerts.

## Switching to Person Detection and Model Selection

Change the pipeline to detect persons instead of faces and explore different models for detection.

### Available Models

| Model Kernel Name    | Description                       | Total Classes | TYPE |
|---------------|-----------------------------------|---------------| --------- |
| Model A       | Suitable for general person detection | 20  | YOLOV3 |
| Model B       | Optimized for low-light conditions  | NN  | SSD   |
| Model C       | High accuracy for crowded scenes   | NN  | RefineDet  |

## Tips and Tricks

- How to read from a file
- Saving detection results to a file
- Links to example projects and additional resources

Remember to replace placeholders (like RTSP URLs and model names) with actual data and add more detailed instructions and code snippets as needed. 
