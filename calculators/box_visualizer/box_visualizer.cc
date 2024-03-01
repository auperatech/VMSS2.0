#include "box_visualizer.h"
#include "aup/avaf/thread_name.h"

#include <atomic>
#include <typeinfo>

// #define AUP_AVAF_DBG_ENABLE (1)
#include "aup/avaf/avaf_dbg.h"

static atomic_int init_no_last = 0;

// this is to visualize the tinyYolo classes for retail demo only
int load_labels(string const& path, vector<string>& labels)
{
	labels.clear();
	ifstream flabels(path);
	if (flabels.fail()) {
		fprintf(stderr, "Error : Open %s failed.\n", path.c_str());
		return -1;
	}
	string kind;
	while (getline(flabels, kind)) {
		labels.push_back(kind);
	}
	flabels.close();
	return 0;
}

BoxVisualizerCalculator::~BoxVisualizerCalculator() {}

static bool is_cvrect2d_empty(const cv::Rect2d& bbox)
{
	// return (bbox.width <= 0 || bbox.height <= 0 || bbox.x >= 1 || bbox.y >= 1 || bbox.x + bbox.width <= 0 ||
	//         bbox.y + bbox.height <= 0);

	return (bbox.width <= 0 || bbox.height <= 0 || bbox.x + bbox.width <= 0 || bbox.y + bbox.height <= 0);
}

