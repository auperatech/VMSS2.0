// avaf headers
#include "aup/avaf/calculator.h"
#include "aup/avaf/utils.h"
#include "aup/avap/kp_predictor.pb.h"

//needed headers
#include "aup/avaf/packets/image_packet.h"
#include "./hfnet.hpp"

using namespace aup::avaf;

class KPPredictorCalculator : public CalculatorBase<KPPredictorOptions>
{
protected:
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

public:
    KPPredictorCalculator(const Node* node) : CalculatorBase(node)
    {
        // TODO add constructor code here
    }

    ~KPPredictorCalculator()
    {
        // TODO add destructor code here
    }

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

private:
    // pointer to the model 
    std::unique_ptr<vitis::ai::HFnet> model;

    // vector for model input images
    std::vector<cv::Mat> imgs;
};

AUP_AVAF_REGISTER_CALCULATOR_EXT("customvendor",
                                 "kp_predictor",
                                 KPPredictorCalculator,
                                 KPPredictorOptions,
                                 true,
                                 "kp_predictor calculator by customvendor.",
                                 {})

