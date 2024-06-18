/**
 *	@file	floor.hpp
 *
 *	@brief	floor の定義
 */

#ifndef HAMON_CHRONO_DURATION_FLOOR_HPP
#define HAMON_CHRONO_DURATION_FLOOR_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::floor;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration/duration.hpp>
#include <hamon/chrono/duration/duration_cast.hpp>
#include <hamon/chrono/detail/is_specialization_of_duration.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

namespace detail {

template <typename ToDuration, typename Duration>
HAMON_CXX11_CONSTEXPR ToDuration floor_impl(Duration const& d, ToDuration const& t)
{
	// [time.duration.cast]/5
	return (t > d) ? (t - ToDuration{1}) : t;
}

}	// namespace detail

// 29.5.8 Conversions[time.duration.cast]

template <typename ToDuration, typename Rep, typename Period,
	typename = hamon::enable_if_t<
		// [time.duration.cast]/4
		hamon::chrono::detail::is_specialization_of_duration<ToDuration>::value>>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR ToDuration	// nodiscard as an extension
floor(duration<Rep, Period> const& d) HAMON_NOEXCEPT_IF(	// noexcept as an extension
	hamon::is_arithmetic<Rep>::value &&
	hamon::is_arithmetic<typename ToDuration::rep>::value)
{
	return detail::floor_impl(d, hamon::chrono::duration_cast<ToDuration>(d));
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_DURATION_FLOOR_HPP
