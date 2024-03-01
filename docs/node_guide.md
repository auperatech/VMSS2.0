# Guide on VMSS Nodes

- [Introduction](#introduction)
  - [Nodes](#nodes)
  - [Config `.pbtxt` Files](#config-pbtxt-files)
  - [Node Options](#node-options)
  - [Graph IO](#graph-io)
  - [Streams and Packets](#streams-and-packets)
  - [Side Packets](#side-packets)
  - [Packet Conversion](#packet-conversion)
- [Node Table](#node-table)
- [Packet Table](#packet-table)

<a name="node_table_top"></a>

# Node Table

| Node Name | Description |
| ----- | ---- |
| [apl\_crowd\_flow](#apl_crowd_flow) | Custom node to count detected objects crossing a border line or region of interest |
| [box\_classifier](#box_classifier) | Performs object classification either on an entire image or a cropped image region if cascaded with a box_detector |
| [box\_detector](#box_detector) | Uses a ML model to find objects in an image, producing bounding boxes for each along with their predicted class |
| [box\_segmentor](#box_segmentor) | Performs semantic segmentation on an image stream classifying each pixel of the input image |
| [box\_tracker](#box_tracker) | Tracks detected objects coming from a detector, assigning a unique ID to each |
| [box\_visualizer](#box_visualizer) | Renders boxes and classification results within images provided through the image stream and returns the updated images |
| [ff\_vfilter](#ff_vfilter) | Applies color space conversion, sets frame rate, and sets resolution of a video stream |
| [frame\_saver](#frame_saver) | Saves frames from a video stream to a directory |
| [landmark\_predictor](#landmark_predictor) | Calls a ML model to find supported face or body/pose landmarks within an image |
| [notification\_message](#notification_message) | Sends a notification via SMS or email |
| [notification\_mongo](#notification_mongo) | Sends customized notifications to a user-specified MongoDB server |
| [notification\_web](#notification_web) | Sends a notification via the web |
| [statistics\_reader](#statistics_reader) | Loads statistics in the form of json files in a directory |
| [stream\_demux](#stream_demux) | Demultiplexes an incoming video stream |
| [stream\_mux](#stream_mux) | Multiplexes an outgoing video stream |
| [to\_json](#to_json) | Converts packets of various types to json format |
| [video\_source](#video_source) | Loads video from a camera device, such as USB |
| [x86\_dec](#x86_dec) | Decodes an incoming video stream using CPU |
| [x86\_enc](#x86_enc) | Encodes an outgoing video stream using CPU |

# Packet Table

| Packet Type | Produced by | Consumed by |
| ----- | ---- | ---- |
| <a name="AVCodecContextPacket" /> AVCodecContextPacket | [x86\_enc](#x86_enc) | [stream\_mux](#stream_mux) |
| <a name="Classifications" /> Classifications | [box\_classifier](#box_classifier) | [box\_visualizer](#box_visualizer), [to\_json](#to_json) |
| <a name="DetectionPacket" /> DetectionPacket | [box\_detector](#box_detector) | [box\_classifier](#box_classifier), [box\_tracker](#box_tracker), [box\_visualizer](#box_visualizer), [landmark\_predictor](#landmark_predictor), [to\_json](#to_json) |
| <a name="ImagePacket" /> ImagePacket | [apl\_crowd\_flow](#apl_crowd_flow), [box\_visualizer](#box_visualizer), [ff\_vfilter](#ff_vfilter), [video\_source](#video_source), [x86\_dec](#x86_dec) | [box\_classifier](#box_classifier), [box\_detector](#box_detector), [box\_segmentor](#box_segmentor), [box\_visualizer](#box_visualizer), [ff\_vfilter](#ff_vfilter), [frame\_saver](#frame_saver), [landmark\_predictor](#landmark_predictor), [x86\_enc](#x86_enc) |
| <a name="JsonPacket" /> JsonPacket | [apl\_crowd\_flow](#apl_crowd_flow), [statistics\_reader](#statistics_reader) | [notification\_message](#notification_message), [notification\_mongo](#notification_mongo), [notification\_web](#notification_web), [to\_json](#to_json) |
| <a name="LandmarksPacket" /> LandmarksPacket | [landmark\_predictor](#landmark_predictor) | [box\_visualizer](#box_visualizer) |
| <a name="Segmentations" /> Segmentations | [box\_segmentor](#box_segmentor) | [box\_visualizer](#box_visualizer), [to\_json](#to_json) |
| <a name="TrackPacket" /> TrackPacket | [box\_tracker](#box_tracker) | [apl\_crowd\_flow](#apl_crowd_flow), (through implicit conversion to DetectionPacket: [box\_classifier](#box_classifier), [box\_tracker](#box_tracker), [box\_visualizer](#box_visualizer), [landmark\_predictor](#landmark_predictor), [to\_json](#to_json)) |
| <a name="UInt64Packet" /> UInt64Packet | [box\_detector](#box_detector) | [apl\_crowd\_flow](#apl_crowd_flow), [box\_tracker](#box_tracker) |
| <a name="VideoPacket" /> VideoPacket | [stream\_demux](#stream_demux), [x86\_enc](#x86_enc) | [stream\_mux](#stream_mux), [x86\_dec](#x86_dec) |
| <a name="VideoStreamInfoPacket" /> VideoStreamInfoPacket | [ff\_vfilter](#ff_vfilter), [stream\_demux](#stream_demux), [video\_source](#video_source), [x86\_dec](#x86_dec) | [apl\_crowd\_flow](#apl_crowd_flow), [ff\_vfilter](#ff_vfilter), [x86\_dec](#x86_dec), [x86\_enc](#x86_enc) |

# Introduction

## Nodes

Nodes are the building blocks of a video pipeline in VMSS. Each node has a unique functionality that it performs on one or more streams of data, usually producing another stream of processed data as a result. Nodes are modular and may be hooked up to one another by connecting their input and output streams to form a graph. VMSS is the engine that turns this graph into a set of steps that are followed on an inference device to process video in real time.

## Config `.pbtxt` Files

`.pbtxt` files are configuration files in which a graph is specified by declaring inputs, outputs, nodes, connecting streams between nodes, and options for the nodes. This file is then parsed by our server `avas` or the command-line runnable version `avaser` to build the graph into a fully-functional video-processing pipeline on the runtime device. 

## Node Options

Each node is configurable with a set of options which allow customization of their function, such as the number of input and output streams they will support, the types of information packets that can be passed to each input or output stream, and other unique options. These options are specified in the `.pbtxt` file for a node under the `node_options` entry for that node (see example `.pbtxt` for the node). In this document, each node has a link to the documentation concerning the options available for that node. Refer to this for a list of required options which must be set for the node to function.

## Graph IO

Every graph has a set of input and output streams that take raw video and pass it to the internal streams of the connected nodes. There are two ways to pass the input and output streams of a graph:
 - Provide a url for a video stream to the `node_options->demux->input_url` option of a [stream_demux](#stream_demux) node and provide a url for the output video stream to the `node_options->mux->input_url` option of a [stream_mux](#stream_mux) node
 - Provide entries at the top of the `.pbtxt` file specifying a `graph_input: "<input stream name>"` entry and a `graph_output: "<input stream name>"` entry (see example below). This will require making associated input `.pbtxt` and output `.pbtxt` files and then passing them to `avaser`, and as such is only recommended if running from the command line.

*NOTE:* If using the web client, only the first option (i.e. setting `node_options->demux->input_url`) will be available

**Running with graph inputs/outputs**

Configuring a `.pbtxt` to take graph inputs and outputs, which can be run with:

`avaser -c <path to config.pbtxt file> -i <path to input.pbtxt file> -o <path to output.pbtxt file>`
```
# Start of config.pbtxt file

control_port: 51881
graph_input: "graph_input1"
graph_output: "graph_output1"

node {
  name: "demux_node"
  calculator: "stream_demux"
  vendor: "Aupera"
  graph_input: "graph_input1"
  output_stream: "packet_stream_demux"
  output_stream: "video_stream_info_demux"
  node_options: {
    [type.googleapis.com/aup.avaf.StreamMuxOptions]: {
      demux: {
        rtsp_transport: "tcp"
        iframe_extract: false
        auto_reconnect: true
      }
    }
  }
}

...

node {
  name: "mux_node"
  calculator: "stream_mux"
  vendor: "Aupera"
  input_stream: "packet_stream_encode"
  input_stream: "codec_context_stream"
  graph_output: "graph_output1"
  node_options: {
    [type.googleapis.com/aup.avaf.StreamMuxOptions]: {
     mux: {
       rtsp_transport: "tcp"
       auto_reconnect: true
     }
    }
  }
}
```
```
# Start of input.pbtxt file

# To take in a file as input we do:
input_urls:"/tmp/aup_cicd_u7GVwvp7/retail.mp4"

# or if we wanted a url, we could do:
# input_urls:"rtsp://avac.auperatechnologies.com:554/crowd"
```
```
# Start of output.pbtxt file

# To produce a file as output we do:
output_urls:"/tmp/aup_cicd_u7GVwvp7/vid-out-1.mp4"

# or if we wanted an output url, we could do:
# output_urls:"rtsp://avac.auperatechnologies.com:554/crowd_out"
```

## Streams and Packets

All nodes in VMSS have inputs and outputs which consist of streams that move packets of information from one node to the next. In a `*.pbtxt` file, these streams are specified by the node options `input_stream` or `output_stream` entries. Generally, a node will only accept a certain number of input and output streams of a particular packet type. It is up to the user building a `*.pbtxt` file to ensure that connected streams from one node to the next have compatible packet types, and that a node has been set up with the correct number of input and output streams. The remainder of this document details the available input and output streams for each node and the available packet types for each.

## Side Packets

A side packet is a stream that is intended to pass a single, constant, value. When a stream is treated as a side packet, a node will take the first packet arriving from that stream and store it for later use, ensuring it remains constant. If a side packet stream is re-initialized, it will overwrite the previous stored packet with the new most recent packet from that stream.

## Packet Conversion

A stream must have packet type that is compatible with the input stream packet type for a node. For instance, a stream on which <a href="#ImagePacket">`ImagePacket`</a> objects are being produced cannot be passed to a node input requiring <a href="#VideoPacket">`VideoPacket`</a> objects. 

There are two exceptions to this rule:
- Nodes taking an input of <a href="#DetectionPacket">`DetectionPacket`</a> can also take <a href="#TrackPacket">`TrackPacket`</a> objects, however nodes taking an input of <a href="#TrackPacket">`TrackPacket`</a> may not take <a href="#DetectionPacket">`DetectionPacket`</a> objects


# Node Configuration

<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## apl_crowd_flow

**Description:** Custom node to count detected objects crossing a border line or region of interest.

**Node Options:** [AplCrowdFlowOptions](avap_doc.md#aplcrowdflowoptions)

**Example `.pbtxt`:** [apl_crowd_flow](avap_doc.md#aupavapapl_crowd_flowproto)

**Basic Node IO:** 

This node in its base configuration has 3 input streams:
- The first input stream takes <a href="#TrackPacket">`TrackPacket`</a> objects
- The second input stream takes <a href="#VideoStreamInfoPacket">`VideoStreamInfoPacket`</a> objects which are treated as [side packets](#side-packets)
- The third input stream takes <a href="#UInt64Packet">`UInt64Packet`</a> objects which contain the detect interval and which are treated as [side packets](#side-packets). 

This node in its base configuration has 1 output stream. It optionally has two additional output streams so that the total number of output streams can also be 2 or 3:
- The first output stream produces <a href="#JsonPacket">`JsonPacket`</a> objects
- The second *optional* output stream produces <a href="#ImagePacket">`ImagePacket`</a> objects
- The third *optional* output stream produces <a href="#JsonPacket">`JsonPacket`</a> objects containing the same content as the first stream

**Node IO with Video Stream:**

This node can optionally have 4 input streams to provide a video stream:
- The first input stream takes <a href="#TrackPacket">`TrackPacket`</a> objects
- The *second input stream* takes <a href="#ImagePacket">`ImagePacket`</a> objects
- The third input stream takes <a href="#VideoStreamInfoPacket">`VideoStreamInfoPacket`</a> objects which are treated as [side packets](#side-packets)
- The fourth input stream takes <a href="#UInt64Packet">`UInt64Packet`</a> objects which contain the detect interval and which are treated as [side packets](#side-packets).

*NOTE:* The output streams remain the same as in the basic IO configuration.


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## box_classifier

**Description:** Performs object classification either on an entire image or a cropped image region if cascaded with a box_detector

**Node Options:** [BoxClassifierOptions](avap_doc.md#boxclassifieroptions)

**Example `.pbtxt`:** [box_classifier](avap_doc.md#aupavapbox_classifierproto)

**Basic Node IO:** 

This node in its base form has one input stream and one output stream:
- The input stream takes in <a href="#ImagePacket">`ImagePacket`</a> objects
- The output stream produces <a href="#Classifications">`Classifications`</a> objects

This node can be scaled to receive multiple input video streams, e.g. for 2 video streams:
- The first input stream takes in <a href="#ImagePacket">`ImagePacket`</a> objects
- The second input stream takes in <a href="#ImagePacket">`ImagePacket`</a> objects
- The first output stream produces <a href="#Classifications">`Classifications`</a> objects associated with the first input stream
- The second output stream produces <a href="#Classifications">`Classifications`</a> objects associated with the second input stream

*NOTE:* This case is only if `node_options->use_detections` is not zero

**IO With Detections**

If `node_options->use_detections` is not zero, the node can use detections to help with classification. In this case, the node has two input streams for every output stream. For example, with 2 inputs and 1 output:
- The first input stream takes <a href="#DetectionPacket">`DetectionPacket`</a> objects 
- The second input takes <a href="#ImagePacket">`ImagePacket`</a> objects
- The output stream produces <a href="#Classifications">`Classifications`</a> objects

We can also have multiple input video streams and corresponding output streams. For instance, in the case of two video streams, with 4 total input streams:
- The first input stream takes <a href="#DetectionPacket">`DetectionPacket`</a> objects
- The second input stream takes <a href="#DetectionPacket">`DetectionPacket`</a> objects
- The third input takes <a href="#ImagePacket">`ImagePacket`</a> objects associated with the first input stream
- The fourth input takes <a href="#ImagePacket">`ImagePacket`</a> objects associated with the second input stream
- The first output stream produces <a href="#Classifications">`Classifications`</a> objects associated with the first input stream
- The second output stream produces <a href="#Classifications">`Classifications`</a> objects associated with the second input stream

*NOTE:* In this case, the number of input streams must be twice the number of output streams


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## box_detector

**Description:** Uses a ML model to find objects in an image, producing bounding boxes for each along with their predicted class.

**Node Options** [BoxDetectorOptions](avap_doc.md#boxdetectoroptions)

**Example `.pbtxt`:** [box_detector](avap_doc.md#aupavapbox_detectorproto)

**Basic Node IO:** 

In its base configuration, this node has one input stream and two output streams:
- The input stream takes <a href="#ImagePacket">`ImagePacket`</a> objects
- The first output stream produces <a href="#DetectionPacket">`DetectionPacket`</a> objects
- The second output stream produces <a href="#UInt64Packet">`UInt64Packet`</a> which are intended to be treated as [side packets](#side-packets) containing the detection interval

This node can be scaled to receive multiple input video streams, in which case the number of output streams should be one more than the number of input streams. For instance, with 2 input video streams, there would be 2 input streams and 3 output streams:
- The first input stream takes <a href="#ImagePacket">`ImagePacket`</a> objects
- The second input stream takes <a href="#ImagePacket">`ImagePacket`</a> objects
- The first output stream produces <a href="#DetectionPacket">`DetectionPacket`</a> objects associated with the first input stream
- The second output stream produces <a href="#DetectionPacket">`DetectionPacket`</a> objects associated with the second input stream
- The third output stream produces <a href="#UInt64Packet">`UInt64Packet`</a> which are intended to be treated as [side packets](#side-packets) containing the detection interval

*NOTE:* For multiple input video streams, the number of output streams must be one more than the number of input streams to account for the extra <a href="#UInt64Packet">`UInt64Packet`</a> output stream


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## box_segmentor

**Description:** Performs semantic segmentation on an image stream classifying each pixel of the input image.

**Node Options:** [BoxSegmentorOptions](avap_doc.md#boxsegmentoroptions)

**Example `.pbtxt`:** [box_segmentor](avap_doc.md#aupavapbox_segmentorproto)

**Basic Node IO:** 

In its base configuration, this node has one input stream and one output stream:
- The input stream takes <a href="#ImagePacket">`ImagePacket`</a> objects
- The output stream produces <a href="#Segmentations">`Segmentations`</a> objects

This node can be scaled to receive multiple input streams at a time and produces corresponding segmentation streams for each, for example with 2 input streams there would be 2 output streams:
- The first input stream takes <a href="#ImagePacket">`ImagePacket`</a> objects
- The second input stream takes <a href="#ImagePacket">`ImagePacket`</a> objects
- The first output stream produces <a href="#Segmentations">`Segmentations`</a> objects associated with the first input stream
- The second output stream produces <a href="#Segmentations">`Segmentations`</a> objects associated with the second input stream

*NOTE:* The Number of input streams must match the number of output streams


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## box_tracker

**Description:** Tracks detected objects coming from a detector, assigning a unique ID to each.

**Node Options:** [BoxTrackerOptions](avap_doc.md#boxtrackeroptions)

**Example `.pbtxt`:** [box_tracker](avap_doc.md#aupavapbox_trackerproto)

**Basic Node IO:** 
This node has two input streams and one output stream:
- The first input stream takes in <a href="#DetectionPacket">`DetectionPacket`</a> objects
- The second input stream takes in <a href="#UInt64Packet">`UInt64Packet`</a> objects that specify the detection interval of the detection node, which are treated as [side packets](#side-packets)
- The output stream produces <a href="#TrackPacket">`TrackPacket`</a> objects


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## box_visualizer

**Description:** Renders boxes and classification results within images provided through the image stream and returns the updated images. Receives a packet containing detected bounding box information, which may be one of <a href="#DetectionPacket">`DetectionPacket`</a>, <a href="#Classifications">`Classifications`</a>, <a href="#Segmentations">`Segmentations`</a>, <a href="#LandmarksPacket">`LandmarksPacket`</a>. 

**Node Options:** [BoxVisualizerOptions](avap_doc.md#boxvisualizeroptions)

**Example `.pbtxt`:** [box_visualizer](avap_doc.md#aupavapbox_visualizerproto)

**Basic Node IO:** 

This node has two input streams and one output stream:
- The first input stream takes in a packet object containing bounding boxes (see Available Packet Types) 
- The second input stream takes in <a href="#ImagePacket">`ImagePacket`</a> objects
- The output stream produces <a href="#ImagePacket">`ImagePacket`</a> objects

**Available Packet Types:** the packet type of the first input stream 0 must be one of the following and must match the corresponding value set in `node_options->input_type`:
  - INPUT_TYPE_DETECTION (0): DetectionPacket
  - INPUT_TYPE_CLASSIFICATION (1): Classifications
  - INPUT_TYPE_SEGMENTATION (2): Segmentations
  - INPUT_TYPE_LANDMARK (3): LandmarksPacket


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## ff_vfilter

**Description:** Applies color space conversion, sets frame rate, and sets resolution of a video stream.

**Node Options:** [VideoFilterOptions](avap_doc.md#videofilteroptions)

**Example `.pbtxt`:** [ff_vfilter](avap_doc.md#aupavapvfilterproto)

**Basic Node IO:** 

This node has two input streams and two output streams:
- The first input stream takes <a href="#ImagePacket">`ImagePacket`</a> objects
- The second input stream takes in <a href="#VideoStreamInfoPacket">`VideoStreamInfoPacket`</a> objects, which are treated as [side packets](#side-packets)
- The first output stream produces <a href="#ImagePacket">`ImagePacket`</a> objects
- The second output stream produces <a href="#VideoStreamInfoPacket">`VideoStreamInfoPacket`</a> objects


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## frame_saver

**Description:** Saves frames from a video stream to a directory.

**Node Options:** [FrameSaverOptions](avap_doc.md#framesaveroptions)

**Example `.pbtxt`:** [frame_saver](avap_doc.md#aupavapframe_saverproto)

**Basic Node IO:** 

This node has one input stream:
- The input stream takes <a href="#ImagePacket">`ImagePacket`</a> objects

**Specifying the Output:** This node has no output streams, rather the files are saved to the path specified in `node_options->directory`.


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## landmark_predictor

**Description:** Calls a ML model to find supported face or body/pose landmarks within an image.

**Node Options:** [LandmarkPredictorOptions](avap_doc.md#landmarkpredictoroptions)

**Example `.pbtxt`:** [landmark_predictor](avap_doc.md#aupavaplandmark_predictorproto)

**Basic Node IO:** 

This node in its base form has one input stream and one output stream:
- The input stream takes in <a href="#ImagePacket">`ImagePacket`</a> objects
- The output stream prdocues <a href="#LandmarksPacket">`LandmarksPacket`</a> objects

This node can be scaled to receive multiple input video streams, e.g. for 2 video streams:
- The first input stream takes in <a href="#ImagePacket">`ImagePacket`</a> objects
- The second input stream takes in <a href="#ImagePacket">`ImagePacket`</a> objects
- The first output stream produces <a href="#LandmarksPacket">`LandmarksPacket`</a> objects associated with the first input stream
- The second output stream produces <a href="#LandmarksPacket">`LandmarksPacket`</a> objects associated with the second input stream

*NOTE:* This case is only if `node_options->use_detections` is not zero

**IO With Detections**

If `node_options->use_detections` is not zero, the node can use detections to help with landmark predictions. In this case, the node has two input streams for every output stream. For example, with 2 inputs and 1 output:
- The first input stream takes <a href="#DetectionPacket">`DetectionPacket`</a> objects 
- The second input takes <a href="#ImagePacket">`ImagePacket`</a> objects
- The output stream produces <a href="#LandmarksPacket">`LandmarksPacket`</a> objects

We can also have multiple input video streams and corresponding output streams. For instance, in the case of two video streams, with 4 total input streams:
- The first input stream takes <a href="#DetectionPacket">`DetectionPacket`</a> objects
- The second input stream takes <a href="#DetectionPacket">`DetectionPacket`</a> objects
- The third input takes <a href="#ImagePacket">`ImagePacket`</a> objects associated with the first input stream
- The fourth input takes <a href="#ImagePacket">`ImagePacket`</a> objects associated with the second input stream
- The first output stream produces <a href="#LandmarksPacket">`LandmarksPacket`</a> objects associated with the first input stream
- The second output stream produces <a href="#LandmarksPacket">`LandmarksPacket`</a> objects associated with the second input stream

*NOTE:* In this case, the number of input streams must be twice the number of output streams


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## notification_message

**Description:** Sends a notification via SMS or email.

**Node Options** [NotificationMessageOptions](avap_doc.md#notificationmessageoptions)

**Example `.pbtxt`:** [notification_message](avap_doc.md#aupavapnotification_messageproto)

**Basic Node IO:** 

This node has one input stream:
- The input stream takes <a href="#JsonPacket">`JsonPacket`</a> objects

*NOTE:* This node does not have any output streams.


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## notification_mongo

**Description:** Sends customized notifications to a user-specified MongoDB server.

**Node Options** [NotificationMongoOptions](avap_doc.md#notificationmongooptions)

**Example `.pbtxt`:** [notification_mongo](avap_doc.md#aupavapnotification_mongoproto)

**Basic Node IO:**

This node has one input stream:
- The input stream takes <a href="#JsonPacket">`JsonPacket`</a> objects

*NOTE:* This node does not have any output streams.


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## notification_web

**Description:** Sends a notification via the web

**[Node Options](avap_doc.md#notificationweboptions)**

**Basic Node IO:** 

This node has one input stream:
- The input stream takes <a href="#JsonPacket">`JsonPacket`</a> objects

*NOTE:* This node does not have any output streams.


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## statistics_reader

**Description:** Loads statistics in the form of json files in a directory.

**Node Options** [StatisticsReaderOptions](avap_doc.md#statisticsreaderoptions)

**Example `.pbtxt`:** [statistics_reader](avap_doc.md#aupavapstatistics_readerproto)

**Basic Node IO:**

This node has one output stream
- The output stream produces <a href="#JsonPacket">`JsonPacket`</a> objects

**Specifying the Input:** This node has no input streams, rather the statistics are loaded from the path specified in `node_options->input_path`.


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## stream_demux

**Description:** Demultiplexes a video stream.

**Node Options** [StreamMuxOptions](avap_doc.md#streammuxoptions)

**Example `.pbtxt`:** [stream_demux](avap_doc.md#aupavapstream_muxproto)

**Basic Node IO:** This node can have 1 or 2 output streams: 
- The first output stream produces <a href="#VideoPacket">`VideoPacket`</a> objects
- The second *optional* output stream produces <a href="#VideoStreamInfoPacket">`VideoStreamInfoPacket`</a> objects

**Specifying the Output:** This node has no input streams, rather the input is set either by providing a url through `node_options->demux->input_url` or by providing a `graph_input` field at the top of the `*.pbtxt` file (see [Graph IO](#graph-io)).


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## stream_mux

**Description:** Multiplexes a video stream.

**Node Options:** [StreamMuxOptions](avap_doc.md#streammuxoptions)**

**Example `.pbtxt`:** [stream_mux](avap_doc.md#aupavapstream_muxproto)

**Basic Node IO:** This node has two input streams:
- The first input stream takes <a href="#VideoPacket">`VideoPacket`</a> objects
- The second input stream takes <a href="#AVCodecContextPacket">`AVCodecContextPacket`</a> objects, which are treated as [side packets](#side-packets)

**Specifying the Output:** This node has no output streams, rather the output is set either by providing a url through `node_options->demux->output_url` or by providing a `graph_input` field at the top of the `*.pbtxt` file (see [Graph IO](#graph-io)).


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## to_json

**Description:** Converts packets of various types to json format.

**Node Options:** [ToJsonOptions](avap_doc.md#tojsonoptions)

**Example `.pbtxt`:** [to_json](avap_doc.md#aupavapto_jsonproto)

**Basic Node IO:** 

This node has one input stream and one output stream:
- The input stream takes takes in a valid packet object type (see conditions)
- The output stream produces <a href="#JsonPacket">`JsonPacket`</a> objects

**Available Packet Types:** The input stream packet type can be one of the following, but must match the corresponding entry of `node_options->input_type`:
 - PACKET_TYPE_CLASSIFICATIONS (1): Classifications
 - PACKET_TYPE_DETECTIONS_OR_TRACKS (2): DetectionPacket
 - PACKET_TYPE_SEGMENTATIONS (4): Segmentations


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## video_source

**Description:** Loads video from a camera device, such as USB.

**Node Options** [VideoSourceOptions](avap_doc.md#videosourceoptions)

**Example `.pbtxt`:** [video_source](avap_doc.md#aupavapvideo_sourceproto)

**Basic Node IO:** This node has two output streams:
- The first output stream produces <a href="#ImagePacket">`ImagePacket`</a> objects
- The second output stream produces <a href="#VideoStreamInfoPacket">`VideoStreamInfoPacket`</a> objects

**Specifying the Input:** This node has no input streams, rather the camera device is specified by `node_options->path`.


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## x86_dec

**Description:** Decodes an incoming video stream using CPU.

**Node Options:** [VideoCodecOptions](avap_doc.md#videocodecoptions)

**Example `.pbtxt`:** [x86_dec](avap_doc.md#aupavapvcodecproto)

**Basic Node IO:** 

This node in its base configuration has two input streams and two output streams:
- The first input stream takes <a href="#VideoPacket">`VideoPacket`</a> objects
- The second input stream takes <a href="#VideoStreamInfoPacket">`VideoStreamInfoPacket`</a> objects
- The first output stream produces <a href="#ImagePacket">`ImagePacket`</a> objects
- The second output stream produces <a href="#VideoStreamInfoPacket">`VideoStreamInfoPacket`</a> objects

**Node IO with Multiple Pixel Formats**

This node is able to produce multiple video output streams at a time from the same input video stream but for different pixel formats. This is configured by the entries in `node_options->dec->opixfmt`. For example, with 2 pixel format entries in `node_options->dec->opixfmt`, there would be 4 output streams:
- The first output stream produces <a href="#ImagePacket">`ImagePacket`</a> objects
- The second output stream produces <a href="#ImagePacket">`ImagePacket`</a> objects
- The third output stream produces <a href="#VideoStreamInfoPacket">`VideoStreamInfoPacket`</a> objects associated with the first output stream
- The fourth output stream produces <a href="#VideoStreamInfoPacket">`VideoStreamInfoPacket`</a> objects associated with the second output stream

The order of the output streams corresponds to the order of entries in `node_options->dec->opixfmt` which lists the requested video formats. Additionally, the number of output streams for this node should match the number of entries in `node_options->dec->opixfmt`.

*NOTE:* The input streams remain the same as in the basic IO configuration.


<p align="right"><a href="#node_table_top">Back to Node Table</a></p>

## x86_enc

**Description:** Encodes an outgoing video stream using CPU.

**Node Options:** [VideoCodecOptions](avap_doc.md#videocodecoptions)

**Example `.pbtxt`:** [x86_enc](avap_doc.md#aupavapvcodecproto)

**Basic Node IO:** 

This node in its base configuration has one input stream and two output streams:
 - The first input stream takes <a href="#ImagePacket">`ImagePacket`</a> objects
 - The first output stream produces <a href="#VideoPacket">`VideoPacket`</a> objects
 - The second output stream produces <a href="#AVCodecContextPacket">`AVCodecContextPacket`</a> objects

NOTE: this is only the case if the `w`, `h`, and `fps` subfields of `node_options->enc` are *all* set (e.g. non-zero)

**Providing an Info Stream:**

If *any* of the w, h, and fps subfields of `node_options->enc` are unset (e.g. equal to zero), then the node must be provided an info stream. In this case, the node has two input streams:
 - The first input stream takes <a href="#ImagePacket">`ImagePacket`</a> objects
 - The second *optional* input stream takes <a href="#VideoStreamInfoPacket">`VideoStreamInfoPacket`</a> objects, which are treated as [side packets](#side-packets)

*NOTE:* The output streams remain the same as in the basic IO configuration.

