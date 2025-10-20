/**
 *	@file	filetime_to_timespec.hpp
 *
 *	@brief	filetime_to_timespec の定義
 */

#ifndef HAMON_CHRONO_DETAIL_FILETIME_TO_TIMESPEC_HPP
#define HAMON_CHRONO_DETAIL_FILETIME_TO_TIMESPEC_HPP

#include <hamon/config.hpp>

#if defined(HAMON_PLATFORM_WIN32)

#include <hamon/cstdint.hpp>

namespace hamon {
namespace chrono {
namespace detail {

struct TimeSpec
{
	hamon::int64_t tv_sec;
	hamon::int64_t tv_nsec;
};

// There were 369 years and 89 leap days from the Windows epoch
// (1601) to the Unix epoch (1970).
#define FILE_TIME_OFFSET_SECS (hamon::uint64_t(369 * 365 + 89) * (24 * 60 * 60))

inline TimeSpec filetime_to_timespec(::LARGE_INTEGER li)
{
	TimeSpec ret;
	ret.tv_sec = li.QuadPart / 10000000 - FILE_TIME_OFFSET_SECS;
	ret.tv_nsec = (li.QuadPart % 10000000) * 100;
	return ret;
}

inline TimeSpec filetime_to_timespec(::FILETIME ft)
{
	::LARGE_INTEGER li;
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	return filetime_to_timespec(li);
}

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_DETAIL_FILETIME_TO_TIMESPEC_HPP
