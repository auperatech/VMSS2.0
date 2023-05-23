#pragma once

// std headers
#include <fstream>
#include <memory>
#include <mutex>
#include <string>

// local headers
#include "aup/avaf/packets/packet_base.h"

namespace aup::avaf {

class Statistician
{
	struct Impl;
	Impl* pimpl;

public:
	Statistician(std::shared_ptr<std::ostream>& results_stream, std::shared_ptr<std::mutex>& results_stream_mux,
	             uint32_t interval_ms);
    ~Statistician();
	// Latency
	void register_src_latency_stream(const std::string& src_stream_name);
	void register_dst_latency_stream(const std::string& dst_stream_name);
	void add_src_sync_timestamp(const timestamp_t& sync_timestamp, const timestamp_t& now_us);
	void add_dst_sync_timestamp(const timestamp_t& sync_timestamp, const timestamp_t& now_us);
	// Throughput
	void set_thruput_ignore_initial_packet_count(uint32_t ignore_init_packet_cnt);
	void register_thruput_stream(const std::string& stream_name);
	void tic_thruput_enqueue(const timestamp_t& now_us);
	// Stream Size
	void register_size_stream(const std::string& stream_name);
	void log_stream_size(const std::string& stream_name, uint32_t size);
};

} // namespace aup::avaf
