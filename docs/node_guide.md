video_source frame_saver

# Table of Contents <!-- omit from toc -->
- [Introduction](#introduction)
  - [Streams and Packets](#streams-and-packets)
  - [Special Packet Types](#special-packet-types)
  - [Packet Conversion](#packet-conversion)
  - [Graph IO](#graph-io)
- [Node Configuration](#node-configuration)
  - [apl\_crowd\_flow](#apl_crowd_flow)
  - [box\_classifier](#box_classifier)
  - [box\_detector](#box_detector)
  - [box\_segmentor](#box_segmentor)
  - [box\_tracker](#box_tracker)
  - [box\_visualizer](#box_visualizer)
  - [ff\_vfilter](#ff_vfilter)
  - [frame\_saver](#frame_saver)
  - [landmark\_predictor](#landmark_predictor)
  - [notification\_message](#notification_message)
  - [notification\_mongo](#notification_mongo)
  - [notification\_web](#notification_web)
  - [statistics\_reader](#statistics_reader)
  - [stream\_demux](#stream_demux)
  - [stream\_mux](#stream_mux)
  - [video\_source](#video_source)
  - [x86\_dec](#x86_dec)
  - [x86\_enc](#x86_enc)


# Introduction

## Streams and Packets

All nodes in VMSS have inputs and outputs which consist of streams that move packets of information from one node to the next. In a `*.pbtxt` file, these streams are specified by the node options `input_stream` or `output_stream` entries. Generally, a node will only accept a certain number of input and output streams of a particular packet type. It is up to the user building a `*.pbtxt` file to ensure that connected streams from one node to the next have compatible packet types, and that a node has been set up with the correct number of input and output streams. The remainder of this document details the available input and output streams for each node and the available packet types for each.

## Special Packet Types

### Side Packets: <!-- omit from toc -->

A side packet is a stream that is intended to pass a single, constant, value. When a stream is treated as a side packet, a node will take the first packet arriving from that stream and store it for later use, ensuring it remains constant. If a side packet stream is re-initialized, it will overwrite the previous stored packet with the new most recent packet from that stream.

## Packet Conversion

A stream must have packet type that is compatible with the input stream packet type for a node. For instance, a stream on which `ImagePacket` objects are being produced cannot be passed to a node input requiring `VideoPacket` objects. 

There are two exceptions to this rule:
- Nodes taking an input of `DetectionPacket` can also take `TrackPacket` objects, however nodes taking an input of `TrackPacket` may not take `DetectionPacket` objects
- Nodes taking an input of `PacketBase` objects can take any packet as input

## Graph IO

asdf `<TODO>`


# Node Configuration

## apl_crowd_flow

**Description:** Custom node to count people crossing a border line or region of interest.

**[Node Options](avap_doc.md#aplcrowdflowoptions)**

**Basic Node IO:** This node in its base configuration has 3 input streams. In this configuration, the first input stream takes `TrackPacket` objects, the second input stream takes `VideoStreamInfoPacket` objects which are treated as [side packets](#side-packets), and the third input stream takes `UInt64Packet` objects which contain the detect interval and which are treated as [side packets](#side-packets). This node can optionally have 4 input streams to provide a video stream, with the first input stream remaining the same, the *second input stream* taking `ImagePacket` objects, and the third and fourth streams taking `VideoStreamInfoPacket` and `UInt64Packet` objects respectively, similarly to the 3-input configuration.

This node in its base configuration has 1 output stream, which produces `JsonPacket` objects. It optionally has two additional output streams so that the total number of output streams can also be 2 or 3. The second *optional* output stream produces `ImagePacket` objects, and the third *optional* output stream produces `JsonPacket` objects containing the same content as the first stream.


## box_classifier

**Description:** Performs object classification on an image cropped by a bounding box.

**[Node Options](avap_doc.md#boxclassifieroptions)**

**Basic Node IO:** This node in its base form takes in an input video stream of type `ImagePacket` and produces an output stream of type `Classifications`. It is able to take in multiple input streams at a time and produces corresponding classification streams for each, for example 3 input streams of type `ImagePacket` and 3 output streams of type `Classifications`. The output streams order will correspond to the input streams order.

**IO With Detections** If `node_options->use_detections` is not zero, the node can use detections to help with classification. In this case, the node has two input streams for every output stream. For example, with 2 inputs and 1 output, the first input takes `DetectionPacket` objects and the second input takes `ImagePacket` objects, and there would be one output stream producing `Classifications` objects. We can also have multiple input video streams and corresponding output streams. For instance, in the case of two video streams, with 4 total input streams, the first two input streams would be `DetectionPacket` streams, and the second two input streams would be `ImagePacket` streams, and there would be two `Classifications` output streams. The first `DetectionPacket` input stream would correspond to the first `ImagePacket` input stream and the first `Classifications` output stream, and so on.

NOTE: If `node_options->use_detections` is zero, the number of input streams and output streams must be equal

NOTE: If `node_options->use_detections` is non-zero, the number of input streams must be twice the number of output streams


## box_detector

**Description:** Uses a ML model to find objects in an image, producing bounding boxes for each.

**[Node Options](avap_doc.md#boxdetectoroptions)**

**Basic Node IO:** In its base configuration, this node has one input stream and two output streams. The input stream takes `ImagePacket` objects. The first output stream produces `DetectionPacket` objects, and the second output stream produces `UInt64Packet` which are intended to be treated as [side packets](#side-packets) containing the detection interval. This node can be scaled to receive multiple input video streams, in which case the number of output streams should be one more than the number of input streams. For instance, with 3 input video streams, there would be 3 input streams taking `ImagePacket` objects, and 4 output streams, with the first 3 output streams producing `DetectionPacket` objects, and the 4th output stream producing `UInt64Packet` objects containing the detection interval. The first `ImagePacket` input stream would correspond to the first `DetectionPacket` output stream, and so on.

NOTE: The number of output streams must be one more than the number of input streams to account for the extra `UInt64Packet` output stream


## box_segmentor

**Description:** Performs box segmentation on an image stream.

**[Node Options](avap_doc.md#boxsegmentoroptions)**

**Basic Node IO:** This node in its base form takes in an input video stream of type `ImagePacket` and produces a corresponding segmentation stream of type `Segmentations`. It is able to take in multiple input streams at a time and produces corresponding segmentation streams for each, for example 3 input streams of type `ImagePacket` and 3 output streams of type `Segmentations`. The output streams order will correspond to the input streams order.

NOTE: The Number of input streams must match the number of output streams


## box_tracker

**Description:** Identifies object for tracking through a video stream.

**[Node Options](avap_doc.md#boxtrackeroptions)**

**Basic Node IO:** This node has two input streams, the first stream takes in `DetectionPacket` objects, and the second stream takes in `UInt64Packet` objects which specify the detection interval of the detection node. This node has one output stream which produces `TrackPacket` objects.


## box_visualizer

**Description:** Renders boxes within images provided through the image stream and returns the updated images. Receives a packet containing detected bounding box information, which may be one of `DetectionPacket`, `Classifications`, `PlateRecognitions`, `Segmentations`, `LandmarksPacket`. 

**[Node Options](avap_doc.md#boxvisualizeroptions)**

**Basic Node IO:** This node has two input streams, the first stream takes in a packet object containing bounding boxes (see Available Packet Types) and the second stream takes in `ImagePacket` objects. This node only has one output stream, which produces `ImagePacket` objects.

**Available Packet Types:** the packet type of the first input stream 0 must be one of the following and must match the corresponding value set in `node_options->input_type`:
  - INPUT_TYPE_DETECTION (0): DetectionPacket
  - INPUT_TYPE_CLASSIFICATION (1): Classifications
  - INPUT_TYPE_SEGMENTATION (2): Segmentations
  - INPUT_TYPE_LANDMARK (3): LandmarksPacket


## ff_vfilter

**Description:** Applies video filters to a video stream and outputs the result.

**[Node Options](avap_doc.md#videofilteroptions)**

**Basic Node IO:** This node has two input streams, the first input takes `ImagePacket` objects, and the second input takes in `VideoStreamInfoPacket` objects, which are treated as [side packets](#side-packets). This node has two output streams, the first input produces `ImagePacket` objects, and the second produces `VideoStreamInfoPacket` objects.


## frame_saver

**Description:** Saves frames from a video stream to a directory.

**[Node Options](avap_doc.md#framesaveroptions)**

**Basic Node IO:** This node has one input stream, which takes `ImagePacket` objects. This node has no output streams, rather the files are saved to the path specified in `node_options->directory`.


## landmark_predictor

**Description:** Calls a ML model to find landmarks within an image

**[Node Options](avap_doc.md#landmarkpredictoroptions)**

**Basic Node IO:** This node in its base form takes in an input video stream of type `ImagePacket` and produces an output stream of type `LandmarksPacket`. It is able to take in multiple input streams at a time and produces corresponding landmark streams for each, for example 3 input streams of type `ImagePacket` and 3 output streams of type `LandmarksPacket`. The output streams order will correspond to the input streams order.

**IO With Detections** If `node_options->use_detections` is not zero, the node can use detections to help with landmark predictions. In this case, the node has two input streams for every output stream. For example, with 2 inputs and 1 output, the first input takes `DetectionPacket` objects and the second input takes `ImagePacket` objects, and there would be one output stream producing `LandmarksPacket` objects. We can also have multiple input video streams and corresponding output streams. For instance, in the case of two video streams, with 4 total input streams, the first two input streams would be `DetectionPacket` streams, and the second two input streams would be `ImagePacket` streams, and there would be two `LandmarksPacket` output streams. The first `DetectionPacket` input stream would correspond to the first `ImagePacket` input stream and the first `LandmarksPacket` output stream, and so on.

NOTE: If `node_options->use_detections` is zero, the number of input streams and output streams must be equal

NOTE: If `node_options->use_detections` is non-zero, the number of input streams must be twice the number of output streams


## notification_message

**Description:** Sends a notification via SMS or email.

**Node Options** `<TODO>`

**Basic Node IO:** This node has one input stream, which takes `JsonPacket` objects. This node does not have any output streams.


## notification_mongo

**Description:** Sends a notification via MongoDB

**[Node Options](avap_doc.md#notificationmongooptions)**

**Basic Node IO:** This node has one input stream, which takes `JsonPacket` objects. This node does not have any output streams.


## notification_web

**Description:** Sends a notification via the web

**[Node Options](avap_doc.md#notificationweboptions)**

**Basic Node IO:** This node has one input stream, which takes `JsonPacket` objects. This node does not have any output streams.


## statistics_reader

**Description:** Loads statistics in the form of json files in a directory.

**[Node Options](avap_doc.md#statisticsreaderoptions)**

**Basic Node IO:** This node has no input streams, rather the statistics are loaded from the path specified in `node_options->input_path`. This node has one output stream, which produces `JsonPacket` objects.



## stream_demux

**Description:** Demultiplexes a video stream.

**[Node Options](avap_doc.md#streammuxoptions)**

**Basic Node IO:** This node has no input streams, rather the input is set either by providing a url through `node_options->demux->input_url` or by providing a `graph_input` field at the top of the `*.pbtxt` file (see [Graph IO](#graph-io)). This node can have 1 or 2 output streams: the first input stream produces `VideoPacket` objects, while the second *optional* stream produces `VideoStreamInfoPacket` objects.


## stream_mux 

**Description:** Multiplexes a video stream.

**[Node Options](avap_doc.md#streammuxoptions)**

**Basic Node IO:** This node has two input streams, the first takes `VideoPacket` objects, and the second takes `AVCodecContextPacket` objects, which are treated as [side packets](#side-packets). This node has no output streams, rather the output is set either by providing a url through `node_options->demux->output_url` or by providing a `graph_input` field at the top of the `*.pbtxt` file (see [Graph IO](#graph-io)).


## video_source

**Description:** Loads video from a camera device, such as USB.

**Node Options** `<TODO>`

**Basic Node IO:** This node has no input streams, rather the camera device is specified by `node_options->path`. This node has two output streams, the first output stream produces `ImagePacket` objects, the second output stream produces `VideoStreamInfoPacket` objects.


## x86_dec 

**Description:** Decodes a video stream.

**[Node Options](avap_doc.md#videocodecoptions)**

**Basic Node IO:** This node has two input streams, the first input takes `VideoPacket` objects, the second input takes `VideoStreamInfoPacket` objects. In its base configuration, this node has two output streams, the first output produces `ImagePacket` objects and the second output produces `VideoStreamInfoPacket` objects. However, it is able to produce multiple video output streams at a time using different pixel formats. For example, with 3 pixel formats, there would be 3 output streams of type `ImagePacket` followed by 3 output streams of type `VideoStreamInfoPacket`. The first `ImagePacket` output stream would correspond to the first `VideoStreamInfoPacket` output stream, and so on. These order of these streams  corresponds to the order of entries in `node_options->dec->opixfmt` which lists the requested video formats.

NOTE: There may be multiple entries in `node_options->dec->opixfmt` to support multiple output picture streams with different pixel format. In this case, the number of output streams for this node should match the number of entries in `opixfmt`.


## x86_enc

**Description:** Encodes a video stream.

**[Node Options](avap_doc.md#videocodecoptions)**

**Basic Node IO:** This node can have 1 or 2 input streams depending on the entries of `node_options->enc` (see conditions). The first input stream produces `ImagePacket` objects, while the second *optional* stream produces `VideoStreamInfoPacket` objects, which are treated as [side packets](#side-packets). This node has two output streams, the first produces `VideoPacket` objects and the second produces `AVCodecContextPacket` packets.

**Conditions:** 
 - If the w, h, and fps subfields of `node_options->enc` are set to non-zero, then the node has one input stream
 - If the w, h, and fps subfields of `node_options->enc` are all set to zero, then the node has two input streams

