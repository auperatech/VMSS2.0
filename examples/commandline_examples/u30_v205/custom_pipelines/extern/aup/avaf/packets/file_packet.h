#pragma once

#include <filesystem>
#include <system_error>

#include "aup/avaf/packets/packet_base.h"

namespace aup::avaf {

class FilePacket : public PacketBase
{
public:
	const std::string path;
	FilePacket(timestamp_t sync_timestamp, const std::string& path) : PacketBase(sync_timestamp), path(path) {}
	FilePacket(const std::string& path) : path(path) {}
	FilePacket() {}
	~FilePacket()
	{
		std::error_code ec;
		std::filesystem::remove(path, ec);
	}
};

} // namespace aup::avaf
