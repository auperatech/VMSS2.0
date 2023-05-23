#pragma once

#include <any>
#include <deque>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <memory>
#include <unordered_set>


using track_obj_t = struct track_obj_t {
    unsigned long long int id;
    int class_id;
    float confidence;
    cv::Rect2d rect;
    int32_t loseTrackCount;
    std::vector<cv::Point2d> traceRecord;
    std::deque<cv::Point2d> speeds;
    std::string meta_name = "";
    bool predicted;
    std::vector<float> encoding;

    track_obj_t& operator =(const track_obj_t& a)
    {
        id = a.id;
        class_id = a.class_id;
        confidence = a.confidence;
        rect = a.rect;
        loseTrackCount = a.loseTrackCount;
        traceRecord = a.traceRecord;
        speeds = a.speeds;
        meta_name = a.meta_name;
        predicted = a.predicted;
        encoding = a.encoding;
        return *this;
    }
};



namespace aup::tracker {

    using TrackerConfig = struct TrackerConfig {
        uint8_t speed_buffer_max_size = 5;
        /// maximum keepalive for an object whose IOU wasn't detected
        int32_t max_keep_alive = 3; //used for both MOSSE & SORT
        /* keep_tracker_iou_thresh is to make sure the tracker update result is right
         * during correct() process bind_obj_iou_thresh is to bind the detected obj to
         * the tracking obj during correct() process
         * */
        float keep_tracker_iou_thresh = 0.9; //used for MOSSE
        float bind_obj_iou_thresh = 0.2; // used for MOSSE
        std::string tracker_type = "MOSSE";
        const int minHits = 1; // Original:3 //used for sort
        const double affinityThreshold = 0.008; //used for sort
        float shapeWeight = 1;
        float positionWeight = 1;
        float appearnaceWeight = 1;
        float shapeDistMax = 1;
        float positionDistMax = 1;
        /// toggling betweeen either exp cost or weighted sum cost
        bool use_exp_cost = true;
    };

    class AupMultiTracker {
    public:

        static std::shared_ptr<AupMultiTracker> create(const aup::tracker::TrackerConfig &init_params);

        virtual bool update(cv::InputArray image);

        virtual void correct(cv::Mat &img, std::vector <cv::Rect2d> &detectBoundingBox);

        virtual void correct(cv::Mat &img, std::vector <track_obj_t> &objs) = 0;

        // Returns the detected object index in input vector<track_obj_t> and its matched predictor tracked ID (-1, if unmatched detection)
        //pair<0,7> -> detected object from vector<track_obj_t> at 0th index matched with tracked ID 7 from previous frame
        //pair<3,-1> -> detected object from vector<track_obj_t> at 3rd index is unmatched and can be assign a new track
        virtual std::vector<std::pair<int, int>> get_detected_to_predicted_association(cv::Mat &img, std::vector <track_obj_t> &objs) = 0;

        virtual void update_objects(std::vector <track_obj_t> &in_objs);

        virtual void clear();


        /* return a pair of objects where first are a list of alive objects and second are dead objects
         * */

        virtual std::pair< std::vector <track_obj_t> , std::vector <track_obj_t> > getObjs();

        // Getter method for instantiated tracker_type
        std::string get_tracker_type();

        virtual void check_init_param_validity(const aup::tracker::TrackerConfig &init_params) = 0;

        void predict(); // predict the objrects by speed.
        //    void predict2();  // predict hidden objrects by speed. not available
        //    now. not used.
        inline static const std::unordered_set <std::string> available_trackers = {
                "MOSSE",
                "SORT++",
                "DEEPSORT"
        };

        std::vector <cv::Ptr<cv::Tracker>> trackers;
        std::vector<bool> trackOkStatuses;
        std::vector <track_obj_t> objs;
        std::vector<track_obj_t> dead_objs;
        TrackerConfig config_;

        float calculateIOU(const cv::Rect2d &trackRect, const cv::Rect2d &detectRect);

        static uint64_t availableID;

        uint64_t getAvailableID();

    private:



    protected:

        AupMultiTracker(const aup::tracker::TrackerConfig &config);
        AupMultiTracker(const AupMultiTracker &) = delete;

        AupMultiTracker(AupMultiTracker &&) = delete;

        ~AupMultiTracker() = default;

        bool log_performance_;
        std::string instantiated_tracker_type_;
    };
}//end of namespace
