#pragma once

#include "aup/avaf/packets/packet_base.h"
#include "detector.hpp"
#include "multitracker.hpp"

namespace aup::avaf {

class DetectionsOrTracks : public PacketBase{
public:
    using DetectedOrTrackedObject = struct DetectedOrTrackedObject{
    	unsigned long long int track_id = 0;
        int class_id = -1;
        float confidence = -1.0;
        cv::Rect2i rect;
	    int32_t loseTrackCount;
	    std::vector<cv::Point2d> traceRecord;
	    std::deque<cv::Point2d> speeds;
	    std::string meta_name = "";
	    bool predicted;
	    bool from_tracker;
	    std::vector<float> encoding;

	    DetectedOrTrackedObject& operator =(const DetectedOrTrackedObject& a)
	    {
	        track_id = a.track_id;
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

    std::vector<DetectedOrTrackedObject> detections_or_live_tracks;
    std::vector<DetectedOrTrackedObject> dead_tracks;
    uint64_t frame_number;
    uint64_t stream_idx;
	uint16_t swidth;
	uint16_t sheight;

	static cv::Rect2i cvrect2d_to_cvrect2i(const cv::Rect2d& class_bbox, const cv::Size& img_size){
		int x = (int)(class_bbox.x);
		int y = (int)(class_bbox.y);
		int w = (int)(class_bbox.width);
		int h = (int)(class_bbox.height);
		

		if( 
			(class_bbox.x - x) != 0 ||
			(class_bbox.y - y) != 0 ||
			(class_bbox.width - w) != 0 ||
			(class_bbox.height - h) != 0
		){
			x = (int)(class_bbox.x * img_size.width);
			y = (int)(class_bbox.y * img_size.height);
			w = (int)(class_bbox.width * img_size.width);
			h = (int)(class_bbox.height * img_size.height);
		}

		
		if (x < 0) {
			x = 0;
		}
		if (y < 0) {
			y = 0;
		}

		if (x + w > img_size.width) {
			w = img_size.width - x;
		}
		if (y + h > img_size.height) {
			h = img_size.height - y;
		}
		return cv::Rect2i(x, y, w, h);
	}

	DetectionsOrTracks(timestamp_t pts, uint16_t swidth, uint16_t sheight,
		std::vector<DetectedOrTrackedObject>& detections_or_live_tracks, uint64_t frame_number,
		uint64_t stream_idx = 0
	) : PacketBase(pts){

		this->detections_or_live_tracks = detections_or_live_tracks;

		this->swidth = swidth;
		this->sheight = sheight;
		this->frame_number = frame_number;
		this->stream_idx = stream_idx;
	}

	DetectionsOrTracks(timestamp_t pts, uint16_t swidth, uint16_t sheight,
		std::vector<aup::detect::Detector::DetectedObject>& detections, uint64_t frame_number,
		uint64_t stream_idx = 0
	) : PacketBase(pts){

		for(auto det : detections){
			detections_or_live_tracks.push_back(DetectedOrTrackedObject{
				.class_id = det.class_id,
				.confidence = det.class_conf,
				.rect = cvrect2d_to_cvrect2i(det.class_bbox, cv::Size(swidth, sheight)),
				.from_tracker = false
			});
		}

		this->swidth = swidth;
		this->sheight = sheight;
		this->frame_number = frame_number;
		this->stream_idx = stream_idx;
	}

	DetectionsOrTracks(uint64_t pts, uint16_t swidth, uint16_t sheight,
	    std::pair<std::vector<track_obj_t>, std::vector<track_obj_t>>& tracks,
	    uint64_t frame_number
	) : PacketBase(pts){

		for(auto& live : tracks.first){
			detections_or_live_tracks.push_back(DetectedOrTrackedObject{
				.track_id = live.id,
				.class_id = live.class_id,
				.confidence = live.confidence,
				.rect = cvrect2d_to_cvrect2i(live.rect, cv::Size(swidth, sheight)),
				.loseTrackCount = live.loseTrackCount,
				.traceRecord = live.traceRecord,
				.speeds = live.speeds,
				.meta_name = live.meta_name,
				.predicted = live.predicted,
				.from_tracker = true,
				.encoding = live.encoding
			});
		}

		for(auto& dead : tracks.second){
			dead_tracks.push_back(DetectedOrTrackedObject{
				.track_id = dead.id,
				.class_id = dead.class_id,
				.confidence = dead.confidence,
				.rect = cvrect2d_to_cvrect2i(dead.rect, cv::Size(swidth, sheight)),
				.loseTrackCount = dead.loseTrackCount,
				.traceRecord = dead.traceRecord,
				.speeds = dead.speeds,
				.meta_name = dead.meta_name,
				.predicted = dead.predicted,
				.from_tracker = true,
				.encoding = dead.encoding
			});
		}

		this->swidth = swidth;
		this->sheight = sheight;
		this->frame_number = frame_number;
		this->stream_idx = stream_idx;
	}

	virtual const std::string get_packet_type() const override { return "DETECTIONS_OR_TRACKS"; }
};

} // namespace aup::avaf