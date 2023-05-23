// std headers
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <thread>
#include <vector>

// sdk headers
#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

// framework headers
#include "../extern/calculator.h"
#include "../extern/image_packet.h"
#include "../extern/detect_track_packet.h"
#include "../extern/protos/vehicle_classificaiton.pb.h"

#include <vitis/ai/vehicleclassification.hpp>

using namespace std;
using namespace aup::avaf;

// Calculator to print Hello, <NAME> on the frames

class VehicleClassificationCalculator : public aup::avaf::CalculatorBase<VehicleClassificationOptions>
{
std::unique_ptr<vitis::ai::VehicleClassification> model = nullptr;

protected:
	aup::avaf::ErrorCode fill_contract(std::shared_ptr<aup::avaf::Contract>& contract) override {
		//you can put a contract here to validate that pipline pbtxt provides correct input
		//output types to your node.
		return aup::avaf::ErrorCode::OK;
	}

public:
	VehicleClassificationCalculator(const aup::avaf::Node* node) : aup::avaf::CalculatorBase<VehicleClassificationOptions>(node) {}
	~VehicleClassificationCalculator() {}
	aup::avaf::ErrorCode initialize(std::string& err_str) override {
		BOOST_LOG_SEV(node->logger()->mlogger(), LOG_INFO)
		    << "\033[33m" << __func__ << " kernel_name: " << options->kernel_name() << "\033[0m" << endl;
		BOOST_LOG_SEV(node->logger()->mlogger(), LOG_INFO)
		    << "\033[33m" << __func__ << " use_detections: " << options->use_detections() << "\033[0m" << endl;
		BOOST_LOG_SEV(node->logger()->mlogger(), LOG_INFO)
		    << "\033[33m" << __func__ << " print_results: " << options->print_results() << "\033[0m" << endl;

		model = vitis::ai::VehicleClassification::create(options->kernel_name());
		return aup::avaf::ErrorCode::OK;

	}

	aup::avaf::ErrorCode execute(){
		PacketPtr<const DetectionsOrTracks> detections;
		aup::avaf::PacketPtr<const aup::avaf::ImagePacket> img_packet;
		std::vector<cv::Mat> images;
		std::vector<cv::Rect2d> bbxs;

		auto ec = node->get_packet(0, img_packet);
		if (ec != aup::avaf::ErrorCode::OK) {
			BOOST_LOG_SEV(node->logger()->mlogger(), LOG_ERROR) << "\033[33m" << __func__ << 
							" failed to deque frames error: " << ec << "\033[0m\n";			
				return ec;
		}

		//only needed if visualizing on frames
		auto img_packet_mutable  = aup::avaf::const_packet_cast<aup::avaf::ImagePacket>(img_packet);
		
		auto cvframe = img_packet_mutable->get_cv_mat();
		auto batch = model->get_input_batch();

		if(options->use_detections()){
			ec = node->get_packet(1, detections);
			if (ec != aup::avaf::ErrorCode::OK) {
				BOOST_LOG_SEV(node->logger()->mlogger(), LOG_ERROR) << "\033[33m" << __func__ << 
							" failed to deque detections error: " << ec << "\033[0m\n";			
				return ec;
			}
	 
		    for (
		    	auto crop_no = 0u;
		    	crop_no < min(batch, detections->detections_or_live_tracks.size()); ++crop_no
		    ){
		    	auto& detection = detections->detections_or_live_tracks.at(crop_no);
		    	auto cvcrop = cvframe(detection.rect);
		    	images.push_back(cvcrop);
		    	bbxs.push_back(detection.rect);
		    }
		}
		else{
			images.push_back(cvframe);
			bbxs.push_back(cv::Rect2d(5, 5, cvframe.cols, cvframe.rows));
		}

	    auto results = model->run(images);

	    for(auto i = 0u; i < results.size();i++){
	    	auto result = results.at(i);
			string best_label;
			float best_score = -1;
			for (auto& r : result.scores){
				if(options->print_results()){
					BOOST_LOG_SEV(node->logger()->mlogger(), LOG_INFO)
				    	<< "\033[33m\n\n" << __func__ << " vehicle_classificaiton results:\n"
				    	<< "r.index " << r.index << " "  //
					    << result.lookup(r.index) << " "
					    << "r.score " << r.score << "\n\n" << "\033[0m" << endl;
				}

			    if(r.score > best_score){
			    	best_score = r.score;
			    	best_label = result.lookup(r.index);
			    }
			}

			auto& bbox = bbxs.at(i);
			int baseline;
			cv::Size textSize = cv::getTextSize(best_label, options->font(), options->font_scale() ?: 0.6,
			                                    options->font_thickness() ?: 2, &baseline);

			auto bbox_i = DetectionsOrTracks::cvrect2d_to_cvrect2i(bbox, cvframe.size());
			cv::rectangle(cvframe, bbox_i, cv::Scalar(0,255,0), options->box_thickness() ?: 2, 1, 0);
			auto of = 2 * (options->box_thickness() ?: 2);
			cv::Point textSp(bbox_i.x + of + textSize.width > cvframe.cols ? bbox_i.x + of
			                                                             : bbox_i.x + bbox_i.width - textSize.width - of,
			                 bbox_i.y - of > textSize.height ? bbox_i.y - of : bbox_i.y + of + textSize.height);
			cv::putText(cvframe, best_label, textSp, options->font(), options->font_scale() ?: 0.6, cv::Scalar(0,255,0),
			            options->font_thickness() ?: 2, options->line_type() ?: cv::LINE_8);
	    }	


	    ec = node->enqueue(0, img_packet_mutable);
		if (ec != aup::avaf::ErrorCode::OK) {
			BOOST_LOG_SEV(node->logger()->mlogger(), LOG_ERROR) << "\033[33m" << __func__ << 
							" failed to enqueue frames error: " << ec << "\033[0m\n";			
				return ec;
		}
	    

		return aup::avaf::ErrorCode::OK;


/*
		//you can get the immutable frame like this:
		

		//you only need to cast to mutable if you're modifying the packet
		

		
		std::string text = "Hello, " + options->name() + ".";
		cv::putText(cv_mat, text, cv::Point(0, 0), cv::FONT_HERSHEY_COMPLEX, options->font_scale() ?: 0.6,
		            cv::Scalar(0, 0, 255), 2, cv::LINE_8);
		
		//enqueue the frame for next node with your modifications (drawn text)
		
*/
	}
};

AUP_AVAF_REGISTER_CALCULATOR("Aupera", "vehicle_classificaiton", VehicleClassificationCalculator, VehicleClassificationOptions,
                             "calculator to pass frames to clip_generator based on detection results", {});