// avaf headers
#include "aup/avaf/calculator.h"
#include "aup/avaf/utils.h"
#include "aup/avap/detection_visualizer.pb.h"

using namespace aup::avaf;

class DetectionVisualizerCalculator : public CalculatorBase<DetectionVisualizerOptions>
{
protected:
    ErrorCode fill_contract(std::shared_ptr<Contract>& contract,
                            std::string& err_str) override
    {
        // TODO implement the function
        return ErrorCode::NOT_IMPLEMENTED;
    }

public:
    DetectionVisualizerCalculator(const Node* node) : CalculatorBase(node)
    {
        // TODO add constructor code here
    }

    ~DetectionVisualizerCalculator()
    {
        // TODO add destructor code here
    }

    ErrorCode initialize(std::string& err_str) override
    {
        // TODO implement
        return ErrorCode::NOT_IMPLEMENTED;
    }

    ErrorCode execute()
    {
        // TODO implement
        return ErrorCode::NOT_IMPLEMENTED;
    }

};

AUP_AVAF_REGISTER_CALCULATOR_EXT("aupera",
                                 "detection_visualizer",
                                 DetectionVisualizerCalculator,
                                 DetectionVisualizerOptions,
                                 true,
                                 "detection_visualizer calculator by aupera.",
                                 {})

