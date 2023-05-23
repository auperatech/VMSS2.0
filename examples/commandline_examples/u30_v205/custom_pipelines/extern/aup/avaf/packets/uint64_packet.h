#pragma once

#include "aup/avaf/packets/packet_base.h"

namespace aup::avaf {

class UInt64Packet : public PacketBase
{
	uint64_t value;

public:
	virtual const std::string get_packet_type() const override { return "UINT64"; }
	UInt64Packet(timestamp_t pts, bool to_be_continued, uint64_t value) : PacketBase(pts, to_be_continued), value(value)
	{
	}
	UInt64Packet(timestamp_t pts, uint64_t value) : PacketBase(pts), value(value) {}
	UInt64Packet(uint64_t value) : value(value) {}
	uint64_t get_value() const { return value; }
	void set_value(uint64_t input_value) { value = input_value; }
};

} // namespace aup::avaf
