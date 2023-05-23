#pragma once

#include <iostream>
#include <string>

namespace aup::avaf {

std::string strip_file_name(std::string name);
void thread_name_set(std::string& thread_name);
std::string& thread_name_get();
void thread_name_unset();
void thread_name_dump();

class ThreadNameHandler
{
public:
	ThreadNameHandler(std::string thread_name) { thread_name_set(thread_name); }
	~ThreadNameHandler() { thread_name_unset(); }
};
} // namespace aup::avaf

#define AUP_AVAF_HANDLE_THREAD_NAME_EXT(str_)                                                                          \
	::std::string AUP_AVAF_HANDLE_THREAD_NAME_thread_name =                                                            \
	    ::aup::avaf::strip_file_name(__FILE__) + ":" + __PRETTY_FUNCTION__ + (str_[0] ? ":" : "") + str_;              \
	::aup::avaf::ThreadNameHandler AUP_AVAF_HANDLE_THREAD_NAME_handler(AUP_AVAF_HANDLE_THREAD_NAME_thread_name)

#define AUP_AVAF_HANDLE_THREAD_NAME() AUP_AVAF_HANDLE_THREAD_NAME_EXT("")