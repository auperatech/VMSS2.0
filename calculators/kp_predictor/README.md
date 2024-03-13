### Purpose of the document
This document is a guide to creating a custom calculator with a model provided in the [Vitis-AI model-zoo](https://github.com/Xilinx/Vitis-AI/tree/2.5/model_zoo). 

Specifically, as a minimum example for this purposes, the calculator `kp_predictor` logs the number of keypoints predicted by a [HFNet](https://github.com/ethz-asl/hfnet/tree/master) model from input images. 

### Steps
1. Download the [model](https://github.com/Xilinx/Vitis-AI/tree/2.5/model_zoo/model-list/tf_HFNet_mixed_960_960_20.09G_2.5) from the [model-zoo](https://github.com/Xilinx/Vitis-AI/tree/2.5/model_zoo) and extract it.
2. As instructed in [basic_node_creation](../../docs/basic_node_creation/README.md)
    1. Define configurable options in a PROTO file
For example, a configurable `string` field `model` is defined in [kp_predictor.proto](./kp_predictor.proto) to specify the path to the XMODLE file.
        ```protobuf
        syntax = "proto3";

        package aup.avaf;

        message KPPredictorOptions {
            string model_path = 1;
        }
        ```
    2. Copy the file to `/opt/aupera/protos/aup/avap/` and rebuild AVAP with 
        ```bash
        cd /opt/aupera/protos
        make clean && make -j2 && make install
        ``` 
    3. Create a empty directory for source code of the calculator and generate code files of the calculator with `init_vmss_node.sh`, e.g., 
        ```bash
        mkdir -p /home/root/custom_calculators/kp_predictor
        cd /home/root/custom_calculators/kp_predictor
        init_vmss_node.sh --vendor customvendor --name-snake kp_predictor --name-camel KPPredictor --options-type KPPredictorOptions --options-header kp_predictor.pb.h
        ```
3. Referring to the [example](https://github.com/Xilinx/Vitis-AI/tree/2.5/examples/Vitis-AI-Library/samples/dpu_task/hfnet) provided by Vitis-AI 
    1. Here we use the `HFNet` class in [the Vitis-AI example](https://github.com/Xilinx/Vitis-AI/tree/2.5/examples/Vitis-AI-Library/samples/dpu_task/hfnet). Alternatively, you can define your own utility library to better manage the DPU tasks and results.
    2. Include needed header files to `kp_predictor.cc`, e.g, 
        ```cpp
        //needed headers
        #include "aup/avaf/packets/image_packet.h"
        #include "./hfnet.hpp"
        ```
    3. Defining private members, e.g.,
        ```cpp
        class KPPredictorCalculator : public CalculatorBase<KPPredictorOptions>
        {
        ...
        private:
            // pointer to the model 
            std::unique_ptr<vitis::ai::HFnet> model;

            // vector for model input images
            std::vector<cv::Mat> imgs;
        };
        ``` 
    4. Define the input and output streams of the calculator in `fill_contract()` function, e.g., 
        ```cpp
        ErrorCode fill_contract(std::shared_ptr<Contract>& contract,
                                std::string& err_str) override
        {
            // In this example, the calculator only has one input stream of ImagePacket 
            if (contract->input_stream_names.size() != 1 || contract->output_stream_names.size() != 0) {
                err_str = "io size invalid";
                return aup::avaf::ErrorCode::INVALID_CONTRACT;
            }
            contract->sample_input_packets[0] = make_packet<ImagePacket>();
            return aup::avaf::ErrorCode::OK;
        }
        ```
    
    5. Initialize the task in the `initialize()` function, e.g., 
        ```cpp
        ErrorCode initialize(std::string& err_str) override
        {
            // raise an error if the model is not defined
            if (options->model_path().empty()) {
                AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
                            "\033[33m" << __func__ << " The model_path should not be empty.\033[0m ");
                return ErrorCode::ERROR;
            }
            model = vitis::ai::HFnet::create(options->model_path());

            // raise an error if the DPU task is not created successfully
            if (model == nullptr) {
                AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
                            "\033[33m" << __func__ << " Failed to create DPU task with the mode "<< options->model_path() <<".\033[0m ");
                return ErrorCode::ERROR;
            }

            // initialize the input vector size to 1
            imgs.resize(1);
            return ErrorCode::OK;
        }

        ```
    6. Call the HFNet in the `execute()` function, e.g.,
        ```cpp
        ErrorCode execute()
        {
            // get the input packet
            PacketPtr<const ImagePacket> image_packet;
            auto ec = node->get_packet(0, image_packet);
            if (ec != ErrorCode::OK) {
                AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
                                "Got " << ec << " getting packet");
            }

            // get the image
            imgs[0] = image_packet->get_cv_mat(); 

            // log the input image size
            AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
                                "Received frame No. " << image_packet->get_itr_no() <<
                                " (size = " << imgs[0].size() << ")");

            // apply the model 
            auto res = model->run(imgs);

            // log the number of predicted keypoints predicted by the model
            AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
                                res[0].keypoints.size() << " keypoints are predicted." );
            return ErrorCode::OK;
        }
        ```
4. Add the depended objects and libraries to the `Makefile`
    ```Makefile
    CALCULATOR = kp_predictor
    VENDOR = customvendor
    WARNFLAGS += -Wno-unused-parameter
    include VERSION.mk

    OBJS = hfnet.o
    LDLIBS += -lvitis_ai_library-math -lvitis_ai_library-dpu_task

    include /opt/aupera/Calculator.mk
    ```
5. Compile the calculator and install with `make -j2 && make install`
6. Construct the pipeline PBTXT, e.g., a `test_kp_predictor.pbtxt` with the following content: 
    ```protobuf
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
        name: "hfnet_node"
        calculator: "kp_predictor"
        vendor: "customvendor"
        input_stream: "image_stream"
        node_options: {
            [type.googleapis.com/aup.avaf.KPPredictorOptions]: {
                # the path to the XMODEL file
                model_path: "./hfnet_tf/hfnet_tf.xmodel" 
            }
        }
    }
    ```
7. Run the pipeline with `avaser -c test_kp_predictor.pbtxt`
