#pragma once

#include <ostream>
#include <stdint.h>

namespace aup::avaf {

typedef int64_t timestamp_t;
static const timestamp_t timestamp_min = std::numeric_limits<timestamp_t>::min();
static const timestamp_t timestamp_max = std::numeric_limits<timestamp_t>::max();

enum class CodecType
{
	NONE = 0,
	H264,
	H265
};

static inline std::ostream& operator<<(std::ostream& strm, const CodecType& input)
{
	return strm << static_cast<std::underlying_type_t<CodecType>>(input);
}

// TODO replace with proto enum
enum class PixFmtType
{
	NONE = 0,
	NV12,
	I420,
	BGR24,
	RGB24
};

static inline std::ostream& operator<<(std::ostream& strm, const PixFmtType& input)
{
	return strm << static_cast<std::underlying_type_t<PixFmtType>>(input);
}

enum class PicType
{
	NONE = 0,
	I,
	P,
	B
};

static inline std::ostream& operator<<(std::ostream& strm, const PicType& input)
{
	return strm << static_cast<std::underlying_type_t<PicType>>(input);
}

enum class UrlType
{
	NATIVE_VIDEO = 0,
	LIVE_STREAM
};

static inline std::ostream& operator<<(std::ostream& strm, const UrlType& input)
{
	return strm << static_cast<std::underlying_type_t<UrlType>>(input);
}

} // namespace aup::avaf

namespace std {
static inline std::string to_string(const aup::avaf::CodecType& input) { return to_string(static_cast<int>(input)); }
static inline std::string to_string(const aup::avaf::PixFmtType& input) { return to_string(static_cast<int>(input)); }
static inline std::string to_string(const aup::avaf::PicType& input) { return to_string(static_cast<int>(input)); }
static inline std::string to_string(const aup::avaf::UrlType& input) { return to_string(static_cast<int>(input)); }
} // namespace std
