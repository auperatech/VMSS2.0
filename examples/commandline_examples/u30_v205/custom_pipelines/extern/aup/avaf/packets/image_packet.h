#pragma once

// std headers
#include <memory>
#include <stdint.h>

// sdk header (ffmpeg)
extern "C"
{
#include <libavutil/frame.h>
}

// sdk headers
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "aup/avaf/error.h"
#include "aup/avaf/packets/packet_base.h"
#include "aup/avaf/type.h"

namespace aup::avaf {

/*
 * ImagePacket: packet to contain image, manage its memory-life-cycle and allow for cross-image memory handling.
 * ImagePacket may work in tandem with allocator to limit the number of possible Images in the memory.
 * If such memory management does not concern you, you can just use the constructor with cv::Mat
 * If you care about putting some control on top of the number of ImagePackets in memory, then you need to use Image
 * Allocator class to control it.
 * In this case, you can use various other constructors to achieve this goal.
 * parent image: the image from which this image is created either via cropping or resizing or letter-boxing
 * orig: the image from which this image's ROI is calculated
 * owner: image that owns the data of this image. this is not settable. only gettable. it is internally optimized.
 * owner is guaranteed to be present and valid. it may be a pointer to self
 * note that owner can be itself or nothing(nullptr)
 * read inline for more info
 */
class ImagePacket : public PacketBasePTS
{
	struct Impl;
	Impl* pimpl;

public:
	virtual const std::string get_packet_type() const override { return "IMAGE_PACKET"; }
	struct Allocator
	{
		struct Impl;
		Impl* pimpl;
		enum class MemoryType
		{
			NORMAL = 0,
			VPM    = 1,
		};
		Allocator(uint16_t width, uint16_t height, PixFmtType pixfmt, uint16_t pool_sz, MemoryType memory_type,
		          ErrorCode& ec);
		Allocator(uint16_t width, uint16_t height, PixFmtType pixfmt, uint16_t pool_sz, ErrorCode& ec);
		~Allocator();
	};
	/*
	 * Region of Interest (ROI) With Regards To (WRT)
	 * this determines from which perspective ROI should be calculated.
	 * Can be to self in which case ROI would be {0,0,1,1}
	 * Can be towards parent or Parent's orig
	 * the ImagePacket towards which ROI_WRT, is called orig
	 */
	enum class ROI_WRT
	{
		PARENT, // calculate ROI with regards to parent
		ORIG,   // calculate ROI with regards to original image
		OWNER,  // calculator ROI with regards to owner image
	};
	// default contructor. just for the purposes of contracts. no other use as of right now
	ImagePacket();
	// constructor from Mat. memory not handled by allocator thus mat must manage its own memory. ROI_WRT_SELF
	ImagePacket(timestamp_t sync_timestamp, bool to_be_continued, cv::Mat& mat);
	// construct from allocator
	ImagePacket(timestamp_t sync_timestamp, bool to_be_continued, std::shared_ptr<Allocator>& allocator, ErrorCode& ec);
	// constructors to crop from another image.
	ImagePacket(timestamp_t sync_timestamp, bool to_be_continued, PacketPtr<ImagePacket>& parent, ROI_WRT roi_wrt,
	            cv::Rect2f& roi, ErrorCode& ec);
	// constructors to resize or letterbox and/or crop from another image with allocator
	ImagePacket(timestamp_t sync_timestamp, bool to_be_continued, PacketPtr<ImagePacket>& parent, ROI_WRT roi_wrt,
	            cv::Rect2f& roi, cv::InterpolationFlags interpolation, bool letterbox,
	            std::shared_ptr<Allocator>& allocator, ErrorCode& ec);
	~ImagePacket();
	// self info
	cv::Mat& get_cv_mat();
	const cv::Mat& get_cv_mat() const;
	PixFmtType get_pix_fmt() const;
	void get_dims(cv::Size&) const;
	void get_dims(int& height, int& width) const;
	// orig info
	void get_orig_dims(cv::Size&) const;
	void get_orig_dims(int& height, int& width) const;
	void get_roi_on_orig(cv::Rect2f&) const;
	// fps info
	void set_fps(float fps);
	float get_fps() const;
	// owner info
	bool is_owner() const;
	PacketPtr<const ImagePacket> get_owner() const;
	PacketPtr<ImagePacket> get_owner();
	// ffmpeg helpers
	ErrorCode get_ffmpeg_avframe(AVFrame* avframe) const;
	ErrorCode fill_with_ffmpeg_avframe(const AVFrame* avframe);
	// save raw image
	void write_raw_disk(const std::string directory) const;
	// void write_jpg_disk(const std::string directory);
	// get raw data
	uint8_t* get_raw_data();
	size_t get_raw_data_sz();
	uint64_t get_phy_addr();
};
} // namespace aup::avaf