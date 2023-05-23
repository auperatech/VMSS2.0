#pragma once

#include <string>

#include "aup/avaf/packets/packet_base.h"

namespace aup::avaf {

class ClipGeneratorCommandPacket : public PacketBase
{
public:
	enum class Command
	{
		CONTINUE   = 0,
		START_CLIP = 1,
		END_CLIP   = 2,
	};
	const Command command;
	const std::string filename_prefix;
	ClipGeneratorCommandPacket(timestamp_t sync_timestamp, const Command command, const std::string& filename_prefix)
	    : PacketBase(sync_timestamp), command(command), filename_prefix(filename_prefix)
	{
	}
	ClipGeneratorCommandPacket(Command command, const std::string& filename_prefix)
	    : ClipGeneratorCommandPacket(0, command, filename_prefix)
	{
	}
	ClipGeneratorCommandPacket() : ClipGeneratorCommandPacket(Command::CONTINUE, "") {}
};

} // namespace aup::avaf
