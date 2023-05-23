#include <filesystem>
#include "aup/avaf/error.h"
#include "aup/avaf/packets/packet_base.h"
#include "aup/avaf/type.h"
#include "json.hpp"

namespace aup::avaf {

class JsonPacket : public PacketBase
{
public:
	virtual const std::string get_packet_type() const override { return "JSON_PACKET"; }

	JsonPacket(timestamp_t pts, const std::vector<nlohmann::json>& json_objects);
	JsonPacket(timestamp_t pts, const nlohmann::json& json_object);
	JsonPacket(timestamp_t pts, const std::vector<std::filesystem::path>::iterator& json_fs_path);
	JsonPacket(timestamp_t pts, const std::vector<std::filesystem::path>& json_paths);
	~JsonPacket();

	std::vector<nlohmann::json> _json_objects;
	nlohmann::json _json_object;
};

} // namespace aup::avaf