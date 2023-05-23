#pragma once

#include <chrono>
#include <cstring>
#include <iostream>
#include <mutex>

namespace aup::avaf {

std::mutex& get_avaf_dbg_mux();

} // namespace aup::avaf

#define AUP_AVAF_GLOBAL_DBG_ENABLE 1
#define AUP_AVAF_DBG_FILENAME() (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#if defined(AUP_AVAF_DBG_ENABLE) && defined(AUP_AVAF_GLOBAL_DBG_ENABLE)
#define AUP_AVAF_DBG(args)                                                                                             \
	do {                                                                                                               \
		auto AVAF_DBG_now = ::std::chrono::system_clock::now();                                                        \
		char AVAF_DBG_timestamp[128];                                                                                  \
		auto AVAF_DBG_ns = AVAF_DBG_now.time_since_epoch().count() % 1000000000;                                       \
		::std::time_t AVAF_DBG_tt;                                                                                     \
		AVAF_DBG_tt            = ::std::chrono::system_clock::to_time_t(AVAF_DBG_now);                                 \
		auto AVAF_DBG_timeinfo = localtime(&AVAF_DBG_tt);                                                              \
		strftime(AVAF_DBG_timestamp, sizeof(AVAF_DBG_timestamp), "%F %H:%M:%S", AVAF_DBG_timeinfo);                    \
		snprintf(AVAF_DBG_timestamp + strlen(AVAF_DBG_timestamp),                                                      \
		         sizeof(AVAF_DBG_timestamp) - strlen(AVAF_DBG_timestamp), ".%09d", (int)AVAF_DBG_ns);                  \
		::std::lock_guard<::std::mutex> lg(::aup::avaf::get_avaf_dbg_mux());                                           \
		::std::cout << "[AVAF_DBG:" << AUP_AVAF_DBG_FILENAME() << ":" << __FUNCTION__ << ":" << __LINE__ << ":"        \
		            << AVAF_DBG_timestamp << "] " << args << ::std::endl                                               \
		            << ::std::flush;                                                                                   \
	} while (0)
#else
#define AUP_AVAF_DBG(args)                                                                                             \
	do {                                                                                                               \
	} while (0)
#endif
#define AUP_AVAF_TRACE() AUP_AVAF_DBG("here")