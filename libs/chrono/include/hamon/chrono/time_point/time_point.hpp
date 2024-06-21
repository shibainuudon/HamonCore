/**
 *	@file	time_point.hpp
 *
 *	@brief	time_point の定義
 */

#ifndef HAMON_CHRONO_TIME_POINT_TIME_POINT_HPP
#define HAMON_CHRONO_TIME_POINT_TIME_POINT_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::time_point;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/time_point/time_point_fwd.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/detail/is_specialization_of_duration.hpp>
#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace chrono {

// 29.6 Class template time_point[time.point]

template <typename Clock, typename Duration>
class time_point
{
public:
	using clock    = Clock;
	using duration = Duration;
	using rep      = typename duration::rep;
	using period   = typename duration::period;

	static_assert(hamon::chrono::detail::is_specialization_of_duration<Duration>::value, "[time.point.general]/1");

private:
	duration m_d;

public:
	// [time.point.cons], construct
	HAMON_CXX11_CONSTEXPR
	time_point()
		: m_d(duration::zero())	// [time.point.cons]/1
	{}

	HAMON_CXX11_CONSTEXPR explicit
	time_point(duration const& d)
		HAMON_NOEXCEPT_IF(hamon::is_arithmetic<rep>::value)	// noexcept as an extension
		: m_d(d)		// [time.point.cons]/2
	{}

	template <typename Duration2,
		typename = hamon::enable_if_t<
			hamon::is_convertible<Duration2, duration>::value>>	// [time.point.cons]/3
	HAMON_CXX11_CONSTEXPR
	time_point(time_point<clock, Duration2> const& t)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_arithmetic<rep>::value &&
			hamon::is_arithmetic<typename Duration2::rep>::value)
		: m_d(t.time_since_epoch())	// [time.point.cons]/4
	{}

	// [time.point.observer], observer
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	duration time_since_epoch() const
		HAMON_NOEXCEPT_IF(hamon::is_arithmetic<rep>::value)	// noexcept as an extension
	{
		// [time.point.observer]/1
		return m_d;
	}

	// [time.point.arithmetic], arithmetic
	HAMON_CXX14_CONSTEXPR time_point& operator++()
		HAMON_NOEXCEPT_IF(hamon::is_arithmetic<rep>::value)	// noexcept as an extension
	{
		// [time.point.arithmetic]/1
		++m_d;
		// [time.point.arithmetic]/2
		return *this;
	}

	HAMON_CXX14_CONSTEXPR time_point operator++(int)
		HAMON_NOEXCEPT_IF(hamon::is_arithmetic<rep>::value)	// noexcept as an extension
	{
		// [time.point.arithmetic]/3
		return time_point{m_d++};
	}

	HAMON_CXX14_CONSTEXPR time_point& operator--()
		HAMON_NOEXCEPT_IF(hamon::is_arithmetic<rep>::value)	// noexcept as an extension
	{
		// [time.point.arithmetic]/4
		--m_d;
		// [time.point.arithmetic]/5
		return *this;
	}

	HAMON_CXX14_CONSTEXPR time_point operator--(int)
		HAMON_NOEXCEPT_IF(hamon::is_arithmetic<rep>::value)	// noexcept as an extension
	{
		// [time.point.arithmetic]/6
		return time_point{m_d--};
	}

	HAMON_CXX14_CONSTEXPR time_point& operator+=(duration const& d)
		HAMON_NOEXCEPT_IF(hamon::is_arithmetic<rep>::value)	// noexcept as an extension
	{
		// [time.point.arithmetic]/7
		m_d += d;
		// [time.point.arithmetic]/8
		return *this;
	}

	HAMON_CXX14_CONSTEXPR time_point& operator-=(duration const& d)
		HAMON_NOEXCEPT_IF(hamon::is_arithmetic<rep>::value)	// noexcept as an extension
	{
		// [time.point.arithmetic]/9
		m_d -= d;
		// [time.point.arithmetic]/10
		return *this;
	}

	// [time.point.special], special values
	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	time_point min() HAMON_NOEXCEPT
	{
		// [time.point.special]/1
		return time_point(duration::min());
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	time_point max() HAMON_NOEXCEPT
	{
		// [time.point.special]/2
		return time_point(duration::max());
	}
};

// [time.point.nonmember], time_point arithmetic
template <typename Clock, typename Duration1, typename Rep2, typename Period2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
time_point<Clock, hamon::common_type_t<Duration1, duration<Rep2, Period2>>>
operator+(time_point<Clock, Duration1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<typename Duration1::rep>::value &&
		hamon::is_arithmetic<Rep2>::value)
{
	// [time.point.nonmember]/1
	using CT = time_point<Clock, hamon::common_type_t<Duration1, duration<Rep2, Period2>>>;
	return CT(lhs.time_since_epoch() + rhs);
}