ErrorCode BoxVisualizerCalculator::initialize(std::string&)
{
	this->init_no = ++init_no_last;
	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[33m" << __func__ << " box visualizer options:"
	                             << "\033[0m");

	if (options->label_name_file() != "") {
		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
		                  "\033[33m" << __func__ << " label_name_file = " << options->label_name_file() << "\033[0m");
		load_labels(options->label_name_file(), labels);
	}

	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[33m" << __func__ << " input type = " << options->input_type() << "\033[0m");
	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[33m" << __func__ << " box thickness = " << options->box_thickness() << "\033[0m");
	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[33m" << __func__ << " text size = " << options->text_size() << "\033[0m");
	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[33m" << __func__ << " font = " << options->font() << "\033[0m");
	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[33m" << __func__ << " line type = " << options->line_type() << "\033[0m");

	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[33m" << __func__ << " text color r: " << options->text_color().r() << ", g: "
	                             << options->text_color().g() << ", b: " << options->text_color().b() << "\033[0m");

	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[33m" << __func__ << " box color r: " << options->box_color().r() << ", g: "
	                             << options->box_color().g() << ", b: " << options->box_color().b() << "\033[0m");

	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[33m" << __func__ << " text offset x: " << options->text_offset().x()
	                             << ", y: " << options->text_offset().y() << "\033[0m");

	for (int i = 0; i < options->class_color_size(); i++) {
		auto& element = options->class_color(i);
		class_colors.emplace(element.label(), Scalar(element.color().b(), element.color().g(), element.color().r()));
		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
		                  "\033[33m" << __func__ << " class color class: " << element.label()
		                             << " color r: " << element.color().r() << ", g: " << element.color().g()
		                             << ", b: " << element.color().b() << "\033[0m");
	}

	if (options->has_default_class_color()) {
		default_class_color = Scalar(options->default_class_color().b(), options->default_class_color().g(),
		                             options->default_class_color().r());
	} else {
		default_class_color = Scalar(0, 0, 255);
	}

	text_offset = cv::Point(options->text_offset().x(), options->text_offset().y());

	if (options->input_type() == BoxVisualizerOptions::INPUT_TYPE_SEGMENTATION) {
		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
		                  "\033[33m" << __func__ << " overlay opacity = " << options->overlay_opacity() << "\033[0m");
	}

	if (options->apply_filter_on_landmarks() == "hat") {
		// Decode the embedded landmark_filter image
		cv::Mat hat_raw_data(1, hat_png_len, CV_8UC1, hat_png);
		landmark_filter = cv::imdecode(hat_raw_data, cv::IMREAD_UNCHANGED);
		if(landmark_filter.empty()) {
			AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_WARN, "\033[33mFailed to decode embedded landmark_filter image.\033[0m");
		}
	}	
	else if (options->apply_filter_on_landmarks() == "mask") {
		// Decode the embedded landmark_filter image
		cv::Mat hat_raw_data(1, mask_png_len, CV_8UC1, mask_png);
		landmark_filter = cv::imdecode(hat_raw_data, cv::IMREAD_UNCHANGED);
		if(landmark_filter.empty()) {
			AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_WARN, "\033[33mFailed to decode embedded landmark_filter image.\033[0m");
		}
	}	

	AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
	                  "\033[34m"
	                      << "        box_visualizer initialzied with input size: " << node->input_streams.size()
	                      << ", output size: " << node->output_streams.size() << "\033[0m");

	return ErrorCode::OK;
}

ErrorCode BoxVisualizerCalculator::fill_contract(shared_ptr<Contract>& contract, string& err_str)
{
	auto sz_input  = contract->input_stream_names.size();
	auto sz_output = contract->output_stream_names.size();

	AUP_AVAF_TRACE();

	if (sz_input != 2) {
		AUP_AVAF_TRACE();
		err_str = "node expects exactly two inputs.";
		return ErrorCode::INVALID_CONTRACT;
	}

	if (sz_output > 1) {
		AUP_AVAF_TRACE();
		err_str = "node cannot have more than 1 output.";
		return ErrorCode::INVALID_CONTRACT;
	}

	AUP_AVAF_TRACE();

	if (options->input_type() == BoxVisualizerOptions::INPUT_TYPE_DETECTION) {
		vector<aup::detect::Detector::DetectedObject> res;
		contract->sample_input_packets[0] = make_packet<DetectionPacket>(0, 0, 0, res, 0);
	} else if (options->input_type() == BoxVisualizerOptions::INPUT_TYPE_CLASSIFICATION) {
		vector<Classifier::ClassifiedRes> res;
		vector<Rect2d> bboxes;
		contract->sample_input_packets[0] = make_packet<Classifications>(0, res, 0, bboxes);
	} else if (options->input_type() == BoxVisualizerOptions::INPUT_TYPE_SEGMENTATION) {
		aup::segment::Segmentor::SegmentedRes res;
		std::string segmentor_type;
		contract->sample_input_packets[0] = make_packet<Segmentations>(0, res, segmentor_type, 0, 0);
	} else if (options->input_type() == BoxVisualizerOptions::INPUT_TYPE_LANDMARK) {
		vector<vector<aup::landmark_predict::LandmarkPredictor::PredictedRes>> res;
		vector<Rect2d> bboxes;
		string landmark_predictor_type;
		contract->sample_input_packets[0] = make_packet<LandmarksPacket>(0, res, 0, bboxes, landmark_predictor_type);
	} else  {
		err_str = "unknown input type " + to_string(options->input_type());
		AUP_AVAF_TRACE();
		return ErrorCode::INVALID_CONTRACT;
	}
	AUP_AVAF_TRACE();
	contract->sample_input_packets[1] = make_packet<ImagePacket>();
	// contract->input_attrs_arr[1].set_type(GraphConfig::Node::InputStreamAttributes::SYNCED_MUTABLE);
	AUP_AVAF_TRACE();

	if (sz_output > 0) {
		contract->sample_output_packets[0] = make_packet<ImagePacket>();
	}

	return ErrorCode::OK;
}

void BoxVisualizerCalculator::visualize_detections(PacketPtr<ImagePacket> image_packet,
                                                   PacketPtr<const DetectionPacket> detections)
{
	AUP_AVAF_DBG_NODE(node, "detections: " << *detections.get());
	auto frame = image_packet->get_cv_mat();

	for (auto& res : detections->detections) {
		cv::rectangle(frame, res.rect,
		              cv::Scalar(options->box_color().b(), options->box_color().g(), options->box_color().r()),
		              options->box_thickness() ?: 2, 1, 0);

		// this is to visualize the tinyYolo classes for retail demo only
		if (options->label_name_file() != "") {
			Scalar& class_color = (class_colors.find(res.class_id) == class_colors.end())
			                          ? default_class_color
			                          : class_colors.at(res.class_id);

			std::string class_label = (res.class_id < (int)labels.size()) ? labels.at(res.class_id) : "unknownClass";

			int baseline;
			cv::Size textSize = cv::getTextSize(class_label, options->font(), options->font_scale() ?: 0.6,
			                                    options->font_thickness() ?: 2, &baseline);
			auto of           = 2 * (options->box_thickness() ?: 2);
			cv::Point textSp(res.rect.x + of + textSize.width > frame.cols
			                     ? res.rect.x + of - text_offset.x
			                     : res.rect.x + res.rect.width - textSize.width - of - text_offset.x,
			                 res.rect.y - of > textSize.height ? res.rect.y - of - text_offset.y
			                                                   : res.rect.y + of + textSize.height - text_offset.y);
			cv::putText(frame, class_label, textSp, options->font(), options->font_scale() ?: 0.6, class_color,
			            options->font_thickness() ?: 2, options->line_type() ?: cv::LINE_8);
		}
	}
}

ErrorCode BoxVisualizerCalculator::handle_detections()
{
	PacketPtr<const DetectionPacket> detections     = nullptr;
	PacketPtr<ImagePacket> image_packet             = nullptr;
	PacketPtr<const ImagePacket> image_packet_const = nullptr;

	auto ret_det   = node->get_packet(0, detections);
	auto ret_frame = node->get_packet(1, image_packet_const);

	AUP_AVAF_DBG_NODE(node, "node EXECUTE with sts:" << detections->get_sync_timestamp() << ","
	                                                 << image_packet_const->get_sync_timestamp());

	if (ret_frame != ErrorCode::OK) {
		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
		                  "\033[33m" << __func__ << " failed to deque frame.\033[0m ");
		return ret_frame;
	}

	image_packet = const_packet_cast<ImagePacket>(image_packet_const);

	if (ret_det == ErrorCode::OK) {
		visualize_detections(image_packet, detections);
	}

	auto frame = image_packet->get_cv_mat();
	if (node->output_streams.size() == 0) {
		auto timenow           = chrono::system_clock::to_time_t(chrono::system_clock::now());
		std::string frame_name = Logger::get()->get_task_dir() + "/frame-" + std::to_string(detections->frame_number) +
		                         "_sts-" + std::to_string(image_packet->get_sync_timestamp()) + "_time-" +
		                         std::to_string(timenow) + ".jpg";

		cv::imwrite(frame_name, frame);

		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
		                  "\033[33m" << __func__ << " wrote output frame:" << frame_name << "to disk."
		                             << "\033[0m");
		return ErrorCode::OK;
	}

	return node->enqueue(0, image_packet);
}

void BoxVisualizerCalculator::visualize_classifications(PacketPtr<ImagePacket> image_packet,
                                                        PacketPtr<const Classifications> classifications)
{
	if (classifications->get_sync_timestamp() != image_packet->get_sync_timestamp()) {
		std::string er = "\033[33mbox_visualizer node: the sync_timestamp of the frame does not match the "
		                 "sync_timestamp of the meta with"
		                 " detected bounding boxes. You probabaly forgot to synchronize the inputs.\033[0m";
		AUP_AVAF_RUNTIME_ERROR(er);
	}

	if (classifications->results.classifications.size() != classifications->results.bboxes.size()) {
		AUP_AVAF_RUNTIME_ERROR("\033[33mbox_visualizer node:number of classification labels and classification "
		                       "bounding boxes do not match.\033[0m");
	}

	auto frame = image_packet->get_cv_mat();

	for (int i = 0; i < (int)classifications->results.bboxes.size(); i++) {
		auto& clas          = classifications->results.classifications.at(i);
		auto& bbox          = classifications->results.bboxes.at(i);
		Scalar& class_color = (class_colors.find(clas.best_res.index) == class_colors.end())
		                          ? default_class_color
		                          : class_colors.at(clas.best_res.index);

		string final_best_class_label = clas.best_res.label;
		if (options->label_name_file() != "") {
			final_best_class_label =
			    (clas.best_res.index < (int)labels.size()) ? labels.at(clas.best_res.index) : "unknownClass";
		}

		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
		                  "\033[33m" << __func__ << " best classified index: " << clas.best_res.index
		                             << ", best classified label: " << clas.best_res.label
		                             << ", final_best_class_label: " << final_best_class_label << ", bbox.x: " << bbox.x
		                             << ", bbox.y: " << bbox.y << "\033[0m");

		int baseline;

		cv::Size textSize = cv::getTextSize(final_best_class_label, options->font(), options->font_scale() ?: 0.6,
		                                    options->font_thickness() ?: 2, &baseline);
		if (is_cvrect2d_empty(bbox)) {
			cv::Point textSp(0 - text_offset.x, textSize.height - text_offset.y);
			cv::putText(frame, final_best_class_label, textSp, options->font(), options->font_scale() ?: 0.6,
			            class_color, options->font_thickness() ?: 2, options->line_type() ?: cv::LINE_8);
			continue;
		}

		auto bbox_i = DetectionPacket::cvrect2d_to_cvrect2i(bbox, frame.size());
		cv::rectangle(frame, bbox_i, class_color, options->box_thickness() ?: 2, 1, 0);
		auto of = 2 * (options->box_thickness() ?: 2);
		cv::Point textSp(bbox_i.x + of + textSize.width > frame.cols
		                     ? bbox_i.x + of - text_offset.x
		                     : bbox_i.x + bbox_i.width - textSize.width - of - text_offset.x,
		                 bbox_i.y - of > textSize.height ? bbox_i.y - of - text_offset.y
		                                                 : bbox_i.y + of + textSize.height - text_offset.y);

		cv::putText(frame, final_best_class_label, textSp, options->font(), options->font_scale() ?: 0.6, class_color,
		            options->font_thickness() ?: 2, options->line_type() ?: cv::LINE_8);
	}
}

ErrorCode BoxVisualizerCalculator::handle_classifications()
{
	PacketPtr<const Classifications> classifications = nullptr;
	PacketPtr<ImagePacket> image_packet              = nullptr;
	PacketPtr<const ImagePacket> image_packet_const  = nullptr;

	auto ret_frame = node->get_packet(1, image_packet_const);
	auto ret_class = node->get_packet(0, classifications);

	if (ret_frame != ErrorCode::OK) {
		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
		                  "\033[33m" << __func__ << " failed to deque frame."
		                             << "\033[0m");
		return ret_frame;
	}

	image_packet = const_packet_cast<ImagePacket>(image_packet_const);

	if (ret_class == ErrorCode::OK) {
		visualize_classifications(image_packet, classifications);
	}

	auto frame = image_packet->get_cv_mat();

	if (node->output_streams.size() == 0) {
		auto timenow           = chrono::system_clock::to_time_t(chrono::system_clock::now());
		std::string frame_name = Logger::get()->get_task_dir() + "/calc-" + std::to_string(init_no) + "_frame-" +
		                         std::to_string(classifications->results.frame_number) + "_sts-" +
		                         std::to_string(image_packet->get_sync_timestamp()) + "_time-" +
		                         std::to_string(timenow) + ".jpg";

		cv::imwrite(frame_name, frame);

		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
		                  "\033[33m" << __func__ << " wrote output frame:" << frame_name << " to disk."
		                             << "\033[0m");
		return ErrorCode::OK;
	}

	return node->enqueue(0, image_packet);
}

