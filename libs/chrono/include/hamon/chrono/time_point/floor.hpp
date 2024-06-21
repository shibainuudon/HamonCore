﻿/**
 *	@file	floor.hpp
 *
 *	@brief	floor の定義
 */

#ifndef HAMON_CHRONO_TIME_POINT_FLOOR_HPP
#define HAMON_CHRONO_TIME_POINT_FLOOR_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::floor;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/time_point/time_point.hpp>
#include <hamon/chrono/detail/is_specialization_of_duration.hpp>
#include <hamon/chrono/duration/floor.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 29.6.8 Conversions[time.point.cast]

template <typename ToDuration, typename Clock, typename Duration,
	typename = hamon::enable_if_t<
		// [time.point.cast]/3
		hamon::chrono::detail::is_specialization_of_duration<ToDuration>::value>>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::chrono::time_point<Clock, ToDuration>
floor(hamon::chrono::time_point<Clock, Duration> const& tp) HAMON_NOEXCEPT_IF(
	hamon::is_arithmetic<typename Duration::rep>::value &&
	hamon::is_arithmetic<typename ToDuration::rep>::value)	// noexcept as an extension
{
	// [time.point.cast]/4
	return hamon::chrono::time_point<Clock, ToDuration>(
		floor<ToDuration>(tp.time_since_epoch()));
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_TIME_POINT_FLOOR_HPP
