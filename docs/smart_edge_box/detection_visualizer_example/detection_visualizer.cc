// avaf headers
#include "aup/avaf/calculator.h"
#include "aup/avaf/utils.h"
#include "aup/avap/detection_visualizer.pb.h"

// Include packets
#include "aup/avaf/packets/image_packet.h"
#include "aup/avaf/packets/json_packet.h"

#include <fstream>
#include <vector>

using namespace aup::avaf;

class DetectionVisualizerCalculator
    : public CalculatorBase<DetectionVisualizerOptions> {

  unordered_map<int, cv::Scalar> class_colors;
  cv::Scalar default_class_color;
  vector<string> labels;

protected:
  ErrorCode fill_contract(std::shared_ptr<Contract> &contract,
                          std::string &err_str) override {
    auto sz_input = contract->input_stream_names.size();
    auto sz_output = contract->output_stream_names.size();

    // Make sure that the node has exactly two inputs
    if (sz_input != 2) {
      err_str = "node expects exactly two inputs.";
      return ErrorCode::INVALID_CONTRACT;
    }
    // make sure that the node has exactly one output
    if (sz_output != 1) {
      err_str = "node expects exactly two inputs.";
      return ErrorCode::INVALID_CONTRACT;
    }
    // create sample packets for inputs and outputs for framework to validate
    contract->sample_input_packets[0] = make_packet<JsonPacket>();
    contract->sample_input_packets[1] = make_packet<ImagePacket>();
    contract->sample_output_packets[0] = make_packet<ImagePacket>();
    // Let avaf know that this node is allowed to modify packets on input 1
    contract->input_attrs_arr[1].set_type(
        GraphConfig::Node::InputStreamAttributes::SYNCED_MUTABLE);
    return ErrorCode::OK;
  }

public:
  DetectionVisualizerCalculator(const Node *node) : CalculatorBase(node) {}

  ~DetectionVisualizerCalculator() {}

  ErrorCode initialize(std::string &err_str) override {
    // print the options
    AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_INFO,
                      "options: " << options->DebugString());
    for (int i = 0; i < options->class_color_size(); i++) {
      auto &element = options->class_color(i);
      class_colors.emplace(element.label(),
                           Scalar(element.color().b(), element.color().g(),
                                  element.color().r()));
    }

    if (options->has_default_class_color()) {
      default_class_color = Scalar(options->default_class_color().b(),
                                   options->default_class_color().g(),
                                   options->default_class_color().r());
    } else {
      default_class_color = Scalar(0, 0, 255);
    }
    labels.clear();
    std::ifstream flabels(path);
    if (flabels.fail()) {
      err_str = "Could not load label file"
      return ErrorCode::ERROR;
    }
    string kind;
    while (getline(flabels, kind)) {
      labels.push_back(kind);
    }
    flabels.close();

    return ErrorCode::OK;
  }

  ErrorCode execute() {

    PacketPtr<const JsonPacket> detections = nullptr;
    PacketPtr<ImagePacket> image_packet = nullptr;

    ErrorCode ec = node->get_packet(0, detections);
    if (ec != ErrorCode::OK) {
      AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
                        "Issue getting detections packet");
      return ec;
    }
    ec = node->get_packet(1, image_packet);
    if (ec != ErrorCode::OK) {
      AUP_AVAF_LOG_NODE(node, GraphConfig::LoggingFilter::SEVERITY_ERROR,
                        "Issue getting detections packet");
      return ec;
    }
    cv::Mat frame = image_packet.get_cv_mat();
    for (auto &[key, val], json_packet->_json_object.items()) {
      // check if json starts with "item "
      if (key.rfind("item ", 0) != 0) {
        // does not start with "item "
        continue;
      }
      cv::Rect2i rect(item["x"], item["y"], item["width"], item["height"]);
      cv::rectangle(frame, rect,
                    cv::Scalar(options->box_color().b(),
                               options->box_color().g(),
                               options->box_color().r()),
                    options->box_thickness() ?: 2, 1, 0);
      int class_id = item["box_id"];
      std::string class_str = to_string(class_id);
      if (label_names.size() > class_id) {
        class_str = label_names[class_id];
      }
      cv::Scalar &class_color =
          (class_colors.find(res.class_id) == class_colors.end())
              ? default_class_color
              : class_colors.at(res.class_id);

      int baseline;
      cv::Size textSize = cv::getTextSize(
          class_label, options->font(), options->font_scale() ?: 0.6,
          options->font_thickness() ?: 2, &baseline);
      auto of = 2 * (options->box_thickness() ?: 2);
      cv::Point textSp(res.rect.x + of + textSize.width > frame.cols
                           ? res.rect.x + of - text_offset.x
                           : res.rect.x + res.rect.width - textSize.width - of -
                                 text_offset.x,
                       res.rect.y - of > textSize.height
                           ? res.rect.y - of - text_offset.y
                           : res.rect.y + of + textSize.height - text_offset.y);
      cv::putText(frame, class_label, textSp, options->font(),
                  options->font_scale() ?: 0.6, class_color,
                  options->font_thickness() ?: 2,
                  options->line_type() ?: cv::LINE_8);
    }

    return ErrorCode::OK;
  }
};

AUP_AVAF_REGISTER_CALCULATOR_EXT("aupera", "detection_visualizer",
                                 DetectionVisualizerCalculator,
                                 DetectionVisualizerOptions, true,
                                 "detection_visualizer calculator by aupera.",
                                 {})
