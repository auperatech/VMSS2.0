# Embedding your logic

This document goes through creation of custom nodes which enables users to embed their custom logic into VMSS with ease. This document assumues that you have a fair amount of expenrience with C++ programming language, protocol buffers version 3 and OpenCV.

User can embed their custom logic into VMSS2.0 by creating node/calculators. This guide will walk you through the creation of custom node and running a pipeline that uses that custom logic.

## Example Calculators

If you need to refer to an example calculator durng this tutorial, please take a look at our open source calculators which may be [found here](https://github.com/auperatech/vmss_calculators)

## Start and execute the docker container
1. Please refer to the [setup documentation](../../setup/K260_Kria_SOM/README.md) for enviroment setup of Kria SOM

## Development of custom node
VMSS2.0 provides a tool to easily create code boiler-plate and build system with a single wizard-like command.
You can use this tool to generate the boiler plate and fill in various call back functions that require filling up. Here we go through an example of a calculator that overlays video histogram frame-by-frame on top of it. Because VMSS2.0 feeds videos to calcualtors frame-by-frame, histogram needs to be calculated frame-by-frame

### `init_vmss_node.sh` Wizard to create custom node boilerplate
Create a folder that you wish your custom node code to be inside of, cd to it. Then run the command `init_vmss_node.sh` to start the wizard for custom node creation.

```
$ mkdir histogram
$ cd histogram
$ init_vmss_node.sh
This script will take you through a wizard to create the boiler-plate code for a new calulator/node.
Enter vendor name [default=aupera]:
Enter calculator name in snake_case [default=custom_logic]:histogram_overlay
Enter calculator class name [default=HistogramOverlayCalculator]:
Are you using existing options from other available nodes? (Y/N) [default=N]:
Enter option name in snake_case which should NOT be in existing option list:
apl_common              epyc_resnet             packet_simulator
apl_crowd_flow          event_based_recorder    packet_type
apl_people_counting     file_saver              pixfmt
apl_person_attribute    frame_saver             statistics_reader
apl_vehicle_reid        graph                   stream_mux
box_classifier          host_source_sink        subgraph
box_detector            image_stream            to_json
box_segmentor           json_stream             v70_dec
box_tracker             landmark_predictor      vcodec
box_visualizer          notification_message    vfilter
clip_generator          notification_mongo      video_source
empty                   notification_web
 [default=histogram_overlay]:
Enter options class name in [default=HistogramOverlayOptions]:
Enter if the calculator will have execute callback. If your calculator has inputs then answer should be Y. If not answer must be N [default=Y]:
Generating histogram_overlay.proto ...
Generating VERSION.mk...
Generating Makefile...
Generating histogram_overlay boiler plate ...
```

Note that this calculator assumes the following:
- User needs to define their own options, User can choose `N` in the prompt `Are you using existing options?` in which case she will be prompted to use an existing option from the list.
- User may define a source node. For example a node to support a specific type of camera. In this case the node would not have any inputs and thus it cannot have `execute` callback. If this is the case she can choose `N` when prompted with `Enter if the calculator will have execute callback`

Back to the example at hand, at this point the following things should be created in the folder.

```
$ ll
total 24
drwxrwxrwx  2 nobody nogroup 4096 Mar 12 22:30 ./
drwxrwxr-x 16   1000    1000 4096 Mar 12 22:17 ../
-rw-rw-rw-  1 nobody nogroup  388 Mar 12 22:30 Makefile
-rw-rw-rw-  1 nobody nogroup   90 Mar 12 22:30 VERSION.mk
-rw-rw-rw-  1 nobody nogroup 1343 Mar 12 22:30 histogram_overlay.cc
-rw-rw-rw-  1 nobody nogroup   75 Mar 12 22:30 histogram_overlay.proto
```

the file `histogram_overlay.cc` now has the following content:

```cpp
// avaf headers
#include "aup/avaf/calculator.h"
#include "aup/avaf/utils.h"
#include "aup/avap/histogram_overlay.pb.h"

using namespace aup::avaf;

class HistogramOverlayCalculator : public CalculatorBase<HistogramOverlayOptions>
{
protected:
    ErrorCode fill_contract(std::shared_ptr<Contract>& contract,
                            std::string& err_str) override
    {
        // TODO implement the function
        return ErrorCode::OK;
    }

public:
    HistogramOverlayCalculator(const Node* node) : CalculatorBase(node)
    {
        // TODO add constructor code here
    }

    ~HistogramOverlayCalculator()
    {
        // TODO add destructor code here
    }

    ErrorCode initialize(std::string& err_str) override
    {
        // TODO implement
        return ErrorCode::OK;
    }

    ErrorCode execute()
    {
        // TODO implement
        return ErrorCode::OK;
    }

};

AUP_AVAF_REGISTER_CALCULATOR_EXT("aupera",
                                 "histogram_overlay",
                                 HistogramOverlayCalculator,
                                 HistogramOverlayOptions,
                                 true,
                                 "histogram_overlay calculator by aupera.",
                                 {})
```

Code boilerplate consists of the following callbacks
- Contructor and Destructor fields may be filled up based on the calculator needs
- `fill_contract` is an optional field that allows for users to specifically define the number and type of inputs and outputs of the node. This function is the first function that framework calls during initialization stage of a node. Use `err_str` to 
- `initialize` is another callback that does not necessarily need to be filled up. In the case that your node requires some initializations that would happen right after `fill_contract`, this is the place to put the logic in. In the case that your node requires initialization.
- `execute` is where the magic happens. it is called whenever there is are packets available on the inputs of the node.

The file `histogram_overlay.proto` now has the following content:

```proto
syntax = "proto3";

package aup.avaf;

message HistogramOverlayOptions {
}
```

You can add any options as you see fit into this node according to protocolbuffers version 3.

### Modify boilerplate of the code

#### Adding options

Here Lets just add an option of how big the histogram overlay is. For this reason we put a `float scale` option in the `.proto` file. This can be between `0.0` and `1.0` to show the histogram scaling. 

```proto
// ....
message HistogramOverlayOptions {
  float scale = 1;
}
```

In order to build the options into the option parser (avap) just run the following command

```bash
$ make avap
```

#### Modifying C++ source code callback

At this point you can modify the `execute` function to handle the histogram overlaying on the frames. This fucntion takes `PacketPtr` to [`ImagePackets`](https://auperatech.github.io/VMSS2.0/packet_documentation/classaup_1_1avaf_1_1ImagePacket.html) as input outputs the same type to output.

1. Firstly we add the `ImagePacket` header to the file
   ```cpp
   #include <aup/avaf/packets/image_packet.h>
   ```

2. After that, we can define a helper function in the class to overlay one `cv::Mat` on another.
   ```cpp
   // ...
   class HistogramOverlayCalculator : public CalculatorBase<HistogramOverlayOptions>
   {
       void overlayHistogram(cv::Mat& image, cv::Mat& histImage, float scale = 1.0)
       {
           using namespace cv;
           // Resize the histogram image to fit the top-left corner of the original image
           int new_width = image.cols / scale; // Adjust scaling factor as needed
           int new_height = image.rows / scale;
           resize(histImage, histImage, Size(new_width, new_height));
   
           // Create a ROI (Region of Interest) in the top-left corner of the original image
           Mat imageROI(image, Rect(0, 0, new_width, new_height));
   
           // Convert the histogram image to BGR format (assuming the original image is BGR)
           Mat histImageBGR;
           cvtColor(histImage, histImageBGR, COLOR_GRAY2BGR);
   
           // Apply weighted addition to overlay the histogram on the ROI, preserving image details
           addWeighted(imageROI, 1.0, histImageBGR, scale, 0.0, imageROI);
       }
   
   protected:
   // .....
   ```

3. At this point, modify the `execute` function
   ```cpp
      class HistogramOverlayCalculator : public CalculatorBase<HistogramOverlayOptions>
   {
      // ....
       ErrorCode execute()
       {
           using namespace cv;
           // Load your image
           PacketPtr<const ImagePacket> image_packet_const;
           ErrorCode ec;
           ec = node->get_packet(0, image_packet_const);
           if (ec != ErrorCode::OK) {
               AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
                                 "Issue getting packet");
               return ec;
           }
           PacketPtr<ImagePacket> image_packet = const_packet_cast<ImagePacket>(image_packet_const);
           Mat image = image_packet->get_cv_mat();
   
           // Calculate the histogram
           int histSize = 256; // Number of bins
           float range[] = { 0, 256 }; // The range of values
           const float* histRanges = { range };
           Mat hist;
           int channels[] = { 0 }; // Analyze only the first channel
   
           calcHist(&image, 1, channels, Mat(), // No mask
                   hist, 1, histSize, histRanges, false);
   
           // Normalize the histogram (optional, but improves visualization)
           normalize(hist, hist, 0, 255, NORM_MINMAX);
   
           // Display the histogram in a separate window
           int hist_w = 512;  // Width of the histogram display
           int hist_h = 400;  // Height of the histogram display
           Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255)); // White background
   
           // Plot the histogram lines 
           for (int i = 1; i < histSize; i++) {
               line(histImage, Point(i - 1, hist_h - cvRound(hist.at<float>(i - 1))),
                    Point(i, hist_h - cvRound(hist.at<float>(i))),
                    Scalar(0, 0, 0), 2, 8, 0);
           }
   
           overlayHistogram(image, histImage, options->scale());
   
           node->enqueue(0, image_packet);
   
           return ErrorCode::OK;
       }
   };
   // ....
   ```

### Testing of custom node
1. Create a config. Let's call it `config.pbtxt`
   ```pbtxt
   control_port: 51881
   node {
     name: "demux_node"
     calculator: "stream_demux"
     output_stream: "packet_stream"
     output_stream: "video_info_side_packet_demux"
     node_options: {
       [type.googleapis.com/aup.avaf.StreamMuxOptions]: {
         demux: {
           rtsp_transport: "tcp"
           iframe_extract: false
           auto_reconnect: true
           input_url: "rtsp://avac.auperatechnologies.com:554/retail"
         }
       }
     }
   }
   node {
     name: "decode_node"
     calculator: "x86_dec"
     input_stream: "packet_stream"
     input_stream: "video_info_side_packet_demux"
     output_stream: "image_stream"
     output_stream: "video_info_side_packet_decode"
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
     name: "histogrammer"
     calculator: "histogram_overlay"
     input_stream: "image_stream"
     output_stream: "image_stream_hist"
     node_options: {
       [type.googleapis.com/aup.avaf.HistogramOverlayOptions]: {
         scale: 0.2
       }
     }
   }

   node {
     name: "vfilter_node"
     calculator: "ff_vfilter"
     vendor: "Aupera"
     input_stream: "image_stream_hist"
     input_stream: "video_info_side_packet_decode"
     output_stream: "image_stream_vfilter_node"
     output_stream: "video_stream_info_vfilter_node"
     node_options: {
       [type.googleapis.com/aup.avaf.VideoFilterOptions]: {
         opixfmt: PIXFMT_I420
         ow: 1280
         oh: 720
         ofps: 20
       }
     }
   }

   node {
     name: "encode_node"
     calculator: "x86_enc"
     vendor: "Aupera"
     input_stream: "image_stream_vfilter_node"
     input_stream: "video_stream_info_vfilter_node"
     output_stream: "packet_stream_encode_node"
     output_stream: "codec_context_stream"
     node_options: {
       [type.googleapis.com/aup.avaf.VideoCodecOptions]: {
         enc: {
           type: MPEG4
           w: 0
           h: 0
           #  fps: 20
         }
       }
     }
   }

   node {
     name: "mux_node"
     calculator: "stream_mux"
     vendor: "Aupera"
     input_stream: "packet_stream_encode_node"
     input_stream: "codec_context_stream"
     node_options: {
       [type.googleapis.com/aup.avaf.StreamMuxOptions]: {
        mux: {
          rtsp_transport: "tcp"
          auto_reconnect: true
          output_url: "rtsp://avac.auperatechnologies.com:554/retail-histogram-overlay"
        }
       }
     }
   }
   ```

2. Run with the following command
   ```bash
   avaser -c config.pbtxt
   ```
You can also add this node inside a subgraph
