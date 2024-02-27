# Start and execute the docker container
1. Please refer to the [setup documentation](../../setup/K260_Kria_SOM/README.md) for enviroment setup

# Custom node creation
## Create options for your node
1. create your own proto file for configuration
   ```bash
   cd /opt/aupera/protos
   vi aup/avap/box_empty.proto
   ```
2. fill it with configurations
   ```proto
   syntax = "proto3";
   
   package aup.avaf;
   
   message BoxEmptyOptions {
   }
   ```
3. build and install avap
   ```bash
   make clean
   make -j2
   make install
   ```
## Create node code
1. go to an empty directory that you would like to save your source code in
2. use init_vmss_node.sh script to generate the boiler plate of the code
   ```bash
   ./init_vmss_node.sh --vendor aupera --name-snake box_empty --name-camel BoxEmpty --options-type BoxEmptyOptions --options-header box_empty.pb.h
   ```
   at this state the content of the folder will look like following
   ```bash
   root@general:.../kria_som# ll box_empty
   total 20
   drwxrwxrwx 2 nobody nogroup 4096 Feb 27 07:00 ./
   drwxrwxr-x 3   1000    1000 4096 Feb 27 07:01 ../
   -rw-rw-rw- 1 nobody root     158 Feb 27 07:00 Makefile
   -rw-rw-rw- 1 nobody root      90 Feb 27 07:00 VERSION.mk
   -rw-rw-rw- 1 nobody root    1231 Feb 27 07:01 box_empty.cc
   ```
3. Complete the implementation of the node in the `.cc` file
   ```cpp
   // avaf headers
   #include "aup/avaf/calculator.h"
   #include "aup/avaf/utils.h"
   #include "aup/avap/box_empty.pb.h"
   #include "aup/avaf/packets/image_packet.h"

   using namespace aup::avaf;

   class BoxEmptyCalculator : public CalculatorBase<BoxEmptyOptions>
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
       BoxEmptyCalculator(const Node* node) : CalculatorBase(node)
       {
           // TODO add constructor code here
       }

       ~BoxEmptyCalculator()
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
           PacketPtr<const ImagePacket> image_packet;
           auto ec = node->get_packet(0, image_packet);
           if (ec != ErrorCode::OK) {
               AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
                                 "Got " << ec << " getting packet");
           }
           auto cv_mat = image_packet->get_cv_mat(); 
           AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
                                 "Received frame No. " << image_packet->get_itr_no() <<
                                 " (size = " << cv_mat.size() << ")");
           return ErrorCode::OK;
       }

   };

   AUP_AVAF_REGISTER_CALCULATOR_EXT("aupera",
                                   "box_empty",
                                   BoxEmptyCalculator,
                                   BoxEmptyOptions,
                                   true,
                                   "box_empty calculator by aupera.",
                                   {})
   ```
4. Make it and install it. 
   ```bash
   make -j2
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
     name: "empty_node"
     calculator: "box_empty"
     input_stream: "image_stream"
     node_options: {
       [type.googleapis.com/aup.avaf.BoxEmptyOptions]: {
       }
     }
   }
  ```
2. Run with the following command
   ```bash
   avaser -c config.pbtxt
   ```

You can also add this node inside a subgraph
