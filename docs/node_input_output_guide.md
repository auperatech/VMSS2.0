# Input and Output Packet Configurations for Each Node <!-- omit from toc -->

- [box\_classifier](#box_classifier)
- [box\_detector](#box_detector)
- [box\_segmentor](#box_segmentor)
- [box\_visualizer](#box_visualizer)
- [ff\_vfilter](#ff_vfilter)
- [landmark\_predictor](#landmark_predictor)
- [notification\_mongo](#notification_mongo)
- [notification\_web](#notification_web)
- [stream\_demux](#stream_demux)
- [stream\_mux](#stream_mux)
- [x86\_dec](#x86_dec)
- [x86\_enc](#x86_enc)


## box_classifier

**Conditions:**
- when using detections (node_options-\>use_detections is not zero), number of inputs must be exactly twice the number of outputs N, with input of N detection packets and N image packets
- when not using detections, number of inputs must be equal to number of outputs N

### Input Stream when USING detections (size 2N, N is number of outputs): <!-- omit from toc -->
- **input stream i \< N:** DetectionPacket
- **input stream N <\= i \< 2N:** ImagePacket

### Input Stream when NOT USING detections (size N, N \> 0, N is number of outputs): <!-- omit from toc -->
- **input stream i \< N:** ImagePacket

### Output Stream when (size N, N is number of outputs): <!-- omit from toc -->
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
- Number of inputs N must match output size

### Input Stream (size N, N \> 0, N is number of inputs): <!-- omit from toc -->
- **input stream i \< N:** ImagePacket

### Output Stream (size N, N \> 0, N is number of inputs): <!-- omit from toc -->
- **output stream i \< N:** Segmentations


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


## ff_vfilter

### Input Stream (size 2): <!-- omit from toc -->
- **input stream 0:** ImagePacket
- **input stream 1:** VideoStreamInfoPacket - side packet

### Output Stream (size 2): <!-- omit from toc -->
- **output stream 0:** ImagePacket
- **output stream 1:** VideoStreamInfoPacket


## landmark_predictor

**Conditions:**
- when using detections (node_options-\>use_detections is not zero), number of inputs must be exactly twice the number of outputs N, with input of N detection packets and N image packets
- when not using detections, number of inputs must be equal to number of outputs N

### Input Stream when USING detections (size 2N, N is number of outputs): <!-- omit from toc -->
- **input stream i \< N:** DetectionPacket
- **input stream N <\= i \< 2N:** ImagePacket

### Input Stream when NOT USING detections (size N, N \> 0, N is number of outputs): <!-- omit from toc -->
- **input stream i \< N:** ImagePacket

### Output Stream when (size N, N is number of outputs): <!-- omit from toc -->
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


## stream_demux

**Conditions:**
- this node does not have any input streams
- input can be set by providing a url through node_options-\>demux-\>input_url
- this node can have 1 or 2 outputs, the second output is optional and will contain video stream information

### Output Stream (size 2): <!-- omit from toc -->
- **output stream 0:** VideoPacket
- **output stream 1 (optional):** VideoStreamInfoPacket


## stream_mux 

**Conditions:**
- this node does not have any outputs

### Input Stream (size 2): <!-- omit from toc -->
- **input stream 0:** VideoPacket
- **input stream 1:** AVCodecContextPacket - side packet


## x86_dec 

**Conditions:** 
- Output size N must match the number of pixel formats specified in node_options-\>dec-\>opixfmt, which supports multiple output picture streams with different pixel format, supported: "RGB24" or "BGR24" or "NV12" or "I420"

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