cv::Scalar BoxVisualizerCalculator::segmentation_color_map(int label)
{
	static cv::Scalar table[80] = {
	    {41, 215, 206},  {40, 136, 255},  {66, 211, 46},   {168, 29, 134}, {145, 253, 52},  {173, 100, 99},
	    {113, 27, 229},  {177, 161, 16},  {17, 217, 46},   {227, 157, 70}, {206, 249, 35},  {164, 225, 245},
	    {16, 3, 124},    {33, 11, 240},   {187, 70, 199},  {62, 19, 108},  {62, 51, 172},   {168, 110, 113},
	    {72, 62, 84},    {245, 143, 170}, {234, 228, 0},   {1, 169, 30},   {32, 34, 168},   {207, 4, 155},
	    {172, 133, 179}, {230, 111, 194}, {21, 165, 138},  {163, 64, 51},  {2, 65, 7},      {229, 214, 12},
	    {209, 209, 221}, {49, 191, 177},  {140, 135, 150}, {137, 32, 97},  {52, 6, 157},    {248, 81, 39},
	    {212, 60, 86},   {130, 215, 115}, {44, 177, 241},  {219, 60, 37},  {100, 124, 189}, {63, 135, 50},
	    {162, 204, 97},  {84, 221, 181},  {83, 139, 119},  {169, 34, 230}, {125, 6, 159},   {217, 99, 100},
	    {218, 17, 54},   {53, 138, 43},   {71, 215, 225},  {109, 5, 86},   {211, 10, 133},  {208, 214, 9},
	    {13, 93, 10},    {190, 143, 46},  {201, 204, 109}, {42, 23, 46},   {30, 216, 194},  {103, 35, 29},
	    {97, 31, 71},    {189, 103, 156}, {105, 249, 121}, {22, 188, 210}, {113, 158, 9},   {166, 158, 31},
	    {253, 172, 135}, {158, 145, 45},  {111, 225, 98},  {115, 204, 90}, {197, 108, 244}, {176, 109, 0},
	    {205, 63, 88},   {138, 130, 20},  {2, 25, 3},      {179, 60, 246}, {66, 104, 40},   {224, 126, 196},
	    {218, 149, 152}, {39, 124, 172}};
	return table[label % 80];
}

