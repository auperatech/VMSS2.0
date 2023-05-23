#pragma once

// standard library headers
#include <algorithm>
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include <string.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>

// local headers
#include "aup/avaf/error.h"
#include "aup/avaf/packet_ptr_use_count_notifier.h"
#include "aup/avaf/packets/packet_base.h"
#include "aup/avaf/statistician.h"
#include "aup/avaf/status.h"
#include "aup/avap/graph.pb.h"

namespace aup::avaf {

class Node;

class DataStream
{
	struct Impl;
	Impl* pimpl;
	ErrorCode enqueue_fail(const Node* node, PacketPtr<PacketBase>& packet);
	ErrorCode enqueue_drop(const Node* node, PacketPtr<PacketBase>& packet);
	ErrorCode enqueue_block(const Node* node, PacketPtr<PacketBase>& packet, uint32_t timeout_ms = 30'000);

public:
	struct NodeInfo;
	DataStream(std::string name, GraphConfig::Node::OutputStreamAttributes& output_attrs,
	           PacketPtrUseCountNotifier& packet_ptr_use_count_notifier);
	DataStream(const DataStream&)            = delete;
	DataStream& operator=(const DataStream&) = delete;
	DataStream(DataStream&&)                 = delete;
	DataStream& operator=(DataStream&&)      = delete;
	~DataStream();
	std::mutex& get_mux();
	uint32_t size(const Node* node, bool do_mux = true);
	uint32_t size(bool do_mux = true);
	ErrorCode add_sink_node(const Node* node, GraphConfig::Node::InputStreamAttributes& attrs);
	enum class DequeueResult
	{
		NO = 0,
		PARTIAL,
		FULL
	};
	struct DequeueResultBundle
	{
		DequeueResult dequeue_result;
		std::chrono::system_clock::time_point min_gen_time_point;
		timestamp_t sync_timestamp;
		uint32_t num_packets;
		bool operator==(const DequeueResultBundle& rhs) const
		{
			return dequeue_result == rhs.dequeue_result && min_gen_time_point == rhs.min_gen_time_point &&
			       sync_timestamp == rhs.sync_timestamp;
		}
	};
	static const DequeueResultBundle default_dequeue_result_bundle;
	ErrorCode get_dequeue_result(const Node* node, DequeueResultBundle& dequeue_result_bundle, bool do_mux = true,
	                             NodeInfo** info_p = NULL);
	ErrorCode dequeue(const Node* node, PacketPtr<PacketBase>& packet, bool do_mux = true);
	ErrorCode dequeue_block(const Node* node, PacketPtr<PacketBase>& packet, uint32_t timeout_ms = 30'000);
	ErrorCode peek(const Node* node, PacketPtr<PacketBase>& packet, bool do_mux = true);
	ErrorCode peek_block(const Node* node, PacketPtr<PacketBase>& packet, uint32_t timeout_ms = 30'000);
	bool has_data(const Node* node);
	ErrorCode enqueue(const Node* node, PacketPtr<PacketBase>& packet);
	// Latency measurement
	void add_src_statistician(std::shared_ptr<Statistician>& statistician);
	void add_dst_statistician(std::shared_ptr<Statistician>& statistician);
	// Throughput measurement
	void add_thruput_statistician(std::shared_ptr<Statistician>& statistician);
	// Stream Size measurement
	void add_size_statistician(std::shared_ptr<Statistician>& statistician);
};

} // namespace aup::avaf