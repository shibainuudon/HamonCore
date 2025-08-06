/**
 *	@file	hive_limits.hpp
 *
 *	@brief	hive_limits の定義
 */

#ifndef HAMON_HIVE_HIVE_LIMITS_HPP
#define HAMON_HIVE_HIVE_LIMITS_HPP

#include <hamon/hive/config.hpp>

#if defined(HAMON_USE_STD_HIVE)

#include <hive>

namespace hamon
{

using std::hive_limits;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

// 23.3.8 Header <hive> synopsis[hive.syn]

struct hive_limits
{
	hamon::size_t min;
	hamon::size_t max;

	HAMON_CXX11_CONSTEXPR
	hive_limits(hamon::size_t minimum, hamon::size_t maximum) HAMON_NOEXCEPT
		: min(minimum), max(maximum) {}
};

}	// namespace hamon

#endif

#endif // HAMON_HIVE_HIVE_LIMITS_HPP