void BoxVisualizerCalculator::visualize_segmentations(PacketPtr<ImagePacket> image_packet,
                                                      PacketPtr<const Segmentations> segmentations)
{
	if (segmentations->get_sync_timestamp() != image_packet->get_sync_timestamp()) {
		std::string er = "\033[33mbox_visualizer node: the sync_timestamps of the frame does not match the "
		                 "sync_timestamp of the meta with"
		                 " segmentation results. You probabaly forgot to synchronize the inputs.\033[0m";
		AUP_AVAF_RUNTIME_ERROR(er);
	}

	auto frame = image_packet->get_cv_mat();

	if (segmentations->results.segmentor_type == "Segmentation2D") {

		auto opacity        = options->overlay_opacity();
		auto segmented_mask = segmentations->results.segmentations.seg_res[0];

		if (frame.size() != segmented_mask.size()) {
			cv::resize(segmented_mask, segmented_mask, frame.size(), 0, 0, 0);
			AUP_AVAF_LOG_NODE(
			    node, GraphConfig::LoggingFilter::SEVERITY_WARN,
			    "\033[33mbox_visualizer node: the size of the frame does not match the size of the segmented mask."
			    " The mask has been resized to the frame size with the nearest neighbor interpolation.\033[0m");
		}

		for (auto row_ind = 0; row_ind < frame.size().height; ++row_ind) {
			for (auto col_ind = 0; col_ind < frame.size().width; ++col_ind) {
				cv::Scalar color_c3 = segmentation_color_map((int)segmented_mask.at<uchar>(row_ind, col_ind));
				frame.at<cv::Vec3b>(row_ind, col_ind) = cv::Vec3b(color_c3[0], color_c3[1], color_c3[2]) * opacity +
				                                        frame.at<cv::Vec3b>(row_ind, col_ind) * (1 - opacity);
			}
		}
	}
}

