#pragma once

#include "aup/avaf/calculator.h"
#include "aup/avaf/graph.h"
#include "aup/avaf/node.h"
#include "aup/avaf/packets/image_packet.h"
#include "aup/avaf/utils.h"
#include "aup/avap/box_visualizer.pb.h"

#include <opencv2/opencv.hpp>
#include <thread>
#include <unistd.h>

#include "aup/avaf/packets/classification_packet.h"
#include "aup/avaf/packets/detection_packet.h"
#include "aup/avaf/packets/segmentation_packet.h"
#include "aup/avaf/packets/landmark_packet.h"
#include "embedded_landmark_filters.h"

#include <chrono>
#include <memory>
#include <unordered_map>
#include <vector>

using namespace cv;
using namespace std;
using namespace aup::avaf;
using namespace aup::classify;
using namespace aup::detect;
using namespace aup::segment;

class BoxVisualizerCalculator : public CalculatorBase<BoxVisualizerOptions>
{
	unordered_map<int, Scalar> class_colors;
	Scalar default_class_color;
	int init_no;
	Mat landmark_filter;

	ErrorCode handle_detections();
	ErrorCode handle_classifications();
	ErrorCode handle_segmentations();
	ErrorCode handle_landmakrs();
	void visualize_detections(PacketPtr<ImagePacket> image_packet, PacketPtr<const DetectionPacket> detections);
	void visualize_classifications(PacketPtr<ImagePacket> image_packet,
	                               PacketPtr<const Classifications> classifications);
	void visualize_segmentations(PacketPtr<ImagePacket> image_packet, PacketPtr<const Segmentations> segmentations);
	cv::Scalar segmentation_color_map(int label);
	void visualize_landmarks(PacketPtr<ImagePacket> image_packet, PacketPtr<const LandmarksPacket> landmarks);

	void connect_landmarks(const aup::landmark_predict::LandmarkPredictor::PredictedRes& landmark_result,
	                       const cv::Rect2d& bbox, cv::Mat& frame, std::string& landmark_predictor_type);
	double get_landmark_angle(const std::vector<cv::Point2f>& landmarks, int idx1, int idx2, int idx0);
	std::pair<int, int> arms_raised_status(const std::vector<cv::Point2f>& landmarks, const std::string& model_type, 
														const std::string& mode = "height", double angle_threshold = 90.0);
	void apply_filters(cv::Mat& frame, const std::vector<cv::Point2f>& current_landmarks, const std::string& landmark_predictor_type);
	// this is to visualize the tinyYolo classes for retail demo only
	vector<string> labels;
	cv::Point text_offset;

protected:
	ErrorCode fill_contract(std::shared_ptr<Contract>& contract, std::string& err_str) override;

public:
	BoxVisualizerCalculator(const ::aup::avaf::Node* node) : CalculatorBase(node) {}
	~BoxVisualizerCalculator();
	ErrorCode initialize(std::string& err_str) override;
	ErrorCode execute() override;
};