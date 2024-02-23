- [Input and Output Packet Configurations for Each Node](#input-and-output-packet-configurations-for-each-node)
  - [apl\_crowd\_flow](#apl_crowd_flow)
  - [apl\_vehicle\_reid](#apl_vehicle_reid)
  - [box\_classifier](#box_classifier)
  - [box\_detector](#box_detector)
  - [box\_segmentor](#box_segmentor)
  - [box\_tracker](#box_tracker)
  - [box\_visualizer](#box_visualizer)
  - [clip\_generator](#clip_generator)
  - [event\_based\_recorder](#event_based_recorder)
  - [ff\_vfilter](#ff_vfilter)
  - [file\_saver](#file_saver)
  - [frame\_saver](#frame_saver)
  - [host\_sink](#host_sink)
  - [host\_source](#host_source)
  - [image\_stream](#image_stream)
  - [image\_stream\_device](#image_stream_device)
  - [json\_stream](#json_stream)
  - [landmark\_predictor](#landmark_predictor)
  - [notification\_mongo](#notification_mongo)
  - [notification\_web](#notification_web)
  - [packet\_simulator](#packet_simulator)
  - [statistics\_reader](#statistics_reader)
  - [stream\_demux](#stream_demux)
  - [stream\_mux](#stream_mux)
  - [subgraph](#subgraph)
  - [to\_json](#to_json)
  - [u30\_dec\_device](#u30_dec_device)
  - [x86\_dec](#x86_dec)
  - [x86\_enc](#x86_enc)
- [Packet Types and Conversion Options](#packet-types-and-conversion-options)

# Input and Output Packet Configurations for Each Node


## apl_crowd_flow

**Conditions:** 
- Number of input streams N must be 3 or 4
- Number of output streams M must be less 

### Input Stream when input streams N = 3 (size 3): <!-- omit from toc -->
- **input stream 0:** TrackPacket
- **input stream 1:** VideoStreamInfoPacket - side packet
- **input stream 2:** UInt64Packet - side packet containing detect interval

### Input Stream when input streams N = 4 (size 4): <!-- omit from toc -->
- **input stream 0:** TrackPacket
- **input stream 1:** ImagePacket
- **input stream 2:** VideoStreamInfoPacket - side packet
- **input stream 3:** UInt64Packet - side packet containing detect interval

### Output Stream (size 1 - 3): <!-- omit from toc -->
- **input stream 0:** JsonPacket
- **input stream 1 (optional):** ImagePacket
- **input stream 2 (optional):** JsonPacket


## apl_vehicle_reid

**Conditions:** 
- Number of input streams N must be 3 or 4
- Number of output streams M must be less 

### Input Stream when input streams N = 3 (size 3): <!-- omit from toc -->
- **input stream 0:** TrackPacket
- **input stream 1:** VideoStreamInfoPacket - side packet
- **input stream 2:** UInt64Packet - side packet containing detect interval

### Input Stream when input streams N = 4 (size 4): <!-- omit from toc -->
- **input stream 0:** TrackPacket
- **input stream 1:** ImagePacket
- **input stream 2:** VideoStreamInfoPacket - side packet
- **input stream 3:** UInt64Packet - side packet containing detect interval

### Output Stream (size 1 - 3): <!-- omit from toc -->
- **input stream 0:** JsonPacket
- **input stream 1 (optional):** ImagePacket
- **input stream 2 (optional):** JsonPacket


## box_classifier

**Conditions:**
- when using detections (node_options-\>use_detections is not zero), number of inputs must be exactly twice the number of outputs N, with input of N detection packets and N image packets
- when not using detections, number of inputs must be equal to number of outputs N

### Input Stream when USING detections (size 2N, N is number of outputs): <!-- omit from toc -->
- **input stream i \< N:** DetectionPacket
- **input stream N <\= i \< 2N:** ImagePacket

### Input Stream when NOT USING detections (size N, N \> 0, N is number of outputs): <!-- omit from toc -->
- **input stream i \< N:** ImagePacket

### Output Stream (size N, N is number of outputs): <!-- omit from toc -->
- **output stream i \< N:** Classifications


## box_detector

**Conditions:**
- number of outputs must be equal to number of inputs + 1

### Input Stream (size N, N \> 0, N is number of inputs): <!-- omit from toc -->
- **input stream i \< N:** ImagePacket

### Output Stream (size N + 1, N is number of inputs): <!-- omit from toc -->
- **output stream i \< N:** DetectionPacket
- **output stream N + 1:** UInt64Packet - side packet storing detect_interval


## box_segmentor

**Conditions:**
- Number of input streams N must match number of output streams

### Input Stream (size N, N \> 0, N is number of inputs): <!-- omit from toc -->
- **input stream i \< N:** ImagePacket

### Output Stream (size N, N \> 0, N is number of inputs): <!-- omit from toc -->
- **output stream i \< N:** Segmentations


## box_tracker

### Input Stream (size 2): <!-- omit from toc -->
- **input stream 0** DetectionPacket
- **input stream 1** UInt64Packet - side packet containing detect interval

### Output Stream (size 2): <!-- omit from toc -->
- **output stream 0** TrackPacket

## box_visualizer

**Conditions:**
- the type of input stream 0 must be one of the following and must match the corresponding value of node_options-\>input_type:
  - INPUT_TYPE_DETECTION (0): DetectionPacket
  - INPUT_TYPE_CLASSIFICATION (1): Classifications
  - INPUT_TYPE_LPR (2): PlateRecognitions
  - INPUT_TYPE_SEGMENTATION (3): Segmentations
  - INPUT_TYPE_LANDMARK (4): LandmarksPacket

### Input Stream (size 2): <!-- omit from toc -->
- **input stream 0:** one of DetectionPacket, Classifications, PlateRecognitions, Segmentations, LandmarksPacket
- **input stream 1:** ImagePacket

### Output Stream (size 1): <!-- omit from toc -->
- **input stream 0:** ImagePacket


## clip_generator

### Input Stream (size 2): <!-- omit from toc -->
- **input stream 0:** ClipGeneratorCommandPacket
- **input stream 1:** ImagePacket

### Output Stream (size 1): <!-- omit from toc -->
- **output stream 0:** FilePacket


## event_based_recorder

### Input Stream (size 2): <!-- omit from toc -->
- **input stream 0:** DetectionPacket
- **input stream 1:** ImagePacket

### Output Stream (size 2): <!-- omit from toc -->
- **output stream 0:** ClipGeneratorCommandPacket
- **output stream 1:** ImagePacket


## ff_vfilter

### Input Stream (size 2): <!-- omit from toc -->
- **input stream 0:** ImagePacket
- **input stream 1:** VideoStreamInfoPacket - side packet

### Output Stream (size 2): <!-- omit from toc -->
- **output stream 0:** ImagePacket
- **output stream 1:** VideoStreamInfoPacket


## file_saver

**Conditions:**
- Node outputs to path specified in node_options-\>directory
- Number of output streams N must be greater than 0 (?? TODO)

### Input Stream (size 1): <!-- omit from toc -->
- **input stream 0:** FilePacket

### Output Stream (size N, N > 0, N is number of output streams): <!-- omit from toc -->
TODO: confirm this sizing, does not appear to put anything into output streams


## frame_saver

**Conditions:**
- This node has no output streams, instead the node outputs to path specified in node_options-\>directory

### Input Stream (size 1): <!-- omit from toc -->
- **input stream 0:** ImagePacket


## host_sink

**Conditions:**
- This node has no output streams, rather the stream is passed to the output of the subgraph node (see [subgraph](#subgraph)) by setting the node_options->index to the index of the corresponding subgraph output stream
- NOTE: there must be one sink for each stream that is passed back out of the subgraph
- The input stream packet can be one of the following types depending on the values specified in the corresponding [subgraph](#subgraph) node_options-\>output_attrs[]-\>type field:
  - PACKET_TYPE_DETECTIONS_OR_TRACKS: DetectionPacket
  - PACKET_TYPE_CLASSIFICATIONS: Classifications
  - PACKET_TYPE_IMAGE: ImagePacket
  - PACKET_TYPE_UINT64: UInt64Packet
  - PACKET_TYPE_VIDEO_STREAM_INFO: VideoStreamInfoPacket
  - PACKET_TYPE_JSON: JsonPacket

TODO check on logic:
(is_fast_sink = !dynamic_cast<packet::IDeviceToHostPacketComm*>(packet.get())) && !dynamic_packet_cast<PacketBasePTS>(packet)

### Input Stream (size 1): <!-- omit from toc -->
- **input stream 0:** one of DetectionPacket, Classifications, ImagePacket, UInt64Packet, VideoStreamInfoPacket, JsonPacket


## host_source

**Conditions:**
- This node has no input streams, rather a stream is passed to the input of the subgraph node (see [subgraph](#subgraph)) by setting the node_options->index to the index of the corresponding subgraph input stream
- NOTE: there must be one source for each stream that is passed into the subgraph
- The output stream packet can be one of the following types depending on the values specified in the corresponding [subgraph](#subgraph) node_options-\>input_attrs[]-\>type field:
  - PACKET_TYPE_DETECTIONS_OR_TRACKS: DetectionPacket
  - PACKET_TYPE_CLASSIFICATIONS: Classifications
  - PACKET_TYPE_IMAGE: ImagePacket
  - PACKET_TYPE_UINT64: UInt64Packet
  - PACKET_TYPE_VIDEO_STREAM_INFO: VideoStreamInfoPacket
  - PACKET_TYPE_JSON: JsonPacket

TODO check on logic:
(is_fast_source = !dynamic_cast<packet::IHostToDevicePacketComm*>(packet.get())) && !dynamic_packet_cast<PacketBasePTS>(packet)

### Output Stream (size 1): <!-- omit from toc -->
- **output stream 0:** one of DetectionPacket, Classifications, ImagePacket, UInt64Packet, VideoStreamInfoPacket, JsonPacket

## image_stream

**Conditions:**
- This node has no input streams, rather the node_options-\>directory must be the path of a valid folder containing images

### Output Stream (size 2): <!-- omit from toc -->
- **output stream 0:** ImagePacket
- **output stream 1:** VideoStreamInfoPacket


## image_stream_device

**Conditions:**
- This node has no input streams, rather the node_options-\>directory must be the path of a valid folder containing images

### Output Stream (size 2): <!-- omit from toc -->
- **output stream 0:** ImagePacket
- **output stream 1:** VideoStreamInfoPacket


## json_stream

**Conditions:**
- This node has no input streams, rather the node_options-\>directory must be the path of a valid folder containing .json files

### Output Stream (size 1): <!-- omit from toc -->
- **output stream 0:** JsonPacket

## landmark_predictor

**Conditions:**
- when using detections (node_options-\>use_detections is not zero), number of inputs must be exactly twice the number of outputs N, with input of N detection packets and N image packets
- when not using detections, number of inputs must be equal to number of outputs N

### Input Stream when USING detections (size 2N, N is number of outputs): <!-- omit from toc -->
- **input stream i \< N:** DetectionPacket
- **input stream N <\= i \< 2N:** ImagePacket

### Input Stream when NOT USING detections (size N, N \> 0, N is number of outputs): <!-- omit from toc -->
- **input stream i \< N:** ImagePacket

### Output Stream (size N, N is number of outputs): <!-- omit from toc -->
- **output stream i \< N:** LandmarksPacket


## notification_mongo

**Conditions:**
- this node does not have any outputs

### Input Stream (size 1): <!-- omit from toc -->
- **input stream 0:** JsonPacket


## notification_web

**Conditions:**
- this node does not have any outputs

### Input Stream (size 1): <!-- omit from toc -->
- **input stream 0:** JsonPacket


## packet_simulator

**Conditions:**
- if node_options-\>op_mode is OP_MODE_ANY (0) then can have any number of input streams and output streams
- if node_options-\>op_mode is OP_MODE_CLIP_GEN (1) then must have one input stream and one output stream

### Input Stream when op_mode is OP_MODE_ANY (size N, N is number of input streams): <!-- omit from toc -->
- **input stream i \< N:** PacketBase

### Output Stream when op_mode is OP_MODE_ANY (size M, M is number of output streams): <!-- omit from toc -->
- **input stream i \< N:** PacketBase

### Input Stream when op_mode is OP_MODE_CLIP_GEN (size 1): <!-- omit from toc -->
- **input stream i \< N:** ImagePacket

### Output Stream when op_mode is OP_MODE_CLIP_GEN (size 1): <!-- omit from toc -->
- **input stream i \< N:** ClipGeneratorCommandPacket

TODO check on this

## statistics_reader

**Conditions:**
- this node does not have any inputs, but rather the node_options-\>input_path must be the path to a valid file or directory, depending on whether node_options-\>input_type is DIRECTORY (0) or FILE (1)

### Output Stream (size 1): <!-- omit from toc -->
- **output stream 0:** JsonPacket


## stream_demux

**Conditions:**
- this node does not have any input streams
- input can be set by providing a url through node_options-\>demux-\>input_url
- this node can have 1 or 2 outputs, the second output is optional and will contain video stream information

### Output Stream (size 1 or 2): <!-- omit from toc -->
- **output stream 0:** VideoPacket
- **output stream 1 (optional):** VideoStreamInfoPacket


## stream_mux 

**Conditions:**
- this node does not have any outputs

### Input Stream (size 2): <!-- omit from toc -->
- **input stream 0:** VideoPacket
- **input stream 1:** AVCodecContextPacket - side packet


## subgraph

**Conditions:**
- number of input streams cannot be more than 127, and likewise, number of output streams cannot be more than 127
- number of input streams must be equal to number of node_options-\>input_attrs entries specified
- number of output streams must be equal to number of node_options-\>output_attrs entries specified
- if an entry of node_options-\>input_attrs has has_packet_on_init not equal to 0, then corresponding pool_size must be 1
- if an entry of node_options-\>output_attrs has has_packet_on_init not equal to 0, then corresponding pool_size must be 1
- the input and output stream packet types must be one of the following depending on the corresponding node_options-\>output_attrs-\>type or node_options-\>input_attrs-\>type entry:
    PACKET_TYPE_IMAGE (8): ImagePacket
    PACKET_TYPE_VIDEO (11): VideoPacket
    PACKET_TYPE_VIDEO_STREAM_INFO (12): VideoStreamInfoPacket

### Input Stream (size N, N is number of input streams specified by input_attrs): <!-- omit from toc -->
- **input stream i \< N>:** one of ImagePacket, VideoPacket, VideoStreamInfoPacket

### Output Stream (size M, M is number of output streams specified by output_attrs): <!-- omit from toc -->
- **output stream i \< M:** one of ImagePacket, VideoPacket, VideoStreamInfoPacket

TODO confirm available packet types (doesn't match pbtxt examples)

## to_json

**Conditions:**
- The input stream packet type can be one of the following, but must match the corresponding entry of node_options-\>input_type:
  - PACKET_TYPE_CLASSIFICATIONS (1): Classifications
  - PACKET_TYPE_DETECTIONS_OR_TRACKS (2): DetectionPacket
  - PACKET_TYPE_SEGMENTATIONS (4): Segmentations

### Input Stream (size 1): <!-- omit from toc -->
- **input stream 0:** one of Classifications, DetectionPacket, Segmentations

### Output Stream (size 1): <!-- omit from toc -->
- **output stream 0:** JsonPacket


## u30_dec_device

### Input Stream (size 2): <!-- omit from toc -->
- **input stream 0:** VideoPacket
- **input stream 1:** VideoStreamInfoPacket - side packet

### Output Stream (size 2): <!-- omit from toc -->
- **output stream 0:** ImagePacket
- **output stream 1:** VideoStreamInfoPacket


## x86_dec 

**Conditions:** 
- Number of output streams N must match the number of pixel formats specified in node_options-\>dec-\>opixfmt, which supports multiple output picture streams with different pixel format, supported: "RGB24" or "BGR24" or "NV12" or "I420"

### Input Stream (size 2): <!-- omit from toc -->
- **input stream 0:** VideoPacket
- **input stream 1:** VideoStreamInfoPacket

### Output Stream (size 2xN, N \> 0, N is number of pixel formats): <!-- omit from toc -->
- **output stream i \< N:** ImagePacket
- **output stream N <\= i \< 2N:** VideoStreamInfoPacket


## x86_enc

**Conditions:** 
 - If encoder w, h, and fps are set to non-zero, then the number of inputs must be 1
 - If encoder w, h, and fps are set to 0, then the number of inputs must be 2

### Input Stream (size 1 or 2): <!-- omit from toc -->
- **input stream 0:** ImagePacket
- **input stream 1 (if w, h, fps are 0):** VideoStreamInfoPacket - side packet

### Output Stream (size 2): <!-- omit from toc -->
- **output stream 0:** VideoPacket
- **output stream 1:** AVCodecContextPacket


# Packet Types and Conversion Options