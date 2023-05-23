#pragma once

#include <boost/core/null_deleter.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/keywords/channel.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/record_ordering.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <fstream>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

namespace aup::avaf {

#define _COLOR_RED "\033[31m"
#define _COLOR_GREEN "\033[32m"
#define _COLOR_YELLOW "\033[33m"
#define _COLOR_WHITE "\033[37m"
#define _COLOR_PURPLE "\033[35m"
#define _COLOR_END "\033[0m"

enum SeverityLevel
{
	LOG_TRACE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL
};

// The formatting logic for the severity level
template <typename CharT, typename TraitsT>
inline std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& strm, SeverityLevel lvl)
{
	switch (lvl) {
		case LOG_TRACE:
			strm << "TRACE";
			break;
		case LOG_DEBUG:
			strm << _COLOR_PURPLE << "DEBUG" << _COLOR_END;
			break;
		case LOG_INFO:
			strm << _COLOR_GREEN << "INFO" << _COLOR_END;
			break;
		case LOG_WARN:
			strm << _COLOR_YELLOW << "WARN" << _COLOR_END;
			break;
		case LOG_ERROR:
			strm << _COLOR_RED << "ERROR" << _COLOR_END;
			break;
		case LOG_FATAL:
			strm << _COLOR_RED << "FATAL" << _COLOR_END;
			break;
		default:
			strm << static_cast<int>(lvl);
			break;
	}
	return strm;
}

typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> log_file_sink;
typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> log_ost_sink;

class Logger
{
public:
	Logger(const std::string& channel);
	virtual ~Logger();

	boost::log::sources::severity_logger_mt<SeverityLevel>& mlogger() { return this->slg; }

	boost::log::sources::severity_logger_mt<SeverityLevel> slg;
	std::string channelName;
	boost::shared_ptr<log_file_sink> fileSink;
	boost::shared_ptr<log_ost_sink> consoleSink;
	std::string task_dir;
};

} // namespace aup::avaf
