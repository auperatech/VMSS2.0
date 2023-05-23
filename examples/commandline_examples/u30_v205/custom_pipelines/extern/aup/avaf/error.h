#pragma once

#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace aup::avaf {

enum class ErrorCode
{
	ERROR = -9999,
	DATATYPE_MISMATCH,
	NO_MEMORY,
	QUEUE_FULL,
	OUT_OF_RANGE,
	OPERATION_UNAVAILABLE,
	PROTOBUF,
	SINK_NODE_DUPLICATE,
	NON_UNIQUE_MUTABLE_SINK,
	INCOMPATIBLE_SINKS,
	INVALID_CONTRACT,
	TIMESTAMP_MISMATCH,
	SIZE_MISMATCH,
	SINK_IMMUT,
	SINK_ARRAY,
	INVALID_SYNC_TIMESTAMP,
	OK = 0,
	END_OF_FILE,
	TRY_LATER,
	INVALID,
};

std::string get_ec_desc(const ErrorCode ec);
static inline constexpr auto get_ec_int(const ErrorCode ec) noexcept
{
	return static_cast<std::underlying_type_t<ErrorCode>>(ec);
}

static inline std::ostream& operator<<(std::ostream& strm, const ErrorCode& ec)
{
	return strm << get_ec_desc(ec) << "(" << get_ec_int(ec) << ")";
}

} // namespace aup::avaf

namespace std {
static inline std::string to_string(const aup::avaf::ErrorCode& ec) { return aup::avaf::get_ec_desc(ec); }
} // namespace std

#define AUP_AVAF_RUNTIME_ERROR_IF(cond_, msg_args_)                                                                    \
	if ((cond_)) {                                                                                                     \
		::std::stringstream AUP_AVAF_RUNTIME_ERROR_er_ss;                                                              \
		AUP_AVAF_RUNTIME_ERROR_er_ss << "runtime error @[" << __FILE__ << ":" << __PRETTY_FUNCTION__ << ":"            \
		                             << __LINE__ << "] " << msg_args_ << ::std::endl;                                  \
		::std::string AUP_AVAF_RUNTIME_ERROR_err_msg = AUP_AVAF_RUNTIME_ERROR_er_ss.str();                             \
		throw ::std::runtime_error(AUP_AVAF_RUNTIME_ERROR_err_msg);                                                    \
	}

#define AUP_AVAF_RUNTIME_ERROR(msg_args_) AUP_AVAF_RUNTIME_ERROR_IF(true, msg_args_)
// ...