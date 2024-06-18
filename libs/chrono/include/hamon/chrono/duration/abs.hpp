/**
 *	@file	abs.hpp
 *
 *	@brief	abs の定義
 */

#ifndef HAMON_CHRONO_DURATION_ABS_HPP
#define HAMON_CHRONO_DURATION_ABS_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::abs;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration/duration.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 29.5.10 Algorithms[time.duration.alg]

template <typename Rep, typename Period,
	typename = hamon::enable_if_t<
		hamon::numeric_limits<Rep>::is_signed>>	// [time.duration.alg]/1
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR duration<Rep, Period>	// nodiscard as an extension
abs(duration<Rep, Period> d) HAMON_NOEXCEPT_IF(	// noexcept as an extension
	hamon::is_arithmetic<Rep>::value)
{
	// [time.duration.alg]/2
	return d >= d.zero() ? d : -d;
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_DURATION_ABS_HPP
