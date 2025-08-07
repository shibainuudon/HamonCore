/**
 *	@file	local_info.hpp
 *
 *	@brief	local_info の定義
 */

#ifndef HAMON_CHRONO_LOCAL_INFO_HPP
#define HAMON_CHRONO_LOCAL_INFO_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::local_info;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/sys_info.hpp>
#include <ostream>	// basic_ostream

namespace hamon {
namespace chrono {

// 30.11.4.2 Class local_info[time.zone.info.local]

struct local_info
{
	static constexpr int unique      = 0;
	static constexpr int nonexistent = 1;
	static constexpr int ambiguous   = 2;

	int result;
	sys_info first;
	sys_info second;
};

#if 0	// TODO
template <typename charT, typename traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, local_info const& li);
#endif

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_LOCAL_INFO_HPP
