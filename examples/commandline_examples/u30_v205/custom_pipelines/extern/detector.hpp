#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <any>

using namespace std::literals::chrono_literals;

// A threadsafe-queue.


namespace aup::detect {

    template <class T>
    class ThreadSafeQueue_
    {
    public:
        ThreadSafeQueue_(void) : q(), m(), c() {}

        ~ThreadSafeQueue_(void) {}

        // Add an element to the queue.
        void enqueue(T t)
        {
            std::lock_guard<std::mutex> lock(m);
            q.push(t);
            c.notify_one();
        }

        // Get the "front"-element.
        // If the queue is empty, wait till an element is avaiable.
        T dequeue(void)
        {
            std::unique_lock<std::mutex> lock(m);
            while(q.empty())
            {
                // release lock as long as the wait and reaquire it afterwards.
                c.wait(lock);
            }
            T val = q.front();
            q.pop();
            return val;
        }

        // Clears the queue
        std::queue<T> clearqueue(void)
        {
            std::unique_lock<std::mutex> lock(m);
            while(!q.empty()) {
                q.pop();
            }
            return q;
        }

        // Clears the queue
        int get_size(void)
        {
            std::unique_lock<std::mutex> lock(m);
            auto size_ = q.size();
            return int(size_);
        }

    private:
        std::queue<T> q;
        mutable std::mutex m;
        std::condition_variable c;
    };


    class Timer {

        public:

            Timer() {
                std::cout << "You are now logging the timing of the detector methods" << std::endl;
            }

            void start() {
                start_time = cv::getTickCount();
            }

            void end(std::string process_name) {
                end_time = cv::getTickCount();
                auto duration = (end_time - start_time) * MILLISECONDS_IN_SECOND / cv::getTickFrequency();

                std::cout << "Process name: " << process_name << " for 1 frame took " << duration << " milli seconds" << std::endl;
            }

        private:
            int64_t start_time;
            int64_t end_time;
            static const int MILLISECONDS_IN_SECOND = 1000;
    };

    class Detector {
    	public:

            //mean_scale_pair = pair(mean_vector{3}, scale_vector{3})
            //interested_label_confidence = map(label, confidence_th_for_label)
            //across_class_nms_th_label = map(across_class_nms_th, across_class_labels)
            using InitParams = struct InitParams{
                std::string detector_type = "";
                std::string kernel_name = "";
                std::pair<std::string, std::string> libname_token_pair;
                bool need_preprocess = true; //for mean-scale processing only
                std::pair<std::vector<float>, std::vector<float>> mean_scale_pair;
                std::unordered_map<int, float> interested_label_confidence;
                std::vector<std::pair<std::unordered_set<int>, float>> across_class_nms_th_label;
                bool log_performance = false;
                bool log_info = false;
                int thread_count = 0;
                int max_thread_q_size = 30;
                int mt_batch_size = 0;
                bool force_batch_size = false;
                int total_classes = 0;
                float default_confidence_thresh = 0.5;
            };

            using RuntimeParams = struct RuntimeParams{
                cv::Mat in_img;
                std::string img_name = "";
                bool run_on_letterboxed_img = false;

                RuntimeParams& operator =(const RuntimeParams& a) {
                    in_img = a.in_img;
                    img_name = a.img_name;
                    run_on_letterboxed_img = a.run_on_letterboxed_img;
                    return *this;
                }
            };

            using PreprocessResult = struct PreprocessResult {
              cv::Point translate;
              std::pair<float, float> scale;
              cv::Mat im;
            };

            using DetectedObject = struct DetectedObject{
                int class_id = -1;
                float class_conf = -1.0;
                cv::Rect2d class_bbox;
            };

            using MtRunTimeParams = struct MtRunTimeParams{
                std::any user_data;
                RuntimeParams detect_runtime_param;
                                /// copy-assignment operator
                MtRunTimeParams& operator =(const MtRunTimeParams& a)
                {
                    user_data = a.user_data;
                    detect_runtime_param = a.detect_runtime_param;
                    return *this;
                }
            };

    	    static std::shared_ptr<Detector> create(const aup::detect::Detector::InitParams& init_params);

        /* Single image DPU processing methods, if your test hardware does not support multi-batch input */
            // If you have a different scaling for a child detector, make this a virtual and override it
            // all following methods for single image processing
            std::vector<aup::detect::Detector::DetectedObject> scale_predictions(
                std::vector<aup::detect::Detector::DetectedObject>& detections, int frame_width, int frame_height);

            virtual std::vector<aup::detect::Detector::DetectedObject> run(const aup::detect::Detector::RuntimeParams& runtime_params);

            virtual void draw_bounding_boxes(const aup::detect::Detector::RuntimeParams& runtime_params);
    	    virtual void save_bounding_boxes(const aup::detect::Detector::RuntimeParams& runtime_params);
            virtual void label_images(const aup::detect::Detector::RuntimeParams& runtime_params);
            virtual aup::detect::Detector::PreprocessResult preprocess_img(
                const cv::Mat& in_img, const bool want_letterbox = false); //,if set false, will do linear resizing

            virtual size_t get_input_batch_size(); // Want to know if your hardware support multi-batch or not?

            virtual cv::Size2d get_detector_input_size(); // Detector input size

