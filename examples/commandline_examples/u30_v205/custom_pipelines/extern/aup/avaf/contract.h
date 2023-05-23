#pragma once

#include "aup/avaf/packet_ptr.h"
#include "aup/avaf/packets/packet_base.h"
#include "aup/avap/graph.pb.h"

#define AUP_AVAF_DEFAULT_STREAM_CAP (64)
#define AUP_AVAF_DEFAULT_STREAM_SYNC_MAXWAIT_MS (3000)

namespace aup::avaf {

class Contract
{
	const GraphConfig::Node& config;
	// void log_contract();

public:
	Contract(const GraphConfig::Node& config);
	ErrorCode override_via_config();
	std::vector<PacketPtr<const PacketBase>> sample_input_packets;
	std::vector<PacketPtr<const PacketBase>> sample_output_packets;
	std::vector<std::string> input_stream_names;
	std::vector<std::string> output_stream_names;
	std::vector<GraphConfig::Node::InputStreamAttributes> input_attrs_arr;
	std::vector<GraphConfig::Node::OutputStreamAttributes> output_attrs_arr;
	GraphConfig::Node::StreamSync stream_sync;
};

} // namespace aup::avaf