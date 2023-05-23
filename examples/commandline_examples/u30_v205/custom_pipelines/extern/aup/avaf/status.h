#pragma once

#include <string>

namespace aup::avaf {

enum class GraphStatus
{
	IDLE,    // in this state, graph threads and nodes are not ready
	READY,   // in this state, graph threads are created, all nodes are initialized
	RUNNING, // in this state, graph accepted the initial input(urls) and outputs(urls)
	PAUSE,   // in this state, the graph threads and node threads should pause but not quit
	FAILED,  // in this state, the graph threads and node threads should be quited, the whole graph will be
	                      // destroy with abnormal state
	FINISHED // in this state, the graph threads and node threads should be quited, the whole graph will be
	                      // destroy with normal state
};

std::string graph_status_desc(GraphStatus status);

} // namespace aup::avaf