ErrorCode BoxVisualizerCalculator::handle_segmentations()
{
	PacketPtr<const Segmentations> segmentations    = nullptr;
	PacketPtr<ImagePacket> image_packet             = nullptr;
	PacketPtr<const ImagePacket> image_packet_const = nullptr;

	auto ret_seg   = node->get_packet(0, segmentations);
	auto ret_frame = node->get_packet(1, image_packet_const);

	if (ret_frame != ErrorCode::OK) {
		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
		                  "\033[33m" << __func__ << " failed to deque frame.\033[0m ");
		return ret_frame;
	}

	image_packet = const_packet_cast<ImagePacket>(image_packet_const);

	if (ret_seg == ErrorCode::OK) {
		visualize_segmentations(image_packet, segmentations);
	}

	auto frame = image_packet->get_cv_mat();
	if (node->output_streams.size() == 0) {
		auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
		std::string frame_name =
		    Logger::get()->get_task_dir() + "/frame-" + std::to_string(segmentations->results.frame_number) + "_sts-" +
		    std::to_string(image_packet->get_sync_timestamp()) + "_time-" + std::to_string(timenow) + ".jpg";

		cv::imwrite(frame_name, frame);

		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
		                  "\033[33m" << __func__ << " wrote output frame:" << frame_name << "to disk."
		                             << "\033[0m");
		return ErrorCode::OK;
	}

	return node->enqueue(0, image_packet);
}


void BoxVisualizerCalculator::connect_landmarks(const aup::landmark_predict::LandmarkPredictor::PredictedRes& landmark_result,
                                                       const cv::Rect2d& bbox, cv::Mat& frame, std::string& landmark_predictor_type) {
	/*
	Movenet:
	[1: 'left_eye', 2: 'right_eye', 3: 'left_ear', 4: 'right_ear', 5: 'left_shoulder', 
	6: 'right_shoulder', 7: 'left_elbow', 8: 'right_elbow', 9: 'left_wrist', 10 : 'right_wrist', 
	11: 'left_hip', 12: 'right_hip', 13: 'left_knee', 14: 'right_knee', 15: 'left_ankle', 16: 'right_ankle']

	Openpose:
	[0: head, 1: neck, 2: L_shoulder, 3:L_elbow, 4: L_wrist, 5: R_shoulder, 6: R_elbow, 7: R_wrist, 8: L_hip, 9:L_knee, 10: L_ankle, 11: R_hip, 12: R_knee, 13: R_ankle]

	hourglass:
	[0 - r ankle, 1 - r knee, 2 - r hip, 3 - l hip, 4 - l knee, 5 - l ankle, 6 - pelvis, 7 - thorax, 8 - upper neck, 9 - head top, 10 - r wrist, 11 - r elbow, 12 - r shoulder, 13 - l shoulder, 14 - l elbow, 15 - l wrist]
	*/

    std::vector<std::vector<int>> limbSeq;

    if (landmark_predictor_type == "Movenet") {
        limbSeq = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {5, 7}, {7, 9}, {6, 8}, {8, 10}, {5, 11}, {6, 12}, {11, 13}, {13, 15}, {12, 14}, {14, 16}};
    } else if (landmark_predictor_type == "Hourglass") {
        limbSeq = {{0, 1}, {1, 2}, {2, 6}, {3, 6},  {3, 4}, {4, 5}, {6, 7}, {7, 8}, {8, 9}, {7, 12}, {12, 11}, {11, 10}, {7, 13}, {13, 14}, {14, 15}};
    } else if (landmark_predictor_type == "Openpose") {
        limbSeq = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {1, 5}, {5, 6}, {6, 7}, {1, 8}, {8, 9}, {9, 10}, {1, 11}, {11, 12}, {12, 13}};
    }

    for (size_t j = 0; j < limbSeq.size(); ++j) {
        if (limbSeq[j][0] < static_cast<int>(landmark_result.landmarks.size()) && limbSeq[j][1] < static_cast<int>(landmark_result.landmarks.size())) {
            cv::Point a = cv::Point(landmark_result.landmarks[limbSeq[j][0]].x * landmark_result.input_width + bbox.x, 
                                    landmark_result.landmarks[limbSeq[j][0]].y * landmark_result.input_height + bbox.y);
            cv::Point b = cv::Point(landmark_result.landmarks[limbSeq[j][1]].x * landmark_result.input_width + bbox.x, 
                                    landmark_result.landmarks[limbSeq[j][1]].y * landmark_result.input_height + bbox.y);
            cv::line(frame, a, b, cv::Scalar(0, 255, 0), 3, 4);
        }
    }
}


