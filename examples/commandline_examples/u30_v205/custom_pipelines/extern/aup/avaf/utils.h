#pragma once

// std headers
#include <mutex>
#include <string>
#include <sys/time.h>
#include <vector>

// sdk headers (ffmpeg)
extern "C"
{
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/eval.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libswscale/swscale.h>
}

// local headres
#include "aup/avaf/error.h"
#include "aup/avaf/packet_ptr.h"
#include "aup/avaf/type.h"

namespace aup::avaf {

UrlType get_url_type(std::string url);
uint8_t* alloc_4k_aligned(uint32_t size);
ErrorCode get_time_with_offset(struct timespec* t, uint32_t offsetMs);
uint32_t get_planes_pitch(uint32_t stride, PixFmtType pixfmt);
std::string get_pixfmt_string(PixFmtType pixfmt);
std::string base64_encode(const char* bytes_to_encode, unsigned int in_len);
std::string base64_decode(const std::string encoded_string);
int64_t get_now_us();
int64_t get_now_ns();
AVPixelFormat pixfmt_to_av_pixfmt(PixFmtType pixfmt);

class ImagePacket;

class MultiOutputScaler
{
public:
	MultiOutputScaler();
	virtual ~MultiOutputScaler();

	ErrorCode initialize(PacketPtr<ImagePacket>& src, std::vector<PacketPtr<ImagePacket>>& dsts);
	ErrorCode do_scale(PacketPtr<const ImagePacket>& src, std::vector<PacketPtr<ImagePacket>>& dsts);
	ErrorCode do_scale(PacketPtr<ImagePacket>& src, std::vector<PacketPtr<ImagePacket>>& dsts);

private:
	std::vector<struct SwsContext*> sws_ctxs;
	AVFrame* src_av_frame = NULL;
	AVFrame* dst_av_frame = NULL;
};

} // namespace aup::avaf