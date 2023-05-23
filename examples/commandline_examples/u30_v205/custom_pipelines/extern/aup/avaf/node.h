#pragma once

// std headers
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <memory>
#include <stdint.h>
#include <thread>
#include <unordered_map>
#include <vector>

// sdk headers
#include <boost/current_function.hpp>
#include <boost/dynamic_bitset.hpp>

// local headers
#include "aup/avaf/contract.h"
#include "aup/avaf/data_stream.h"
#include "aup/avaf/error.h"
#include "aup/avaf/graph.h"
#include "aup/avaf/log.h"
#include "aup/avaf/packets/packet_base.h"
#include "aup/avaf/status.h"

namespace aup::avaf {

struct CalculatorAPIs;

#define DEFAULT_STREAM_SYNC_MAX_WAIT_MS 3000

class Node
{
	friend class Graph;
	std::string input_url;
	std::string output_url;

public:
	Node(const GraphConfig::Node& config, Graph* graph, std::string input_url, std::string output_url, ErrorCode& ec);
	virtual ~Node();
	std::string get_input_url() const { return input_url; }
	std::string get_output_url() const { return output_url; }

	/* try to dequeue one element from specified stream name */
	template <typename PacketType>
	ErrorCode dequeue(uint32_t strm_idx, PacketPtr<PacketType>& packet) const
	{
		if (strm_idx >= (uint32_t)input_streams.size() || input_streams.at(strm_idx).second == nullptr) {
			BOOST_LOG_SEV(logger()->mlogger(), LOG_ERROR) << "Input stream " << strm_idx << " doesn't exist.\n";
			return ErrorCode::ERROR;
		}
		PacketPtr<PacketBase> packet_base;
		auto ret = input_streams.at(strm_idx).second->dequeue(this, packet_base);
		if (ret == ErrorCode::OK) {
			packet = dynamic_packet_cast<PacketType>(packet_base);
		} else {
			packet = nullptr;
		}
		return ret;
	}
	template <typename PacketType>
	ErrorCode dequeue_block(uint32_t strm_idx, PacketPtr<const PacketType>& packet, uint32_t timeout_ms = 30'000) const
	{
		if (strm_idx >= (uint32_t)input_streams.size() || input_streams.at(strm_idx).second == nullptr) {
			BOOST_LOG_SEV(logger()->mlogger(), LOG_ERROR) << "Input stream " << strm_idx << " doesn't exist.\n";
			return ErrorCode::ERROR;
		}
		PacketPtr<PacketBase> packet_base;
		auto ret = input_streams.at(strm_idx).second->dequeue_block(this, packet_base, timeout_ms);
		if (ret == ErrorCode::OK) {
			packet = dynamic_packet_cast<PacketType>(packet_base);
		} else {
			packet = nullptr;
		}
		return ret;
	}
	template <typename PacketType>
	ErrorCode dequeue_block(uint32_t strm_idx, PacketPtr<PacketType>& packet, uint32_t timeout_ms = 30'000) const
	{
		if (strm_idx >= (uint32_t)input_streams.size() || input_streams.at(strm_idx).second == nullptr) {
			BOOST_LOG_SEV(logger()->mlogger(), LOG_ERROR) << "Input stream " << strm_idx << " doesn't exist.\n";
			return ErrorCode::ERROR;
		}
		PacketPtr<PacketBase> packet_base;
		auto ret = input_streams.at(strm_idx).second->dequeue_block(this, packet_base, timeout_ms);
		if (ret == ErrorCode::OK) {
			packet = dynamic_packet_cast<PacketType>(packet_base);
		} else {
			packet = nullptr;
		}
		return ret;
	}
	/* try to peek one element from specified stream name */
	template <typename PacketType>
	ErrorCode peekqueue(uint32_t strm_idx, PacketPtr<PacketType>& packet) const
	{
		if (strm_idx >= (uint32_t)input_streams.size() || input_streams.at(strm_idx).second == nullptr) {
			BOOST_LOG_SEV(logger()->mlogger(), LOG_ERROR) << "Input stream " << strm_idx << " doesn't exist.\n";
			return ErrorCode::ERROR;
		}
		PacketPtr<PacketBase> packet_base;
		auto ret = input_streams.at(strm_idx).second->peek(this, packet);
		if (ret == ErrorCode::OK) {
			packet = dynamic_packet_cast<PacketType>(packet_base);
		} else {
			packet = nullptr;
		}
		return ret;
	}
	/* check if queue is empty */
	bool is_queue_empty(uint32_t input_strm_idx) const;
	/* try to enqueue one element from specified stream name */
	template <typename PacketType>
	ErrorCode enqueue(uint32_t strm_idx, PacketPtr<PacketType>& packet) const
	{
		if (strm_idx >= (uint32_t)output_streams.size() || output_streams.at(strm_idx).second == nullptr) {
			BOOST_LOG_SEV(logger()->mlogger(), LOG_ERROR) << "Output stream " << strm_idx << " doesn't exist.\n";
			return ErrorCode::ERROR;
		}
		auto packet_base = dynamic_packet_cast<PacketBase>(packet);
		return output_streams.at(strm_idx).second->enqueue(this, packet_base);
	}

	/* initialize current node, will open the calculator and create manage thread */
	ErrorCode initialize();
	/* uninitialize current node, will close the calculator and destroy manage thread */
	void uninitialize();

	GraphStatus get_graph_status() const;
	void set_graph_status(GraphStatus status_) const;
	Logger* logger() const;
	std::string get_node_name() const;
	std::string get_calculator_name() const;
	/* call this api in calculator to get handler return by CalculatorAPIs->open() */
	void* get_calculator_handler() const;

	std::vector<std::pair<std::string, std::shared_ptr<DataStream>>> input_streams;
	std::vector<std::pair<std::string, std::shared_ptr<DataStream>>> output_streams;
	const GraphConfig::Node& config;
	std::vector<google::protobuf::Any> options;
	std::shared_ptr<Contract> contract = nullptr;
	// APIs for execute
	CalculatorAPIs* calc_apis = NULL;
	std::condition_variable* get_convar() const;
	std::mutex* get_mux() const;

private:
	mutable std::condition_variable convar;
	mutable std::mutex mux;
	// last used streams data
	timestamp_t exec_sync_timestamp_last;
	// stream data that is going to be accessed by
	timestamp_t exec_sync_timestamp;
	bool exec_sync_failure;
	mutable std::vector<std::list<PacketPtr<PacketBase>>> streams_data;
	bool is_execute = false;
	// stream data results internal
	typedef std::multimap<std::chrono::system_clock::time_point, uint32_t> DequeueResultMap;
	typedef std::map<timestamp_t, DequeueResultMap> DequeueResultMaps;
	DequeueResultMaps dequeue_results_maps;
	boost::dynamic_bitset<> synced_immutable_streams_bitmap; // const
	boost::dynamic_bitset<> synced_mutable_streams_bitmap; // const
	boost::dynamic_bitset<> synced_streams_bitmap; // const
	boost::dynamic_bitset<> unsynced_streams_bitmap; // const
	boost::dynamic_bitset<> side_packet_streams_bitmap; // const
	boost::dynamic_bitset<> synced_stream_is_complete;
	boost::dynamic_bitset<> synced_stream_is_partial_or_complete;
	std::vector<std::tuple<DataStream::DequeueResultBundle, std::list<PacketPtr<PacketBase>>>> dequeue_result_datas;
	/**
	 * @brief determine details of what kind of data dequeueing should happen
	 *
	 * @return true if there is unsynced data
	 * @return false if there is no unsynced data
	 */
	bool update_dequeue_results();
	void update_dequeue_results_one_synced(uint32_t idx);
	bool update_dequeue_results_one_unsynced(uint32_t idx);
	// calc info
	std::string name;
	std::string vendor;
	std::string calculator;
	std::thread manage_thread;
	std::thread::id manage_thread_id;
	void manage_task();
	ErrorCode handle_execute();
	void fill_stream_data_one(uint32_t idx, bool has_synced_packet, bool drop_synced);
	Graph* graph  = NULL;
	void* calc_vp = NULL;
	std::string ml_model_kernel_name;
	boost::dynamic_bitset<> determine_timedout_stream_indexes();

public:
	// APIs for execute
	template <typename PacketType>
	ErrorCode get_packet(int idx, std::list<PacketPtr<PacketType>>& packets) const
	{
		AUP_AVAF_RUNTIME_ERROR_IF(!is_execute || manage_thread_id != std::this_thread::get_id(),
		                          "function " << BOOST_CURRENT_FUNCTION
		                                      << " called outside of execute callback of node " << get_node_name());
		if (idx < 0 || idx >= (int)input_streams.size()) {
			return ErrorCode::OUT_OF_RANGE;
		}
		if (side_packet_streams_bitmap[idx]) {
			return ErrorCode::INVALID;
		}
		const auto& attrs = contract->input_attrs_arr[idx];
		if (attrs.type() != attrs.SYNCED_MUTABLE) {
			return ErrorCode::SINK_IMMUT;
		}
		packets.clear();
		for (auto& itr : streams_data[idx]) {
			packets.push_back(dynamic_packet_cast<PacketType>(itr));
		}
		return ErrorCode::OK;
	}
	template <typename PacketType>
	ErrorCode get_packet(int idx, std::list<PacketPtr<const PacketType>>& packets) const
	{
		AUP_AVAF_RUNTIME_ERROR_IF(!is_execute || manage_thread_id != std::this_thread::get_id(),
		                          "function " << BOOST_CURRENT_FUNCTION
		                                      << " called outside of execute callback of node " << get_node_name());
		if (idx < 0 || idx >= (int)input_streams.size()) {
			return ErrorCode::OUT_OF_RANGE;
		}
		if (side_packet_streams_bitmap[idx]) {
			return ErrorCode::INVALID;
		}
		packets.clear();
		for (auto& itr : streams_data[idx]) {
			packets.push_back(dynamic_packet_cast<const PacketType>(itr));
		}
		return ErrorCode::OK;
	}
	template <typename PacketType>
	ErrorCode get_packet(int idx, PacketPtr<PacketType>& packet) const
	{
		AUP_AVAF_RUNTIME_ERROR_IF(!is_execute || manage_thread_id != std::this_thread::get_id(),
		                          "function " << BOOST_CURRENT_FUNCTION
		                                      << " called outside of execute callback of node " << get_node_name());
		if (idx < 0 || idx >= (int)input_streams.size()) {
			return ErrorCode::OUT_OF_RANGE;
		}
		if (side_packet_streams_bitmap[idx]) {
			return ErrorCode::INVALID;
		}
		const auto& attrs = contract->input_attrs_arr[idx];
		if (attrs.type() != attrs.SYNCED_MUTABLE) {
			return ErrorCode::SINK_IMMUT;
		}
		if (attrs.can_continue() != GraphConfig::Node::NO) {
			return ErrorCode::SINK_ARRAY;
		}
		if (streams_data[idx].size() != 1) {
			return ErrorCode::TRY_LATER;
		}
		packet = dynamic_packet_cast<PacketType>(streams_data[idx].front());
		return ErrorCode::OK;
	}
	template <typename PacketType>
	ErrorCode get_packet(int idx, PacketPtr<const PacketType>& packet) const
	{
		AUP_AVAF_RUNTIME_ERROR_IF(!is_execute || manage_thread_id != std::this_thread::get_id(),
		                          "function " << BOOST_CURRENT_FUNCTION
		                                      << " called outside of execute callback of node " << get_node_name());
		if (idx < 0 || idx >= (int)input_streams.size()) {
			return ErrorCode::OUT_OF_RANGE;
		}
		if (side_packet_streams_bitmap[idx]) {
			PacketPtr<PacketBase> side_packet_base;
			auto ec = input_streams[idx].second->peek(this, side_packet_base);
			if (ec != ErrorCode::OK) {
				packet = nullptr;
				return ec;
			}
			packet = const_packet_cast<const PacketType>(dynamic_packet_cast<PacketType>(side_packet_base));
			return ErrorCode::OK;
		}
		const auto& attrs = contract->input_attrs_arr[idx];
		if (attrs.can_continue() != GraphConfig::Node::NO) {
			return ErrorCode::SINK_ARRAY;
		}
		if (streams_data[idx].size() != 1) {
			return ErrorCode::TRY_LATER;
		}
		packet = dynamic_packet_cast<const PacketType>(streams_data[idx].front());
		return ErrorCode::OK;
	}
	bool has_sync_failure() const { return exec_sync_failure; };
	timestamp_t get_current_sync_timestamp() const { return exec_sync_timestamp; };

	std::string get_ml_model_kernel_name() const;
	void set_ml_model_kernel_name(std::string get_ml_model_kernel_name);

private:
};

} // namespace aup::avaf
