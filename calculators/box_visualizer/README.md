### Purpose of the document
Purpose is to share the source code of our box_visualizer node

### Steps

1. Here the proto file is given here as the file [box_visualizer.proto](box_visualizer.proto). Make your modifications to it
2. Copy the file to `/opt/aupera/protos/aup/avap/` and rebuild AVAP with 
    ```bash
    cd /opt/aupera/protos
    make clean
    make -j2
    make install
    ```
3. Modify the source code for [box_visualizer.cc](box_visualizer.cc) and [box_visualizer.h](box_visualizer.h).
1. Referring to the [example](https://github.com/Xilinx/Vitis-AI/tree/2.5/examples/Vitis-AI-Library/samples/dpu_task/hfnet) provided by Vitis-AI 
    1. Implement a utility class as the `HFNet` in the Vitis-AI example
    2. Defining private members, e.g.,
        ```cpp
        class BoxHFNetCalculator : public CalculatorBase<BoxHFNetOptions>
        {
        ...
        private:
            // pointer to the model 
            std::unique_ptr<vitis::ai::HFnet> model;

            // vector for model input images
            std::vector<cv::Mat> imgs;
        };
        ``` 
    3. Define the input and output streams of the calculator in `fill_contract()` function, e.g., 
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
        2. Initialize the task in the `initialize()` function, e.g., 
        ```cpp
        ErrorCode initialize(std::string& err_str) override
        {
            // raise an error if the model is not defined
            if (options->model().empty()) {
                AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
                            "\033[33m" << __func__ << " The model should not be empty.\033[0m ");
                return ErrorCode::ERROR;
            }
            model = vitis::ai::HFnet::create(options->model());

            // raise an error if the DPU task is not created successfully
            if (model == nullptr) {
                AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
                            "\033[33m" << __func__ << " Failed to create DPU task with the mode "<< options->model() <<".\033[0m ");
                return ErrorCode::ERROR;
            }

            // initialize the input vector size to 1
            imgs.resize(1);
            return ErrorCode::OK;
        }

        ```
    4. Call the HFNet in the `execute()` function, e.g.,
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

            // log the number of predicted keypoints
            AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
                                res[0].keypoints.size() << " keypoints are predicted." );
            return ErrorCode::OK;
        }
        ```
4. Add the depended objects and libraries to the `Makefile`
    ```Makefile
    CALCULATOR = box_hfnet
    VENDOR = customvendor
    WARNFLAGS += -Wno-unused-parameter
    include VERSION.mk

    OBJS = hfnet.o
    LDLIBS += -lvitis_ai_library-math -lvitis_ai_library-dpu_task

    include /opt/aupera/Calculator.mk
    ```
5. Compile the calculator and install with `make -j2 && make install`
5. Construct the pipeline PBTXT, e.g., a `test_box_hfnet.pbtxt` with the following content: 
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
        calculator: "box_hfnet"
        input_stream: "image_stream"
        node_options: {
            [type.googleapis.com/aup.avaf.BoxHFNetOptions]: {
                model: "./hfnet_tf/hfnet_tf.xmodel"
            }
        }
    }
    ```
5. Run the pipeline with `avaser -c test_box_hfnet.pbtxt`
