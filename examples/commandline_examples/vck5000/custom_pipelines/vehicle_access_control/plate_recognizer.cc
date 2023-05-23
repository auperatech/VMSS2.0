// std
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// sdk
#include <opencv2/opencv.hpp>

// framework
#include "aup/avaf/calculator.h"
#include "aup/avaf/node.h"
#include "aup/avaf/packet_ptr.h"
#include "aup/avaf/packets/image_packet.h"
#include "aup/avaf/packets/json_packet.h"
#include "aup/avap/box_detector.pb.h"

// local
#include "../extern/protos/plate_recognizer.pb.h"
#include "../extern/detect_track_packet.h"
#include "../extern/plate.hpp"
#include "../extern/plate_recognizer_packet.h"

//#define AUP_AVAF_DBG_ENABLE (1)
#include "aup/avaf/avaf_dbg.h"

// ATTENTION: please refer to your task for model locations
using namespace cv;
using namespace std;
using namespace aup::avaf;

class PlateRecognizerCalculator : public CalculatorBase<PlateRecognizerOptions>
{
	int plate_run_cnt               = 0;
	timestamp_t plate_run_delay_sum = 0;

protected:
	virtual ErrorCode fill_contract(shared_ptr<Contract>& contract) override;
	PacketPtr<PlateRecognitions> run_with_detections(PacketPtr<ImagePacket> image_packet);

public:
	PlateRecognizerCalculator(const ::aup::avaf::Node* node) : CalculatorBase(node) {}
	virtual ErrorCode initialize(std::string& err_str) override;
	virtual ErrorCode execute() override;
	std::shared_ptr<aup::plate::LicensePlate> plate = nullptr;
};

ErrorCode PlateRecognizerCalculator::fill_contract(shared_ptr<Contract>& contract)
{
	if (contract->input_stream_names.size() != 2) {
		return ErrorCode::SIZE_MISMATCH;
	}
	if (contract->output_stream_names.size() > 2) {
		return ErrorCode::SIZE_MISMATCH;
	}

	vector<aup::detect::Detector::DetectedObject> res;
	contract->sample_input_packets[0] = make_packet<DetectionsOrTracks>(0, 0, 0, res, 0);
	contract->sample_input_packets[1] = make_packet<ImagePacket>();

	if (contract->output_stream_names.size() > 0) {
		contract->sample_output_packets[0] = make_packet<PlateRecognitions>(0);
	}
	contract->stream_sync.set_drop_strategy(contract->stream_sync.DROP_INCOMPLETE_PACKETS);
	if (contract->output_stream_names.size() > 1) {
		nlohmann::json res;
		contract->sample_output_packets[1] = make_packet<JsonPacket>(0, res);
	}
	return ErrorCode::OK;
}

ErrorCode PlateRecognizerCalculator::initialize(std::string& err_str)
{
	BOOST_LOG_SEV(node->logger()->mlogger(), LOG_INFO) << "\035[34m" << __func__ << " plate recognizer options:"
	                                                   << "\035[0m" << endl;
	BOOST_LOG_SEV(node->logger()->mlogger(), LOG_INFO)
	    << "\035[34m"
	    << "        plate_confidence = " << options->plate_confidence() << "\035[0m" << endl;

	BOOST_LOG_SEV(node->logger()->mlogger(), LOG_INFO)
	    << "\035[34m"
	    << "        plate_area_threshold = " << options->plate_area_threshold() << "\035[0m" << endl;
	BOOST_LOG_SEV(node->logger()->mlogger(), LOG_INFO)
	    << "\035[34m"
	    << "        detector_type = " << options->detector_type() << "\035[0m" << endl;
	BOOST_LOG_SEV(node->logger()->mlogger(), LOG_INFO)
	    << "\035[34m"
	    << "        recog_type = " << options->recog_type() << "\035[0m" << endl;
	BOOST_LOG_SEV(node->logger()->mlogger(), LOG_INFO)
	    << "\035[34m"
	    << "        run_checksum_valid = " << options->run_checksum_valid() << "\035[0m" << endl;
	BOOST_LOG_SEV(node->logger()->mlogger(), LOG_INFO)
	    << "\035[34m"
	    << "        run_preprocessing = " << options->run_preprocessing() << "\035[0m" << endl;

	/**********************************************************************************************/
	// plate lib obj setup
	/**********************************************************************************************/

	aup::plate::PlateInitParams init_params = {};
	init_params.plate_confidence            = options->plate_confidence();
	init_params.plate_area_threshold        = options->plate_area_threshold();
	init_params.detector_type               = options->detector_type();
	init_params.recog_type                  = options->recog_type();
	init_params.run_checksum_valid          = options->run_checksum_valid();
	init_params.run_preprocessing           = options->run_preprocessing();
	try {
		plate = std::make_unique<aup::plate::LicensePlate>(init_params);
	} catch (exception& e) {
		err_str = e.what();
		return ErrorCode::ERROR;
	}

	return ErrorCode::OK;
}

