#pragma once

#include "plate.hpp"
#include "aup/avaf/packets/packet_base.h"

namespace aup::avaf {

class PlateRecognitions : public PacketBase
{
public:
	virtual const std::string get_packet_type() const override { return "PLATE_RECOGNITIONS"; }
	std::vector<std::shared_ptr<::aup::plate::PlateResult>> plate_results;
	PlateRecognitions(timestamp_t pts) : PacketBase(pts) {}
};


} // namespace gvis