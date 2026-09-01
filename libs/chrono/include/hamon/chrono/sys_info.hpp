/**
 *	@file	sys_info.hpp
 *
 *	@brief	sys_info の定義
 */

#ifndef HAMON_CHRONO_SYS_INFO_HPP
#define HAMON_CHRONO_SYS_INFO_HPP

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/sys_seconds.hpp>
#include <hamon/ostream/basic_ostream.hpp>
#include <hamon/string.hpp>

namespace hamon {
namespace chrono {

// 30.11.4.1 Class sys_info[time.zone.info.sys]

struct sys_info
{
	sys_seconds   begin;
	sys_seconds   end;
	seconds       offset;
	minutes       save;
	hamon::string abbrev;
};

#if 0	// TODO
template <typename charT, typename traits>
hamon::basic_ostream<charT, traits>&
operator<<(hamon::basic_ostream<charT, traits>& os, sys_info const& si);
#endif

}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_SYS_INFO_HPP
