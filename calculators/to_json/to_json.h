#pragma once
#pragma GCC diagnostic ignored "-Wdeprecated-copy"


#include <opencv2/opencv.hpp>
#include <thread>
#include <unistd.h>


#include <chrono>
#include <memory>
#include <unordered_map>
#include <vector>

#include "aup/avap/to_json.pb.h"

#include "aup/avaf/packets/detection_packet.h"
#include "aup/avaf/packets/classification_packet.h"
#include "aup/avaf/packets/segmentation_packet.h"

using namespace cv;
using namespace std;
using namespace aup::avaf;
using namespace aup::classify;
using namespace aup::detect;
using namespace aup::segment;

class ToJsonCalculator : public CalculatorBase<ToJsonOptions>
{
public:
	ToJsonCalculator(const ::aup::avaf::Node* node) : CalculatorBase(node) {}
	~ToJsonCalculator();
	ErrorCode initialize(std::string& err_str) override;
	ErrorCode execute() override;

protected:
	ErrorCode fill_contract(std::shared_ptr<Contract>& contract, std::string& err_str) override;

private:

	PacketPtr<PacketBase> get_in_stream_packet_by_type(PacketType input_type);
	
	vector<string> labels;
	bool is_first_pkg = false;
	timestamp_t initial_timestamp; 

};