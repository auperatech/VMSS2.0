# Example PBTXT for K260 Kria SOM tutorial

## Table of Contents
- [Example PBTXT for K260 Kria SOM tutorial](#example-pbtxt-for-k260-kria-som-tutorial)
  - [Table of Contents](#table-of-contents)
  - [Face Detection on RTSP Streams](#face-detection-on-rtsp-streams)
  - [Adding a Tracker and Reducing Detection Interval](#adding-a-tracker-and-reducing-detection-interval)
  - [Changing Input from RTSP to USB](#changing-input-from-rtsp-to-usb)
  - [Adding SMS Message Notification Alert](#adding_sms_message_notification_alert)
  - [Switching to Person Detection and Model Selection](#switching-to-person-detection-and-model-selection)

## Face Detection on RTSP Streams

  ```protobuf
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

  node {
    name: "detector"
    calculator: "box_detector"
    input_stream: "image_stream_decode"
    output_stream: "detections_stream"
    output_stream: "detect_interval"
    ml_model_kernel_name: "densebox_320_320"
    node_options: {
      [type.googleapis.com/aup.avaf.BoxDetectorOptions]: {
        detect_interval: 3
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
        text_offset: {
          x: 0
          y: 0
        }
        font: 0 
        line_type: 0
        box_thickness: 3
        text_size: 3 
      }
    }
  }

  node {
    name: "vfilter_node"
    calculator: "ff_vfilter"
    vendor: "Aupera"
    input_stream: "image_stream_viz"
    input_stream: "video_stream_info_decode"
    output_stream: "image_stream_vfilter"
    output_stream: "video_stream_info_vfilter"
    node_options: {
      [type.googleapis.com/aup.avaf.VideoFilterOptions]: {
        roi_x: 0
        roi_y: 0
        roi_w: 0
        roi_h: 0
        opixfmt: PIXFMT_I420
        ow: 960
        oh: 540
        ofps: 12
      }
    }
  }

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
        fps: 12
        bitrate: 100
      }
      }
    }
  }

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


## Adding a Tracker and Reducing Detection Interval

  ```protobuf
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

  node {
    name: "tracker"
    calculator: "box_tracker"
    input_stream: "detections_stream"
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
        tracker_type: "SORT++"
        min_object_area_th: 200
      }
    }
  }

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
        text_offset: {
          x: 0
          y: 0
        }
        font: 0 
        line_type: 0
        box_thickness: 3
        text_size: 3 
      }
    }
  }

  node {
    name: "vfilter_node"
    calculator: "ff_vfilter"
    vendor: "Aupera"
    input_stream: "image_stream_viz"
    input_stream: "video_stream_info_decode"
    output_stream: "image_stream_vfilter"
    output_stream: "video_stream_info_vfilter"
    node_options: {
      [type.googleapis.com/aup.avaf.VideoFilterOptions]: {
        roi_x: 0
        roi_y: 0
        roi_w: 0
        roi_h: 0
        opixfmt: PIXFMT_I420
        ow: 960
        oh: 540
        ofps: 12
      }
    }
  }

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
        fps: 12
        bitrate: 100
      }
      }
    }
  }

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

