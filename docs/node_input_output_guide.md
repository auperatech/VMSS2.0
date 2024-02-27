- [Input and Output Packet Configurations for Kria SOM Nodes](#input-and-output-packet-configurations-for-kria-som-nodes)
  - [apl\_crowd\_flow](#apl_crowd_flow)
  - [box\_detector](#box_detector)
  - [box\_visualizer](#box_visualizer)
  - [ff\_vfilter](#ff_vfilter)
  - [notification\_message](#notification_message)
  - [notification\_web](#notification_web)
  - [statistics\_reader](#statistics_reader)
  - [stream\_demux](#stream_demux)
  - [stream\_mux](#stream_mux)
  - [x86\_dec](#x86_dec)
  - [x86\_enc](#x86_enc)
- [IO Packet Configurations for Other Aupera Nodes](#io-packet-configurations-for-other-aupera-nodes)
  - [apl\_vehicle\_reid](#apl_vehicle_reid)
  - [box\_classifier](#box_classifier)
  - [box\_segmentor](#box_segmentor)
  - [box\_tracker](#box_tracker)
  - [clip\_generator](#clip_generator)
  - [event\_based\_recorder](#event_based_recorder)
  - [file\_saver](#file_saver)
  - [frame\_saver](#frame_saver)
  - [host\_sink](#host_sink)
  - [host\_source](#host_source)
  - [image\_stream](#image_stream)
  - [json\_stream](#json_stream)
  - [landmark\_predictor](#landmark_predictor)
  - [notification\_mongo](#notification_mongo)
  - [packet\_simulator](#packet_simulator)
  - [subgraph](#subgraph)
  - [to\_json](#to_json)
- [Packet Types and Conversion Options](#packet-types-and-conversion-options)

# Input and Output Packet Configurations for Kria SOM Nodes

notification_message

## apl_crowd_flow

**Description:** Custom node to count people crossing a border line or region of interest.

**Basic Node IO:** This node in its base configuration has 3 input streams. In this configuration, the first input stream takes `TrackPacket` objects, the second input stream takes `VideoStreamInfoPacket` objects which are treated as side packets, and the third input stream takes `UInt64Packet` objects which contain the detect interval and which are treated as side packets. This node can optionally have 4 input streams to provide a video stream, with the first input stream remaining the same, the *second input stream* taking `ImagePacket` objects, and the third and fourth streams taking `VideoStreamInfoPacket` and `UInt64Packet` objects respectively, similarly to the 3-input configuration.

This node in its base configuration has 1 output stream, which produces `JsonPacket` objects. It optionally has two additional output streams so that the total number of output streams can also be 2 or 3. The second *optional* output stream produces `ImagePacket` objects, and the third *optional* output stream produces `JsonPacket` objects containing the same content as the first stream.

**Conditions:** 
- The number of input streams N must be 3 or 4
- The number of output streams M must be between 1 and 3


## box_detector

**Description:** Uses a ML model to find objects in an image, producing bounding boxes for each.

**Basic Node IO:** In its base configuration, this node has one input stream and two output streams. The input stream takes `ImagePacket` objects. The first output stream produces `DetectionPacket` objects, and the second output stream produces `UInt64Packet` which are intended to be treated as side packets containing the detection interval. This node can be scaled to receive multiple input video streams, in which case the number of output streams should be one more than the number of input streams. For instance, with 3 input video streams, there would be 3 input streams taking `ImagePacket` objects, and 4 output streams, with the first 3 output streams producing `DetectionPacket` objects, and the 4th output stream producing `UInt64Packet` objects containing the detection interval. The first `ImagePacket` input stream would correspond to the first `DetectionPacket` output stream, and so on.

**Conditions:**
- The number of output streams must be one more than the number of input streams


## box_visualizer

**Description:** Renders boxes within images provided through the image stream and returns the updated images. Receives a packet containing detected bounding box information, which may be one of `DetectionPacket`, `Classifications`, `PlateRecognitions`, `Segmentations`, `LandmarksPacket`. 

**Basic Node IO:** This node has two input streams, the first stream takes in a packet object containing bounding boxes (see conditions) and the second stream takes in `ImagePacket` objects. This node only has one output stream, which produces `ImagePacket` objects.

**Conditions:**
- the packet type of the first input stream 0 must be one of the following and must match the corresponding value set in `node_options->input_type`:
  - INPUT_TYPE_DETECTION (0): DetectionPacket
  - INPUT_TYPE_CLASSIFICATION (1): Classifications
  - INPUT_TYPE_LPR (2): PlateRecognitions
  - INPUT_TYPE_SEGMENTATION (3): Segmentations
  - INPUT_TYPE_LANDMARK (4): LandmarksPacket


## ff_vfilter

**Description:** Applies video filters to a video stream and outputs the result.

**Basic Node IO:** This node has two input streams, the first input takes `ImagePacket` objects, and the second input takes in `VideoStreamInfoPacket` objects, which are treated as side packets. This node has two output streams, the first input produces `ImagePacket` objects, and the second produces `VideoStreamInfoPacket` objects.


## notification_message

**Description:** Sends a notification via SMS or email.

**Basic Node IO:** This node has one input stream, which takes `JsonPacket` objects. This node does not have any output streams.


## notification_web

**Description:** Sends a notification via the web

**Basic Node IO:** This node has one input stream, which takes `JsonPacket` objects. This node does not have any output streams.


## statistics_reader

**Description:** Loads statistics in the form of json files in a directory.

**Basic Node IO:** This node has no input streams, rather the statistics are loaded from the path specified in `node_options->input_path`. This node has one output stream, which produces `JsonPacket` objects.



## stream_demux

**Description:** Demultiplexes a video stream.

**Basic Node IO:** This node has no input streams, rather the input is set by providing a url through `node_options->demux->input_url` (TODO check that this is the only way). This node can have 1 or 2 output streams: the first input stream produces `VideoPacket` objects, while the second *optional* stream produces `VideoStreamInfoPacket` objects.


## stream_mux 

**Description:** Multiplexes a video stream.

**Basic Node IO:** This node has two input streams, the first takes `VideoPacket` objects, and the second takes `AVCodecContextPacket` objects, which are treated as side packets. This node has no output streams, rather the output is set by providing a url through `node_options->demux->output_url` (TODO check that this is the only way). 


## x86_dec 

**Description:** Decodes a video stream.

**Basic Node IO:** This node has two input streams, the first input takes `VideoPacket` objects, the second input takes `VideoStreamInfoPacket` objects. In its base configuration, this node has two output streams, the first output produces `ImagePacket` objects and the second output produces `VideoStreamInfoPacket` objects. However, it is able to produce multiple video output streams at a time using different pixel formats. For example, with 3 pixel formats, there would be 3 output streams of type `ImagePacket` followed by 3 output streams of type `VideoStreamInfoPacket`. The first `ImagePacket` output stream would correspond to the first `VideoStreamInfoPacket` output stream, and so on. These order of these streams  corresponds to the order of entries in `node_options->dec->opixfmt` which lists the requested video formats.

**Conditions:** 
- Number of output streams N must be twice the number of pixel formats specified in node_options-\>dec-\>opixfmt, which supports multiple output picture streams with different pixel format, supported: "RGB24" or "BGR24" or "NV12" or "I420"


## x86_enc

**Description:** Encodes a video stream.

**Basic Node IO:** This node can have 1 or 2 input streams depending on the entries of `node_options->enc` (see conditions). The first input stream produces `ImagePacket` objects, while the second *optional* stream produces `VideoStreamInfoPacket` objects, which are treated as side packets. This node has two output streams, the first produces `VideoPacket` objects and the second produces `AVCodecContextPacket` packets.

**Conditions:** 
 - If the w, h, and fps subfields of `node_options->enc` are set to non-zero, then the number of inputs must be 1
 - If the w, h, and fps subfields of `node_options->enc` are all set to zero, then the number of inputs must be 2


# IO Packet Configurations for Other Aupera Nodes


## apl_vehicle_reid

**Description:** Re-identifies cars in a video stream.

**Basic Node IO:** This node in its base configuration has 3 input streams. In this configuration, the first input stream takes `TrackPacket` objects, the second input stream takes `VideoStreamInfoPacket` objects which are treated as side packets, and the third input stream takes `UInt64Packet` objects which contain the detect interval and which are treated as side packets. This node can optionally have 4 input streams to provide a video stream, with the first input stream remaining the same, the *second input stream* taking `ImagePacket` objects, and the third and fourth streams taking `VideoStreamInfoPacket` and `UInt64Packet` objects respectively, similarly to the 3-input configuration.

This node in its base configuration has 1 output stream, which produces `JsonPacket` objects. It optionally has two additional output streams so that the total number of output streams can also be 2 or 3. The second *optional* output stream produces `ImagePacket` objects, and the third *optional* output stream produces `JsonPacket` objects containing the same content as the first stream.


## box_classifier

**Description:** Performs object classification on an image cropped by a bounding box.

**Basic Node IO:** This node in its base form takes in an input video stream of type `ImagePacket` and produces an output stream of type `Classifications`. It is able to take in multiple input streams at a time and produces corresponding classification streams for each, for example 3 input streams of type `ImagePacket` and 3 output streams of type `Classifications`. The output streams order will correspond to the input streams order.

**IO With Detections** If `node_options->use_detections` is not zero, the node can use detections to help with classification. In this case, the node has two input streams for every output stream. For example, with 2 inputs and 1 output, the first input takes `DetectionPacket` objects and the second input takes `ImagePacket` objects, and there would be one output stream producing `Classifications` objects. We can also have multiple input video streams and corresponding output streams. For instance, in the case of two video streams, with 4 total input streams, the first two input streams would be `DetectionPacket` streams, and the second two input streams would be `ImagePacket` streams, and there would be two `Classifications` output streams. The first `DetectionPacket` input stream would correspond to the first `ImagePacket` input stream and the first `Classifications` output stream, and so on.

**Conditions:**
- If `node_options->use_detections` is zero, the number of input streams and output streams must be equal
- If `node_options->use_detections` is non-zero, the number of input streams must be twice the number of output streams


## box_segmentor

**Description:** Performs box segmentation on an image stream.

**Basic Node IO:** This node in its base form takes in an input video stream of type `ImagePacket` and produces a corresponding segmentation stream of type `Segmentations`. It is able to take in multiple input streams at a time and produces corresponding segmentation streams for each, for example 3 input streams of type `ImagePacket` and 3 output streams of type `Segmentations`. The output streams order will correspond to the input streams order.

**Conditions:**
- Number of input streams must match number of output streams


## box_tracker

**Description:** Identifies object for tracking through a video stream.

**Basic Node IO:** This node has two input streams, the first stream takes in `DetectionPacket` objects, and the second stream takes in `UInt64Packet` objects which specify the detection interval of the detection node. This node has one output streams which produces `TrackPacket` objects.


## clip_generator

**Description:** Records and saves a clips generated from incoming image packets. Receives ClipGeneratorCommandPacket entries which tell it to start or stop recording.

**Basic Node IO:** This node has two input streams, the first input takes `ClipGeneratorCommandPacket` objects, and the second input takes in `ImagePacket` objects. This node only has one output stream, which produces `FilePacket` objects each time a clip is saved.


## event_based_recorder

**Description:** Produces frames and commands for a [`clip_generator`](#clip_generator) node based on the results of an object detection node. Gives frames to a `clip_generator` and tells it when to start or stop recording.

**Basic Node IO:** This node has two input streams, the first input takes `DetectionPacket` objects, and the second input takes in `ImagePacket` objects. This node has two output streams, the first output produces `ClipGeneratorCommandPacket` objects, and the second produces `ImagePacket` objects.


## file_saver

**Description:** Saves files from a file stream to a directory.

**Basic Node IO:** This node has one input stream, which takes `FilePacket` objects. This node has no output streams, rather the files are saved to the path specified in `node_options->directory`.


## frame_saver

**Description:** Saves frames from a video stream to a directory.

**Basic Node IO:** This node has one input stream, which takes `ImagePacket` objects. This node has no output streams, rather the files are saved to the path specified in `node_options->directory`.


## host_sink

**Description:** This node takes input streams which exist on a device (see [`subgraph`](#subgraph)) and moves them out of the subgraph to be accessed on the host. As a result, it has no output stream. However, each instance of host_sink must have a corresponding output_attrs entry in the relevant subgraph, and likewise each output_attrs entry in the subgraph must have a corresponding host_sink (refer to [`subgraph`](#subgraph) for more information).

**Basic Node IO:** This node has one input stream, which can be any of the allowed device packet objects (see conditions). This node has no output streams, rather the stream will be passed through the subgraph and be available on the host from the subgraph node.

**Conditions:**
- The input stream packet can be one of the following types depending on the values specified in the corresponding [subgraph](#subgraph) `node_options->output_attrs->type field`:
  - PACKET_TYPE_DETECTIONS_OR_TRACKS: DetectionPacket
  - PACKET_TYPE_CLASSIFICATIONS: Classifications
  - PACKET_TYPE_IMAGE: ImagePacket
  - PACKET_TYPE_UINT64: UInt64Packet
  - PACKET_TYPE_VIDEO_STREAM_INFO: VideoStreamInfoPacket
  - PACKET_TYPE_JSON: JsonPacket

TODO check on logic:
`is_fast_sink = !dynamic_cast<packet::IDeviceToHostPacketComm*>(packet.get())) && !dynamic_packet_cast<PacketBasePTS>(packet)`


## host_source

**Description:** This node takes streams which are passed in a subgraph from the host (see [`subgraph`](#subgraph)) and moves them into the subgraph to be accessed on a device. As a result, it has no input stream. However, each instance of host_source must have a corresponding input_attrs entry in the relevant subgraph, and likewise each input_attrs entry in the subgraph must have a corresponding host_sink (refer to [`subgraph`](#subgraph) for more information).

**Basic Node IO:** This node has no input streams, rather the stream will be passed through the subgraph and be available on the device from the subgraph node. This node has one output stream, which can be any of the allowed device packet objects (see conditions). 

**Conditions:**
- The output stream packet can be one of the following types depending on the values specified in the corresponding [subgraph](#subgraph) `node_options->input_attrs->type field`:
  - PACKET_TYPE_DETECTIONS_OR_TRACKS: DetectionPacket
  - PACKET_TYPE_CLASSIFICATIONS: Classifications
  - PACKET_TYPE_IMAGE: ImagePacket
  - PACKET_TYPE_UINT64: UInt64Packet
  - PACKET_TYPE_VIDEO_STREAM_INFO: VideoStreamInfoPacket
  - PACKET_TYPE_JSON: JsonPacket

TODO check on logic:
`is_fast_source = !dynamic_cast<packet::IHostToDevicePacketComm*>(packet.get())) && !dynamic_packet_cast<PacketBasePTS>(packet)`


## image_stream

**Description:** This node generates a video stream based on a directory containing a series of images.

**Basic Node IO:** This node has no input streams, rather the images are loaded from the path specified in `node_options->directory`. This node has two output streams, the first output produces `ImagePacket` objects, and the second output produces `VideoStreamInfoPacket` objects.


## json_stream

**Description:** This node generates a stream of json packets based on a directory containing a series of json files.

**Basic Node IO:** This node has no input streams, rather the images are loaded from the path specified in `node_options->directory`. This node has one output stream, which produces `JsonPacket` objects.


## landmark_predictor

**Description:** Calls a ML model to find landmarks within an image

**Basic Node IO:** This node in its base form takes in an input video stream of type `ImagePacket` and produces an output stream of type `LandmarksPacket`. It is able to take in multiple input streams at a time and produces corresponding landmark streams for each, for example 3 input streams of type `ImagePacket` and 3 output streams of type `LandmarksPacket`. The output streams order will correspond to the input streams order.

**IO With Detections** If `node_options->use_detections` is not zero, the node can use detections to help with landmark predictions. In this case, the node has two input streams for every output stream. For example, with 2 inputs and 1 output, the first input takes `DetectionPacket` objects and the second input takes `ImagePacket` objects, and there would be one output stream producing `LandmarksPacket` objects. We can also have multiple input video streams and corresponding output streams. For instance, in the case of two video streams, with 4 total input streams, the first two input streams would be `DetectionPacket` streams, and the second two input streams would be `ImagePacket` streams, and there would be two `LandmarksPacket` output streams. The first `DetectionPacket` input stream would correspond to the first `ImagePacket` input stream and the first `LandmarksPacket` output stream, and so on.

**Conditions:**
- If `node_options->use_detections` is zero, the number of input streams and output streams must be equal
- If `node_options->use_detections` is non-zero, the number of input streams must be twice the number of output streams


## notification_mongo

**Description:** Sends a notification via MongoDB

**Basic Node IO:** This node has one input stream, which takes `JsonPacket` objects. This node does not have any output streams.


## packet_simulator

**Description:** This node simulates the generation and receipt of packets.

**Basic Node IO:** In its base configuration (`node_options->op_mode` is OP_MODE_ANY (0)), this node can have any number of input streams, which must take packet objects that inherit from `PacketBase` (TODO see packets). This node can also have any number of output streams, which will produce `PacketBase` objects.

**IO in Clip Gen Mode:** If `node_options->op_mode` is OP_MODE_CLIP_GEN (1), then this Node will be in Clip Gen mode. In this mode, the node has one input stream which takes `ImagePacket` objects, and one output stream which produces `ClipGeneratorCommandPacket` objects.


## subgraph

**Description:** The subgraph allows defining a node graph that will run on a device rather than on the host. It manages the passing of packets and streams from the host to the device and vice versa. 

**Basic Node IO:** In a subgraph, input streams correspond to streams passed from the device to the host, while output streams correspond to streams passed from the host to the device. The subgraph has a unique approach for setting up input and output streams:
- Each input stream must have a corresponding `node_options->input_attrs` entry (see TODO link to example) and must have a corresponding [`host_source`](#host_source) node defined within the subgraph
- Each output stream must have a corresponding `node_options->output_attrs` entry (see TODO link to example) and must have a corresponding [`host_sink`](#host_sink) node defined within the subgraph

Each `input_attrs` or `output_attrs` entry must have a `type` subfield which specifies the type of packet being passed to an input stream or produced by an output stream (see conditions for available types)

**Conditions:**
- number of input streams cannot be more than 127, and likewise, number of output streams cannot be more than 127
- if an entry of `node_options->input_attrs` or `node_options->output_attrs` has has_packet_on_init not equal to 0, then corresponding pool_size must be 1
- the input and output stream packet types must be one of the following depending on the corresponding `node_options->output_attrs->type` or `node_options->input_attrs->type` entry:
  - PACKET_TYPE_IMAGE (8): ImagePacket
  - PACKET_TYPE_VIDEO (11): VideoPacket
  - PACKET_TYPE_VIDEO_STREAM_INFO (12): VideoStreamInfoPacket

TODO confirm available packet types (doesn't match pbtxt examples)


## to_json

**Description:** Converts packets of various types to json format.

**Basic Node IO:** This node has one input stream, which takes in a valid packet object type (see conditions). This node has one output stream, which produces `JsonPacket` objects.

**Conditions:**
- The input stream packet type can be one of the following, but must match the corresponding entry of node_options-\>input_type:
  - PACKET_TYPE_CLASSIFICATIONS (1): Classifications
  - PACKET_TYPE_DETECTIONS_OR_TRACKS (2): DetectionPacket
  - PACKET_TYPE_SEGMENTATIONS (4): Segmentations

TODO check the above


# Packet Types and Conversion Options