template <typename Rep1, typename Period1, typename Clock, typename Duration2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
time_point<Clock, hamon::common_type_t<duration<Rep1, Period1>, Duration2>>
operator+(duration<Rep1, Period1> const& lhs, time_point<Clock, Duration2> const& rhs)
	HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<Rep1>::value &&
		hamon::is_arithmetic<typename Duration2::rep>::value)
{
	// [time.point.nonmember]/2
	return rhs + lhs;
}

template <typename Clock, typename Duration1, typename Rep2, typename Period2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
time_point<Clock, hamon::common_type_t<Duration1, duration<Rep2, Period2>>>
operator-(time_point<Clock, Duration1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<typename Duration1::rep>::value &&
		hamon::is_arithmetic<Rep2>::value)
{
	// [time.point.nonmember]/3
	using CT = time_point<Clock, hamon::common_type_t<Duration1, duration<Rep2, Period2>>>;
	return CT(lhs.time_since_epoch() - rhs);
}

template <typename Clock, typename Duration1, typename Duration2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::common_type_t<Duration1, Duration2>
operator-(time_point<Clock, Duration1> const& lhs, time_point<Clock, Duration2> const& rhs)
	HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<typename Duration1::rep>::value &&
		hamon::is_arithmetic<typename Duration2::rep>::value)
{
	// [time.point.nonmember]/4
	return lhs.time_since_epoch() - rhs.time_since_epoch();
}

// [time.point.comparisons], time_point comparisons
template <typename Clock, typename Duration1, typename Duration2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator==(time_point<Clock, Duration1> const& lhs, time_point<Clock, Duration2> const& rhs)
	HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<typename Duration1::rep>::value &&
		hamon::is_arithmetic<typename Duration2::rep>::value)
{
	// [time.point.comparisons]/1
	return lhs.time_since_epoch() == rhs.time_since_epoch();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename Clock, typename Duration1, typename Duration2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator!=(time_point<Clock, Duration1> const& lhs, time_point<Clock, Duration2> const& rhs)
	HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<typename Duration1::rep>::value &&
		hamon::is_arithmetic<typename Duration2::rep>::value)
{
	return !(lhs == rhs);
}
#endif

template <typename Clock, typename Duration1, typename Duration2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator<(time_point<Clock, Duration1> const& lhs, time_point<Clock, Duration2> const& rhs)
	HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<typename Duration1::rep>::value &&
		hamon::is_arithmetic<typename Duration2::rep>::value)
{
	// [time.point.comparisons]/2
	return lhs.time_since_epoch() < rhs.time_since_epoch();
}

template <typename Clock, typename Duration1, typename Duration2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator>(time_point<Clock, Duration1> const& lhs, time_point<Clock, Duration2> const& rhs)
	HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<typename Duration1::rep>::value &&
		hamon::is_arithmetic<typename Duration2::rep>::value)
{
	// [time.point.comparisons]/3
	return rhs < lhs;
}

template <typename Clock, typename Duration1, typename Duration2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator<=(time_point<Clock, Duration1> const& lhs, time_point<Clock, Duration2> const& rhs)
	HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<typename Duration1::rep>::value &&
		hamon::is_arithmetic<typename Duration2::rep>::value)
{
	// [time.point.comparisons]/4
	return !(rhs < lhs);
}

template <typename Clock, typename Duration1, typename Duration2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool operator>=(time_point<Clock, Duration1> const& lhs, time_point<Clock, Duration2> const& rhs)
	HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<typename Duration1::rep>::value &&
		hamon::is_arithmetic<typename Duration2::rep>::value)
{
	// [time.point.comparisons]/5
	return !(lhs < rhs);
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename Clock, typename Duration1, hamon::three_way_comparable_with<Duration1> Duration2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
auto operator<=>(time_point<Clock, Duration1> const& lhs, time_point<Clock, Duration2> const& rhs)
	HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<typename Duration1::rep>::value &&
		hamon::is_arithmetic<typename Duration2::rep>::value)
{
	// [time.point.comparisons]/6
	return lhs.time_since_epoch() <=> rhs.time_since_epoch();
}
#endif

}	// namespace chrono
}	// namespace hamon

#endif

#include <hamon/chrono/time_point/common_type.hpp>

#endif // HAMON_CHRONO_TIME_POINT_TIME_POINT_HPP
