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
- [aup/avap/apl\_people\_counting.proto](#aupavapapl_people_countingproto)
  - [AplPeopleCountingOptions](#aplpeoplecountingoptions)
- [aup/avap/apl\_person\_attribute.proto](#aupavapapl_person_attributeproto)
  - [AplPersonAttributeOptions](#aplpersonattributeoptions)
- [aup/avap/apl\_vehicle\_reid.proto](#aupavapapl_vehicle_reidproto)
  - [AplVehicleReIDOptions](#aplvehiclereidoptions)
  - [AplVehicleReIDOptions.HaltingAlertRectsEntry](#aplvehiclereidoptionshaltingalertrectsentry)
  - [AplVehicleReIDOptions.ParkingZoneEntry](#aplvehiclereidoptionsparkingzoneentry)
  - [AplVehicleReIDOptions.Rect](#aplvehiclereidoptionsrect)
  - [AplVehicleReIDOptions.Size](#aplvehiclereidoptionssize)
  - [AplVehicleReIDOptions.ViolationRoiEntry](#aplvehiclereidoptionsviolationroientry)
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
- [aup/avap/clip\_generator.proto](#aupavapclip_generatorproto)
  - [ClipGeneratorOptions](#clipgeneratoroptions)
- [aup/avap/codec\_type.proto](#aupavapcodec_typeproto)
  - [CodecType](#codectype)
- [aup/avap/empty.proto](#aupavapemptyproto)
  - [EmptyOptions](#emptyoptions)
- [aup/avap/epyc\_resnet.proto](#aupavapepyc_resnetproto)
  - [EpycResnetOptions](#epycresnetoptions)
- [aup/avap/event\_based\_recorder.proto](#aupavapevent_based_recorderproto)
  - [EventBasedRecorderOptions](#eventbasedrecorderoptions)
- [aup/avap/file\_saver.proto](#aupavapfile_saverproto)
  - [FileSaverOptions](#filesaveroptions)
  - [FileSaverOptions.Target](#filesaveroptionstarget)
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
- [aup/avap/host\_source\_sink.proto](#aupavaphost_source_sinkproto)
  - [HostSourceSinkOptions](#hostsourcesinkoptions)
- [aup/avap/image\_stream.proto](#aupavapimage_streamproto)
  - [ImageStreamOptions](#imagestreamoptions)
- [aup/avap/json\_stream.proto](#aupavapjson_streamproto)
  - [JsonStreamOptions](#jsonstreamoptions)
- [aup/avap/landmark\_predictor.proto](#aupavaplandmark_predictorproto)
  - [LandmarkPredictorOptions](#landmarkpredictoroptions)
- [aup/avap/notification\_message.proto](#aupavapnotification_messageproto)
  - [NotificationMessageOptions](#notificationmessageoptions)
  - [NotificationMessageOptions.Trigger](#notificationmessageoptionstrigger)
  - [NotificationMessageOptions.Trigger.ManualCrowdFlowOptions](#notificationmessageoptionstriggermanualcrowdflowoptions)
  - [NotificationMessageOptions.Trigger.ManualDetectOptions](#notificationmessageoptionstriggermanualdetectoptions)
  - [NotificationMessageOptions.Trigger.ManualTrackOptions](#notificationmessageoptionstriggermanualtrackoptions)
  - [NotificationMessageOptions.MessageType](#notificationmessageoptionsmessagetype)
  - [NotificationMessageOptions.Trigger.Type](#notificationmessageoptionstriggertype)
- [aup/avap/notification\_mongo.proto](#aupavapnotification_mongoproto)
  - [NotificationMongoOptions](#notificationmongooptions)
- [aup/avap/notification\_web.proto](#aupavapnotification_webproto)
  - [NotificationWebOptions](#notificationweboptions)
  - [NotificationWebOptions.ProtocolType](#notificationweboptionsprotocoltype)
- [aup/avap/packet\_simulator.proto](#aupavappacket_simulatorproto)
  - [PacketSimulatorOptions](#packetsimulatoroptions)
  - [PacketSimulatorOptions.AnyOptions](#packetsimulatoroptionsanyoptions)
  - [PacketSimulatorOptions.ClipGenOptions](#packetsimulatoroptionsclipgenoptions)
  - [PacketSimulatorOptions.OpMode](#packetsimulatoroptionsopmode)
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
- [aup/avap/to\_json.proto](#aupavapto_jsonproto)
  - [ToJsonOptions](#tojsonoptions)
- [aup/avap/v70\_dec.proto](#aupavapv70_decproto)
  - [V70DecodeOptions](#v70decodeoptions)
- [aup/avap/vcodec.proto](#aupavapvcodecproto)
  - [VideoCodecOptions](#videocodecoptions)
  - [VideoCodecOptions.Decoder](#videocodecoptionsdecoder)
  - [VideoCodecOptions.Encoder](#videocodecoptionsencoder)
- [aup/avap/vfilter.proto](#aupavapvfilterproto)
  - [VideoFilterOptions](#videofilteroptions)
- [aup/avap/video\_sink.proto](#aupavapvideo_sinkproto)
  - [VideoSinkOptions](#videosinkoptions)
- [aup/avap/video\_source.proto](#aupavapvideo_sourceproto)
  - [VideoSourceOptions](#videosourceoptions)
  - [VideoSourceOptions.SourceType](#videosourceoptionssourcetype)
- [Scalar Value Types](#scalar-value-types)



<a name="aup_avap_apl_common-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/apl_common.proto
This file defines common options for application calculators


<a name="aup-avaf-AplCommonOptions"></a>

### AplCommonOptions
Common options for application calculators


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| max_file_cache | [int32](#int32) |  | The maximum number of images saved in the task directory |
| debug | [bool](#bool) |  | If it runs in debug mode |
| draw | [bool](#bool) |  | If the node plots on the video stream |
| max_cluster_size | [int32](#int32) |  | The maximum number of frames of tracking history of a tracklet |
| border | [AplCommonOptions.Border](#aup-avaf-AplCommonOptions-Border) | repeated | The borders for specific applications |
| roi | [AplCommonOptions.Roi](#aup-avaf-AplCommonOptions-Roi) |  | The RoI for specific applications |
| notification_port | [int32](#int32) |  | the port of notification |






<a name="aup-avaf-AplCommonOptions-Border"></a>

### AplCommonOptions.Border
Represents a 2-D border


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| p1 | [AplCommonOptions.Point](#aup-avaf-AplCommonOptions-Point) |  | Starting point of the border |
| p2 | [AplCommonOptions.Point](#aup-avaf-AplCommonOptions-Point) |  | End point of the border |
| threshold | [float](#float) |  | The threshold for border crossing |






<a name="aup-avaf-AplCommonOptions-Point"></a>

### AplCommonOptions.Point
Represents a 2-D point


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| x | [int32](#int32) |  | Pixelwise x coordinate |
| y | [int32](#int32) |  | Pixelwise y coordinate |






<a name="aup-avaf-AplCommonOptions-Roi"></a>

### AplCommonOptions.Roi
Represents a 2-D region of interest (RoI)


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| point | [AplCommonOptions.Point](#aup-avaf-AplCommonOptions-Point) | repeated | Verteices |
| threshold | [float](#float) | repeated | Thresholds for the edges |





 

 

 

 



<a name="aup_avap_apl_crowd_flow-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/apl_crowd_flow.proto
The crowd flow calculator counts the number of objects moving across a given 
border or RoI.

Example:
```
node {
  name: "crowd_flow"
  calculator: "apl_crowd_flow"
  input_stream: "tracks_stream"
  input_stream: "image_stream_decode"
  input_stream: "video_stream_info_demux"
  input_stream: "detect_interval"
  output_stream: "image_stream_crowd_flow"
  stream_sync: {
    drop_strategy: DROP_INCOMPLETE_PACKETS
    timeout_ms: 0
  }
  node_options: {
    [type.googleapis.com/aup.avaf.AplCrowdFlowOptions]: {
      update_interval_seconds: 30
      initial_entering_count: 0
      initial_exiting_count: 0
      max_allowed_borders: 10
      use_roi: false
      common_fields: {
        max_file_cache: 100
        max_cluster_size: 100
        debug: false
        draw: true
        border: {
          p1: {
            x: 0
            y: 900
          }
          p2: {
            x: 1920
            y: 900
          }
          threshold: 0.055
        }
      }
    }
  }
}
```


<a name="aup-avaf-AplCrowdFlowOptions"></a>

### AplCrowdFlowOptions
Options for the crowd flow calculator


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| common_fields | [AplCommonOptions](#aup-avaf-AplCommonOptions) |  | __**REQUIRED**__. At least one border (2 points) or RoI (3 points) should be defined in the common_fields. General application config parameters |
| update_interval_seconds | [int32](#int32) |  | __**REQUIRED**__. The expected value range is &gt; 0. The interval length in terms of seconds for information update and sending notification |
| initial_entering_count | [int32](#int32) |  | The initial count for entering people |
| initial_exiting_count | [int32](#int32) |  | The initial count for exiting people |
| max_allowed_borders | [int32](#int32) |  | The maximum number of borders |
| default_border_crossing_th | [float](#float) |  | The default crossing threshold for all the borders |
| use_roi | [bool](#bool) |  | If use the RoI for crowd flow statistics instead of the borders |





 

 

 

 



<a name="aup_avap_apl_people_counting-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/apl_people_counting.proto
This file defines options for the people counting calculator


<a name="aup-avaf-AplPeopleCountingOptions"></a>

### AplPeopleCountingOptions
Options for the people counting calculator


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| common_fields | [AplCommonOptions](#aup-avaf-AplCommonOptions) |  | Common options of a application calculator |
| aggregation_threshold | [int32](#int32) |  | When there are more people inside the RoI than this threshold, the calculator will notify for aggregation if sudden_change_by_count is set to true. |
| sudden_change_by_count | [bool](#bool) |  | If use the count of people inside the RoI to decide the sudden change status |
| dispersion_threshold | [int32](#int32) |  | When the count of people inside the RoI is less than the one sudden_change_len_in_sec ago by a number more than this threshold, the calculator will notify for dispersion if sudden_change_by_count is set to true. |
| sudden_change_threshold | [float](#float) |  | The threshold for sudden change decision if sudden_change_by_count is set to false |
| update_interval_seconds | [int32](#int32) |  | The interval length in terms of seconds for sending notification |
| sudden_change_len_in_sec | [int32](#int32) |  | The time window length in terms of seconds to decide if there is aggregation of dispersion |





 

 

 

 



<a name="aup_avap_apl_person_attribute-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/apl_person_attribute.proto
This file defines options for the person attribute calculator


<a name="aup-avaf-AplPersonAttributeOptions"></a>

### AplPersonAttributeOptions
Options for the person attribute calculator


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| common_fields | [AplCommonOptions](#aup-avaf-AplCommonOptions) |  | Common options of a application calculator |
| person_cloth_color_conf_th | [float](#float) |  | The confidence threshold for person cloth color classification |
| person_attrib_color_output_mean_th | [float](#float) |  | The threshold of average confidence value for the calcultor to decide the cloth color |
| person_color_attrib_confident_min_sample_size | [int32](#int32) |  | The minimum sample size for a confident color attribute result |
| tracklet_reporting_interval_in_sec | [int32](#int32) |  | The interval length in terms of seconds for sending notification of alive tracklets |





 

 

 

 



<a name="aup_avap_apl_vehicle_reid-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/apl_vehicle_reid.proto
This file defines options for the vehicle ReID calculator


<a name="aup-avaf-AplVehicleReIDOptions"></a>

### AplVehicleReIDOptions
Options for the vehicle ReID calculator


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| common_fields | [AplCommonOptions](#aup-avaf-AplCommonOptions) |  | Common options of a application calculator |
| clean_plot | [bool](#bool) |  | If it’s set to true, the pipeline will draw less information for demo purposes. The default value is false. |
| save_gallery | [bool](#bool) |  | If save tracklet images to the task directory for debugging purposes |
| traffic_vehicle_plate_vehicle_rotation | [float](#float) |  | The angular degree of counterclockwise rotation for each vehicle detection before running LPR. |
| traffic_plate_confidence_threshold | [float](#float) |  | A plate detected with a confidence score below this threshold will be rejected. The recognized result with an average score below this threshold will be set to NOTREAD. |
| traffic_plate_area_threshold | [uint32](#uint32) |  | If a detected plate has less pixels than this threshold, it will be rejected. |
| traffic_vehicle_plate_recognizer_from_xilinx | [bool](#bool) |  | If it’s set to true, the plate recognition model from Xilinx (for Chinese LPR) will be used. Otherwise, the one from Aupera will be used. |
| traffic_vehicle_plate_detector_skip | [bool](#bool) |  | If it’s set to true, the plate_lib expects the input image as cropped plate instead of cropped vehicles, so that the detection phase will be skipped. |
| traffic_plate_checksum_verification | [bool](#bool) |  | If it’s set to true, the plate_lib will assume the plate to be a Singaporean or Malaysian plat and check the checksum of the recognized plate number. |
| traffic_plate_run_preprocessing | [bool](#bool) |  | If it’s set to true, the plate_lib will preprocess the incoming image. |
| traffic_vehicle_plate_detector_from_xilinx | [bool](#bool) |  | If it’s set to true, the plate detection model from Xilinx (for Chinese LPR) will be used. Otherwise, the one from Aupera will be used |
| traffic_vehicle_plate_plausible_results_only | [bool](#bool) |  | If the plate lib will only return LPR numbers that match the Malaysian or Singaporean format. Note that the traffic_plate_checksum_verification must also be set to `true` in this case. |
| traffic_get_attributes | [bool](#bool) |  | If it’s set to true, the pipeline will run LPR on tracked vehicles |
| traffic_vehicle_plate_update_with_area | [bool](#bool) |  | If it’s set to true, it assumes that the larger a detected plate box, the more credible the LPR result, so it will ignore new results with a smaller average plate area. |
| traffic_verified_plate_selction_criteria | [string](#string) |  | It specifies that based on which criteria a verified plate will be selected as the final LPR result. "default": Using the comparison algorithm provided in the plate_lib by comparing the readings. "mode": The verified plate number that got recognized for the most times will be selected. This is the most recommended way for now. "mean_conf": The verified plate number that got recognized with the highest average confidence will be selected. "max_conf": The verified plate number that got recognized with the highest confidence will be selected. |
| traffic_plate_update_threshold | [int32](#int32) |  | If the Levenshtein distance between the incoming verified plate and the previous one is smaller or equal to this threshold, the pipeline will pick the best one from all verified candidates. Otherwise, the incoming one is assumed to be the plate of another vehicle and gets ignored. The recommended value is 8. |
| traffic_plate_min_history | [uint32](#uint32) |  | The minimum number of recognized plate number before we pick the most frequent one as the plate number of a tracklet. |
| traffic_vehicle_pad_plate_bbox | [AplVehicleReIDOptions.Size](#aup-avaf-AplVehicleReIDOptions-Size) |  | The rectangle size for padding the detected license plate for cropping if the model in the box_detector node is set as a plate detector. |
| traffic_plate_cluster_distance_threshold | [uint32](#uint32) |  | A verified plate is only eligible for the final result when it's there are similar plates (Levenshtein distance &lt;= traffic_plate_cluster_distance_threshold) recognized. The suggested value is 3. |
| traffic_plate_min_count | [uint32](#uint32) |  | A verified plate is only eligible for the final result when it's recognized at least traffic_plate_min_count times, The suggested value is 2. |
| traffic_class_min_history | [uint32](#uint32) |  | The pipeline will decide the class of a tracklet after this number of detections. |
| traffic_check_plate_detection_in_parking_zone | [bool](#bool) |  | When set to 'true', the pipeline considers the presence and location of the plate detection in relation to the parking zone when determining the validity of the vehicle detection. This parameter is used to assist in the filtering of false positive vehicle detections occurring within the RoI. |
| object_movement_iou_threshold | [float](#float) |  | Only when the IoU of a detected objects and the matching tracklet below this threshold, it will be encoded. |
| traffic_parking_alert_alarm_time_in_sec | [float](#float) |  | If a tracked vehicle stays in the parking violation zone more than this time, a notification will be sent. |
| traffic_parking_zone_notify_time_in_sec | [float](#float) |  | A vehicle is considered parked in a parking zone if it's constantly detected inside it for at least that long after it's inside the parking zone for `alarm_clear_frame_delay` frames consecutively. |
| tracklet_reporting_interval_in_sec | [float](#float) |  | LPR notification of the alive tracklets will be sent for every specified interval. |
| alarm_clear_frame_delay | [float](#float) |  | The number of consecutive frames for considering a vehicle's parking status change |
| halting_alert_len_in_sec | [float](#float) |  | If a tracked vehicle stays in a parking zone with a low average liveness value for this period of time, it will be considered as halting |
| active_alert_len_in_sec | [float](#float) |  | If a halted vehicle stays in a parking zone with a high average liveness value for this period of time, it will be considered as active. |
| owner_left_alert_len_in_sec | [float](#float) |  | If a halted vehicle stays in a parking zone with a low average liveness value for this period of time, it will be considered as its owner has been left. |
| mse_liveliness_threshold | [float](#float) |  | A threshold below which the MSE liveliness will be set to 0.0. |
| avg_active_threshold | [float](#float) |  | If the vehicle is halted in a parking zone associated with a halting rectangle for more than a specific time (ctive_alert_len_in_sec), and the average liveliness is above this threshold, then the vehicle will be marked as halting. |
| avg_halting_threshold | [float](#float) |  | If the vehicle is parked in a parking zone associated with a halting rectangle for more than a specific time (halting_alert_len_in_sec), and the average liveliness is below this threshold, then the vehicle will be marked as halting. |
| halting_alert_rects | [AplVehicleReIDOptions.HaltingAlertRectsEntry](#aup-avaf-AplVehicleReIDOptions-HaltingAlertRectsEntry) | repeated | A dictionary configuring the frame regions that correspond to the parking zones. The key is the parking zone index, and the value is a Rect |
| manager_roi | [AplCommonOptions.Roi](#aup-avaf-AplCommonOptions-Roi) |  | A polygon region inside the RoI. The encoding of the tracklets inside the manager RoI will be updated. For LPR usage, it’s recommended to be set to the same as the RoI. |
| violation_roi | [AplVehicleReIDOptions.ViolationRoiEntry](#aup-avaf-AplVehicleReIDOptions-ViolationRoiEntry) | repeated | Polygon regions where a vehicle will trigger parking alert notification if it stays longer than traffic_parking_alert_alarm_time_in_sec |
| parking_zone | [AplVehicleReIDOptions.ParkingZoneEntry](#aup-avaf-AplVehicleReIDOptions-ParkingZoneEntry) | repeated | Polygon regions where a vehicle will be considered as parked if it stays longer than traffic_parking_zone_notify_time_in_sec |
| traffic_encoder_kernel | [string](#string) |  | The kernel name of the vehicle encoder model |
| traffic_encoder_model | [string](#string) |  | The type of the encoder model. |
| enable_encoding | [bool](#bool) |  | If ti’s set to true, the pipeline will encode the tracked vehicles inside the manager RoI for tracking and reidntification across cameras. The default value is true. For single camera using (LPR and VIP parking) and ReID-lite, it’s set to false for better runtime performance. |
| max_camera_avg_enc_objs | [uint32](#uint32) |  | The maximum number of detected objects that are used for calculating the average camera encoding. |
| cam_avg_enc_update_sim_th | [float](#float) |  | The average encoding will be updated is the cosing similarity between the previous one and the latest one. |
| want_cam_avg_enc | [bool](#bool) |  | If it’s set to true, the average camera encoding will be calculated. |
| traffic_plate_detection_or_violation_roi_only | [bool](#bool) |  | If it’s set to true, LPR will only be applied to the vehicles inside the detection RoI or a violation RoI to avoid low-quality results from distant detections. It’s recommended to set it to true for LPR. |
| traffic_only_send_new_image | [bool](#bool) |  | If it’s set to true, the pipeline will only send the cropped image of the tracklet in the message if it’s not sent before to save the bandwidth. It’s recommended to set it to true for LPR when the reporting interval is small. |
| traffic_only_notify_vehicle_with_LP | [bool](#bool) |  | If it’s set to true, tracklets without an LPR number will not be notified. It’s recommended to set it to true for LPR and VIP parking to avoid irrelevant detections. |
| traffic_notify_reporting_interval | [bool](#bool) |  | When it is set to false, the message "REPORTING_INTERVAL" is disabled. T |
| traffic_update_image_mode | [string](#string) |  | a. if it's specified as "plate", the images will be updated in the following way as before: If the LPR of a tracklet has not been unverified, the image is updated when it gets a reading with a higher confidence. If the LPR of a tracklet is verified for the first time, the image is initialized with the current crop. If the LPR of a tracklet has been verified, the image is updated when its LPR gets updated or the same reading gets one with higher confidence. b. If it's specified as "parking", the images will be updated when the tracklet's halting status changes from or to HaltingStatus::NA, indicating that it enters or exits a parking zone. c. if it's specified as `"detection"`, the images will be updated when the tracklet has higher detection confidence as in the vehicle ReID scenario |
| send_mlops_notifications | [bool](#bool) |  | If we also send MLOps notifications |
| save_eval_results | [bool](#bool) |  | If it’s set to true, the pipeline will save the tracking results to a pred.txt for evaluation purposes. |
| camera_id | [uint32](#uint32) |  | The camera ID of the video stream. |
| traffic_track_in_parking_zone | [bool](#bool) |  | If set to `true`, the pipeline wilk match detections inside a parking zone for using the scenario of VIP parking. |
| setup_base_assets_sleep_insec | [int32](#int32) |  | The sleeping time for initialization |
| want_tracklet_curve_fitting | [bool](#bool) |  | If it’s set to true, a curve will be fit based on the trajectory of the tracklet. |
| trajectory_min_points | [uint32](#uint32) |  | The minimum number of points for curve fitting. |
| trajectory_poly | [uint32](#uint32) |  | The poly nomial order of the fitted curve. |
| curve_fitting_method | [string](#string) |  | The form of the curve. If it’s set to “parametric” (default), the curve will be represented in the form of y=f(x). If it’s set to “implicit”, the curve will be represented in the form of f(x,y) = 0 |
| curve_fitting_var | [string](#string) |  | The variables in the curve. If it’s set to “xy” (default), only the coordinates will be used to fit the curve If it’s set to “xyt”, the time will also be used to fit the curve |
| homography_file | [string](#string) |  | The path to the homography file. If the file exists, the pipeline will load the homography matrix from the file so that the fitted curve is in the converted coordnate system (e.g. GPS). |
| vehicle_color_classifier_model | [string](#string) |  | The kernel name of the vehicle color classicifation model if it's not an empty string. |
| vehicle_make_classifier_model | [string](#string) |  | The kernel name of the vehicle make classicifation model if it's not an empty string. |
| vehicle_type_classifier_model | [string](#string) |  | The kernel name of the vehicle type classicifation model if it's not an empty string. |






<a name="aup-avaf-AplVehicleReIDOptions-HaltingAlertRectsEntry"></a>

### AplVehicleReIDOptions.HaltingAlertRectsEntry



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| key | [int32](#int32) |  |  |
| value | [AplVehicleReIDOptions.Rect](#aup-avaf-AplVehicleReIDOptions-Rect) |  |  |






<a name="aup-avaf-AplVehicleReIDOptions-ParkingZoneEntry"></a>

### AplVehicleReIDOptions.ParkingZoneEntry



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| key | [int32](#int32) |  |  |
| value | [AplCommonOptions.Roi](#aup-avaf-AplCommonOptions-Roi) |  |  |






<a name="aup-avaf-AplVehicleReIDOptions-Rect"></a>

### AplVehicleReIDOptions.Rect
Represents a rectangle


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| x | [int32](#int32) |  | Pixelwise x coordinate of the top-left corner |
| y | [int32](#int32) |  | Pixelwise y coordinate of the top-left corner |
| w | [int32](#int32) |  | Pixelwise width of the rectangle |
| h | [int32](#int32) |  | Pixelwise height of the rectangle |






<a name="aup-avaf-AplVehicleReIDOptions-Size"></a>

### AplVehicleReIDOptions.Size
Represents the size of a rectangle


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| w | [int32](#int32) |  | Pixelwise width of the rectangle |
| h | [int32](#int32) |  | Pixelwise height of the rectangle |






<a name="aup-avaf-AplVehicleReIDOptions-ViolationRoiEntry"></a>

### AplVehicleReIDOptions.ViolationRoiEntry



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| key | [int32](#int32) |  |  |
| value | [AplCommonOptions.Roi](#aup-avaf-AplCommonOptions-Roi) |  |  |





 

 

 

 



<a name="aup_avap_box_classifier-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/box_classifier.proto
The box_classifier calculator classifies input images or detected objects.

Example:
```
node {
 name: "classifier"
 calculator: "box_classifier"
 input_stream: "image_stream_decode"
 output_stream: "classification_stream"
 ml_model_kernel_name: "resnet18"
 node_options: {
   [type.googleapis.com/aup.avaf.BoxClassifierOptions]: {
     classifier_type: "General"
     need_preprocess: true
     run_on_letterboxed_img: false
     batch_size: 8
     return_in_order: true
     classification_threads: 1
     batch_collection_timeout_ms: 0
     use_detections: false
     log_performance: false
     max_classification_lib_q_size: 200
   }
 }
}
```


<a name="aup-avaf-BoxClassifierOptions"></a>

### BoxClassifierOptions
BoxClassifierOptions defines configuration parameters for the Box Classifier.
It allows specifying classifier type, preprocessing needs, batch processing parameters,
and performance logging options.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| classifier_type | [string](#string) |  | _**REQUIRED**_. The expected value is "General". The type of classifier to use. |
| need_preprocess | [bool](#bool) |  | Indicates if preprocessing is required before classification. |
| run_on_letterboxed_img | [bool](#bool) |  | Specifies if the classifier should run on letterboxed images. |
| batch_size | [int32](#int32) |  | The size of batches for classification. Larger batches may increase performance but require more memory. |
| return_in_order | [bool](#bool) |  | Determines if the classification results should be returned in the order they were received. |
| classification_threads | [int32](#int32) |  | The number of threads dedicated to classification tasks. |
| force_batch_size | [bool](#bool) |  | Forces the classifier to wait for a full batch before processing. |
| batch_collection_timeout_ms | [uint64](#uint64) |  | The maximum time in milliseconds to wait for a full batch before processing. |
| use_detections | [bool](#bool) |  | If true, uses detection results as input for classification, otherwise uses raw images. |
| log_performance | [bool](#bool) |  | Enables logging of performance metrics, this will print on the termianl screen. |
| max_classification_lib_q_size | [int32](#int32) |  | The maximum size of the classification library's queue. |
| max_frame_cache_size | [int32](#int32) |  | The maximum size of the frame cache. Helps manage memory usage. |





 

 

 

 



<a name="aup_avap_box_detector-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/box_detector.proto
The BoxDetectorOptions defines configuration parameters for the Box Detector.
It includes preprocessing options such as mean subtraction and scale multiplications,
and detection specifics like interval, type, preprocessing necessity, and model specifics.

Example:
```
node {
  name: "detector"
  calculator: "box_detector"
  input_stream: "image_stream_decode"
  output_stream: "detections_stream"
  output_stream: "detect_interval"
  ml_model_kernel_name: "densebox_320_320"
  node_options: {
    [type.googleapis.com/aup.avaf.BoxDetectorOptions]: {
      detect_interval: 1
      detector_type: "FaceDetectDenseBox"
      need_preprocess: true
      log_performance: false
      run_on_letterboxed_img: false
      batch_size: 1
      return_frames_inorder: true
      batch_collection_timeout_ms: 0
      ignore_black_frames: false
      max_detection_lib_q_size: 30
      total_classes: 2
      default_confidence_threshold: 0.9
      mean: {
        r: 128.0
        g: 128.0
        b: 128.0
      }
      scale: {
        ch1: 1.0
        ch2: 1.0
        ch3: 1.0
      }
    }
  }
}
```


<a name="aup-avaf-BoxDetectorOptions"></a>

### BoxDetectorOptions
OBoxDetectorOptionsptions for detector calculator mean substraction


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| detect_interval | [int32](#int32) |  | _**REQUIRED**_. The expected value range is &gt; 0. Interval between detections. |
| detector_type | [string](#string) |  | _**REQUIRED**_. The expected value should be one of: "SSD","YoloV2","YoloV3","YoloVX","TinyYolo","OFAYolo", "RefineDet", "FaceDetectDenseBox", and "EfficientDetD2".Type of the detection model. |
| obfuscated_token | [string](#string) |  | Token for obfuscation purposes, unused. |
| need_preprocess | [bool](#bool) |  | Indicates if preprocessing is needed. This is false if the user is passing preprocessed images |
| mean | [BoxDetectorOptions.Mean](#aup-avaf-BoxDetectorOptions-Mean) |  | Mean values for preprocessing. (Optional as typically this is available in model prototxt) |
| scale | [BoxDetectorOptions.Scale](#aup-avaf-BoxDetectorOptions-Scale) |  | Scale values for preprocessing. |
| label_confidence | [BoxDetectorOptions.LabelConfidence](#aup-avaf-BoxDetectorOptions-LabelConfidence) | repeated | Specific label confidence thresholds. This is to filter all the objects in the scene except the ones provide by this value. You can provide one or more pairs of label/confidence if at least one label_confidence is provided, total classes and default_confidence_threshold is ignored This means that the detector only considers the labels that label_confidence provide if there is no label_confidence defined, then detector will use total_classes and default_confidence_thresh if no label_confidence is defined and total_classes=0, then an error will be returned |
| total_classes | [uint32](#uint32) |  | Total number of classes. It will be ignored if label_confidence is provided. Otherwise, it's REQUIRED, and its expected value range is &gt; 0. |
| default_confidence_threshold | [float](#float) |  | The default value is set to default confidence threshold. It is REQUIRED if label_confidence is not provided and its expected value range is (0, 1). |
| inter_class_nms | [BoxDetectorOptions.InterClassNms](#aup-avaf-BoxDetectorOptions-InterClassNms) | repeated | Settings for inter-class NMS. |
| run_on_letterboxed_img | [bool](#bool) |  | Whether to run detection on letterboxed images. This means resizing by keeping the original aspect ratio and black padding the image |
| batch_size | [int32](#int32) |  | Batch size for detection. |
| return_frames_inorder | [bool](#bool) |  | Whether to return frames in order. |
| detection_threads | [int32](#int32) |  | Number of threads for detection. |
| force_batch_size | [bool](#bool) |  | Forces the batch size, even if smaller batches are available, waits until batch size is reached. |
| batch_collection_timeout_ms | [int32](#int32) |  | Timeout for collecting a batch in milliseconds. |
| ignore_black_frames | [bool](#bool) |  | Whether to ignore black frames. |
| log_performance | [bool](#bool) |  | Enables logging of performance metrics. |
| log_info | [bool](#bool) |  | Enables logging of informational messages. |
| max_detection_lib_q_size | [int32](#int32) |  | Maximum queue size for the detection library. |
| roi | [BoxDetectorOptions.Roi](#aup-avaf-BoxDetectorOptions-Roi) |  | Region of Interest for detection. |
| crop_region | [BoxDetectorOptions.Rect](#aup-avaf-BoxDetectorOptions-Rect) |  | Specifies a region to crop for detection. |
| center_crop_w_roi | [bool](#bool) |  | Indicates whether to center crop using RoI. |
| crop_mode | [string](#string) |  | Specifies the cropping mode ("default", "letterbox", "stretch"). |






<a name="aup-avaf-BoxDetectorOptions-InterClassNms"></a>

### BoxDetectorOptions.InterClassNms
InterClassNms a type specifies Non-Maximum Suppression (NMS) settings for between classes.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| threshold | [float](#float) |  | NMS threshold. |
| labels | [int32](#int32) | repeated | Labels to apply NMS. |






<a name="aup-avaf-BoxDetectorOptions-LabelConfidence"></a>

### BoxDetectorOptions.LabelConfidence
LabelConfidence is a type that maps a label with its confidence threshold.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| label | [int32](#int32) |  | The class label. |
| confidence | [float](#float) |  | The confidence threshold for the label. |






<a name="aup-avaf-BoxDetectorOptions-Mean"></a>

### BoxDetectorOptions.Mean
Represents a mean value for subtraction based on your model for preprocessing


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| r | [float](#float) |  | Red component of color, range 0-1. |
| g | [float](#float) |  | Green component of color, range 0-1. |
| b | [float](#float) |  | Blue component of color, range 0-1. |






<a name="aup-avaf-BoxDetectorOptions-Point"></a>

### BoxDetectorOptions.Point
Point is a type that defines a point in 2D space.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| x | [int32](#int32) |  | X coordinate. |
| y | [int32](#int32) |  | Y coordinate. |






<a name="aup-avaf-BoxDetectorOptions-Rect"></a>

### BoxDetectorOptions.Rect
Rect is a type defines a rectangle using top-left coordinates, width, and height.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| x | [int32](#int32) |  | Top-left X coordinate. |
| y | [int32](#int32) |  | Top-left Y coordinate. |
| w | [int32](#int32) |  | Width of the rectangle. |
| h | [int32](#int32) |  | Height of the rectangle. |






<a name="aup-avaf-BoxDetectorOptions-Roi"></a>

### BoxDetectorOptions.Roi
Roi is a Type defines a Region of Interest (RoI) using points and thresholds.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| point | [BoxDetectorOptions.Point](#aup-avaf-BoxDetectorOptions-Point) | repeated | Points defining the RoI polygon. |
| threshold | [float](#float) | repeated | Thresholds for the RoI, unused in this context. |






<a name="aup-avaf-BoxDetectorOptions-Scale"></a>

### BoxDetectorOptions.Scale
Represents a Scale multipier value for based on your model


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| ch1 | [float](#float) |  | Multiplier for the first channel. |
| ch2 | [float](#float) |  | Multiplier for the second channel. |
| ch3 | [float](#float) |  | Multiplier for the third channel |





 

 

 

 



<a name="aup_avap_box_segmentor-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/box_segmentor.proto
The box_segmentor calculator generates semantic segmentation of input images.

Example:
```
node {
  name: "segmentor"
  calculator: "box_segmentor"
  input_stream: "image_stream_decode"
  output_stream: "segmentation_stream"
  ml_model_kernel_name: "fpn"
  node_options: {
    [type.googleapis.com/aup.avaf.BoxSegmentorOptions]: {
      segmentor_type: "Segmentation2D"
      need_preprocess: true
      log_performance: false
      log_info: false
      run_on_letterboxed_img: false
      batch_size: 8
      force_batch_size: false
      return_frames_inorder: true
      segmentation_threads: 1
      batch_collection_timeout_ms: 0
      ignore_black_frames: false
      max_segmentation_lib_q_size: 30
      resizing: true
      interpolation_flag: 0
    }
  }
}
```


<a name="aup-avaf-BoxSegmentorOptions"></a>

### BoxSegmentorOptions
BoxSegmentorOptions configures the box segmentor with various operational parameters. This includes options for selecting the segmentor type, managing preprocessing, handling input images, setting batch sizes, and configuring performance logging.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| segmentor_type | [string](#string) |  | _**REQUIRED**_. The expected value is either "Segmentation2D" or "Solo". Specifies the type of segmentor to use. |
| need_preprocess | [bool](#bool) |  | Indicates if input images require preprocessing before segmentation. |
| run_on_letterboxed_img | [bool](#bool) |  | If true, processes letterboxed images to maintain aspect ratio. |
| batch_size | [int32](#int32) |  | Determines the number of images to process in a single batch. |
| return_frames_inorder | [bool](#bool) |  | If true, ensures output frames are returned in the order they were received. |
| segmentation_threads | [int32](#int32) |  | Number of threads allocated for segmentation tasks. |
| force_batch_size | [bool](#bool) |  | Forces the segmentor to wait for a full batch before processing. |
| batch_collection_timeout_ms | [uint64](#uint64) |  | Maximum time in milliseconds to wait for a full batch. |
| ignore_black_frames | [bool](#bool) |  | If true, ignores frames that are predominantly black. |
| log_performance | [bool](#bool) |  | Enables logging of performance metrics. |
| log_info | [bool](#bool) |  | Enables logging of informational messages. |
| max_segmentation_lib_q_size | [int32](#int32) |  | Maximum queue size for the segmentation library. |
| resizing | [bool](#bool) |  | Indicates if resizing is applied to the input images. |
| interpolation_flag | [int32](#int32) |  | Specifies the interpolation method used for resizing. |
| solo_score_thr | [float](#float) |  | Threshold for solo segmentation score to filter results. |





 

 

 

 



<a name="aup_avap_box_tracker-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/box_tracker.proto
The tracker calculator that tracks objests from detection inputs. 
It initializes and updates tracked objects using either SORT&#43;&#43; or DEEPSORT algorithm. 

Example:
```
 node {
   name: "tracker"
   calculator: "box_tracker"
   input_stream: "detection_stream"
   input_stream: "detect_interval"
   output_stream: "tracks_stream"
   node_options: {
     [type.googleapis.com/aup.avaf.BoxTrackerOptions]: {
       max_keep_alive: 5
       min_hits: 1
       affinity_threshold: 0.008  
       shape_weight: 1
       position_weight: 1
       appearance_weight: 1
       shape_dist_max: 1
       position_dist_max: 1
       use_exp_cost: true
       tracker_type: "SORT&#43;&#43;"
       min_object_area_th: 200
     }
   }
 }
```


<a name="aup-avaf-BoxTrackerOptions"></a>

### BoxTrackerOptions
Options for the tracker calculator


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| max_keep_alive | [int32](#int32) |  | _**REQUIRED**_. The expected value range is &gt;= 0. The max detect_interval used to keep the track alive |
| min_hits | [int32](#int32) |  | _**REQUIRED**_. The expected value is 1. The minimum number of detections for initializing tracking |
| min_object_area_th | [int32](#int32) |  | Ignore detections smaller than this area threshold |
| affinity_threshold | [double](#double) |  | _**REQUIRED**_. The expected value range is [0, 1). The affinity threshold between detections and tracklets |
| shape_weight | [float](#float) |  | _**REQUIRED**_. The expected value range is &gt;= 0. The weight of shape cost between a detection rectengle and a traclet |
| position_weight | [float](#float) |  | _**REQUIRED**_. The expected value range is &gt;= 0. The weight of position cost between a detection rectengle and a traclet |
| appearance_weight | [float](#float) |  | _**REQUIRED**_. The expected value range is &gt;= 0. The weight of appearanr cost between a detection and a traclet |
| shape_dist_max | [float](#float) |  | _**REQUIRED**_. The expected value range is &gt; 0. The maximum value of the shape cost |
| position_dist_max | [float](#float) |  | _**REQUIRED**_. The expected value range is &gt; 0. The maximum value of the position cost |
| use_exp_cost | [bool](#bool) |  | If use the exponential formula to calculate the matching cost |
| disable_tracker_update | [bool](#bool) |  | If disable the kalman filter to predict tracklet bounding boxes |
| tracker_type | [string](#string) |  | _**REQUIRED**_. The expected value is either "SORT&#43;&#43;" or "DEEPSORT". The tracker type |
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
The visualizer calculator displays bounding boxes and classification results in the image. 
It can take detection results, classification results, segmentation results, and landmark results.

Example with detections:
```
 node {
   name: "visualizer"
   calculator: "box_visualizer"
   input_stream: "detections_stream"
   input_stream: "image_stream_decode"
   output_stream: "image_stream_viz"
   stream_sync: {
     drop_strategy: DROP_INCOMPLETE_PACKETS
     timeout_ms: 5000
   }
   node_options: {
     [type.googleapis.com/aup.avaf.BoxVisualizerOptions]: {
       input_type: INPUT_TYPE_DETECTION
       # enum InputType {
       #   INPUT_TYPE_DETECTION = 0; // Visualize object detection bounding boxes.
       #   INPUT_TYPE_CLASSIFICATION = 1; // Visualize classification results.
       #   INPUT_TYPE_SEGMENTATION = 2; // Visualize segmentation maps.
       #   INPUT_TYPE_LANDMARK = 3; // Visualize landmarks
       # }
       text_color: {
         r: 255
         g: 0
         b: 0
       }
       box_color: {
         r: 255
         g: 0
         b: 0
       }
       class_color: {
         label: 1
         color: {
           r: 0
           g: 255
           b: 0
         }
       }
       default_class_color: {
           r: 0
           g: 0
           b: 0
       }
       text_offset: {
         x: 0
         y: 0
       }
       font: 0 
       font_scale: 0.6
       font_thickness: 2
       line_type: 0
       box_thickness: 2
       text_size: 2
       label_name_file: ""
       overlay_opacity: 0.5
     }
   }
 }
```
Example with classifications:
```
 node {
   name: "visualizer"
   calculator: "box_visualizer"
   input_stream: "classification_stream"
   input_stream: "image_stream_decode"
   output_stream: "image_stream_viz"
   stream_sync: {
     drop_strategy: DROP_INCOMPLETE_PACKETS
     timeout_ms: 5000
   }
   node_options: {
     [type.googleapis.com/aup.avaf.BoxVisualizerOptions] {
       input_type: INPUT_TYPE_CLASSIFICATION
       text_color: {
         r: 255
         g: 0
         b: 0
       }
       text_offset: {
         x: 0
         y: 0
       }
       font_thickness: 4
       font_scale: 1.4
       font: 0
       line_type: 0
     }
   }
 }
```
Example with segmentations:
```
 node {
   name: "visualizer"
   calculator: "box_visualizer"
   input_stream: "segmentation_stream"
   input_stream: "image_stream_decode"
   output_stream: "image_stream_viz"
   stream_sync: {
     drop_strategy: DROP_INCOMPLETE_PACKETS
     timeout_ms: 5000
   }
   node_options: {
     [type.googleapis.com/aup.avaf.BoxVisualizerOptions]: {
       input_type: INPUT_TYPE_SEGMENTATION
       overlay_opacity: 0.5
     }
   }
 }
```


<a name="aup-avaf-BoxVisualizerOptions"></a>

### BoxVisualizerOptions
BoxVisualizerOptions configures the visual aspects of bounding boxes and classifications on video frames.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| input_type | [BoxVisualizerOptions.InputType](#aup-avaf-BoxVisualizerOptions-InputType) |  | Defines the type of input to be visualized. |
| text_color | [BoxVisualizerOptions.Color](#aup-avaf-BoxVisualizerOptions-Color) |  | Color for text (class names, labels). |
| box_color | [BoxVisualizerOptions.Color](#aup-avaf-BoxVisualizerOptions-Color) |  | Color for bounding box. |
| class_color | [BoxVisualizerOptions.ClassColor](#aup-avaf-BoxVisualizerOptions-ClassColor) | repeated | Specific colors for different classes. |
| default_class_color | [BoxVisualizerOptions.Color](#aup-avaf-BoxVisualizerOptions-Color) |  | Default color for classes without a specified ClassColor. |
| text_offset | [BoxVisualizerOptions.Offset](#aup-avaf-BoxVisualizerOptions-Offset) |  | Position offset for the text from the top left corner of the bounding box. |
| box_thickness | [int32](#int32) |  | Thickness of the bounding box lines. |
| text_size | [int32](#int32) |  | Size of the text. |
| font | [int32](#int32) |  | Font type of the text. |
| font_scale | [double](#double) |  | Scale of the font used for text. |
| font_thickness | [int32](#int32) |  | Thickness of the font. |
| line_type | [int32](#int32) |  | The type of the line used for drawing boxes and text. |
| label_name_file | [string](#string) |  | Path to file containing label names for classes. |
| overlay_opacity | [float](#float) |  | Opacity of the overlay on the video frame. |
| connect_landmarks | [bool](#bool) |  | When set to true, this feature is activated for Movenet, Hourglass, and Openpose models where it connects detected landmark points in a predefined order. |
| apply_filter_on_landmarks | [string](#string) |  | Option for application of various filters (options include "mask", "bbox", "hat") on a detected face landmark |
| arm_raise_check | [string](#string) |  | Supplementary feature for apply_filter_on_landmarks in conjunction with human pose estimators (options include "angles" and "height" to determine if an arm is raised), which applies the filter to the face if either or both arms are detected as raised. |
| render_on_nv12 | [bool](#bool) |  | Is rendering done on NV12 image |
| ttf_file_path_for_nv12 | [string](#string) |  | file path to true type font file |






<a name="aup-avaf-BoxVisualizerOptions-ClassColor"></a>

### BoxVisualizerOptions.ClassColor
ClassColor associates a Color with a class label for differentiated visualization.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| color | [BoxVisualizerOptions.Color](#aup-avaf-BoxVisualizerOptions-Color) |  | The color to use for the class label. |
| label | [int32](#int32) |  | The label id corresponding to a class. |






<a name="aup-avaf-BoxVisualizerOptions-Color"></a>

### BoxVisualizerOptions.Color
Color defines the RGB color components with floating-point numbers.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| r | [float](#float) |  | Red component of color, range 0-1. |
| g | [float](#float) |  | Green component of color, range 0-1. |
| b | [float](#float) |  | Blue component of color, range 0-1. |






<a name="aup-avaf-BoxVisualizerOptions-Offset"></a>

### BoxVisualizerOptions.Offset
Offset represents the x and y displacement values.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| x | [float](#float) |  | Horizontal offset. |
| y | [float](#float) |  | Vertical offset. |





 


<a name="aup-avaf-BoxVisualizerOptions-InputType"></a>

### BoxVisualizerOptions.InputType
InputType enumerates the types of inputs that can be visualized.

| Name | Number | Description |
| ---- | ------ | ----------- |
| INPUT_TYPE_DETECTION | 0 | Visualize object detection bounding boxes. |
| INPUT_TYPE_CLASSIFICATION | 1 | Visualize classification results. |
| INPUT_TYPE_SEGMENTATION | 2 | Visualize segmentation maps. |
| INPUT_TYPE_LANDMARK | 3 | Visualize landmarks |


 

 

 



<a name="aup_avap_clip_generator-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/clip_generator.proto



<a name="aup-avaf-ClipGeneratorOptions"></a>

### ClipGeneratorOptions
Configures Clip Generator options


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| name_prefix | [string](#string) |  | name prefix for the clip file name |





 

 

 

 



<a name="aup_avap_codec_type-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/codec_type.proto


 


<a name="aup-avaf-CodecType"></a>

### CodecType
Codec Type enumeration for supported codec types

| Name | Number | Description |
| ---- | ------ | ----------- |
| CODEC_TYPE_NONE | 0 | Codec type not specified |
| CODEC_TYPE_H264 | 1 | Codec type is H264 |
| CODEC_TYPE_H265 | 2 | Codec type is H265 |
| CODEC_TYPE_MPEG4 | 3 | Codec type is MPEG4 |


 

 

 



<a name="aup_avap_empty-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/empty.proto
Empty options. This option is useful for any calculator that does not require any options

Example:
```
 node {
   name: "custom"
   calculator: "custom_node"
   input_stream: "input_stream"
   output_stream: "output_stream"
   node_options: {
     [type.googleapis.com/aup.avaf.EmptyOptions]: {
     }
   }
 }
```


<a name="aup-avaf-EmptyOptions"></a>

### EmptyOptions






 

 

 

 



<a name="aup_avap_epyc_resnet-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/epyc_resnet.proto



<a name="aup-avaf-EpycResnetOptions"></a>

### EpycResnetOptions



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| model_path | [string](#string) |  |  |
| label_file_path | [string](#string) |  |  |
| input_height | [int32](#int32) |  |  |
| input_width | [int32](#int32) |  |  |
| input_channels | [int32](#int32) |  | string input_node = 2; string output_node = 3; int32 output_classes = 7; int32 inter_op_threads = 8; int32 intra_op_threads = 9; int32 warm_up_steps = 10; |





 

 

 

 



<a name="aup_avap_event_based_recorder-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/event_based_recorder.proto



<a name="aup-avaf-EventBasedRecorderOptions"></a>

### EventBasedRecorderOptions
Options for event based video records


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| frames_before_event | [int32](#int32) |  | Number of frames to be included before the event |
| frames_after_event | [int32](#int32) |  | Number of frames to be included after the event |





 

 

 

 



<a name="aup_avap_file_saver-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/file_saver.proto



<a name="aup-avaf-FileSaverOptions"></a>

### FileSaverOptions
options for file saver node. Node


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| target | [FileSaverOptions.Target](#aup-avaf-FileSaverOptions-Target) |  | value of the target |
| directory | [string](#string) |  | Directory in the target on which file will be saved |
| directory_cleanup | [bool](#bool) |  | Whether directory should be cleaned up or not |





 


<a name="aup-avaf-FileSaverOptions-Target"></a>

### FileSaverOptions.Target
Target of the file to be saved

| Name | Number | Description |
| ---- | ------ | ----------- |
| TARGET_DISK | 0 | Target is disk |
| TARGET_FTP | 1 | Target is FTP |
| TARGET_MONGODB | 2 | Target is MongoDB |


 

 

 



<a name="aup_avap_frame_saver-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/frame_saver.proto
These are the options for the frame_saver calculator which saves a subsequence of frames into disk
Here is an example
```
node {
  name: "frame_saver"
  calculator: "frame_saver"
  input_stream: "image_stream"
  node_options: {
    [type.googleapis.com/aup.avaf.FrameSaverOptions]: {
      directory: "/tmp/saved_frames/"
      directory_cleanup: true
      save_limit: 10000
      output_type: JPEG
    }
  }
}
```


<a name="aup-avaf-FrameSaverOptions"></a>

### FrameSaverOptions
Options for frame saver node which saves frames to disk for specific interval


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| directory | [string](#string) |  | Directory on which frames will be saved. Default is current directory |
| directory_cleanup | [bool](#bool) |  | Whether directory should be cleaned up on node startup or not. Use with causion because it will remove all the files in the directory specifed |
| save_limit | [uint32](#uint32) |  | Maximum number of files that can be saved |
| save_offset | [uint32](#uint32) |  | Number of initial frames to be ignored from being saved |
| output_type | [FrameSaverOptions.OutputType](#aup-avaf-FrameSaverOptions-OutputType) |  | Output type of the saved frames |
| save_skip | [uint32](#uint32) |  | How many frames to skip between each write |





 


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

Messages that can be in configuration pbtxt


<a name="aup-avaf-GraphConfig"></a>

### GraphConfig

Message describing all possible component that can be in configuration pbtxt.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| node | [GraphConfig.Node](#aup-avaf-GraphConfig-Node) | repeated | List of nodes in the graph |
| control_port | [int32](#int32) |  | Control port number |
| graph_input | [string](#string) | repeated | List of graph inputs |
| graph_output | [string](#string) | repeated | List of graph outputs |
| statistics_collector | [GraphConfig.StatisticsCollector](#aup-avaf-GraphConfig-StatisticsCollector) | repeated | Statistics collectors |
| console_logging_filter | [GraphConfig.LoggingFilter](#aup-avaf-GraphConfig-LoggingFilter) |  | Logging filter for console logger |
| file_logging_filter | [GraphConfig.LoggingFilter](#aup-avaf-GraphConfig-LoggingFilter) |  | Logging filter for file logger |
| task_id | [string](#string) |  | The graph-level task_id and notification_url |
| notification_url | [string](#string) |  | Notification URL |






<a name="aup-avaf-GraphConfig-LoggingFilter"></a>

### GraphConfig.LoggingFilter
Message describing Logging Filter


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| enable_log | [bool](#bool) |  | Enable logs |
| enable_all | [bool](#bool) |  | Ignore all filters and enable all logs |
| filter | [GraphConfig.LoggingFilter.Filter](#aup-avaf-GraphConfig-LoggingFilter-Filter) | repeated | Filter values |






<a name="aup-avaf-GraphConfig-LoggingFilter-Filter"></a>

### GraphConfig.LoggingFilter.Filter
Message describing log filter


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| entity | [GraphConfig.LoggingFilter.Entity](#aup-avaf-GraphConfig-LoggingFilter-Entity) |  | Entity of the filter |
| severity | [GraphConfig.LoggingFilter.Severity](#aup-avaf-GraphConfig-LoggingFilter-Severity) | repeated | values for severities |
| name | [string](#string) | repeated | Node name in the case that entity is node |






<a name="aup-avaf-GraphConfig-Node"></a>

### GraphConfig.Node
Denoting a Node
A node is an instantiation of a calculator.
It has input and output streams.
Its responsibility is to read packets from input streams in orderly fasion
process them and send packets to output streams.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| name | [string](#string) |  | This denotes the calculator name. This can be an arbitrary string determined by graph author in order to uniquely identify the node by. |
| vendor | [string](#string) |  | the vendor of the calculator. This determines who/what company wrote the node this is useful to differentiate same calculators via different vendors. If not specified, it will default to Aupera. |
| calculator | [string](#string) |  | This denotes the calculator name a.k.a. the type of node. |
| input_stream | [string](#string) | repeated | node input stream name. this is connected to another node's output stream. |
| input_stream_attributes | [GraphConfig.Node.InputStreamAttributes](#aup-avaf-GraphConfig-Node-InputStreamAttributes) | repeated | list of attributes for all the input streams that may need to be |
| output_stream | [string](#string) | repeated | node output stream name, can be multiple, each stream should be unique for current graph |
| output_stream_attributes | [GraphConfig.Node.OutputStreamAttributes](#aup-avaf-GraphConfig-Node-OutputStreamAttributes) | repeated | list of attributes for all the output streams that may need to be |
| stream_sync | [GraphConfig.Node.StreamSync](#aup-avaf-GraphConfig-Node-StreamSync) |  | denote stream synchronization attributes |
| ml_model_kernel_name | [string](#string) |  | Name of the machine learning model |
| node_options | [google.protobuf.Any](#google-protobuf-Any) | repeated | Options passing to each node. Each node may have its own options |
| graph_input | [string](#string) |  | Graph input for communicating input url |
| graph_output | [string](#string) |  | Graph output for communicating output url |






<a name="aup-avaf-GraphConfig-Node-InputStreamAttributes"></a>

### GraphConfig.Node.InputStreamAttributes
ADVANCED: Attributes that are related to a node's input stream.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| name | [string](#string) |  | input stream name referring to these attributes |
| type | [GraphConfig.Node.InputStreamAttributes.Type](#aup-avaf-GraphConfig-Node-InputStreamAttributes-Type) |  |  |
| can_continue | [GraphConfig.Node.ContractNoYes](#aup-avaf-GraphConfig-Node-ContractNoYes) |  | This denodes if the sink expects continueable packets. This means consecutive packets with the same timestamp |






<a name="aup-avaf-GraphConfig-Node-OutputStreamAttributes"></a>

### GraphConfig.Node.OutputStreamAttributes
ADVANCED: Attributes that are related to a node's output stream.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| name | [string](#string) |  | name of input stream |
| capacity | [uint32](#uint32) |  | This denotes the capacity of the stream. In the case that it is not defined, global graph capacity will be used for this specific stream instead |
| on_full_act | [GraphConfig.Node.OutputStreamAttributes.OnFullAct](#aup-avaf-GraphConfig-Node-OutputStreamAttributes-OnFullAct) |  |  |
| can_continue | [GraphConfig.Node.ContractNoYes](#aup-avaf-GraphConfig-Node-ContractNoYes) |  | same as can_continue in input_stream_attributes. Note that if source is continuable, all the sinks must be continueable. The reverse is not true so non-continueable source may be connected to continueable sinks. |






<a name="aup-avaf-GraphConfig-Node-StreamSync"></a>

### GraphConfig.Node.StreamSync
This is a message to denote the stream synchronization attributes between
synchronized inputs of the node


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| drop_strategy | [GraphConfig.Node.StreamSync.DropStrategy](#aup-avaf-GraphConfig-Node-StreamSync-DropStrategy) |  | Drop strategy used for input streams of the node |
| timeout_ms | [int32](#int32) |  | Synchronization timeout in milliseconds |






<a name="aup-avaf-GraphConfig-StatisticsCollector"></a>

### GraphConfig.StatisticsCollector
Message describling statistic collectors which is a facility to collect
statistics from the framework


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| target_file | [string](#string) |  | Target file in which statistics report will be stored in. If left empty, output will be to STDOUT |
| measurement_print_interval_ms | [uint32](#uint32) |  | Interval of printing the measurements into the output in milliseconds. Default value is 1000ms |
| latency_stream_start | [string](#string) |  | For measuring latency accross the pipeline. This indicates the starting stream point on which latency should be measured |
| latency_stream_end | [string](#string) |  | For measuring latency accross the pipeline. This indicates the ending stream point on which latency should be measured |
| throughput_stream_name | [string](#string) | repeated | Name of the streams that are used to measure total throughput |
| throughput_ignore_initial_packets_count | [uint32](#uint32) |  | Number of packets to be ignored what measuring throughput |
| size_stream_name | [string](#string) | repeated | Name of the streams that are used to measure their size |





 


<a name="aup-avaf-GraphConfig-LoggingFilter-Entity"></a>

### GraphConfig.LoggingFilter.Entity
Enumeration describing the entity which is logging

| Name | Number | Description |
| ---- | ------ | ----------- |
| ENTITY_NODE | 0 | Entity is Node |
| ENTITY_FRAMEWORK | 1 | Entity is Framework |



<a name="aup-avaf-GraphConfig-LoggingFilter-Severity"></a>

### GraphConfig.LoggingFilter.Severity
Enumeration describing severity of logs

| Name | Number | Description |
| ---- | ------ | ----------- |
| SEVERITY_TRACE | 0 | Severity Trace |
| SEVERITY_DEBUG | 1 | Severity Debug |
| SEVERITY_INFO | 2 | Severity Info |
| SEVERITY_WARN | 3 | Severtiy Warning |
| SEVERITY_ERROR | 4 | Severity Errror |
| SEVERITY_FATAL | 5 | Severity Fatal |



<a name="aup-avaf-GraphConfig-Node-ContractNoYes"></a>

### GraphConfig.Node.ContractNoYes
ADVANCED: This message specifies if some boolean (Yes/No) attribute is
according to contract, or overridden by this configuration.

| Name | Number | Description |
| ---- | ------ | ----------- |
| CONTRACT | 0 | Use default value specified in the contract |
| NO | 1 | override the contract value to No |
| YES | 2 | override the contract value to Yes |



<a name="aup-avaf-GraphConfig-Node-InputStreamAttributes-Type"></a>

### GraphConfig.Node.InputStreamAttributes.Type
Denotes the type of input stream.
In general there are side-packets, unsynchronized streams and
synchronized streams. execute callback of node is called when either of
the following conditions is met:
- any unsynchronzed input stream has a new packet
- all synchronized streams have new packets before sychronization
  timeout
- some synchronzied streams have new packets but some don't.
  synchronization timeout is reached
Side packets are static data which are not removed from the stream when
dequeued. They only maintain their last value

| Name | Number | Description |
| ---- | ------ | ----------- |
| CONTRACT | 0 | Input stream type is determined by node's contract implementation. This is the default value |
| SYNCED_IMMUTABLE | 1 | Stream is synchronized with other SYNCED_IMMUTABLE and SYNCED_MUTABLE inputs of the node. Synchronization happens with regards to synchoronization timestamp of the packets. Node is not allowed to modify the packet. Meaning that the packet is treated as const. Direction of this stream can only be foreward. |
| SYNCED_MUTABLE | 2 | Stream is synchronized with other SYNCED_IMMUTABLE and SYNCED_MUTABLE inputs of the node. Synchronization happens with regards to synchoronization timestamp of the packets. Node is allowed to modify the packet. Meaning that the packet is not treated as const Direction of this stream can only be foreward. |
| UNSYNCED_IMMUTABLE | 3 | Stream is not synchronized with any other streams. Node is not allowed to modify these packets which means that these are const packets.option These packets can travel either forward or backward |
| SIDE_PACKET | 4 | these streams can have any direction and not synced and timestamped like UNSYNCED_IMMUTABLE. The difference is that these streams only keep track of the latest packet as opposed to UNSYNCED which act as a queue. These streams are useful for communicating various configurations |



<a name="aup-avaf-GraphConfig-Node-OutputStreamAttributes-OnFullAct"></a>

### GraphConfig.Node.OutputStreamAttributes.OnFullAct
This determines the behavior of aup::avaf::Node::enqueue member
function in the case that stream's full capacity is reached

| Name | Number | Description |
| ---- | ------ | ----------- |
| BLOCK | 0 | block the enqueue function call until room is available in the stream via dequeueing from other nodes |
| DROP_FRONT | 1 | DROP_FRONT: automatically drop the oldest packet (front of the stream) to make room for the new packet being enqueued |
| FAIL | 2 | FAIL: fail the enqueue call immediately in case that stream is full |



<a name="aup-avaf-GraphConfig-Node-StreamSync-DropStrategy"></a>

### GraphConfig.Node.StreamSync.DropStrategy
DropStrategy determines the scenario that framework drop the packet in
case that synchronization timeout is reached

| Name | Number | Description |
| ---- | ------ | ----------- |
| CONTRACT | 0 | Determient the packet dropping strategy from the contract |
| DROP_INCOMPLETE_PACKETS | 1 | This option will drop the packets in case at least one of the input streams do not have complete packet sequence at the timeout time. Complete packet sequence means a single packet for non-continuable streams. For the case of contiued streams, it means that the final packet of the continued series of packets is not delivered before timeout. Any time that drop happens, execute will not be called |
| DROP_MISSING_PACKETS | 2 | Drop if there are any packets in any of the streams that are completely missing |
| NEVER_DROP | 3 | never drop packets. if timeout is reached and one synced input is available |


 

 

 



<a name="aup_avap_host_source_sink-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/host_source_sink.proto



<a name="aup-avaf-HostSourceSinkOptions"></a>

### HostSourceSinkOptions
Options for calculators host_source or host_sink.
host_source is used to send data from super graph to subgrpah.
host_sink is used to send data from subgrpah to the super graph.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| index | [uint32](#uint32) |  | Index of the source or sink on the corresponding subgrpah calculator |





 

 

 

 



<a name="aup_avap_image_stream-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/image_stream.proto
This is a calculator that streams images in a folder
Here is an example of it
```
node {
  name: "img_stream"
  calculator: "image_stream"
  output_stream: "image_stream"
  output_stream: "decode_vid_info_side_packet_dangling"
  node_options: {
    [type.googleapis.com/aup.avaf.ImageStreamOptions]: {
      playback_fps: 1
      directory: "/home/aupera/mehdiz/smart_edge_box/corst2/SharedFiles/images/single-image/"
      width: 416
      height: 416
      loop_over: true
      preload_images: true
    }
  }
}
```


<a name="aup-avaf-ImageStreamOptions"></a>

### ImageStreamOptions
Optinos for image_stream calculator which sends frames sequentially


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| playback_fps | [float](#float) |  | frames per second sent |
| directory | [string](#string) |  | directory containing the frames |
| width | [uint32](#uint32) |  | width of the frame |
| height | [uint32](#uint32) |  | height of the frame |
| vooya_input | [bool](#bool) |  | if input is raw vooya frame (not regular frame formats) |
| loop_over | [bool](#bool) |  | loop over the frames when finished |
| pool_size | [uint32](#uint32) |  | size of the output pool |
| preload_images | [bool](#bool) |  | preload images (for throughput measurement) |
| host_sink_index | [uint32](#uint32) |  | index of host sink for the case that image_stream is sending from subgraph to supergraph |





 

 

 

 



<a name="aup_avap_json_stream-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/json_stream.proto



<a name="aup-avaf-JsonStreamOptions"></a>

### JsonStreamOptions
options for json_stream calculator


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| interval_us | [int64](#int64) |  | interval between two JsonPackets |
| directory | [string](#string) |  | Directory containing josn files |
| loop_over | [bool](#bool) |  | whether calculator should loop over the files |





 

 

 

 



<a name="aup_avap_landmark_predictor-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/landmark_predictor.proto
The landmark_predictor predicts landmarks in images.

Example:
```
node {
  name: "landmark"
  calculator: "landmark_predictor"
  input_stream: "image_stream_decode"
  output_stream: "landmark_stream"
  ml_model_kernel_name: "openpose_pruned_0_3"
  node_options: {
    [type.googleapis.com/aup.avaf.LandmarkPredictorOptions]: {
        landmark_predictor_type: "Openpose"
        use_detections: false
        need_preprocess: true
        log_performance: false
        run_on_letterboxed_img: false
        batch_size: 3
        force_batch_size: false
        return_frames_inorder: true
        landmark_prediction_threads: 1
        batch_collection_timeout_ms: 0
        max_landmark_prediction_lib_q_size: 30
    }
  }
}
```


<a name="aup-avaf-LandmarkPredictorOptions"></a>

### LandmarkPredictorOptions
Options for the landmark predictor


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| landmark_predictor_type | [string](#string) |  | _**REQUIRED**_. The expected value should be one of: "Movenet", "FaceLandmark", "Hourglass", "Openpose", and "RetinaFace". The type of the landmark prediction model. |
| need_preprocess | [bool](#bool) |  | Indicates if preprocessing is required before landmark prediction |
| run_on_letterboxed_img | [bool](#bool) |  | Specifies if the landmark predictor should run on letterboxed images. |
| batch_size | [int32](#int32) |  | The size of batches for landmark prediction. Larger batches may increase performance but require more memory. |
| return_frames_inorder | [bool](#bool) |  | Determines if the landmark prediction results should be returned in the order they were received. |
| landmark_prediction_threads | [int32](#int32) |  | The number of threads dedicated to landmark prediction tasks. |
| force_batch_size | [bool](#bool) |  | Forces the landmark predictor to wait for a full batch before processing. |
| batch_collection_timeout_ms | [uint64](#uint64) |  | The maximum time in milliseconds to wait for a full batch before processing. |
| log_performance | [bool](#bool) |  | Enables logging of performance metrics, this will print on the termianl screen. |
| max_landmark_prediction_lib_q_size | [int32](#int32) |  | The maximum size of the landmark prediction library's queue. |
| use_detections | [bool](#bool) |  | If true, uses detection results as input for landmark prediction, otherwise uses raw images. |
| max_frame_cache_size | [int32](#int32) |  | The maximum size of the frame cache. Helps manage memory usage. |





 

 

 

 



<a name="aup_avap_notification_message-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/notification_message.proto
The notification_message calculator is designed to send customized notifications to users through emails or SMS messages. 
Example:
```
node {
 name: "email_notification"
 calculator: "notification_message"
 input_stream: "json_notification"
 node_options: {
   [type.googleapis.com/aup.avaf.NotificationMessageOptions]: {
     sender: "xxxxxx@auperatech.com"
     receiver: ["xxxxxxx1@gmail.com", "xxxxxxx2@gmail.com"]
     sender_username: "xxxxxxxxxxxx"
     sender_password: "xxxxxxxxxxxxx"
     server_url: "smtps://mail.auperatech.com:465"
     trigger: {
       trigger_type: JQ
       trigger_consecutive_packet: 3
       jq_query_string: "'select(.total_persons_entering &gt; 10 and .interval_persons_entering % 2 == 1)'"
       notification_title: "email_notification_test"
       notification_body: "xxxxxxxxxxxxxxxxxx"
       attach_json: true
     }
   }
 }
}
```


<a name="aup-avaf-NotificationMessageOptions"></a>

### NotificationMessageOptions
Options for the notification_mongo calculator
/ Defines the configurations and credentials needed for sending notifications using emails or SMS messages.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| message_type | [NotificationMessageOptions.MessageType](#aup-avaf-NotificationMessageOptions-MessageType) |  | The expected value is EMAIL or SMS, the default value is EMAIL. |
| server_url | [string](#string) |  | _**REQUIRED**_. The expected value is a string. If send email notification, this is email SMTP URL, eg: "smtps://mail.auperatech.com:465" If send SMS notification, this is SMS gateway API URL, eg: "https://api.twilio.com/2010-04-01/Accounts/&lt;Account-SID&gt;/Messages.json" |
| sender | [string](#string) |  | _**REQUIRED**_. The expected value is a string. / If send notification via email, the value should be an email address; if send notification via SMS, the value should be a phone number. |
| receiver | [string](#string) | repeated | _**REQUIRED**_. The expected value is an array of strings. / If send notification via email, the value should be an array of email address; if send notification via SMS, the value should be an array of phone number. |
| sender_username | [string](#string) |  | _**REQUIRED**_. The expected value is a string. / The credentials or authentications for connecting the server url / If send email notification, username and password are sender's email credentials / If send SMS notification, username and password are account's ID and token for authentications |
| sender_password | [string](#string) |  |  |
| trigger | [NotificationMessageOptions.Trigger](#aup-avaf-NotificationMessageOptions-Trigger) | repeated | _**REQUIRED**_. The expected value is user-defiend trigger object as listed in example / The jq trigger to select and filter messages sent |






<a name="aup-avaf-NotificationMessageOptions-Trigger"></a>

### NotificationMessageOptions.Trigger
Triggers to specify user-defiend notifications and jq filters.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| trigger_type | [NotificationMessageOptions.Trigger.Type](#aup-avaf-NotificationMessageOptions-Trigger-Type) |  | The expected value is PACKET or JQ, the default value is PACKET. Device if apply jq_query_string to filter the packet; otherwise we keep the packet as is. |
| jq_query_string | [string](#string) |  | REQUIRED when trigger_type is JQ. The expected value is a string. The jq string to filter the contents, eg: "jq '.detections | any(.[]; (.h * .w &gt; 200) and .class == \"bear\")' example.json" |
| manual_detect_options | [NotificationMessageOptions.Trigger.ManualDetectOptions](#aup-avaf-NotificationMessageOptions-Trigger-ManualDetectOptions) |  | Manual filtering options for detections NOTE: trigger_type must be JSON_DETECTION |
| manual_track_options | [NotificationMessageOptions.Trigger.ManualTrackOptions](#aup-avaf-NotificationMessageOptions-Trigger-ManualTrackOptions) |  | Manual filtering options for detections NOTE: trigger_type must be JSON_TRACK |
| manual_crowd_options | [NotificationMessageOptions.Trigger.ManualCrowdFlowOptions](#aup-avaf-NotificationMessageOptions-Trigger-ManualCrowdFlowOptions) |  | Manual filtering options for crowd flow tracking NOTE: trigger_type must be JSON_CROWD_FLOW |
| trigger_consecutive_packet | [uint32](#uint32) |  | _**REQUIRED**_. The expected value is a number &gt; 0. Sent notification when the previously received packet numbers meet the trigger_consecutive_packet value. |
| notification_title | [string](#string) |  | _**REQUIRED**_. The expected value is a string. User-defined notification_title. |
| notification_body | [string](#string) |  | The expected value is a string. User-defined notification_body. |
| attach_json | [bool](#bool) |  | The expected value is a boolean and it defaults to false. Choose to attach the packets into the notification or not. |






<a name="aup-avaf-NotificationMessageOptions-Trigger-ManualCrowdFlowOptions"></a>

### NotificationMessageOptions.Trigger.ManualCrowdFlowOptions
ManualCrowdFlowOptions to specify options for incoming crowd flow frames instead of using jq_query_string


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| min_total_entering | [uint32](#uint32) |  | Minimum total number of people who must have entered |
| min_total_exiting | [uint32](#uint32) |  | Minimum total number of people who must have exited |
| min_total_persons | [uint32](#uint32) |  | Minimum total people detected to pass filters |
| max_total_persons | [uint32](#uint32) |  | Maximum total people detected to pass filters |
| min_crowd_density | [float](#float) |  | Minimum crowd density to pass filters |
| max_crowd_density | [float](#float) |  | Maximum crowd density to pass filters |






<a name="aup-avaf-NotificationMessageOptions-Trigger-ManualDetectOptions"></a>

### NotificationMessageOptions.Trigger.ManualDetectOptions
ManualDetectOptions to specify filter options for incoming detection frames instead of using jq_query_string


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| min_objects | [uint32](#uint32) |  | REQUIRED Minimum number of objects that must be detected in an image and pass filters |
| min_confidence | [float](#float) |  | Minimum confidence score of object to pass filters (between 0.0 and 1.0) |
| roi_x | [uint32](#uint32) |  | REQUIRED Minimum x location in pixels (from top-left corner) of left-most region of roi bounding box |
| roi_y | [uint32](#uint32) |  | REQUIRED Minimum y location in pixels (from top-left corner) of top-most region of roi bounding box |
| roi_w | [uint32](#uint32) |  | REQUIRED width of roi bounding box |
| roi_h | [uint32](#uint32) |  | REQUIRED height of roi bounding box |
| object_id | [uint32](#uint32) |  | Classification id of object to pass filters |






<a name="aup-avaf-NotificationMessageOptions-Trigger-ManualTrackOptions"></a>

### NotificationMessageOptions.Trigger.ManualTrackOptions
ManualTrackOptions to specify filter options for incoming tracked frames instead of using jq_query_string


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| min_objects | [uint32](#uint32) |  | REQUIRED Minimum number of objects that must be detected in an image and pass filters |
| min_confidence | [float](#float) |  | Minimum confidence score of object to pass filters (between 0.0 and 1.0) |
| roi_x | [uint32](#uint32) |  | REQUIRED Minimum x location in pixels (from top-left corner) of left-most region of roi bounding box |
| roi_y | [uint32](#uint32) |  | REQUIRED Minimum y location in pixels (from top-left corner) of top-most region of roi bounding box |
| roi_w | [uint32](#uint32) |  | REQUIRED width of roi bounding box |
| roi_h | [uint32](#uint32) |  | REQUIRED height of roi bounding box |
| object_id | [uint32](#uint32) |  | Classification id of object to pass filters |
| min_track_age | [uint32](#uint32) |  | Minimum tracking age of an object to pass filters NOTE: only use when tracking objects |
| max_track_age | [uint32](#uint32) |  | Maximum tracking age of an object to pass filters NOTE: only use when tracking objects |





 


<a name="aup-avaf-NotificationMessageOptions-MessageType"></a>

### NotificationMessageOptions.MessageType
MessageType defines the supported methods to send the notifications.

| Name | Number | Description |
| ---- | ------ | ----------- |
| EMAIL | 0 | Use EMAIL protocol. |
| SMS | 1 | Use SMS protocol. |



<a name="aup-avaf-NotificationMessageOptions-Trigger-Type"></a>

### NotificationMessageOptions.Trigger.Type
Type defines the supported notifications types.

| Name | Number | Description |
| ---- | ------ | ----------- |
| PACKET | 0 | Send plain notification packet text. |
| JQ | 1 | Send notification after jq filter process |
| JSON_DETECTION | 2 | Send notification after manual detection filter process. |
| JSON_TRACK | 3 | Send notification after manual tracked detection filter process. |
| JSON_CROWD_FLOW | 4 | Send notification after manual crowd flow filter process. |


 

 

 



<a name="aup_avap_notification_mongo-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/notification_mongo.proto
The notification_mongo calculator is designed to send customized notifications to a user-specified MongoDB server. 
Example:
node {
```
 name: "mongo_node"
 calculator: "notification_mongo"
 input_stream: "json_notification"
 node_options: {
   [type.googleapis.com/aup.avaf.NotificationMongoOptions]: {
     mongodb_address: "mongodb://127.0.0.1:27019"
     database_name: "aupera_mongodb"
     collection_name: "test_collection"
     notification_q_size: 2
   }
 }
}
```


<a name="aup-avaf-NotificationMongoOptions"></a>

### NotificationMongoOptions
Options for the notification_mongo calculator
/ Defines the configurations needed to connect and interact with a MongoDB database for notification_mongo.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| mongodb_address | [string](#string) |  | _**REQUIRED**_. The expected value is a string. The address of the MongoDB server. |
| database_name | [string](#string) |  | _**REQUIRED**_. The expected value is a string. The name of the database within MongoDB to use. |
| collection_name | [string](#string) |  | _**REQUIRED**_. The expected value is a string. The name of the collection within the database to use for storing notifications. |
| notification_q_size | [uint32](#uint32) |  | The expected value is a number &gt; 0, suggest range is [1, 4]. The size of the queue for holding pending notifications before they are written to the database. |





 

 

 

 



<a name="aup_avap_notification_web-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/notification_web.proto
The notification_web calculator is designed to send customized notifications using HTTPs or UDP protocol to a user-specified URL. 
Example:
```
node {
 name: "udp_notification"
 calculator: "notification_web"
input_stream: "json_notification"
 node_options: {
   [type.googleapis.com/aup.avaf.NotificationWebOptions]: {
     notification_url: "udp://127.0.0.1:8888"
     notification_q_size: 1
     protocol_type: UDP
   }
 }
}
```


<a name="aup-avaf-NotificationWebOptions"></a>

### NotificationWebOptions
Options for the notification_web calculator
/ Defines the configurations needed for sending notifications over the web using various protocols.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| notification_url | [string](#string) |  | _**REQUIRED**_. The expected value is a string. The URL to which notifications will be sent. |
| protocol_type | [NotificationWebOptions.ProtocolType](#aup-avaf-NotificationWebOptions-ProtocolType) |  | The expected value is HTTP or UDP, the default value is HTTP. The type of protocol to use for sending notifications (HTTP or UDP). |
| notification_q_size | [uint32](#uint32) |  | The expected value is a number &gt; 0, suggest range is [1, 4]. The size of the queue for holding pending notifications before they are sent. |
| https_username | [string](#string) |  | The expected value is a string. The username for authentication if using HTTPS. |
| https_password | [string](#string) |  | The expected value is a string. The password for authentication if using HTTPS. |





 


<a name="aup-avaf-NotificationWebOptions-ProtocolType"></a>

### NotificationWebOptions.ProtocolType
ProtocolType defines the types of supported protocols for sending notifications.

| Name | Number | Description |
| ---- | ------ | ----------- |
| HTTP | 0 | Use HTTP protocol. |
| UDP | 1 | Use UDP protocol. |


 

 

 



<a name="aup_avap_packet_simulator-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/packet_simulator.proto



<a name="aup-avaf-PacketSimulatorOptions"></a>

### PacketSimulatorOptions
PacketSimulatorOptions configures the behavior of a packet simulator used for testing or simulation purposes.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| op_mode | [PacketSimulatorOptions.OpMode](#aup-avaf-PacketSimulatorOptions-OpMode) |  | The operational mode selected for the simulator. |
| any_options | [PacketSimulatorOptions.AnyOptions](#aup-avaf-PacketSimulatorOptions-AnyOptions) |  | Specific options for OP_MODE_ANY. |
| clip_gen_options | [PacketSimulatorOptions.ClipGenOptions](#aup-avaf-PacketSimulatorOptions-ClipGenOptions) |  | Specific options for OP_MODE_CLIP_GEN. |






<a name="aup-avaf-PacketSimulatorOptions-AnyOptions"></a>

### PacketSimulatorOptions.AnyOptions
AnyOptions provides options for the general mode (OP_MODE_ANY).


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| source_packet_per_second | [float](#float) |  | The number of packets generated per second when acting as a source node. |
| packet_latency_us | [uint32](#uint32) |  | The amount of time in microseconds it takes to generate a packet. |






<a name="aup-avaf-PacketSimulatorOptions-ClipGenOptions"></a>

### PacketSimulatorOptions.ClipGenOptions
ClipGenOptions provides options for clip generation mode (OP_MODE_CLIP_GEN).


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| frame_offset | [uint32](#uint32) |  | The offset for the frame sequence to start generating packets. |
| frame_count | [uint32](#uint32) |  | The number of frames to generate packets for. |
| filename_prefix | [string](#string) |  | The prefix for any filenames generated during clip generation. |





 


<a name="aup-avaf-PacketSimulatorOptions-OpMode"></a>

### PacketSimulatorOptions.OpMode
OpMode defines the operational mode of the packet simulator.

| Name | Number | Description |
| ---- | ------ | ----------- |
| OP_MODE_ANY | 0 | A mode that applies to any general case. |
| OP_MODE_CLIP_GEN | 1 | A mode specifically for generating clips. |


 

 

 



<a name="aup_avap_packet_type-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/packet_type.proto


 


<a name="aup-avaf-PacketType"></a>

### PacketType
PacketType enumerates different types of packets used in video and data processing.

| Name | Number | Description |
| ---- | ------ | ----------- |
| PACKET_TYPE_NONE | 0 | Indicates no specific packet type or the type is not applicable. |
| PACKET_TYPE_CLASSIFICATIONS | 1 | Packet contains classification results. |
| PACKET_TYPE_DETECTIONS | 2 | Packet contains object detection information. |
| PACKET_TYPE_TRACKS | 3 | Packet contains object tracking information. |
| PACKET_TYPE_PLATE_RECOGNITIONS | 4 | Packet contains license plate recognition data. |
| PACKET_TYPE_SEGMENTATIONS | 5 | Packet contains image segmentation data. |
| PACKET_TYPE_AV_CODEC_CONTEXT | 6 | Packet contains audio/video codec context or parameters. |
| PACKET_TYPE_CLIP_GENERATOR_COMMAND | 7 | Packet contains commands or data for a clip generator. |
| PACKET_TYPE_FILE | 8 | Packet represents a file or file data. |
| PACKET_TYPE_IMAGE | 9 | Packet contains image data. |
| PACKET_TYPE_JSON | 10 | Packet contains data in JSON format. |
| PACKET_TYPE_UINT64 | 11 | Packet contains data of type uint64. |
| PACKET_TYPE_VIDEO | 12 | Packet contains video data. |
| PACKET_TYPE_VIDEO_STREAM_INFO | 13 | Packet contains video stream information or metadata. |
| PACKET_TYPE_ANY | 14 | Packet can be of any type, used for generic purposes. |
| PACKET_TYPE_MAX | 15 | Represents the maximum value in the enumeration for bounds checking. |


 

 

 



<a name="aup_avap_pixfmt-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/pixfmt.proto


 


<a name="aup-avaf-PixFmt"></a>

### PixFmt
PixFmt enumerates different pixel formats that can be used in video processing.

| Name | Number | Description |
| ---- | ------ | ----------- |
| PIXFMT_NONE | 0 | Indicates no pixel format is specified or the pixel format is not applicable. |
| PIXFMT_NV12 | 1 | NV12 pixel format, a type of YUV format with one plane for Y and one plane for UV. |
| PIXFMT_I420 | 2 | I420 pixel format, a type of YUV format with three planes, one for Y and two for U and V. |
| PIXFMT_BGR24 | 3 | BGR24 pixel format, 24-bit Blue Green Red packed pixel format. |
| PIXFMT_RGB24 | 4 | RGB24 pixel format, 24-bit Red Green Blue packed pixel format. |


 

 

 



<a name="aup_avap_statistics_reader-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/statistics_reader.proto
The statistics_reader calculator is designed to send customized notifications to a user-specified MongoDB server. 
Example:
```
node {
   name: "stats_reader"
   calculator: "statistics_reader"
   output_stream: "json_notification"
   node_options: {
   [type.googleapis.com/aup.avaf.StatisticsReaderOptions]: {
       interval_us: 1000000
       input_path: "/tmp/stats/stats.json"
       loop_over: true
       input_type: FILE
       only_send_throughput: true
   }
 }
}
```


<a name="aup-avaf-StatisticsReaderOptions"></a>

### StatisticsReaderOptions
Options for the statistics_reader calculator
/ Configures the behavior and parameters for reading and interpreting statistics file


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| interval_us | [int64](#int64) |  | _**REQUIRED**_. The expected value is a number, suggest 1000000. The time interval in microseconds between reading statistics. |
| input_path | [string](#string) |  | _**REQUIRED**_. The expected value is a string. The path to the file or directory containing statistical data. |
| loop_over | [bool](#bool) |  | _**REQUIRED**_. The expected value is a boolean value. Whether to loop over the input source when the end is reached. |
| only_send_throughput | [bool](#bool) |  | The expected value is a boolean value. Whether to only send throughput-related statistics and ignore others. |
| input_type | [StatisticsReaderOptions.InputType](#aup-avaf-StatisticsReaderOptions-InputType) |  | The expected value is DIRECTORY or FILE, the default value is DIRECTORY. The type of input source being used (directory or file). |





 


<a name="aup-avaf-StatisticsReaderOptions-InputType"></a>

### StatisticsReaderOptions.InputType
InputType enumerates the types of input sources from which statistics can be read.

| Name | Number | Description |
| ---- | ------ | ----------- |
| DIRECTORY | 0 | Indicates that the input is a directory containing multiple files. |
| FILE | 1 | Indicates that the input is a single file. |


 

 

 



<a name="aup_avap_stream_mux-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/stream_mux.proto
These options are used to configure the calculators stream_demux and stream_mux
These calcualtors are used for muxing and demuxing rtsp streams or video files
Here is an example of use case of both of these nodes
for demux:
```
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
```
for mux:
```
node {
  name: "mux_node"
  calculator: "stream_mux"
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


<a name="aup-avaf-StreamMuxOptions"></a>

### StreamMuxOptions
StreamMuxOptions configures the settings for multiplexing and demultiplexing streams.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| demux | [StreamMuxOptions.Demux](#aup-avaf-StreamMuxOptions-Demux) |  | Configuration settings for the demultiplexing calculator. |
| mux | [StreamMuxOptions.Mux](#aup-avaf-StreamMuxOptions-Mux) |  | Configuration settings for the multiplexing calculator. |






<a name="aup-avaf-StreamMuxOptions-Demux"></a>

### StreamMuxOptions.Demux
Demux is responsible for demultiplexing incoming streams.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| rtsp_transport | [string](#string) |  | REQUIRED. Transport method for receiving RTSP streams, options are "udp" or "tcp". |
| force_fps | [float](#float) |  | Specify a frame rate to avoid calculating the actual fps, enhancing the start-up speed. |
| iframe_extract | [bool](#bool) |  | If true, only I-frames are sent to the decoder, otherwise all packets are sent. |
| auto_reconnect | [bool](#bool) |  | If true, attempts to reconnect to the input stream upon poor network conditions or EOF. |
| input_url | [string](#string) |  | The URL of the input stream to be demultiplexed. |
| is_dummy | [bool](#bool) |  | If set to true, creates a dummy node for the demuxing process. |






<a name="aup-avaf-StreamMuxOptions-Mux"></a>

### StreamMuxOptions.Mux
Mux is responsible for multiplexing outgoing streams.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| rtsp_transport | [string](#string) |  | REQUIRED. Transport method for sending RTSP streams, options are "udp" or "tcp". |
| auto_reconnect | [bool](#bool) |  | If true, attempts to reconnect the output stream when it disconnects. |
| output_url | [string](#string) |  | The URL of the output stream to be multiplexed. |





 

 

 

 



<a name="aup_avap_subgraph-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/subgraph.proto



<a name="aup-avaf-SubgraphOptions"></a>

### SubgraphOptions
SubgraphOptions configures the parameters and behaviors for a subgraph within a processing graph.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| input_attrs | [SubgraphOptions.IOAttributes](#aup-avaf-SubgraphOptions-IOAttributes) | repeated | Attributes for all input streams. |
| output_attrs | [SubgraphOptions.IOAttributes](#aup-avaf-SubgraphOptions-IOAttributes) | repeated | Attributes for all output streams. |
| xdma_reader_sz | [uint32](#uint32) |  | The size of the XDMA reader. Defaults to 1. |
| xdma_writer_sz | [uint32](#uint32) |  | The size of the XDMA writer. Defaults to 1. |
| subgraph_config | [GraphConfig](#aup-avaf-GraphConfig) |  | Configuration for the subgraph itself. |
| attach_gdb_on_device | [bool](#bool) |  | Whether to attach a GDB on the device for debugging. Only applicable for debug builds. |






<a name="aup-avaf-SubgraphOptions-IOAttributes"></a>

### SubgraphOptions.IOAttributes
IOAttributes defines the attributes for input or output packets of the subgraph.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| type | [PacketType](#aup-avaf-PacketType) |  | The type of packet (e.g., ImagePacket, VideoPacket, DetectionPacket,etc). |
| pool_sz | [uint32](#uint32) |  | The number of packets available in the pool |
| entry_sz_kb | [uint32](#uint32) |  | The size of each packet entry in kilobytes. |
| has_packet_on_init | [bool](#bool) |  | Whether a packet should exist on initialization. |
| image_packet_width | [uint32](#uint32) |  | The width of the image packet, if applicable. |
| image_packet_height | [uint32](#uint32) |  | The height of the image packet, if applicable. |
| image_packet_pixfmt | [PixFmt](#aup-avaf-PixFmt) |  | The pixel format of the image packet, if applicable. |





 

 

 

 



<a name="aup_avap_to_json-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/to_json.proto
This is a calculator to convert meta data packets like DetectionPacket into JSON packet
Here is an example
node {
```
  name: "to_json"
  calculator: "to_json"
  input_stream: "detection_stream"
  output_stream: "json_stream"
  node_options: {
    [type.googleapis.com/aup.avaf.ToJsonOptions]: {
      label_name_file: "/opt/aupera/avas/label_files/dk_tiny_yolo.txt"
      network: "tinyyolov3"
      input_type: PACKET_TYPE_DETECTIONS
    }
  }
}
```


<a name="aup-avaf-ToJsonOptions"></a>

### ToJsonOptions
Options for the to_json calculator
Provides configuration settings for a node that converts various types of packets to a JSON format.
It is specifically tailored for converting DetectionPacket types.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| input_type | [PacketType](#aup-avaf-PacketType) |  | _**REQUIRED**_. The expected value is one of the PacketType listed above. Specifies the type of input packet to be converted. Should be set to DetectionPacket for these options. |
| label_name_file | [string](#string) |  | _**REQUIRED**_. The expected value is a string. The path to the file containing labels or names for detected objects. Applicable only when input_type is DetectionPacket. |
| network | [string](#string) |  | _**REQUIRED**_. The expected value is a string. Specifies the network configuration or type that was used for detection. Applicable only when input_type is DetectionPacket. |





 

 

 

 



<a name="aup_avap_v70_dec-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/v70_dec.proto



<a name="aup-avaf-V70DecodeOptions"></a>

### V70DecodeOptions
V70DecodeOptions provides configuration settings for decoding operations, particularly with V70 hardware.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| input_path | [string](#string) |  | The path to the input data or stream to be decoded. |
| decode_kernel | [string](#string) |  | Specifies the decoding kernel or algorithm to use. |
| xclbin_location | [string](#string) |  | The location of the xclbin file for FPGA configuration specific to decoding. |
| pool_size | [uint32](#uint32) |  | The size of the buffer pool for decoded frames or packets. |
| ow | [uint32](#uint32) |  | Output width: the target width of the decoded video or image. |
| oh | [uint32](#uint32) |  | Output height: the target height of the decoded video or image. |





 

 

 

 



<a name="aup_avap_vcodec-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/vcodec.proto
These options are for x86_dec and x86_enc calculators
these are used for conversion between Image packets and video packets
Here is an example for both of these calculators
x86_dec (converts video packets into sequence of image packets)
```
node {
  name: "decode_node"
  calculator: "x86_dec"
  vendor: "Aupera"
  input_stream: "packet_stream_demux"
  input_stream: "video_stream_info_demux"
  output_stream: "image_stream_decode"
  output_stream: "video_stream_info_decode"
  node_options: {
    [type.googleapis.com/aup.avaf.VideoCodecOptions]: {
      dec: {
        ow: 1920
        oh: 1080
        opixfmt: PIXFMT_BGR24
        queue_size: 12
        low_latency: false
      }
    }
  }
}
```
x86_dec (converts image packets to video packets)
```
node {
  name: "encode_node"
  calculator: "x86_enc"
  vendor: "Aupera"
  input_stream: "image_stream_vfilter"
  input_stream: "video_stream_info_vfilter"
  output_stream: "packet_stream_encode"
  output_stream: "codec_context_stream"
  node_options: {
    [type.googleapis.com/aup.avaf.VideoCodecOptions]: {
     enc: {
       type: H264
       w: 0 
       h: 0
       fps: 0
     }
    }
  }
}
```


<a name="aup-avaf-VideoCodecOptions"></a>

### VideoCodecOptions
VideoCodecOptions provides configurations for video decoding and encoding processes.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| dec | [VideoCodecOptions.Decoder](#aup-avaf-VideoCodecOptions-Decoder) |  | Decoder configuration. |
| enc | [VideoCodecOptions.Encoder](#aup-avaf-VideoCodecOptions-Encoder) |  | Encoder configuration. |
| host_source_index | [uint32](#uint32) |  | Index of the source on the host side. |
| host_sink_index | [uint32](#uint32) |  | Index of the sink on the host side. |
| video_packet_fifo_cap | [uint32](#uint32) |  | Video packet FIFO capacity. |
| drop_packet_on_full_data_stream | [bool](#bool) |  | Drop packets when the data stream is full. |






<a name="aup-avaf-VideoCodecOptions-Decoder"></a>

### VideoCodecOptions.Decoder
Decoder specifies the settings for video decoding.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| ow | [uint32](#uint32) | repeated | Output widths for multiple streams, 0 for input resolution. |
| oh | [uint32](#uint32) | repeated | Output heights for multiple streams, 0 for input resolution. |
| opixfmt | [PixFmt](#aup-avaf-PixFmt) | repeated | REQUIRED. Output pixel formats, default is NV12. |
| queue_size | [uint32](#uint32) |  | Size of the decoder buffer queue. |
| low_latency | [bool](#bool) |  | Enable low latency mode if no B frames are present, outputs pictures as soon as possible. |






<a name="aup-avaf-VideoCodecOptions-Encoder"></a>

### VideoCodecOptions.Encoder
Encoder specifies the settings for video encoding.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| codec_type | [CodecType](#aup-avaf-CodecType) |  | Encoding type (H264, H265, MPEG4). |
| w | [uint32](#uint32) |  | Encoder width, 0 to use input stream resolution. |
| h | [uint32](#uint32) |  | Encoder height, 0 to use input stream resolution. |
| fps | [float](#float) |  | Frame rate for the encoded video. |
| queue_size | [uint32](#uint32) |  | Size of the encoder queue. |
| b_adapt | [bool](#bool) |  | Adaptive B-frame decision. |
| bframes | [uint32](#uint32) |  | Number of B-frames between I and P. |
| gop_size | [uint32](#uint32) |  | Group of Pictures size, affects compression and quality. |
| bitrate | [uint32](#uint32) |  | Bitrate for the video in bits per second. |
| gop_mode | [string](#string) |  | GOP mode ("default", "low-latency-B", "low-latency-P", "dynamic"). |
| rc_mode | [string](#string) |  | Rate control mode ("CBR", "VBR", "CRF"). |
| threads | [uint32](#uint32) |  | Number of threads used for encoding, affects performance. |





 

 

 

 



<a name="aup_avap_vfilter-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/vfilter.proto
This is the options for ff_vfilter node. This nodes is used for conversion of Image colorspace, framerate and dimensions
Here is an example
```
node {
  name: "vfilter_node"
  calculator: "ff_vfilter"
  input_stream: "image_stream_viz"
  input_stream: "video_stream_info_decode"
  output_stream: "image_stream_vfilter"
  output_stream: "video_stream_info_vfilter"
  node_options: {
    [type.googleapis.com/aup.avaf.VideoFilterOptions]: {
      opixfmt: PIXFMT_I420
      ow: 1280
      oh: 720
      ofps: 25
    }
  }
}
```


<a name="aup-avaf-VideoFilterOptions"></a>

### VideoFilterOptions
VideoFilterOptions configures the settings for various video filtering operations.


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| roi_x | [uint32](#uint32) |  | The x-coordinate for the top-left corner of the Region of Interest (ROI). |
| roi_y | [uint32](#uint32) |  | The y-coordinate for the top-left corner of the Region of Interest (ROI). |
| roi_w | [uint32](#uint32) |  | Width of the Region of Interest (ROI) in pixels. |
| roi_h | [uint32](#uint32) |  | Height of the Region of Interest (ROI) in pixels. |
| opixfmt | [PixFmt](#aup-avaf-PixFmt) |  | REQUIRED. Output pixel format for the filtered video (e.g., RGB24, BGR24, NV12, I420). |
| ow | [uint32](#uint32) |  | Output width of the filtered video in pixels. |
| oh | [uint32](#uint32) |  | Output height of the filtered video in pixels. |
| ofps | [float](#float) |  | Output frame rate of the filtered video in frames per second. |
| queue_size | [uint32](#uint32) |  | Size of the queue for buffering frames during filtering operations. |





 

 

 

 



<a name="aup_avap_video_sink-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/video_sink.proto
These are the options for video_sink calculator which is a calculator to output video via rtsp
Here as example of usage of this node
```
node {
  calculator: "video_sink"
  name: "sink"
  input_stream: "nv12"
  input_stream: "nv12_infopacket"
  node_options: {
    [type.googleapis.com/aup.avaf.VideoSinkOptions]: {
      codec_type: CODEC_TYPE_H264
      bframes: 0
      gop_size: 60
      gop_mode: "low-latency-P"
      bitrate: 3000
      rc_mode: "Low Latency"
      path: "rtsp://127.0.0.1:554/my_car_stream"
    }
  }
}
```


<a name="aup-avaf-VideoSinkOptions"></a>

### VideoSinkOptions
Options for video_sink calculator


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| codec_type | [CodecType](#aup-avaf-CodecType) |  | Encoding type (H264, H265, MPEG4). |
| bframes | [uint32](#uint32) |  | Number of B-frames between I and P. |
| gop_size | [uint32](#uint32) |  | Group of Pictures size, affects compression and quality |
| gop_mode | [string](#string) |  | GOP mode ("default", "low-latency-B", "low-latency-P", "adaptive-B"). |
| bitrate | [uint32](#uint32) |  | Bitrate for the video in bits per second. |
| rc_mode | [string](#string) |  | Rate control mode ("CBR", "VBR"). |
| udp_port | [uint32](#uint32) |  | UDP port of rtsp pipeline, for dev only (set internally, recommend user to not specify this) |
| path | [string](#string) |  | Path to video rtsp output |





 

 

 

 



<a name="aup_avap_video_source-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## aup/avap/video_source.proto
These are the options for video_source calculator which is a calculator for reading any kind of video
This calculator supports USB cameras as well as RTSP streams.
For the case of USB cameras, the calculator has two outputs
Here as example of usage of this node
```
node {
  name: "usb_cam"
  calculator: "video_source"
  output_stream: "image_stream_bgr"
  output_stream: "video_stream_info_bgr"
  node_options: {
  output_stream: "video_stream_info_nv12"
    [type.googleapis.com/aup.avaf.VideoSourceOptions]: {
    }
  }
}
```
For the case of RTSP, the calculator has three outputs
Here is an exaple of usage of this node
```
node {
  name: "rtsp_in"
  calculator: "video_source"
  output_stream: "image_stream_bgr"
  output_stream: "video_stream_info_bgr"
  output_stream: "image_stream_nv12"
  output_stream: "video_stream_info_nv12"
  node_options: {
    [type.googleapis.com/aup.avaf.VideoSourceOptions]: {
      path: "rtsp://localhost:554/mystream"
    }
  }
}
```
For the case of Video, the calculator has three outputs
Here is an exaple of usage of this node
```
node {
  name: "video_in"
  calculator: "video_source"
  output_stream: "image_stream_bgr"
  output_stream: "video_stream_info_bgr"
  output_stream: "image_stream_nv12"
  output_stream: "video_stream_info_nv12"
  node_options: {
    [type.googleapis.com/aup.avaf.VideoSourceOptions]: {
      path: "/home/me/my_video.264"
    }
  }
}
```


<a name="aup-avaf-VideoSourceOptions"></a>

### VideoSourceOptions
Options for video_source calculator


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| source_type | [VideoSourceOptions.SourceType](#aup-avaf-VideoSourceOptions-SourceType) |  | type of video source |
| codec_type | [CodecType](#aup-avaf-CodecType) |  | Codec type of the video |
| path | [string](#string) |  | Path to video source |
| width | [uint32](#uint32) |  | width of video source. Will select the best value for width if not specified based on combination of resoltion and framerates available |
| height | [uint32](#uint32) |  | height of the video source. Will select best value for height if not specificed based on combination of resoltion and framerates available |
| framerate_numerator | [uint32](#uint32) |  | framerate of the video. Will select best framerate if not specified based on combination of resoltion and framerates available |
| framerate_denominator | [uint32](#uint32) |  | framerate of the video. Will select best framerate if not specified based on combination of resoltion and framerates available |
| pool_size | [uint32](#uint32) |  | Number of frames in the frame pool. Larger value will allow more frames to flow in the pipeline but will use more memory |
| drop_packet_on_full_data_stream | [bool](#bool) |  | Drop image packet in case that the data stream is full. More accurately, drop the packet in the case that the image allocator does not have any more room |
| play_file_once | [bool](#bool) |  | If set to false, it will only play the file once. otherwise it will loop over the file |





 


<a name="aup-avaf-VideoSourceOptions-SourceType"></a>

### VideoSourceOptions.SourceType
Type of source

| Name | Number | Description |
| ---- | ------ | ----------- |
| AUTO_SOURCE_TYPE | 0 | Auto-detect the source type |
| USB | 1 | USB |
| RTSP | 2 | RTSP (rtsp://....) |
| FILE | 3 | VIDEO FILE |


 

 

 



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

