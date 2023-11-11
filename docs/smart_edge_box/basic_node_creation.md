# Installing SDK
1. Run `install_and_update_sdk.sh` inside the docker to setup SDK environment for device side development

Note that for building anything on host side, you should NOT run `setenv_device_devel`. For anything that needs running on device side you NEED TO run `setenv_device_devel`. This procedure sets up environment variable `$STAGING_DIR`.

# Custom node creation
Note: that the following should be done host development. If you like your node to run on device side, it should be done with device development environment as well.
## Create options for your node
Note that for building options you need build for both host and device.
1. create your own proto file for configuration
   ```bash
   cd /opt/aupera/avaf/sdk_avaf_extra/protos
   vi aup/avap/photo_pixel_stat.proto
   ```
2. fill it with configurations
   ```proto
   syntax = "proto3";
   
   package aup.avaf;
   
   message PhotoPixelStatOptions {
           uint32 print_interval = 1;
   }
   ```
3. build and install avap
   ```bash
   make clean
   make -j4
   make install
   ```
## Create node code
1. go to an empty directory that you would like to save your source code in
2. use init_vmss_node.sh script to generate the boiler plate of the code
   ```bash
   init_vmss_node.sh --vendor aupera --name-snake photo_pixel_stat --name-camel PhotoPixelStat --options-type PhotoPixelStatOptions --options-header photo_pixel_stat.pb.h
   ```
   at this state the content of the folder will look like following
   ```bash
   root@general:.../Aupera/smart_edge_box/photo_pixel_stat# ll
   total 20K
   drw-rw-rw- 2 nobody root 4.0K Nov 10 21:20 ./
   drwxrwxr-x 8   1000 1000 4.0K Nov 10 21:12 ../
   -rw-rw-rw- 1 nobody root  110 Nov 10 21:20 Makefile
   -rw-rw-rw- 1 nobody root   90 Nov 10 21:20 VERSION.mk
   -rw-rw-rw- 1 nobody root 1.4K Nov 10 21:20 photo_pixel_stat.cc
   ```
3. Complete the implementation of the node in the `.cc` file
   ```cpp
   // avaf headers
   #include "aup/avaf/calculator.h"
   #include "aup/avaf/utils.h"
   #include "aup/avap/photo_pixel_stat.pb.h"
   #include "aup/avaf/packets/image_packet.h"
   
   using namespace aup::avaf;
   
   class PhotoPixelStatCalculator : public CalculatorBase<PhotoPixelStatOptions>
   {
   protected:
       ErrorCode fill_contract(std::shared_ptr<Contract>& contract,
                               std::string& err_str) override
       {
            if (contract->input_stream_names.size() != 1 || contract->output_stream_names.size() != 0) {
                err_str = "io size invalid";
                return aup::avaf::ErrorCode::INVALID_CONTRACT;
            }
            contract->sample_input_packets[0] = make_packet<ImagePacket>();
            return aup::avaf::ErrorCode::OK;
       }
   
   public:
       PhotoPixelStatCalculator(const Node* node) : CalculatorBase(node) {}
       ~PhotoPixelStatCalculator() {}
   
       ErrorCode initialize(std::string& err_str) override
       {
           if (options->print_interval() <= 0) {
               err_str = "print interval must be positive.";
               return ErrorCode::ERROR;
           }
           return ErrorCode::OK;
       }
   
       ErrorCode execute()
       {
           PacketPtr<ImagePacket> image_packet;
           auto ec = node->get_packet(0, image_packet);
           if (ec != ErrorCode::OK) {
               AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
                                 "Got " << ec << " getting packet");
           }
           if (image_packet->get_itr_no() % options->print_interval() != 0) {
               return ErrorCode::OK;
           }
           auto cv_mat = image_packet->get_cv_mat();
           std::vector<cv::Mat> bgr_planes;
           cv::split(cv_mat, bgr_planes);
   
           // Calculate mean and standard deviation for each channel
           cv::Scalar meanB, stdDevB, meanG, stdDevG, meanR, stdDevR;
           cv::meanStdDev(bgr_planes[0], meanB, stdDevB);
           cv::meanStdDev(bgr_planes[1], meanG, stdDevG);
           cv::meanStdDev(bgr_planes[2], meanR, stdDevR);
   
           // Print statistics
           std::cout << "Blue channel: mean = " << meanB[0] << ", stdDev = " << stdDevB[0] << std::endl;
           std::cout << "Green channel: mean = " << meanG[0] << ", stdDev = " << stdDevG[0] << std::endl;
           std::cout << "Red channel: mean = " << meanR[0] << ", stdDev = " << stdDevR[0] << std::endl;
           return ErrorCode::OK;
       }
   
   };
   
   AUP_AVAF_REGISTER_CALCULATOR_EXT("aupera",
                                    "photo_pixel_stat",
                                    PhotoPixelStatCalculator,
                                    PhotoPixelStatOptions,
                                    true,
                                    "photo_pixel_stat calculator by aupera.",
                                    {})
   ```
4. Make it and install it. Note that if you want the node to run inside subgraph you need to `setenv_device_devel` bofore
   ```bash
   setenv_device_devel # only for building for device side
   make -j4
   make install
   ```

# Create Config and run pipeline
1. Create a config. Lets call it `config.pbtxt`
   ```
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
     name: "image_stats"
     calculator: "photo_pixel_stat"
     input_stream: "image_stream"
     node_options: {
       [type.googleapis.com/aup.avaf.PhotoPixelStatOptions]: {
         print_interval: 2
       }
     }
   }
   ```
2. Run with the following command
   ```bash
   avaser -c config.pbtxt
   ```

You can also add this node inside a subgraph