double BoxVisualizerCalculator::get_landmark_angle(const std::vector<cv::Point2f>& landmarks, int idx1, int idx2, int idx0) {
    // Check if the indices are valid
    if (static_cast<int>(landmarks.size()) > std::max({idx1, idx2, idx0})) {
        // Compute the vectors
        cv::Point2f a = landmarks[idx1] - landmarks[idx0];
        cv::Point2f b = landmarks[idx2] - landmarks[idx0];

        // Compute the dot product and magnitudes
        double dot_product = a.x * b.x + a.y * b.y;
        double mag_a = cv::norm(a);
        double mag_b = cv::norm(b);

        // Compute and return the angle in degrees
        double angle = acos(dot_product / (mag_a * mag_b)) * 180.0 / CV_PI;
        return angle;
    }

    // Return 0.0 if indices are not valid
    return 0.0;
}


std::pair<int, int> BoxVisualizerCalculator::arms_raised_status(const std::vector<cv::Point2f>& landmarks, const std::string& model_type, const std::string& mode, double angle_threshold) {
    
    bool left_raised = false, right_raised = false;

    // check angles between landmarks
    if (mode == "angles") {
        double left_angle = 0;
		double right_angle = 0;

        if (model_type == "Movenet") {
            // For left arm: angles between vectors (left_elbow-left_shoulder) & (left_hip-left_shoulder) 
            // and (left_wrist-left_shoulder) & (left_hip-left_shoulder)
            left_angle = std::max(
                get_landmark_angle(landmarks, 7, 11, 5), 
                get_landmark_angle(landmarks, 9, 11, 5)
            );
            // For right arm: angles between vectors (right_elbow-right_shoulder) & (right_hip-right_shoulder) 
            // and (right_wrist-right_shoulder) & (right_hip-right_shoulder)
            right_angle = std::max(
                get_landmark_angle(landmarks, 8, 12, 6), 
                get_landmark_angle(landmarks, 10, 12, 6)
            );
        } 
        else if (model_type == "Openpose") {
            left_angle = std::max(
                get_landmark_angle(landmarks, 3, 8, 2), 
                get_landmark_angle(landmarks, 4, 8, 2)
            );
            right_angle = std::max(
                get_landmark_angle(landmarks, 6, 11, 5), 
                get_landmark_angle(landmarks, 7, 11, 5)
            );
        }
        else if (model_type == "Hourglass") {
            left_angle = std::max(
                get_landmark_angle(landmarks, 14, 3, 13), 
                get_landmark_angle(landmarks, 10, 3, 13)
            );
            right_angle = std::max(
                get_landmark_angle(landmarks, 11, 2, 12), 
                get_landmark_angle(landmarks, 10, 2, 12)
            );
        }

        left_raised = left_angle > angle_threshold;
        right_raised = right_angle > angle_threshold;
    } 

    else {
        // Check y-coordinates
        if (model_type == "Movenet") {
            // For Movenet, simply check y-coordinate of elbow (7, 8) or wrist (9, 10) is higher than shoulder (5, 6)
            left_raised = (landmarks.size() > 7 && landmarks[7].y < landmarks[5].y) || (landmarks.size() > 9 && landmarks[9].y < landmarks[5].y); 
            right_raised = (landmarks.size() > 8 && landmarks[8].y < landmarks[6].y) || (landmarks.size() > 10 && landmarks[10].y < landmarks[6].y);
        } 
        else if (model_type == "Openpose") {
            // For Openpose, simply check y-coordinate of elbow (3, 6) or wrist (4, 7) is higher than shoulder (2, 5)
            left_raised = (landmarks.size() > 3 && landmarks[3].y < landmarks[2].y) || (landmarks.size() > 4 && landmarks[4].y < landmarks[2].y); 
            right_raised = (landmarks.size() > 6 && landmarks[6].y < landmarks[5].y) || (landmarks.size() > 7 && landmarks[7].y < landmarks[5].y);
        }
        else if (model_type == "Hourglass") {
            // For Hourglass, simply check y-coordinate of elbow (14, 11) or wrist (15, 10) is higher than shoulder (13, 12)
            left_raised = (landmarks.size() > 14 && landmarks[14].y < landmarks[13].y) || (landmarks.size() > 15 && landmarks[15].y < landmarks[13].y); 
            right_raised = (landmarks.size() > 12 && landmarks[11].y < landmarks[12].y) || (landmarks.size() > 12 && landmarks[10].y < landmarks[12].y);
        }
    }

    return {left_raised, right_raised};
}

