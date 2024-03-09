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

[Check example here](./k260_kria_som_pbtxt.md#face-detection-on-rtsp-streams)

## Adding a Tracker and Reducing Detection Interval

Learn how to add a tracker to the face detection pipeline and reduce the detection interval for improved performance.

[Check example here](./k260_kria_som_pbtxt.md#adding-a-tracker-and-reducing-detection-interval)

## Changing Input from RTSP to USB

This section describes how to change the input source from an RTSP stream to a USB camera.

[Check example here](./k260_kria_som_pbtxt.md#changing-input-from-rtsp-to-usb)

## Adding SMS Message Notification Alert

We can also add notification_message calculator to send personalized SMS notifications. This innovative functionality is designed to cater to the specific needs of customers by enabling alerts based on custom object detection criteria. When the system identifies predefined objects in certain quantities—meticulously set by the customers themselves—it triggers an automated process to dispatch tailored SMS messages directly to the customers. This real-time notification system not only keeps customers informed about critical events as they unfold but also adds a layer of interactive and proactive communication, significantly enhancing the overall user experience. Through this feature, the pipeline transcends traditional boundaries, transforming into a dynamic tool that empowers customers with immediate insights and actionable information delivered straight to their mobile devices.

What we need to do to enable this functionality is just adding the to_json calculator and notification_message calculator at the end.

```
node {
  name: "to_json"
  calculator: "to_json"
  input_stream: "tracks_stream"
  output_stream: "json_stream"
  node_options: {
    [type.googleapis.com/aup.avaf.ToJsonOptions]: {
      label_name_file: ""
      network: "FaceDetectDenseBox"
      input_type: PACKET_TYPE_DETECTIONS_OR_TRACKS
    }
  }
}

node {
  name: "sms_notification"
  calculator: "notification_message"
  input_stream: "json_stream"
  node_options: {
    [type.googleapis.com/aup.avaf.NotificationMessageOptions]: {
      message_type: SMS
      sender: "1xxxxxxxxxxx"
      receiver: ["1xxxxxxxxxxx"]
      notification_q_size: 2
      sender_username: "xxxxxxxxxxxxxxxxxxxxx"
      sender_password: "xxxxxxxxxxxxxxxxxxxxx"
      server_url: "https://api.twilio.com/2010-04-01/Accounts/ACf7ec64f832871ba7f8512d64bf566f68/Messages.json"
      trigger: {
        trigger_type: JQ
        trigger_consecutive_packet: 3
        jq_query_string: "'select(.average_throughput_value > 20)'"
        notification_title: "sms_notification_test"
        notification_body: "xxxxxxxxxxxxxxxxxx"
      }
    }
  }
}
```

**The to_json calculator is a calculator to convert meta data packets like DetectionPacket into JSON packets.**

[details parameter explanation about to_json]

**The notification_message calculator is a calculator designed to send customized notifications to users through emails or SMS messages.**

[details parameter explanation about notification_message]



Now I'm going to give an example that will send the SMS to users phone when at least 5 faces detected in a region of interest.

[Check example here](./k260_kria_som_pbtxt.md#modifying-output-to-send-sms)



## Switching to Person Detection and Model Selection

Change the pipeline to detect persons instead of faces and explore different models for detection.

### Available Models

| Model Kernel Name    | Description                       | Total Classes | TYPE |
|---------------|-----------------------------------|---------------| --------- |
| Model A       | Suitable for general person detection | 20  | YOLOV3 |
| Model B       | Optimized for low-light conditions  | NN  | SSD   |
| Model C       | High accuracy for crowded scenes   | NN  | RefineDet  |

[Check example here](./k260_kria_som_pbtxt.md#switching-to-person-detection-and-model-selection)

## Tips and Tricks

- How to read from a file
- Saving detection results to a file
- Links to example projects and additional resources

Remember to replace placeholders (like RTSP URLs and model names) with actual data and add more detailed instructions and code snippets as needed. 
