#pragma once

// std headers
#include <chrono>
#include <limits>
#include <memory>
#include <mutex>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>
// sdk headers
// repository headers
#include "aup/avaf/error.h"
#include "aup/avaf/packet_ptr.h"
#include "aup/avaf/utils.h"

namespace aup::avaf {

class PacketBase
{

private:
	const std::chrono::system_clock::time_point gen_time_point;
	timestamp_t sync_timestamp;
	size_t itr_no; // iteration number for the stream
	const bool to_be_continued;

public:
	// Determine the packet type via a string. its purpose is
	// - Give a concise and human readable packet type
	// - Allow the framework to check the packet type
	// When you override this class to define a packet type, you would need to set this function to return a string
	// uniquely indicating its type Example: for the case of a packet denoting an image, we may use "AUP:IMAGE" In order
	// to standardize and avoid conflicts, prefix your return value with <vendor>:
	virtual const std::string get_packet_type() const { return "ANY"; }
	// This function determines if one packet is cast-able to another
	virtual bool can_be_casted_to(PacketPtr<const PacketBase>& other) const
	{
		if (get_packet_type() == "ANY") {
			return true;
		}
		return get_packet_type() == other->get_packet_type();
	}
	// Constructor for a packet which is timestamped with absolute timestamp which is contructed via
	// sync_timestamp is the value of synchronization timestamp
	// to_be_continued is a boolean indicating if a packet should be continued or not
	PacketBase(timestamp_t sync_timestamp, bool to_be_continued)
	    : gen_time_point(std::chrono::system_clock::now()), sync_timestamp(sync_timestamp),
	      to_be_continued(to_be_continued) {}
	// same as the above constructor except that to_be_continued is assumed to be false
	PacketBase(timestamp_t sync_timestamp) : PacketBase(sync_timestamp, false) {}
	// This constructor is used for non-timestamped packets.
	// Because the concept of timestamp only applies to timestamped packets, non-timestamped packets are always not
	// continued
	PacketBase() : PacketBase(timestamp_min) {}
	virtual ~PacketBase() {}
	// this will the generation time point of the packet
	// this indicates the absolute time in which the packet was generated in
	// it is primarily used by the framework to determine sync failures
	inline const std::chrono::system_clock::time_point& get_gen_time_point() const { return gen_time_point; }
	// This gets the sync timestamp
	inline const timestamp_t get_sync_timestamp() const { return sync_timestamp; }
	// with this you can directly set the sync timestamp
	inline void set_sync_timestamp(timestamp_t val) { sync_timestamp = val; }
	// This will get the value of the iteration number of the packet
	inline size_t get_itr_no() const { return itr_no; }
	// This will set the value of the iteration number. primarily used by the framework
	inline void set_itr_no(const size_t itr_no) { this->itr_no = itr_no; }
	// This is to determine if a packet is continued
	inline const bool is_continued() const { return this->to_be_continued; };
};

class PacketBasePTS : public PacketBase
{
	timestamp_t pts;

public:
	PacketBasePTS(timestamp_t sync_timestamp, bool to_be_continued) : PacketBase(sync_timestamp, to_be_continued) {}
	PacketBasePTS(timestamp_t sync_timestamp) : PacketBase(sync_timestamp) {}
	PacketBasePTS() : PacketBase() {}
	inline void set_pres_timestamp(timestamp_t pts) { this->pts = pts; }
	inline timestamp_t get_pres_timestamp() const { return pts; }
};

} // namespace aup::avaf