void BoxVisualizerCalculator::apply_filters(cv::Mat& frame, const std::vector<cv::Point2f>& current_landmarks, const std::string& landmark_predictor_type) {
	
	cv::Point2f head_center;
	auto half_head_size = 60.0;

    if (landmark_predictor_type == "Movenet") {
        if (current_landmarks.size() < 5) return;
        head_center = (current_landmarks[1] + current_landmarks[2] + current_landmarks[3] + current_landmarks[4]) / 4;
        half_head_size = std::abs(current_landmarks[3].x - current_landmarks[4].x) * 1.2;
    } 
    else if (landmark_predictor_type == "Openpose") {
        if (current_landmarks.size() < 2) return;
        head_center = (current_landmarks[0] + current_landmarks[1]) * 0.5;
        half_head_size = std::abs(current_landmarks[0].x - current_landmarks[1].x) * 1.5;
    }
    else if (landmark_predictor_type == "Hourglass") {
        if (current_landmarks.size() < 10) return;
        head_center = (current_landmarks[9] + current_landmarks[8]) * 0.5;
        half_head_size = std::abs(current_landmarks[8].x - current_landmarks[9].x) * 1.2;
    }
    else if (landmark_predictor_type == "RetinaFace" || landmark_predictor_type == "FaceLandmark") {
        if (current_landmarks.size() < 2) return;
        head_center = (current_landmarks[0] + current_landmarks[1]) / 2;
        half_head_size = std::abs(current_landmarks[1].x - current_landmarks[0].x) * 2;
    } 

	half_head_size = std::clamp(half_head_size, 40.0, 140.0); // Due to the variation of false predictions, clamp the filter size to a certain range 

	if (options->apply_filter_on_landmarks() == "bbox") {
		cv::Rect head_bbox(head_center.x - half_head_size, head_center.y - half_head_size, 2 * half_head_size, 2 * half_head_size);
		cv::rectangle(frame, head_bbox, cv::Scalar(255, 255, 0), 2);
		return;
	}
		
	// Use the half_head_size to determine the hat size, ensuring it's similar to the head bounding box
	int hat_width = 2 * half_head_size;
	int hat_height = landmark_filter.rows * hat_width / landmark_filter.cols;  // Keep the aspect ratio

	// Resize the hat image
	cv::Mat resized_landmark_filter;
	cv::resize(landmark_filter, resized_landmark_filter, cv::Size(hat_width, hat_height));

	// Overlay the filter on the frame, making sure it starts from the top of the head bounding box
	int startY = head_center.y;
	if (options->apply_filter_on_landmarks() == "hat") {
		startY = head_center.y - half_head_size * 2;
	}
	else if (options->apply_filter_on_landmarks() == "mask") {
		startY = head_center.y - half_head_size;
	}
	int startX = head_center.x - hat_width / 2;

	for (int y = 0; y < resized_landmark_filter.rows; y++) {
		for (int x = 0; x < resized_landmark_filter.cols; x++) {
			// Only overlay pixels that are not fully transparent
			if (resized_landmark_filter.at<cv::Vec4b>(y, x)[3] > 0) {
				cv::Vec3b hatColor = cv::Vec3b(
					resized_landmark_filter.at<cv::Vec4b>(y, x)[0],
					resized_landmark_filter.at<cv::Vec4b>(y, x)[1],
					resized_landmark_filter.at<cv::Vec4b>(y, x)[2]
				);
				frame.at<cv::Vec3b>(startY + y, startX + x) = hatColor;
			}
		}
	}
}


