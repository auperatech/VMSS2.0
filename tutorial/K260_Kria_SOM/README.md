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

Learn how to add a tracker to the face detection pipeline and reduce the detection interval for improved performance.

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

This section describes how to change the input source from an RTSP stream to a USB camera.

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

## Modifying Output to Send SMS

Instructions on how to change the output of the detection system to send SMS alerts.

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

## Switching to Person Detection and Model Selection

Change the pipeline to detect persons instead of faces and explore different models for detection.

### Available Models

| Model Kernel Name    | Description                       | Total Classes | TYPE |
|---------------|-----------------------------------|---------------| --------- |
| Model A       | Suitable for general person detection | 20  | YOLOV3 |
| Model B       | Optimized for low-light conditions  | NN  | SSD   |
| Model C       | High accuracy for crowded scenes   | NN  | RefineDet  |

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

## Tips and Tricks

- How to read from a file
- Saving detection results to a file
- Links to example projects and additional resources

Remember to replace placeholders (like RTSP URLs and model names) with actual data and add more detailed instructions and code snippets as needed. 
