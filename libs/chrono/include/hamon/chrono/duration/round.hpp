/**
 *	@file	round.hpp
 *
 *	@brief	round の定義
 */

#ifndef HAMON_CHRONO_DURATION_ROUND_HPP
#define HAMON_CHRONO_DURATION_ROUND_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::round;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration/duration.hpp>
#include <hamon/chrono/duration/floor.hpp>
#include <hamon/chrono/detail/is_specialization_of_duration.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

namespace detail {

template <typename ToDuration, typename T>
HAMON_CXX11_CONSTEXPR ToDuration
round_impl3(ToDuration const& t0, ToDuration const& t1, T const& diff0, T const& diff1)
{
	return
		(diff0 < diff1) ? t0 :
		(diff0 > diff1) ? t1 :
		t0.count() & 1 ? t1 : t0;
}

template <typename ToDuration, typename Duration>
HAMON_CXX11_CONSTEXPR ToDuration
round_impl2(Duration const& d, ToDuration const& t0, ToDuration const& t1)
{
	return round_impl3(t0, t1, d - t0, t1 - d);
}

template <typename ToDuration, typename Duration>
HAMON_CXX11_CONSTEXPR ToDuration
round_impl(Duration const& d, ToDuration const& t0)
{
	return round_impl2(d, t0, t0 + ToDuration{1});
}

}	// namespace detail

// 29.5.8 Conversions[time.duration.cast]

template <typename ToDuration, typename Rep, typename Period,
	typename = hamon::enable_if_t<
		// [time.duration.cast]/8
		hamon::chrono::detail::is_specialization_of_duration<ToDuration>::value &&
		!treat_as_floating_point<typename ToDuration::rep>::value>>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR ToDuration	// nodiscard as an extension
round(duration<Rep, Period> const& d) HAMON_NOEXCEPT_IF(	// noexcept as an extension
	hamon::is_arithmetic<Rep>::value &&
	hamon::is_arithmetic<typename ToDuration::rep>::value)
{
	return detail::round_impl(d, hamon::chrono::floor<ToDuration>(d));
}

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_DURATION_ROUND_HPP
