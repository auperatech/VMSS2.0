#pragma once

#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "aup/avaf/contract.h"
#include "aup/avaf/error.h"
#include "aup/avaf/log.h"
#include "aup/avaf/packet_ptr_use_count_notifier.h"
#include "aup/avaf/statistician.h"
#include "aup/avaf/status.h"
#include "aup/avaf/type.h"
#include "aup/avap/graph.pb.h"

namespace aup::avaf {

class Node;
class DataStream;
class PacketBase;

class Graph
{
public:
	Graph();
	Graph(const Graph&)            = delete;
	Graph& operator=(const Graph&) = delete;

	explicit Graph(std::string graph_config_name); // create an instance by proto description file

	virtual ~Graph();

	/* initialize the whole graph including each node and each data stream with given input urls and output urls */
	ErrorCode initialize(const std::vector<std::string>& input_urls, const std::vector<std::string>& output_urls);
	/* start to run the whole graph */
	ErrorCode run();
	/* uninitialize the whole graph */
	void uninitialize();

	std::vector<std::pair<std::string, const Node*>> input_urls();
	std::vector<std::pair<std::string, const Node*>> output_urls();
	/* get data stream element count(depth) */

	const Node* get_node_by_name(const std::string nodeName);
	bool find_node(const Node* pNode);
	std::shared_ptr<DataStream> get_data_stream(std::string name);

	int32_t controlPort = -1;
	std::shared_ptr<Logger> logger; // logger for current graph

	GraphStatus get_status();
	void set_status(GraphStatus status_);
	struct NodeIO
	{
		std::shared_ptr<Node> node;
		uint32_t stream_idx;
		PacketPtr<const PacketBase> sample;
	};
	struct StreamConn
	{
		std::string name;
		NodeIO src;
		std::vector<NodeIO> dsts;
	};
	// returns all contracts are consistent with node IOs. ITC, there might be illegal connections in ret
	// returns false otherwise. ITC, illegal connections will NOT be calculated
	bool get_illegal_connections(std::unordered_map<std::string, std::shared_ptr<Contract>>& node_name_to_contract,
	                             std::vector<StreamConn>& ret);

private:
	std::unordered_map<std::string, std::string> graph_input_to_url;
	std::unordered_map<std::string, std::string> graph_output_to_url;
	std::vector<std::shared_ptr<Node>> nodes;
	std::unordered_map<std::string, std::shared_ptr<DataStream>> streams;
	std::vector<std::pair<std::string, const Node*>> inputUrls;
	std::vector<std::pair<std::string, const Node*>> outputUrls;
	bool initialized_ = false;
	GraphConfig config;
	GraphStatus status;
	PacketPtrUseCountNotifier packet_ptr_use_count_notifier;
	void initialize_statistician_latency(const GraphConfig::StatisticsCollector& statistics_collector,
	                                     std::shared_ptr<Statistician>& statistician);
	void initialize_statistician_thruput(const GraphConfig::StatisticsCollector& statistics_collector,
	                                     std::shared_ptr<Statistician>& statistician);
	void initialize_statistician_size(const GraphConfig::StatisticsCollector& statistics_collector,
	                                  std::shared_ptr<Statistician>& statistician);
	void initialize_statisticians();
};

/* find belonging graph based on given node pointer */
Graph* find_ine_graph(const Node* pNode);

} // namespace aup::avaf