## Changing Input from RTSP to USB

  ```protobuf
  control_port: 51881
  graph_output: "graph_output1"

  node {
    name: "usb_cam"
    calculator: "video_source"
    output_stream: "image_stream_decode"
    output_stream: "video_stream_info_decode"
    node_options: {
      [type.googleapis.com/aup.avaf.VideoSourceOptions]: {
      }
    }
  }

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

  node {
    name: "tracker"
    calculator: "box_tracker"
    input_stream: "detections_stream"
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
        tracker_type: "SORT++"
        min_object_area_th: 200
      }
    }
  }

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
        text_offset: {
          x: 0
          y: 0
        }
        font: 0 
        line_type: 0
        box_thickness: 3
        text_size: 3 
      }
    }
  }

  node {
    name: "vfilter_node"
    calculator: "ff_vfilter"
    vendor: "Aupera"
    input_stream: "image_stream_viz"
    input_stream: "video_stream_info_decode"
    output_stream: "image_stream_vfilter"
    output_stream: "video_stream_info_vfilter"
    node_options: {
      [type.googleapis.com/aup.avaf.VideoFilterOptions]: {
        roi_x: 0
        roi_y: 0
        roi_w: 0
        roi_h: 0
        opixfmt: PIXFMT_I420
        ow: 960
        oh: 540
        ofps: 12
      }
    }
  }

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
        fps: 12
        bitrate: 100
      }
      }
    }
  }

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

## Adding SMS Message Notification Alert

  ```protobuf
  control_port: 51881
  graph_output: "graph_output1"
  task_id: "sms_test_only"

  node {
    name: "usb_cam"
    calculator: "video_source"
    output_stream: "image_stream_decode"
    output_stream: "video_stream_info_decode"
    node_options: {
      [type.googleapis.com/aup.avaf.VideoSourceOptions]: {
      }
    }
  }

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

  node {
    name: "tracker"
    calculator: "box_tracker"
    input_stream: "detections_stream"
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
        tracker_type: "SORT++"
        min_object_area_th: 200
      }
    }
  }

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
        text_offset: {
          x: 0
          y: 0
        }
        font: 0 
        line_type: 0
        box_thickness: 3
        text_size: 3 
      }
    }
  }

  node {
    name: "vfilter_node"
    calculator: "ff_vfilter"
    vendor: "Aupera"
    input_stream: "image_stream_viz"
    input_stream: "video_stream_info_decode"
    output_stream: "image_stream_vfilter"
    output_stream: "video_stream_info_vfilter"
    node_options: {
      [type.googleapis.com/aup.avaf.VideoFilterOptions]: {
        roi_x: 0
        roi_y: 0
        roi_w: 0
        roi_h: 0
        opixfmt: PIXFMT_I420
        ow: 960
        oh: 540
        ofps: 12
      }
    }
  }

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
        fps: 12
        bitrate: 100
      }
      }
    }
  }

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
        server_url: "https://api.twilio.com/2010-04-01/Accounts/<sender_username>/Messages.json"
        trigger: {
          trigger_type: JQ
          trigger_consecutive_packet: 3
          jq_query_string: "'select(.items | to_entries | map(.value | select(.x >= 0 and .y >= 0 and (.x + .width) <= 1920 and (.y + .height) <= 1080)) | length >= 4)'"
          notification_title: "sms_notification_alert"
          notification_body: "At least 5 faces are detected in a region for consecutive 3 packets"
        }
      }
    }
  }
  ```

## Switching to Person Detection and Model Selection

  ```protobuf
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

  node {
    name: "detector"
    calculator: "box_detector"
    input_stream: "image_stream_decode"
    output_stream: "detections_stream"
    output_stream: "detect_interval"
    ml_model_kernel_name: "ssd_pedestrian_pruned_0_97"
    node_options: {
      [type.googleapis.com/aup.avaf.BoxDetectorOptions]: {
        detect_interval: 1
        detector_type: "SSD"
        need_preprocess: true
        log_performance: false
        run_on_letterboxed_img: false
        batch_size: 1
        return_frames_inorder: true 
        batch_collection_timeout_ms: 0
        ignore_black_frames: false
        max_detection_lib_q_size: 30
        mean: {
          r: 104.0
          g: 117.0
          b: 123.0
        }
        scale: {
          ch1: 1.0
          ch2: 1.0
          ch3: 1.0
        }
        label_confidence: {
          label: 0
          confidence: 0.0
        }
        label_confidence: {
          label: 1
          confidence: 0.55
        }
      }
    }
  }

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
        text_offset: {
          x: 0
          y: 0
        }
        font: 0 
        line_type: 0
        box_thickness: 3
        text_size: 3 
      }
    }
  }

  node {
    name: "vfilter_node"
    calculator: "ff_vfilter"
    vendor: "Aupera"
    input_stream: "image_stream_viz"
    input_stream: "video_stream_info_decode"
    output_stream: "image_stream_vfilter"
    output_stream: "video_stream_info_vfilter"
    node_options: {
      [type.googleapis.com/aup.avaf.VideoFilterOptions]: {
        roi_x: 0
        roi_y: 0
        roi_w: 0
        roi_h: 0
        opixfmt: PIXFMT_I420
        ow: 960
        oh: 540
        ofps: 12
      }
    }
  }

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
        fps: 12
        bitrate: 100
      }
      }
    }
  }

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