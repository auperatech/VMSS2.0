#include "to_json.h"
#include "aup/avaf/thread_name.h"

#include <atomic>
#include <typeinfo>

// #define AUP_AVAF_DBG_ENABLE (1)
#include "aup/avaf/avaf_dbg.h"

// this is to visualize the tinyYolo classes for retail demo only
int load_labels(string const& path, vector<string>& labels)
{
	labels.clear();
	ifstream flabels(path);
	if (flabels.fail()) {
		fprintf(stderr, "Error : Open %s failed.\n", path.c_str());
		return -1;
	}
	string label_str;
	while (getline(flabels, label_str)) {
		labels.push_back(label_str);
	}
	flabels.close();
	return 0;
}

ToJsonCalculator::~ToJsonCalculator() {}

ErrorCode ToJsonCalculator::initialize(std::string&)
{
	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[33m" << __func__ << " to_json options:"
	                             << "\033[0m");

	if (options->label_name_file() != "") {
		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
		                  "\033[33m" << __func__ << " label_name_file = " << options->label_name_file() << "\033[0m");
		load_labels(options->label_name_file(), labels);
	}

	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[33m" << __func__ << " input type = " << options->input_type() << "\033[0m");
	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[33m" << __func__ << " network = " << options->network() << "\033[0m");
	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[34m"
	                      << "        to_json initialzied with input size: " << node->input_streams.size()
	                      << ", output size: " << node->output_streams.size() << "\033[0m");

	return ErrorCode::OK;
}

PacketPtr<PacketBase> ToJsonCalculator::get_in_stream_packet_by_type(PacketType input_type)
{
	switch (input_type) {
		case PACKET_TYPE_DETECTIONS_OR_TRACKS: { // detections
			vector<aup::detect::Detector::DetectedObject> res;
			return make_packet<DetectionPacket>(0, 0, 0, res, 0);
		}
		case PACKET_TYPE_CLASSIFICATIONS: { // classification
			vector<Classifier::ClassifiedRes> res;
			vector<Rect2d> bboxes;
			return make_packet<Classifications>(0, res, 0, bboxes);
		}
		case PACKET_TYPE_SEGMENTATIONS: { // segmentation
			aup::segment::Segmentor::SegmentedRes res;
			std::string segmentor_type;
			return make_packet<Segmentations>(0, res, segmentor_type, 0, 0);
		}
		default:
			break;
	}
	return nullptr;
}

ErrorCode ToJsonCalculator::fill_contract(shared_ptr<Contract>& contract, string& err_str)
{
	auto sz_input  = contract->input_stream_names.size();
	auto sz_output = contract->output_stream_names.size();
	if (sz_input != 1) {
		AUP_AVAF_TRACE();
		err_str = "node expects exactly one input.";
		return ErrorCode::INVALID_CONTRACT;
	}
	if (sz_output > 1) {
		AUP_AVAF_TRACE();
		err_str = "node cannot have more than 1 output.";
		return ErrorCode::INVALID_CONTRACT;
	}

	AUP_AVAF_TRACE();
	auto packet = get_in_stream_packet_by_type(options->input_type());
	if (packet) {
		contract->sample_input_packets[0] = packet;
	} else {
		err_str = "unknown input type " + to_string(options->input_type());
		AUP_AVAF_TRACE();
		return ErrorCode::INVALID_CONTRACT;
	}

	AUP_AVAF_TRACE();
	if (sz_output > 0) {
		nlohmann::json res;
		contract->sample_output_packets[0] = make_packet<JsonPacket>(0, res);
	}
	return ErrorCode::OK;
}

ErrorCode ToJsonCalculator::execute()
{
	try {
		ErrorCode ec;
		nlohmann::json tmp;
		PacketPtr<const PacketBase> input_packet = nullptr;
		PacketPtr<JsonPacket> json_packet        = nullptr;

		if ((ec = node->get_packet(0, input_packet)) != ErrorCode::OK) {
			AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
			                  "\033[33m" << __func__ << " failed to deque the input packet.\033[0m ");
			return ErrorCode::ERROR;
		}

		auto i_to_json = dynamic_cast<const packet::IToJsonPacket*>(input_packet.get());
		if (!i_to_json) {
			AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
			                  "\033[33m" << __func__ << " failed to convert input packet to json packet.\033[0m ");
			return ErrorCode::ERROR;
		}

		if ((ec = i_to_json->to_json_packet(json_packet)) != ErrorCode::OK) {
			AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
			                  "\033[33m" << __func__ << " failed to run to_json_packet to get the json data.\033[0m ");
			return ErrorCode::ERROR;
		}

		nlohmann::json j_detections_or_tracks = json_packet->get_json_content();

		// set network
		j_detections_or_tracks["network"] = options->network();
		// calculate ts_us_offset
		if (!this->is_first_pkg) {
			// record the first packet and calculate the ts_us_offset
			if (j_detections_or_tracks["timestamp"] != nullptr && j_detections_or_tracks["timestamp"] != 0) {
				this->initial_timestamp                = j_detections_or_tracks["timestamp"];
				j_detections_or_tracks["ts_us_offset"] = 0;
				this->is_first_pkg                     = true;
			}
		} else {
			timestamp_t ts_us_offset = static_cast<timestamp_t>(j_detections_or_tracks["timestamp"]) - this->initial_timestamp;
			j_detections_or_tracks["ts_us_offset"] = ts_us_offset;
		}

		// get the label
		if (!labels.empty()) {
			for (auto& obj : j_detections_or_tracks["items"]) {
				if (!obj["box_id"].empty()) {
					int obj_box_id = obj["box_id"];
					if (obj_box_id < (int)labels.size()) {
						obj["classification"] = labels.at(obj_box_id);
					} else {
						obj["classification"] = "unknownClass";
						AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
						                  "\033[33m" << __func__ << " The box_id " << obj_box_id
						                             << " exceeds the label size.\033[0m ");
					}
				}
			}
		}
		
		json_packet->update_json_content(j_detections_or_tracks);
		return node->enqueue(0, json_packet);

	} catch (const nlohmann::json::exception& e) {
		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
		                  "\033[33m" << __func__ << " Exception throw: " << e.what() << "\033[0m ");
	} catch (const std::exception& e) {
		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
		                  "\033[33m" << __func__ << " Exception throw: " << e.what() << "\033[0m ");
	}
	return ErrorCode::ERROR;
}

AUP_AVAF_REGISTER_CALCULATOR("Aupera", "to_json", ToJsonCalculator, ToJsonOptions, "Aupera's to json calculator.", {})
