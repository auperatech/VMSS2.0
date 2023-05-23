#pragma once

#include <any>
#include <memory>
#include <string>
#include <vector>
#include <numeric>

#include "detector.hpp"
#include <vitis/ai/platenum.hpp>
#include <opencv2/opencv.hpp>
#include <vitis/ai/platedetect.hpp>

namespace aup::plate {
    constexpr auto version = "3.6.0";
    using PlateResult = struct PlateResult {
        /// plate confidence
        float plate_confidence;
        /// the plate number
        std::string plate_number;
        /// the plate color, Blue / Yellow
        std::string plate_color;
        /// plate area
        int plate_area;
        /// plate bbox
        cv::Rect plate_box;
        ///checsum verification result for singapore
        bool verified;
    };
    using PlateDetectResult = struct PlateDetectResult {
        /// plate confidence
        float plate_confidence;
        /// plate area
        int plate_area;
        /// plate bbox
        cv::Rect plate_box;
        /// double row or single row plate number
        bool double_row;
    };

    using PlateInitParams = struct PlateInitParams {
        /// plate confidence
        float plate_confidence = 0.1;
        /// plate area
        int plate_area_threshold = 50;
        // acceptable types: "xilinx", "aup"
        std::string detector_type = "aup";
        // acceptable types: "xilinx", "aup"
        std::string recog_type = "aup";
        /// run checksum singapore validation
        bool run_checksum_valid = true;
        /// run image plate preprocessing
        bool run_preprocessing = false;

        PlateInitParams& operator = (const PlateInitParams&  a) {
          plate_confidence = a.plate_confidence;
          plate_area_threshold = a.plate_area_threshold;
          detector_type = a.detector_type;
          recog_type = a.recog_type;
          run_checksum_valid = a.run_checksum_valid;
          run_preprocessing = a.run_preprocessing;
          return *this;
        }
    };

    class LicensePlate {
    public:
        // instantiate the license plate detector with a minimum plate confidence
        // score
        LicensePlate(PlateInitParams);
        LicensePlate(const LicensePlate &) = delete;
        LicensePlate(LicensePlate &&) = delete;
        ~LicensePlate() = default;
        std::shared_ptr<PlateResult> run(const cv::Mat &);
        std::string comp_valid_singapore_plates(const std::string&, const std::string&);
    private:
        bool verify_checksum(const std::string&, const std::string& digits, const std::string&);
        std::pair<std::string, bool> post_process_plate(std::vector<aup::detect::Detector::DetectedObject>&, std::vector<float>&, bool);
        PlateDetectResult run_plate_detect_aup(const cv::Mat &);
        PlateDetectResult run_plate_detect_xilinx(const cv::Mat &);
        std::pair<vitis::ai::PlateNumResult, bool> run_plate_recog_aup(const cv::Mat &, std::vector<float>&, bool);
        PlateInitParams lpr_init_params_;
        std::unique_ptr<vitis::ai::PlateDetect> detect_x;
        std::shared_ptr<aup::detect::Detector> detect_a;
        std::any recog_;
    };
} // namespace aup::plate