void BoxVisualizerCalculator::visualize_landmarks(PacketPtr<ImagePacket> image_packet,
                                                        PacketPtr<const LandmarksPacket> landmarks)
{
	if (landmarks->get_sync_timestamp() != image_packet->get_sync_timestamp()) {
		std::string er = "\033[33mbox_visualizer node: the sync_timestamp of the frame does not match the "
		                 "sync_timestamp of the meta with"
		                 " detected bounding boxes. You probabaly forgot to synchronize the inputs.\033[0m";
		AUP_AVAF_RUNTIME_ERROR(er);
	}

	if (landmarks->results.landmarks.size() != landmarks->results.bboxes.size()) {
		AUP_AVAF_RUNTIME_ERROR("\033[33mbox_visualizer node:number of landmarks  and  detected "
		                       "bounding boxes do not match.\033[0m");
	}

	auto frame = image_packet->get_cv_mat();
	std::string landmark_predictor_type = landmarks->results.landmark_predictor_type;
	bool is_pose_model = (landmark_predictor_type == "Movenet" || landmark_predictor_type == "Hourglass" ||  landmark_predictor_type == "Openpose");

	for (int i = 0; i < (int)landmarks->results.bboxes.size(); i++) {
		auto& lmark         = landmarks->results.landmarks.at(i);
		auto& bbox          = landmarks->results.bboxes.at(i);
		cv::Scalar class_color = {0, 0, 255};

		auto bbox_i = DetectionPacket::cvrect2d_to_cvrect2i(bbox, frame.size());
		cv::rectangle(frame, bbox_i, class_color, options->box_thickness() ?: 2, 1, 0);

		for (auto& single_obj_lmark : lmark) {
			auto rect_h  = single_obj_lmark.input_height;
			auto rect_w = single_obj_lmark.input_width;
			std::vector<cv::Point2f> current_landmarks;
			for (auto& r : single_obj_lmark.landmarks) {
				auto p = cv::Point(r.x * rect_w + bbox.x, r.y * rect_h + bbox.y);
				current_landmarks.push_back(p);
				cv::circle(frame, p, 5, cv::Scalar(0, 0, 255), cv::FILLED);
			}

			auto bbox_from_lmark_model = single_obj_lmark.class_bbox;

			// for some landmark models (retinaface), the predicted results contains bboxes.
			if (is_cvrect2d_empty(bbox) && !is_cvrect2d_empty(bbox_from_lmark_model)){
				auto retina_bbox_i = DetectionPacket::cvrect2d_to_cvrect2i(bbox_from_lmark_model, frame.size());
				cv::rectangle(frame, retina_bbox_i, cv::Scalar(0, 255, 0), options->box_thickness() ?: 2, 1, 0);
			}

			if (options->connect_landmarks() && is_pose_model) {
				connect_landmarks(single_obj_lmark, bbox, frame, landmark_predictor_type);
			}

			if (!options->apply_filter_on_landmarks().empty()) {
				
				if (!options->arm_raise_check().empty() && is_pose_model) {
					bool apply_filter = false; 
					// Check arm status
					auto arm_status = arms_raised_status(current_landmarks, landmark_predictor_type, options->arm_raise_check());

					std::string arm_text;
					if (arm_status.first && arm_status.second) {
						arm_text = "[left, right]";
					} else if (arm_status.first) {
						arm_text = "[left, /]";
					} else if (arm_status.second) {
						arm_text = "[/, right]";
					} else {
						arm_text = "[/, /]";
					}

					// Display arm status on top of the bbox
					cv::putText(frame, arm_text, cv::Point(bbox.x, bbox.y-10), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);

					if (arm_status.first || arm_status.second) {
						apply_filter = true;
					}

					if (apply_filter) {
						apply_filters(frame, current_landmarks, landmark_predictor_type);
					}
				}
				else {
					apply_filters(frame, current_landmarks, landmark_predictor_type);
				}
			}
		}
	}
}


ErrorCode BoxVisualizerCalculator::handle_landmakrs()
{
	PacketPtr<const LandmarksPacket> landmakrs = nullptr;
	PacketPtr<ImagePacket> image_packet              = nullptr;
	PacketPtr<const ImagePacket> image_packet_const  = nullptr;
	auto ret_frame = node->get_packet(1, image_packet_const);
	auto ret_class = node->get_packet(0, landmakrs);

	if (ret_frame != ErrorCode::OK) {
		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
		                  "\033[33m" << __func__ << " failed to deque frame."
		                             << "\033[0m");
		return ret_frame;
	}

	image_packet = const_packet_cast<ImagePacket>(image_packet_const);

	if (ret_class == ErrorCode::OK) {
		visualize_landmarks(image_packet, landmakrs);
	}

	auto frame = image_packet->get_cv_mat();

	if (node->output_streams.size() == 0) {
		auto timenow           = chrono::system_clock::to_time_t(chrono::system_clock::now());
		std::string frame_name = Logger::get()->get_task_dir() + "/calc-" + std::to_string(init_no) + "_frame-" +
		                         std::to_string(landmakrs->results.frame_number) + "_sts-" +
		                         std::to_string(image_packet->get_sync_timestamp()) + "_time-" +
		                         std::to_string(timenow) + ".jpg";

		cv::imwrite(frame_name, frame);

		AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
		                  "\033[33m" << __func__ << " wrote output frame:" << frame_name << " to disk."
		                             << "\033[0m");
		return ErrorCode::OK;
	}

	return node->enqueue(0, image_packet);
}

ErrorCode BoxVisualizerCalculator::execute()
{
	switch (options->input_type()) {
		case BoxVisualizerOptions_InputType_INPUT_TYPE_DETECTION:
			return handle_detections();
		case BoxVisualizerOptions_InputType_INPUT_TYPE_CLASSIFICATION:
			return handle_classifications();
		case BoxVisualizerOptions_InputType_INPUT_TYPE_SEGMENTATION:
			return handle_segmentations();
		case BoxVisualizerOptions_InputType_INPUT_TYPE_LANDMARK:
			return handle_landmakrs();
		default:
			break;
	}
	return ErrorCode::INVALID;
}

AUP_AVAF_REGISTER_CALCULATOR("Aupera", "box_visualizer", BoxVisualizerCalculator, BoxVisualizerOptions,
                             "Aupera's box visualizer calculator.", {})
