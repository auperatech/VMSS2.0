#pragma once

#include <stdint.h>

#include "aup/avaf/packets/packet_base.h"

namespace aup::avaf {

class VideoPacket : public PacketBasePTS
{
public:
	virtual const std::string get_packet_type() const override { return "VIDEO_PACKET"; }
	VideoPacket();
	VideoPacket(timestamp_t sync_timestamp, timestamp_t dts, uint32_t size, bool& success);
	VideoPacket(timestamp_t sync_timestamp, timestamp_t dts, uint32_t size, uint8_t* pBuf);
	~VideoPacket();
	timestamp_t dts; // video packet decode timestamp
	uint32_t size;   // video packet buffer size
	uint32_t len;    // video packet data length
	uint8_t* pBuf;   // video packet data buffer
	PicType picType; // video packet picture type, I/P/B
};

} // namespace aup::avaf