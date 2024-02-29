# Protocol Documentation <!-- omit from toc -->
<a name="top"></a>

## Table of Contents <!-- omit from toc -->

- [aup/avap/apl\_common.proto](#aupavapapl_commonproto)
  - [AplCommonOptions](#aplcommonoptions)
  - [AplCommonOptions.Border](#aplcommonoptionsborder)
  - [AplCommonOptions.Point](#aplcommonoptionspoint)
  - [AplCommonOptions.Roi](#aplcommonoptionsroi)
- [aup/avap/apl\_crowd\_flow.proto](#aupavapapl_crowd_flowproto)
  - [AplCrowdFlowOptions](#aplcrowdflowoptions)
- [aup/avap/box\_classifier.proto](#aupavapbox_classifierproto)
  - [BoxClassifierOptions](#boxclassifieroptions)
- [aup/avap/box\_detector.proto](#aupavapbox_detectorproto)
  - [BoxDetectorOptions](#boxdetectoroptions)
  - [BoxDetectorOptions.InterClassNms](#boxdetectoroptionsinterclassnms)
  - [BoxDetectorOptions.LabelConfidence](#boxdetectoroptionslabelconfidence)
  - [BoxDetectorOptions.Mean](#boxdetectoroptionsmean)
  - [BoxDetectorOptions.Point](#boxdetectoroptionspoint)
  - [BoxDetectorOptions.Rect](#boxdetectoroptionsrect)
  - [BoxDetectorOptions.Roi](#boxdetectoroptionsroi)
  - [BoxDetectorOptions.Scale](#boxdetectoroptionsscale)
- [aup/avap/box\_segmentor.proto](#aupavapbox_segmentorproto)
  - [BoxSegmentorOptions](#boxsegmentoroptions)
- [aup/avap/box\_tracker.proto](#aupavapbox_trackerproto)
  - [BoxTrackerOptions](#boxtrackeroptions)
  - [BoxTrackerOptions.Size](#boxtrackeroptionssize)
- [aup/avap/box\_visualizer.proto](#aupavapbox_visualizerproto)
  - [BoxVisualizerOptions](#boxvisualizeroptions)
  - [BoxVisualizerOptions.ClassColor](#boxvisualizeroptionsclasscolor)
  - [BoxVisualizerOptions.Color](#boxvisualizeroptionscolor)
  - [BoxVisualizerOptions.Offset](#boxvisualizeroptionsoffset)
  - [BoxVisualizerOptions.InputType](#boxvisualizeroptionsinputtype)
- [aup/avap/demux\_decode.proto](#aupavapdemux_decodeproto)
  - [DemuxDecodeOptions](#demuxdecodeoptions)
- [aup/avap/frame\_saver.proto](#aupavapframe_saverproto)
  - [FrameSaverOptions](#framesaveroptions)
  - [FrameSaverOptions.OutputType](#framesaveroptionsoutputtype)
- [aup/avap/graph.proto](#aupavapgraphproto)
  - [GraphConfig](#graphconfig)
  - [GraphConfig.LoggingFilter](#graphconfigloggingfilter)
  - [GraphConfig.LoggingFilter.Filter](#graphconfigloggingfilterfilter)
  - [GraphConfig.Node](#graphconfignode)
  - [GraphConfig.Node.InputStreamAttributes](#graphconfignodeinputstreamattributes)
  - [GraphConfig.Node.OutputStreamAttributes](#graphconfignodeoutputstreamattributes)
  - [GraphConfig.Node.StreamSync](#graphconfignodestreamsync)
  - [GraphConfig.StatisticsCollector](#graphconfigstatisticscollector)
  - [GraphConfig.LoggingFilter.Entity](#graphconfigloggingfilterentity)
  - [GraphConfig.LoggingFilter.Severity](#graphconfigloggingfilterseverity)
  - [GraphConfig.Node.ContractNoYes](#graphconfignodecontractnoyes)
  - [GraphConfig.Node.InputStreamAttributes.Type](#graphconfignodeinputstreamattributestype)
  - [GraphConfig.Node.OutputStreamAttributes.OnFullAct](#graphconfignodeoutputstreamattributesonfullact)
  - [GraphConfig.Node.StreamSync.DropStrategy](#graphconfignodestreamsyncdropstrategy)
  - [GraphConfig.Node.StreamSync.SyncTimeStampMatch](#graphconfignodestreamsyncsynctimestampmatch)
  - [GraphConfig.SyncTimeStampType](#graphconfigsynctimestamptype)
- [aup/avap/landmark\_predictor.proto](#aupavaplandmark_predictorproto)
  - [LandmarkPredictorOptions](#landmarkpredictoroptions)
- [aup/avap/notification\_message.proto](#aupavapnotification_messageproto)
  - [NotificationMessageOptions](#notificationmessageoptions)
  - [NotificationMessageOptions.Trigger](#notificationmessageoptionstrigger)
  - [NotificationMessageOptions.MessageType](#notificationmessageoptionsmessagetype)
  - [NotificationMessageOptions.Trigger.Type](#notificationmessageoptionstriggertype)
- [aup/avap/notification\_mongo.proto](#aupavapnotification_mongoproto)
  - [NotificationMongoOptions](#notificationmongooptions)
- [aup/avap/notification\_web.proto](#aupavapnotification_webproto)
  - [NotificationWebOptions](#notificationweboptions)
  - [NotificationWebOptions.ProtocolType](#notificationweboptionsprotocoltype)
- [aup/avap/packet\_type.proto](#aupavappacket_typeproto)
  - [PacketType](#packettype)
- [aup/avap/pixfmt.proto](#aupavappixfmtproto)
  - [PixFmt](#pixfmt)
- [aup/avap/statistics\_reader.proto](#aupavapstatistics_readerproto)
  - [StatisticsReaderOptions](#statisticsreaderoptions)
  - [StatisticsReaderOptions.InputType](#statisticsreaderoptionsinputtype)
- [aup/avap/stream\_mux.proto](#aupavapstream_muxproto)
  - [StreamMuxOptions](#streammuxoptions)
  - [StreamMuxOptions.Demux](#streammuxoptionsdemux)
  - [StreamMuxOptions.Mux](#streammuxoptionsmux)
- [aup/avap/subgraph.proto](#aupavapsubgraphproto)
  - [SubgraphOptions](#subgraphoptions)
  - [SubgraphOptions.IOAttributes](#subgraphoptionsioattributes)
- [aup/avap/vcodec.proto](#aupavapvcodecproto)
  - [VideoCodecOptions](#videocodecoptions)
  - [VideoCodecOptions.Decoder](#videocodecoptionsdecoder)
  - [VideoCodecOptions.Encoder](#videocodecoptionsencoder)
  - [VideoCodecOptions.Encoder.Type](#videocodecoptionsencodertype)
- [aup/avap/vfilter.proto](#aupavapvfilterproto)
  - [VideoFilterOptions](#videofilteroptions)
- [aup/avap/video\_source.proto](#aupavapvideo_sourceproto)
  - [VideoSourceOptions](#videosourceoptions)
  - [VideoSourceOptions.SourceType](#videosourceoptionssourcetype)
- [aup/avap/video\_stream.proto](#aupavapvideo_streamproto)
  - [VideoStreamOptions](#videostreamoptions)
- [Scalar Value Types](#scalar-value-types)



<a name="aup_avap_apl_common-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/apl_common.proto



<a name="aup-avaf-AplCommonOptions"></a>

### AplCommonOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| max_file_cache | int32 |  |  |
| debug | bool |  |  |
| draw | bool |  |  |
| need_output_stream | bool |  |  |
| max_cluster_size | int32 |  |  |
| border | [AplCommonOptions.Border](#aplcommonoptionsborder) | repeated |  |
| roi | [AplCommonOptions.Roi](#aplcommonoptionsroi) |  |  |
| notification_port | int32 |  |  |






<a name="aup-avaf-AplCommonOptions-Border"></a>

### AplCommonOptions.Border



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| p1 | [AplCommonOptions.Point](#aplcommonoptionspoint) |  |  |
| p2 | [AplCommonOptions.Point](#aplcommonoptionspoint) |  |  |
| threshold | float |  |  |






<a name="aup-avaf-AplCommonOptions-Point"></a>

### AplCommonOptions.Point



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| x | int32 |  |  |
| y | int32 |  |  |






<a name="aup-avaf-AplCommonOptions-Roi"></a>

### AplCommonOptions.Roi



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| point | [AplCommonOptions.Point](#aplcommonoptionspoint) | repeated |  |
| threshold | float | repeated |  |





 

 

 

 



<a name="aup_avap_apl_crowd_flow-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/apl_crowd_flow.proto



<a name="aup-avaf-AplCrowdFlowOptions"></a>

### AplCrowdFlowOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| common_fields | [AplCommonOptions](#aplcommonoptions) |  |  |
| update_interval_seconds | int32 |  |  |
| initial_entering_count | int32 |  |  |
| initial_exiting_count | int32 |  |  |
| max_allowed_borders | int32 |  |  |
| default_border_crossing_th | float |  |  |
| use_roi | bool |  |  |




 

 

 

 



<a name="aup_avap_box_classifier-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/box_classifier.proto



<a name="aup-avaf-BoxClassifierOptions"></a>

### BoxClassifierOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| classifier_type | [string](#string) |  |  |
| need_preprocess | [bool](#bool) |  |  |
| run_on_letterboxed_img | [bool](#bool) |  |  |
| batch_size | [int32](#int32) |  |  |
| return_in_order | [bool](#bool) |  |  |
| classification_threads | [int32](#int32) |  |  |
| force_batch_size | [bool](#bool) |  |  |
| batch_collection_timeout_ms | [uint64](#uint64) |  |  |
| use_detections | [bool](#bool) |  |  |
| log_performance | [bool](#bool) |  |  |
| max_classification_lib_q_size | [int32](#int32) |  |  |
| max_frame_cache_size | [int32](#int32) |  |  |





 

 

 

 


<a name="aup_avap_box_detector-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/box_detector.proto



<a name="aup-avaf-BoxDetectorOptions"></a>

### BoxDetectorOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| detect_interval | int32 |  |  |
| detector_type | string |  |  |
| obfuscated_token | string |  |  |
| need_preprocess | bool |  |  |
| mean | [BoxDetectorOptions.Mean](#boxdetectoroptionsmean) |  |  |
| scale | [BoxDetectorOptions.Scale](#boxdetectoroptionsscale) |  |  |
| label_confidence | [BoxDetectorOptions.LabelConfidence](#boxdetectoroptionslabelconfidence) | repeated | if at least one label_confidence is provided, total classes and default_confidence_threshold is ignored This means that the detector only considers the labels that label_confidence provide if there is no label_confidence defined, then detector will use total_classes and default_confidence_thresh if no label_confidence is defined and total_classes=0, then an error will be returned |
| total_classes | uint32 |  |  |
| default_confidence_threshold | float |  | default 0.5 |
| inter_class_nms | [BoxDetectorOptions.InterClassNms](#boxdetectoroptionsinterclassnms) | repeated |  |
| run_on_letterboxed_img | bool |  |  |
| batch_size | int32 |  |  |
| return_frames_inorder | bool |  |  |
| detection_threads | int32 |  |  |
| force_batch_size | bool |  |  |
| batch_collection_timeout_ms | int32 |  |  |
| ignore_black_frames | bool |  |  |
| log_performance | bool |  |  |
| log_info | bool |  |  |
| max_detection_lib_q_size | int32 |  |  |
| roi | [BoxDetectorOptions.Roi](#boxdetectoroptionsroi) |  |  |
| crop_region | [BoxDetectorOptions.Rect](#boxdetectoroptionsrect) |  |  |
| center_crop_w_roi | bool |  |  |
| crop_mode | string |  |  |






<a name="aup-avaf-BoxDetectorOptions-InterClassNms"></a>

### BoxDetectorOptions.InterClassNms



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| threshold | float |  |  |
| labels | int32 | repeated |  |






<a name="aup-avaf-BoxDetectorOptions-LabelConfidence"></a>

### BoxDetectorOptions.LabelConfidence



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| label | int32 |  |  |
| confidence | float |  |  |






<a name="aup-avaf-BoxDetectorOptions-Mean"></a>

### BoxDetectorOptions.Mean



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| r | float |  |  |
| g | float |  |  |
| b | float |  |  |






<a name="aup-avaf-BoxDetectorOptions-Point"></a>

### BoxDetectorOptions.Point



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| x | int32 |  |  |
| y | int32 |  |  |






<a name="aup-avaf-BoxDetectorOptions-Rect"></a>

### BoxDetectorOptions.Rect



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| x | int32 |  |  |
| y | int32 |  |  |
| w | int32 |  |  |
| h | int32 |  |  |






<a name="aup-avaf-BoxDetectorOptions-Roi"></a>

### BoxDetectorOptions.Roi



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| point | [BoxDetectorOptions.Point](#boxdetectoroptionspoint) | repeated |  |
| threshold | float | repeated |  |






<a name="aup-avaf-BoxDetectorOptions-Scale"></a>

### BoxDetectorOptions.Scale



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| ch1 | float |  |  |
| ch2 | float |  |  |
| ch3 | float |  |  |





 

 

 

 



<a name="aup_avap_box_segmentor-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/box_segmentor.proto



<a name="aup-avaf-BoxSegmentorOptions"></a>

### BoxSegmentorOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| segmentor_type | [string](#string) |  |  |
| need_preprocess | [bool](#bool) |  |  |
| run_on_letterboxed_img | [bool](#bool) |  |  |
| batch_size | [int32](#int32) |  |  |
| return_frames_inorder | [bool](#bool) |  |  |
| segmentation_threads | [int32](#int32) |  |  |
| force_batch_size | [bool](#bool) |  |  |
| batch_collection_timeout_ms | [uint64](#uint64) |  |  |
| ignore_black_frames | [bool](#bool) |  |  |
| log_performance | [bool](#bool) |  |  |
| log_info | [bool](#bool) |  |  |
| max_segmentation_lib_q_size | [int32](#int32) |  |  |
| resizing | [bool](#bool) |  |  |
| interpolation_flag | [int32](#int32) |  |  |
| solo_score_thr | [float](#float) |  |  |





 

 

 

 


<a name="aup_avap_box_tracker-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/box_tracker.proto



<a name="aup-avaf-BoxTrackerOptions"></a>

### BoxTrackerOptions
Options for the tracker calculator


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| max_keep_alive | [int32](#int32) |  | The max detect_interval used to keep the track alive |
| min_hits | [int32](#int32) |  | The minimum number of detections for initializing tracking |
| min_object_area_th | [int32](#int32) |  | Ignore detections smaller than this area threshold |
| affinity_threshold | [double](#double) |  | The affinity threshold between detections and tracklets |
| shape_weight | [float](#float) |  | The weight of shape cost between a detection rectengle and a traclet |
| position_weight | [float](#float) |  | The weight of position cost between a detection rectengle and a traclet |
| appearance_weight | [float](#float) |  | The weight of appearanr cost between a detection and a traclet |
| shape_dist_max | [float](#float) |  | The maximum value of the shape cost |
| position_dist_max | [float](#float) |  | The maximum value of the position cost |
| use_exp_cost | [bool](#bool) |  | If use the exponential formula to calculate the matching cost |
| disable_tracker_update | [bool](#bool) |  | If disable the kalman filter to predict tracklet bounding boxes |
| tracker_type | [string](#string) |  | The tracker type, could be either SORT&#43;&#43; or DEEPSORT |
| max_object_area_th | [int32](#int32) |  | Ignore detections greater than this threshold |
| fixed_box_size | [BoxTrackerOptions.Size](#aup-avaf-BoxTrackerOptions-Size) |  | Compute the position cost with a fixed box size instead of the detected ones |






<a name="aup-avaf-BoxTrackerOptions-Size"></a>

### BoxTrackerOptions.Size
Represents a rectangle size


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| w | [int32](#int32) |  | pixelwise width |
| h | [int32](#int32) |  | pixelwise height |





 

 

 

 



<a name="aup_avap_box_visualizer-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/box_visualizer.proto



<a name="aup-avaf-BoxVisualizerOptions"></a>

### BoxVisualizerOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| input_type | [BoxVisualizerOptions.InputType](#boxvisualizeroptionsinputtype) |  |  |
| text_color | [BoxVisualizerOptions.Color](#boxvisualizeroptionscolor) |  |  |
| box_color | [BoxVisualizerOptions.Color](#boxvisualizeroptionscolor) |  |  |
| class_color | [BoxVisualizerOptions.ClassColor](#boxvisualizeroptionsclasscolor) | repeated |  |
| default_class_color | [BoxVisualizerOptions.Color](#boxvisualizeroptionscolor) |  |  |
| text_offset | [BoxVisualizerOptions.Offset](#boxvisualizeroptionsoffset) |  |  |
| box_thickness | int32 |  |  |
| text_size | int32 |  |  |
| font | int32 |  |  |
| font_scale | double |  |  |
| font_thickness | int32 |  |  |
| line_type | int32 |  |  |
| label_name_file | string |  |  |
| overlay_opacity | float |  |  |
| connect_landmarks | bool |  |  |
| apply_filter_on_landmarks | string |  |  |
| arm_raise_check | string |  |  |






<a name="aup-avaf-BoxVisualizerOptions-ClassColor"></a>

### BoxVisualizerOptions.ClassColor



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| color | [BoxVisualizerOptions.Color](#boxvisualizeroptionscolor) |  |  |
| label | int32 |  |  |






<a name="aup-avaf-BoxVisualizerOptions-Color"></a>

### BoxVisualizerOptions.Color



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| r | float |  |  |
| g | float |  |  |
| b | float |  |  |






<a name="aup-avaf-BoxVisualizerOptions-Offset"></a>

### BoxVisualizerOptions.Offset



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| x | float |  |  |
| y | float |  |  |





 


<a name="aup-avaf-BoxVisualizerOptions-InputType"></a>

### BoxVisualizerOptions.InputType


| Name | Number | Description |
| ---- | ------ | ----------- |
| INPUT_TYPE_DETECTION | 0 |  |
| INPUT_TYPE_CLASSIFICATION | 1 |  |
| INPUT_TYPE_SEGMENTATION | 2 |  |
| INPUT_TYPE_LANDMARK | 3 |  |


 

 

 



<a name="aup_avap_demux_decode-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/demux_decode.proto



<a name="aup-avaf-DemuxDecodeOptions"></a>

### DemuxDecodeOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| demux_options | [StreamMuxOptions](#streammuxoptions) |  |  |
| decode_options | [VideoCodecOptions](#videocodecoptions) |  |  |





 

 

 

 



<a name="aup_avap_frame_saver-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/frame_saver.proto



<a name="aup-avaf-FrameSaverOptions"></a>

### FrameSaverOptions
Options for frame saver node which saves frames to disk for specific interval


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| directory | [string](#string) |  | Directory on which frames will be saved |
| directory_cleanup | [bool](#bool) |  | Whether directory should be cleaned up on node startup or not |
| save_limit | [uint32](#uint32) |  | Maximum number of files that can be saved |
| save_offset | [uint32](#uint32) |  | Number of initial frames to be ignored from being saved |
| output_type | [FrameSaverOptions.OutputType](#aup-avaf-FrameSaverOptions-OutputType) |  | Output type of the saved frames |





 


<a name="aup-avaf-FrameSaverOptions-OutputType"></a>

### FrameSaverOptions.OutputType
Enum denoting the file type to be saved

| Name | Number | Description |
| ---- | ------ | ----------- |
| RAW | 0 | Raw in the format readable by vooya |
| JPEG | 1 | JPEG format |


 

 

 


<a name="aup_avap_graph-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/graph.proto



<a name="aup-avaf-GraphConfig"></a>

### GraphConfig
Describes the topology and function of an avaf Graph.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| node | [GraphConfig.Node](#graphconfignode) | repeated | The nodes. |
| control_port | int32 |  |  |
| sync_timestamp_type | [GraphConfig.SyncTimeStampType](#graphconfigsynctimestamptype) |  |  |
| graph_input | string | repeated |  |
| graph_output | string | repeated |  |
| statistics_collector | [GraphConfig.StatisticsCollector](#graphconfigstatisticscollector) | repeated |  |
| console_logging_filter | [GraphConfig.LoggingFilter](#graphconfigloggingfilter) |  |  |
| file_logging_filter | [GraphConfig.LoggingFilter](#graphconfigloggingfilter) |  |  |
| task_id | string |  | The graph-level task_id and notification_url |
| notification_url | string |  |  |
| subgraph | [GraphConfig](#graphconfig) |  |  |






<a name="aup-avaf-GraphConfig-LoggingFilter"></a>

### GraphConfig.LoggingFilter



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| enable_log | bool |  |  |
| enable_all | bool |  |  |
| filter | [GraphConfig.LoggingFilter.Filter](#graphconfigloggingfilterfilter) | repeated |  |






<a name="aup-avaf-GraphConfig-LoggingFilter-Filter"></a>

### GraphConfig.LoggingFilter.Filter



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| entity | [GraphConfig.LoggingFilter.Entity](#graphconfigloggingfilterentity) |  |  |
| severity | [GraphConfig.LoggingFilter.Severity](#graphconfigloggingfilterseverity) | repeated |  |
| name | string | repeated |  |






<a name="aup-avaf-GraphConfig-Node"></a>

### GraphConfig.Node



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| name | string |  | this denotes the calculator name this can be an arbitrary string determined by graph author in order to uniquely identify the node by. |
| vendor | string |  | the vendor of the calculator. This determines who/what company wrote the node this is useful to differentiate same calculators via different vendors |
| calculator | string |  | in avaf, it means processor plugin name. Plugin name is known as calculator |
| input_stream | string | repeated | node input stream name, can be multiple, each stream name should be unique for current graph |
| input_stream_attributes | [GraphConfig.Node.InputStreamAttributes](#graphconfignodeinputstreamattributes) | repeated | list of attributes for all the input streams |
| output_stream | string | repeated | node output stream name, can be multiple, each stream should be unique for current graph |
| output_stream_attributes | [GraphConfig.Node.OutputStreamAttributes](#graphconfignodeoutputstreamattributes) | repeated |  |
| stream_sync | [GraphConfig.Node.StreamSync](#graphconfignodestreamsync) |  |  |
| ml_model_kernel_name | string |  |  |
| node_options | [google.protobuf.Any](#googleprotobufany) | repeated | the private options passing to each node, defined by users |
| graph_input | string |  | graph input and graph output. for now assuming a node may have maximum one graph input/output |
| graph_output | string |  |  |

TODO link to google protobuf




<a name="aup-avaf-GraphConfig-Node-InputStreamAttributes"></a>

### GraphConfig.Node.InputStreamAttributes



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| name | string |  | input stream name referring to input_stream field |
| type | [GraphConfig.Node.InputStreamAttributes.Type](#graphconfignodeinputstreamattributestype) |  |  |
| can_continue | [GraphConfig.Node.ContractNoYes](#graphconfignodecontractnoyes) |  | This denodes if the sink expects continueable packets. This means consecutive packets with the same timestamp |






<a name="aup-avaf-GraphConfig-Node-OutputStreamAttributes"></a>

### GraphConfig.Node.OutputStreamAttributes



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| name | string |  | name of input stream |
| capacity | uint32 |  | This denotes the capacity of the stream. In the case that it is not defined, global graph capacity will be used for this specific stream instead |
| on_full_act | [GraphConfig.Node.OutputStreamAttributes.OnFullAct](#graphconfignodeoutputstreamattributesonfullact) |  |  |
| can_continue | [GraphConfig.Node.ContractNoYes](#graphconfignodecontractnoyes) |  | same as can_continue in input_stream_attributes. Node that if source is continuable, all the sinks must be continueable. The reverse is not true so non-continueable source may be connected to continueable sinks. |






<a name="aup-avaf-GraphConfig-Node-StreamSync"></a>

### GraphConfig.Node.StreamSync



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| drop_strategy | [GraphConfig.Node.StreamSync.DropStrategy](#graphconfignodestreamsyncdropstrategy) |  |  |
| sync_match | [GraphConfig.Node.StreamSync.SyncTimeStampMatch](#graphconfignodestreamsyncsynctimestampmatch) |  | ReuseStrategy reuse_strategy = 2; |
| timeout_ms | int32 |  | timeout |






<a name="aup-avaf-GraphConfig-StatisticsCollector"></a>

### GraphConfig.StatisticsCollector



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| target_file | string |  | if empty, statistics will be printed to STDOUT |
| measurement_print_interval_ms | uint32 |  | default value is 1000 |
| latency_stream_start | string |  | framework-level latency |
| latency_stream_end | string |  |  |
| throughput_stream_name | string | repeated | stream throughput |
| throughput_ignore_initial_packets_count | uint32 |  |  |
| size_stream_name | string | repeated | stream size |





 


<a name="aup-avaf-GraphConfig-LoggingFilter-Entity"></a>

### GraphConfig.LoggingFilter.Entity


| Name | Number | Description |
| ---- | ------ | ----------- |
| ENTITY_NODE | 0 |  |
| ENTITY_FRAMEWORK | 1 |  |



<a name="aup-avaf-GraphConfig-LoggingFilter-Severity"></a>

### GraphConfig.LoggingFilter.Severity


| Name | Number | Description |
| ---- | ------ | ----------- |
| SEVERITY_TRACE | 0 |  |
| SEVERITY_DEBUG | 1 |  |
| SEVERITY_INFO | 2 |  |
| SEVERITY_WARN | 3 |  |
| SEVERITY_ERROR | 4 |  |
| SEVERITY_FATAL | 5 |  |



<a name="aup-avaf-GraphConfig-Node-ContractNoYes"></a>

### GraphConfig.Node.ContractNoYes


| Name | Number | Description |
| ---- | ------ | ----------- |
| CONTRACT | 0 |  |
| NO | 1 |  |
| YES | 2 |  |



<a name="aup-avaf-GraphConfig-Node-InputStreamAttributes-Type"></a>

### GraphConfig.Node.InputStreamAttributes.Type
InputStreamAttributes:
name: name of input stream
CONTRACT: stream type to be fetched from contract

SYNCED_IMMUTABLE: stream type is forward. Forward streams are not
allowed to contain loops and they are synced. IMMUTABLE denodes that
the node is not allowed to modify these packets via sync-time-stamp.
the node is not allowed to modify this packet

SYNCED_MUTABLE: stream type is forward. The different is that this kind
of sink allows the node to modify the packet

UNSYNCED_IMMUTABLE: is a type of stream that can have any direction
whether forwards or backwards. The packets of these streams are always
immutable meaning that the sink is not allowed to modify it.

SIDE_PACKET: these streams can have any direction and not synced and
timestamped like UNSYNCED_IMMUTABLE. The difference is that these
streams only keep track of the latest packet as opposed to UNSYNCED
which act as a queue. These streams are useful for communicating
various configurations

| Name | Number | Description |
| ---- | ------ | ----------- |
| CONTRACT | 0 |  |
| SYNCED_IMMUTABLE | 1 |  |
| SYNCED_MUTABLE | 2 |  |
| UNSYNCED_IMMUTABLE | 3 |  |
| SIDE_PACKET | 4 |  |



<a name="aup-avaf-GraphConfig-Node-OutputStreamAttributes-OnFullAct"></a>

### GraphConfig.Node.OutputStreamAttributes.OnFullAct
This determines the behavior of aup::avaf::Node::enqueue member
function in the case that stream&#39;s full capacity is reached

BLOCK: block the enqueue function call until room is available in the
stream via dequeueing from other nodes

DROP_FRONT: automatically drop the oldest packet (front of the stream)
to make room for the new packet being enqueued

FAIL: fail the enqueue call immediately in case that stream is full

| Name | Number | Description |
| ---- | ------ | ----------- |
| BLOCK | 0 |  |
| DROP_FRONT | 1 |  |
| FAIL | 2 |  |



<a name="aup-avaf-GraphConfig-Node-StreamSync-DropStrategy"></a>

### GraphConfig.Node.StreamSync.DropStrategy
DropStrategy determines the scenario that framework drop the packet in
case that timeout is reached

CONTRACT: determient the packet dropping strategy from the contract

DROP_INCOMPLETE_PACKETS: this option will drop the packets in case at
least one of the input streams do not have complete packet sequence at
the timeout time. Complete packet sequence means a single packet for
non-continuable streams. For the case of contiued streams, it means
that the final packet of the continued series of packets is not delivered
before timeout. Any time that drop happens, execute will not be called

DROP_MISSING_PACKETS: drop if there are any packets in any of the
streams that are completely missing

NEVER_DROP: never drop packets. if timeout is reached and one synced
input is available

| Name | Number | Description |
| ---- | ------ | ----------- |
| CONTRACT | 0 |  |
| DROP_INCOMPLETE_PACKETS | 1 |  |
| DROP_MISSING_PACKETS | 2 |  |
| NEVER_DROP | 3 |  |



<a name="aup-avaf-GraphConfig-Node-StreamSync-SyncTimeStampMatch"></a>

### GraphConfig.Node.StreamSync.SyncTimeStampMatch
enum ReuseStrategy {
  CONTRACT2 = 0;
  EMPTY = 1;
  REUSE_LAST_COMPLETE_PACKETS = 2;
  REUST_LAST_AVAILABLE_PACKETS = 3;
}

| Name | Number | Description |
| ---- | ------ | ----------- |
| CONTRACT3 | 0 | sync based on what is available in the contract |
| EQUAL | 1 | sync based on sync-time-stamp equality |



<a name="aup-avaf-GraphConfig-SyncTimeStampType"></a>

### GraphConfig.SyncTimeStampType


| Name | Number | Description |
| ---- | ------ | ----------- |
| PTS | 0 |  |


 

 

 



<a name="aup_avap_landmark_predictor-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/landmark_predictor.proto



<a name="aup-avaf-LandmarkPredictorOptions"></a>

### LandmarkPredictorOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| landmark_predictor_type | string |  |  |
| need_preprocess | bool |  |  |
| run_on_letterboxed_img | bool |  |  |
| batch_size | int32 |  |  |
| return_frames_inorder | bool |  |  |
| landmark_prediction_threads | int32 |  |  |
| force_batch_size | bool |  |  |
| batch_collection_timeout_ms | uint64 |  |  |
| log_performance | bool |  |  |
| max_landmark_prediction_lib_q_size | int32 |  |  |
| use_detections | bool |  |  |
| max_frame_cache_size | int32 |  |  |





 

 

 

 



<a name="aup_avap_notification_message-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/notification_message.proto



<a name="aup-avaf-NotificationMessageOptions"></a>

### NotificationMessageOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| message_type | [NotificationMessageOptions.MessageType](#notificationmessageoptionsmessagetype) |  |  |
| server_url | string |  | If send email notification, this is email SMTP URL, eg: &#34;smtps://mail.auperatech.com:465&#34; If send SMS notification, this is SMS gateway API URL, eg: &#34;https://api.twilio.com/2010-04-01/Accounts/&lt;Account-SID&gt;/Messages.json&#34; |
| sender | string |  | If send email notification, sender and receiver are email address: &#34;xxxxxxx@auperatech.com&#34; If send SMS notification, sender and receiver are phone number string, eg: &#34;19734255123&#34; |
| receiver | string | repeated |  |
| sender_username | string |  | The credentials or authentications for connecting the server url If send email notification, username and password are sender&#39;s email credentials If send SMS notification, username and password are account&#39;s ID and token for authentications |
| sender_password | string |  |  |
| notification_q_size | uint32 |  | notification thread queue size |
| trigger | [NotificationMessageOptions.Trigger](#notificationmessageoptionstrigger) | repeated | The jq trigger to select and filter messages sent |






<a name="aup-avaf-NotificationMessageOptions-Trigger"></a>

### NotificationMessageOptions.Trigger



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| trigger_type | [NotificationMessageOptions.Trigger.Type](#notificationmessageoptionstriggertype) |  | If choose JQ, we will apply jq_query_string to filter the packet; otherwise we keep the packet as is. |
| jq_query_string | string |  | The jq string to filter the contents, eg: &#34;jq &#39;.detections | any(.[]; (.h * .w &gt; 200) and .class == \&#34;bear\&#34;)&#39; example.json&#34; |
| trigger_consecutive_packet | uint32 |  | Each notification sent when the previously received packet numbers meet the trigger_consecutive_packet value |
| notification_title | string |  | user-defined notification_title |
| notification_body | string |  | user-defined notification_body |
| attach_json | bool |  | If wanted to attach the packets into the notification |





 


<a name="aup-avaf-NotificationMessageOptions-MessageType"></a>

### NotificationMessageOptions.MessageType


| Name | Number | Description |
| ---- | ------ | ----------- |
| EMAIL | 0 |  |
| SMS | 1 |  |



<a name="aup-avaf-NotificationMessageOptions-Trigger-Type"></a>

### NotificationMessageOptions.Trigger.Type


| Name | Number | Description |
| ---- | ------ | ----------- |
| PACKET | 0 |  |
| JQ | 1 |  |


 

 

 



<a name="aup_avap_notification_mongo-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/notification_mongo.proto



<a name="aup-avaf-NotificationMongoOptions"></a>

### NotificationMongoOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| mongodb_address | string |  |  |
| database_name | string |  |  |
| collection_name | string |  |  |
| notification_q_size | uint32 |  |  |





 

 

 

 



<a name="aup_avap_notification_web-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/notification_web.proto



<a name="aup-avaf-NotificationWebOptions"></a>

### NotificationWebOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| notification_url | string |  |  |
| protocol_type | [NotificationWebOptions.ProtocolType](#notificationweboptionsprotocoltype) |  |  |
| notification_q_size | uint32 |  |  |
| https_username | string |  |  |
| https_password | string |  |  |





 


<a name="aup-avaf-NotificationWebOptions-ProtocolType"></a>

### NotificationWebOptions.ProtocolType


| Name | Number | Description |
| ---- | ------ | ----------- |
| HTTP | 0 |  |
| UDP | 1 |  |


 

 

 



<a name="aup_avap_packet_type-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/packet_type.proto


 


<a name="aup-avaf-PacketType"></a>

### PacketType


| Name | Number | Description |
| ---- | ------ | ----------- |
| PACKET_TYPE_NONE | 0 |  |
| PACKET_TYPE_CLASSIFICATIONS | 1 |  |
| PACKET_TYPE_DETECTIONS_OR_TRACKS | 2 | implement |
| PACKET_TYPE_PLATE_RECOGNITIONS | 3 |  |
| PACKET_TYPE_SEGMENTATIONS | 4 |  |
| PACKET_TYPE_AV_CODEC_CONTEXT | 5 |  |
| PACKET_TYPE_CLIP_GENERATOR_COMMAND | 6 |  |
| PACKET_TYPE_FILE | 7 |  |
| PACKET_TYPE_IMAGE | 8 | implement |
| PACKET_TYPE_JSON | 9 |  |
| PACKET_TYPE_UINT64 | 10 | implement |
| PACKET_TYPE_VIDEO | 11 | implement |
| PACKET_TYPE_VIDEO_STREAM_INFO | 12 | implement |
| PACKET_TYPE_ANY | 13 |  |
| PACKET_TYPE_MAX | 14 |  |


 

 

 



<a name="aup_avap_pixfmt-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/pixfmt.proto


 


<a name="aup-avaf-PixFmt"></a>

### PixFmt


| Name | Number | Description |
| ---- | ------ | ----------- |
| PIXFMT_NONE | 0 |  |
| PIXFMT_NV12 | 1 |  |
| PIXFMT_I420 | 2 |  |
| PIXFMT_BGR24 | 3 |  |
| PIXFMT_RGB24 | 4 |  |


 

 

 



<a name="aup_avap_statistics_reader-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/statistics_reader.proto



<a name="aup-avaf-StatisticsReaderOptions"></a>

### StatisticsReaderOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| interval_us | [int64](#int64) |  |  |
| input_path | string |  |  |
| loop_over | bool |  |  |
| only_send_throughput | bool |  |  |
| input_type | [StatisticsReaderOptions.InputType](#statisticsreaderoptionsinputtype) |  |  |





 


<a name="aup-avaf-StatisticsReaderOptions-InputType"></a>

### StatisticsReaderOptions.InputType


| Name | Number | Description |
| ---- | ------ | ----------- |
| DIRECTORY | 0 |  |
| FILE | 1 |  |


 

 

 



<a name="aup_avap_stream_mux-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/stream_mux.proto



<a name="aup-avaf-StreamMuxOptions"></a>

### StreamMuxOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| demux | [StreamMuxOptions.Demux](#streammuxoptionsdemux) |  |  |
| mux | [StreamMuxOptions.Mux](#streammuxoptionsmux) |  |  |






<a name="aup-avaf-StreamMuxOptions-Demux"></a>

### StreamMuxOptions.Demux



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| rtsp_transport | string |  | for receiving rtsp stream, we can choose &#34;udp&#34; or &#34;tcp&#34; transport method |
| force_fps | float |  | for some situation, say that we want to see the result as soon as possible, we don&#39;t want demux node spending time(1~2s) to calculate actual fps, then we can specify the fps to demux node |
| iframe_extract | bool |  | if set to true, then demux node will only send the I frame packet to decoder, otherwise send all kind of packets |
| auto_reconnect | bool |  | if set to true, then demux node will try to reconnect the input stream when network is poor or when receive eof |
| input_url | string |  |  |
| is_dummy | bool |  |  |






<a name="aup-avaf-StreamMuxOptions-Mux"></a>

### StreamMuxOptions.Mux



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| rtsp_transport | string |  | for sending rtsp stream, we can choose &#34;udp&#34; or &#34;tcp&#34; transport method |
| auto_reconnect | bool |  | if set to true, then mux node will try to reconnect the output stream when output stream disconnect |
| output_url | string |  |  |





 

 

 

 



<a name="aup_avap_subgraph-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/subgraph.proto



<a name="aup-avaf-SubgraphOptions"></a>

### SubgraphOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| input_attrs | [SubgraphOptions.IOAttributes](#subgraphoptionsioattributes) | repeated |  |
| output_attrs | [SubgraphOptions.IOAttributes](#subgraphoptionsioattributes) | repeated |  |
| xdma_reader_sz | uint32 |  |  |
| xdma_writer_sz | uint32 |  |  |
| subgraph_config | [GraphConfig](#graphconfig) |  |  |
| attach_gdb_on_device | bool |  |  |






<a name="aup-avaf-SubgraphOptions-IOAttributes"></a>

### SubgraphOptions.IOAttributes



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| type | [PacketType](#packettype) |  |  |
| pool_sz | uint32 |  |  |
| entry_sz_kb | uint32 |  |  |
| has_packet_on_init | bool |  |  |
| image_packet_width | uint32 |  |  |
| image_packet_height | uint32 |  |  |
| image_packet_pixfmt | [PixFmt](#pixfmt) |  |  |





 

 

 

 



<a name="aup_avap_vcodec-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/vcodec.proto



<a name="aup-avaf-VideoCodecOptions"></a>

### VideoCodecOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| dec | [VideoCodecOptions.Decoder](#videocodecoptionsdecoder) |  |  |
| enc | [VideoCodecOptions.Encoder](#videocodecoptionsencoder) |  |  |
| host_source_index | uint32 |  |  |
| host_sink_index | uint32 |  |  |
| video_packet_fifo_cap | uint32 |  |  |
| drop_packet_on_full_data_stream | bool |  |  |






<a name="aup-avaf-VideoCodecOptions-Decoder"></a>

### VideoCodecOptions.Decoder



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| ow | uint32 | repeated | support multiple output picture streams with different resolution, if set to 0, then use the same resolution with input stream |
| oh | uint32 | repeated |  |
| opixfmt | [PixFmt](#pixfmt) | repeated | support multiple output picture streams with different pixel format, supported: &#34;RGB24&#34; or &#34;BGR24&#34; or &#34;NV12&#34; or &#34;I420&#34;, default use NV12 as output pixel format |
| queue_size | uint32 |  | decoder buffer queue size |
| low_latency | bool |  | decoder enable low_latency or not, it can be true if input stream do not contain B frame, once enable low_latency mode, decoder will output pictures ASAP |






<a name="aup-avaf-VideoCodecOptions-Encoder"></a>

### VideoCodecOptions.Encoder



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| type | [VideoCodecOptions.Encoder.Type](#videocodecoptionsencodertype) |  |  |
| w | uint32 |  | encoder width and height, if set to 0, then use the same resolution with input stream |
| h | uint32 |  |  |
| fps | float |  |  |
| queue_size | uint32 |  |  |
| b_adapt | bool |  |  |
| bframes | uint32 |  |  |
| gop_size | uint32 |  |  |
| bitrate | uint32 |  | video bitrate, bit/s |
| gop_mode | string |  | support &#34;default&#34;, &#34;low-latency-B&#34;, &#34;low-latency-P&#34;, &#34;dynamic&#34; |
| rc_mode | string |  | support &#34;CBR&#34;, &#34;VBR&#34;, &#34;CRF&#34; |
| threads | uint32 |  | encoding using threads, usually it&#39;s a option to |





 


<a name="aup-avaf-VideoCodecOptions-Encoder-Type"></a>

### VideoCodecOptions.Encoder.Type


| Name | Number | Description |
| ---- | ------ | ----------- |
| H264 | 0 |  |
| H265 | 1 |  |
| MPEG4 | 2 |  |


 

 

 



<a name="aup_avap_vfilter-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/vfilter.proto



<a name="aup-avaf-VideoFilterOptions"></a>

### VideoFilterOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| roi_x | uint32 |  |  |
| roi_y | uint32 |  |  |
| roi_w | uint32 |  |  |
| roi_h | uint32 |  |  |
| opixfmt | [PixFmt](#pixfmt) |  |  |
| ow | uint32 |  |  |
| oh | uint32 |  |  |
| ofps | float |  |  |
| queue_size | uint32 |  |  |





 

 

 

 



<a name="aup_avap_video_source-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/video_source.proto



<a name="aup-avaf-VideoSourceOptions"></a>

### VideoSourceOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| source_type | [VideoSourceOptions.SourceType](#videosourceoptionssourcetype) |  |  |
| path | string |  |  |
| width | uint32 |  |  |
| height | uint32 |  |  |
| framerate | float |  |  |
| pool_size | uint32 |  |  |





 


<a name="aup-avaf-VideoSourceOptions-SourceType"></a>

### VideoSourceOptions.SourceType


| Name | Number | Description |
| ---- | ------ | ----------- |
| AUTO | 0 |  |
| USB | 1 |  |


 

 

 



<a name="aup_avap_video_stream-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/video_stream.proto



<a name="aup-avaf-VideoStreamOptions"></a>

### VideoStreamOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| playback_fps | float |  |  |
| path | string |  |  |
| width | uint32 |  |  |
| height | uint32 |  |  |
| loop_over | bool |  |  |
| pool_size | uint32 |  |  |





 

 

 

 



## Scalar Value Types

| .proto Type | Notes | C++ | Java | Python | Go | C# | PHP | Ruby |
| ----------- | ----- | --- | ---- | ------ | -- | -- | --- | ---- |
| <a name="double" /> double |  | double | double | float | float64 | double | float | Float |
| <a name="float" /> float |  | float | float | float | float32 | float | float | Float |
| <a name="int32" /> int32 | Uses variable-length encoding. Inefficient for encoding negative numbers – if your field is likely to have negative values, use sint32 instead. | int32 | int | int | int32 | int | integer | Bignum or Fixnum (as required) |
| <a name="int64" /> int64 | Uses variable-length encoding. Inefficient for encoding negative numbers – if your field is likely to have negative values, use sint64 instead. | int64 | long | int/long | int64 | long | integer/string | Bignum |
| <a name="uint32" /> uint32 | Uses variable-length encoding. | uint32 | int | int/long | uint32 | uint | integer | Bignum or Fixnum (as required) |
| <a name="uint64" /> uint64 | Uses variable-length encoding. | uint64 | long | int/long | uint64 | ulong | integer/string | Bignum or Fixnum (as required) |
| <a name="sint32" /> sint32 | Uses variable-length encoding. Signed int value. These more efficiently encode negative numbers than regular int32s. | int32 | int | int | int32 | int | integer | Bignum or Fixnum (as required) |
| <a name="sint64" /> sint64 | Uses variable-length encoding. Signed int value. These more efficiently encode negative numbers than regular int64s. | int64 | long | int/long | int64 | long | integer/string | Bignum |
| <a name="fixed32" /> fixed32 | Always four bytes. More efficient than uint32 if values are often greater than 2^28. | uint32 | int | int | uint32 | uint | integer | Bignum or Fixnum (as required) |
| <a name="fixed64" /> fixed64 | Always eight bytes. More efficient than uint64 if values are often greater than 2^56. | uint64 | long | int/long | uint64 | ulong | integer/string | Bignum |
| <a name="sfixed32" /> sfixed32 | Always four bytes. | int32 | int | int | int32 | int | integer | Bignum or Fixnum (as required) |
| <a name="sfixed64" /> sfixed64 | Always eight bytes. | int64 | long | int/long | int64 | long | integer/string | Bignum |
| <a name="bool" /> bool |  | bool | boolean | boolean | bool | bool | boolean | TrueClass/FalseClass |
| <a name="string" /> string | A string must always contain UTF-8 encoded or 7-bit ASCII text. | string | String | str/unicode | string | string | string | String (UTF-8) |
| <a name="bytes" /> bytes | May contain any arbitrary sequence of bytes. | string | ByteString | str | []byte | ByteString | string | String (ASCII-8BIT) |

