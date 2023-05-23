#pragma once

// sdk headers (ffmpeg)
extern "C"
{
#include "libavcodec/avcodec.h"
}

// local headers
#include "aup/avaf/packets/packet_base.h"

namespace aup::avaf {

class AVCodecContextPacket : public PacketBase
{
public:
	virtual const std::string get_packet_type() const override { return "AV_CODEC_CONTEXT"; }
	AVCodecContext ctx;
	AVCodecContextPacket() {}
	AVCodecContextPacket(const AVCodecContext* ctx) : ctx(*ctx) {}
};

} // namespace aup::avaf
