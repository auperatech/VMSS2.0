#pragma once

// std headers
#include <memory>
#include <mutex>
#include <ostream>
#include <string>

// local headers
#include "aup/avaf/type.h"

namespace aup::avaf::muxed_stream {

void destroy(const std::string& path);
std::shared_ptr<std::mutex> get_mutex(const std::string& path);
std::shared_ptr<std::ostream> get_stream(const std::string& path);
const std::string& get_datetime();

} // namespace aup::avaf::muxed_stream