PacketPtr<PlateRecognitions> PlateRecognizerCalculator::run_with_detections(PacketPtr<ImagePacket> image_packet)
{
	PacketPtr<const DetectionsOrTracks> detections;

	if (node->get_packet(0, detections) != ErrorCode::OK) {
		std::string er = "\035[plate_recognizer failed to receive detections\035[0m\n";
		throw runtime_error(er);
	}

	if (detections == nullptr) {
		std::string er = "\035[plate_recognizer received empty detections\035[0m\n";
		throw runtime_error(er);
	}

	if (detections->get_sync_timestamp() != image_packet->get_sync_timestamp()) {
		std::string er =
		    "\035[plate_recognizer received detections with pts: " + std::to_string(detections->get_sync_timestamp()) +
		    " which does not match the frame pts: " + std::to_string(image_packet->get_sync_timestamp()) + "\035[0m\n";
		throw runtime_error(er);
	}

	auto input_frame = image_packet->get_cv_mat();

	auto results = make_packet<PlateRecognitions>(image_packet->get_sync_timestamp());

	auto before_loop = get_now_us();
	for (auto& det : detections->detections_or_live_tracks) {
		try {
			auto result = plate->run(input_frame(det.rect));
			// auto result = make_shared<aup::plate::PlateResult>(aup::plate::PlateResult{
			//     .plate_confidence = 1.0,
			//     .plate_number = "MahsaAmini",
			//     .plate_color = "",
			//     .plate_area = 0,
			//     .plate_box = cv::Rect(0,0,0,0),
			//     .verified = true,
			// });

			auto roi_wrt_parent = Rect((result->plate_box.x + det.rect.x), (result->plate_box.y + det.rect.y),
			                           result->plate_box.width, result->plate_box.height);

			result->plate_box = roi_wrt_parent;

			results->plate_results.push_back(result);
		} catch (...) {
			continue;
		}
	}
	auto after_loop = get_now_us();
	plate_run_cnt++;
	plate_run_delay_sum += (after_loop - before_loop);
	AUP_AVAF_DBG("LOOP LATENCY AVERAGE: " << plate_run_delay_sum / plate_run_cnt
	                                      << " LOOP LATENCY:" << after_loop - before_loop);

	for (auto& det : detections->detections_or_live_tracks) {
		cv::rectangle(input_frame, det.rect, cv::Scalar(0, 255, 0), 2, 1, 0);
	}

	return results;
}

ErrorCode PlateRecognizerCalculator::execute()
{
	PacketPtr<const ImagePacket> image_packet_immut;
	ErrorCode ec;

	if ((ec = node->get_packet(1, image_packet_immut)) != ErrorCode::OK) {
		return ec;
	}

	// TODO remove mutable image packet. unsafe code
	auto image_packet = const_packet_cast<ImagePacket>(image_packet_immut);

	PacketPtr<PlateRecognitions> results;

	results = run_with_detections(image_packet);

	auto& input_frame = image_packet->get_cv_mat();

	if (node->output_streams.size() == 0) {
		std::cout << "\n\n\n\035plate_recognizer results: \n";

		for (auto& res : results->plate_results) {
			cv::rectangle(input_frame, res->plate_box, cv::Scalar(255, 0, 0), 2, 1, 0);

			cv::Point textSp(res->plate_box.x, res->plate_box.y - 5);
			auto font_scale = cv::getFontScaleFromHeight(0, res->plate_box.height, 2);
			cv::putText(input_frame, res->plate_number, textSp, 0, font_scale, cv::Scalar(255, 0, 0), 2, cv::LINE_8);

			auto timenow           = chrono::system_clock::to_time_t(chrono::system_clock::now());
			std::string frame_name = node->logger()->task_dir + "/lp-" + res->plate_number + "_pts-" +
			                         std::to_string(image_packet->get_sync_timestamp()) + "_time-" +
			                         std::to_string(timenow) + ".jpg";

			cv::imwrite(frame_name, input_frame);

			std::cout << "plate confidence: " << to_string(res->plate_confidence)
			          << "\nplate number: " << res->plate_number << "\n";
		}

		std::cout << "\035[0m\n\n\n";
	}

	if (node->output_streams.size() > 0) {
		auto errorCode = node->enqueue(0, results);
		if (errorCode != ErrorCode::OK) {
			BOOST_LOG_SEV(node->logger()->mlogger(), LOG_ERROR)
			    << __func__ << " plate results enqueue to: " << node->output_streams.at(0).first
			    << " failed. ErrorCode: " << errorCode << endl;
			return errorCode;
		}
	}

	if (node->output_streams.size() > 1) {
		nlohmann::json j_all_res;
		for (auto& res : results->plate_results) {
			auto j_res = nlohmann::json{{"video_path", "/some/path"},
			                            {"license_plate", res->plate_number},
			                            {"confidence", to_string(res->plate_confidence)},
			                            {"plate_box",
			                             {{"x", to_string(res->plate_box.x)},
			                              {"y", to_string(res->plate_box.y)},
			                              {"width", to_string(res->plate_box.width)},
			                              {"height", to_string(res->plate_box.height)}}},
			                            {"timestamp", chrono::system_clock::to_time_t(chrono::system_clock::now())}};
			j_all_res.push_back(j_res);
		}

		PacketPtr<JsonPacket> jpkg = make_packet<JsonPacket>(image_packet->get_sync_timestamp(), j_all_res);

		return node->enqueue(1, jpkg);
	}

	return ErrorCode::OK;
}

AUP_AVAF_REGISTER_CALCULATOR("Aupera", "plate_recognizer", PlateRecognizerCalculator, PlateRecognizerOptions,
                             "Aupera's node for recognizing license plates on images.", {})