            /* Batch image DPU processing methids, if your test hardware supports multi-batch input */
            // all of the following overloaded methods are for batch processing, if your hardware supports multi-batch
            std::vector<std::vector<aup::detect::Detector::DetectedObject>> scale_predictions(
                std::vector<std::vector<aup::detect::Detector::DetectedObject>>& batch_detections, int frame_width, int frame_height);

            virtual std::vector<std::vector<aup::detect::Detector::DetectedObject>> run(
                const std::vector<aup::detect::Detector::RuntimeParams>& batch_runtime_params);

            virtual void draw_bounding_boxes(const std::vector<aup::detect::Detector::RuntimeParams>& batch_runtime_params);
            virtual void save_bounding_boxes(const std::vector<aup::detect::Detector::RuntimeParams>& batch_runtime_params);
            virtual void label_images(const std::vector<aup::detect::Detector::RuntimeParams>& batch_runtime_params);

            virtual std::vector<aup::detect::Detector::PreprocessResult> preprocess_img(
                const std::vector<cv::Mat>& batch_in_img, const bool want_letterbox = false); //,if set false, will do linear resizing

            // all other general getter method
            std::string get_detector_type();
            std::string get_kernel_name();
            std::pair<std::vector<float>, std::vector<float>> get_mean_scale_values();
            std::unordered_map<int, float> get_interested_labels_confidence();
            std::vector<std::pair<std::unordered_set<int>, float>> get_across_class_nms_th_label_map();
            std::pair<std::string, std::string> get_obfuscated_libname_token(); // we do not use obfuscation of VitisAI models for now

            void check_init_param_validity(const aup::detect::Detector::InitParams& init_params);

            virtual void init_mt() = 0;
            virtual void close_mt() = 0;

            /**
             * @brief push an element to the queue
             *
             * @param in
             * @return true if susccessful
             * @return false if queue has reached the max queue size
             */
            bool enqueue( MtRunTimeParams& in );

            /**
             * @brief overloaded method push batch an element to the queue
             *
             * @param in
             * @return true if susccessful
             * @return false if queue has reached the max queue size
             */
            bool enqueue( std::vector< MtRunTimeParams >& in );

            /**
             * @brief dequeue the first element in the queue
             *
             * @param in
             * @return true if successful dequeue
             * @return false if queue empty and no element is returend
             */
            bool dequeue( std::pair<MtRunTimeParams, std::vector<DetectedObject> >& in );

            /**
             * @brief overloaded batch dequeue the first element in the queue
             *
             * @param in
             * @return true  if successful dequeue
             * @return false  if queue empty and no element is returend
             */
            bool dequeue( std::vector< std::pair<MtRunTimeParams, std::vector<DetectedObject> > >& in );

            /**
             * @brief dequeue that calls dequeue function without checking the size but instead waits on the conditional variable
             *
             * @param in
             * @return void
             */
            void dequeue_wait_covar( std::pair<MtRunTimeParams, std::vector<DetectedObject> >& in );

            /**
             * @brief overloaed batch dequeue that calls dequeue function without checking the size but instead waits on the conditional variable
             *
             * @param in
             * @return void
             */
            void dequeue_wait_covar( std::vector< std::pair<MtRunTimeParams, std::vector<DetectedObject> > >& in );

            size_t get_in_q_size();

            size_t get_out_q_size();
            
            

    	private:
    	     inline static const std::unordered_set<std::string> available_detectors = {
                 "SSD",
                 "YoloV2",
                 "YoloV3",
                 "YoloV4",
                 "YoloVX",
                 "TinyYolo",
                 "RefineDet",
                 "SSDLowLevelAPI",
                 "FaceDetectDenseBox"
    	     };

    	protected:

    	    Detector(const aup::detect::Detector::InitParams& init_params);
            ~Detector();
            virtual void run_mt(int) = 0;
            std::vector<cv::Mat> prep_img_batch(
                std::vector<aup::detect::Detector::RuntimeParams>& batch_runtime_params,
                std::vector<float>& const_width_addition,
                std::vector<float>& const_height_addition
            );

            std::vector<cv::Mat> prep_img_batch(
                std::vector<aup::detect::Detector::RuntimeParams>& batch_runtime_params
            );

            bool running_mt = false;
            int max_thread_q_size_;
            std::string detector_type_;
            std::string kernel_name_;
            std::pair<std::vector<float>, std::vector<float>> mean_scale_pair_;
            std::unordered_map<int, float> interested_label_confidence_;
            std::vector<std::pair<std::unordered_set<int>, float>> across_class_nms_th_label_;
            bool log_performance_;
            bool log_info_;
            bool need_preprocess_;
            std::pair<std::string, std::string>libname_token_pair_;
            std::vector<std::shared_ptr<aup::detect::Timer>> timer_ptr_;
            std::vector<std::thread> worker_thread;
            int num_threads_;
            int batch_size_;
            bool force_batch_size_;
            int total_classes_;
            float default_confidence_thresh_;


            // multi-threaded assests
            ThreadSafeQueue_< MtRunTimeParams > thread_in_q;
            ThreadSafeQueue_< std::pair<MtRunTimeParams, std::vector<DetectedObject> > > thread_out_q;

            ThreadSafeQueue_< std::vector<MtRunTimeParams> > thread_in_q_batch;
            ThreadSafeQueue_< std::vector< std::pair<MtRunTimeParams, std::vector<DetectedObject> > > > thread_out_q_batch;
            const int thread_num = 0; // Dummy needed for timing measurements

    };
} //End of aup::detect namespace