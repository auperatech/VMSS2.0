#pragma once

#include "aup/avaf/packets/packet_base.h"
#include "aup/avaf/type.h"

namespace aup ::avaf {

class VideoStreamInfoPacket : public PacketBase
{
public:
	VideoStreamInfoPacket() {}
	VideoStreamInfoPacket(const VideoStreamInfoPacket&)            = default;
	VideoStreamInfoPacket(VideoStreamInfoPacket&&)                 = default;
	VideoStreamInfoPacket& operator=(const VideoStreamInfoPacket&) = default;
	VideoStreamInfoPacket& operator=(VideoStreamInfoPacket&&)      = default;
	virtual const std::string get_packet_type() const override { return "VIDEO_STREAM_INFO_PACKET"; }
	uint32_t w           = 0;
	uint32_t h           = 0;
	float fps            = 0;
	PixFmtType pixfmt    = PixFmtType::NONE;
	uint32_t max_bframes = 0;
	bool iframe_extract  = false;
	CodecType codec_type = CodecType::NONE;
};

} // namespace aup::avaf
