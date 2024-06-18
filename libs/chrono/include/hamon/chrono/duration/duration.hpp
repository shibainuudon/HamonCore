/**
 *	@file	duration.hpp
 *
 *	@brief	duration の定義
 */

#ifndef HAMON_CHRONO_DURATION_DURATION_HPP
#define HAMON_CHRONO_DURATION_DURATION_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::duration;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration/duration_fwd.hpp>
#include <hamon/chrono/duration/duration_cast.hpp>
#include <hamon/chrono/duration/duration_values.hpp>
#include <hamon/chrono/duration/detail/units_suffix.hpp>
#include <hamon/chrono/treat_as_floating_point.hpp>
#include <hamon/chrono/detail/is_specialization_of_duration.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/ratio/ratio_divide.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/config.hpp>
#include <ostream>	// basic_ostream
#include <sstream>	// basic_ostringstream

namespace hamon {
namespace chrono {

// 29.5 Class template duration[time.duration]

template <typename Rep, typename Period>
class duration
{
public:
	using rep    = Rep;
	using period = typename Period::type;

	static_assert(!hamon::chrono::detail::is_specialization_of_duration<Rep>::value, "[time.duration.general]/2");
	// TODO
//	static_assert(hamon::detail::is_specialization_of_ratio<Period>::value, "[time.duration.general]/3");
	static_assert(Period::num > 0, "[time.duration.general]/3");

private:
	rep m_rep;

public:
	// [time.duration.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR duration() = default;

	template <typename Rep2,
		typename = hamon::enable_if_t<
			hamon::is_convertible<Rep2 const&, rep>::value &&	// [time.duration.cons]/1
			( treat_as_floating_point<rep>::value ||			// [time.duration.cons]/1.1
			 !treat_as_floating_point<Rep2>::value)>>			// [time.duration.cons]/1.2
	HAMON_CXX11_CONSTEXPR explicit
	duration(Rep2 const& r) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<Rep>::value && hamon::is_arithmetic<Rep2>::value)
		: m_rep(static_cast<Rep>(r))	// [time.duration.cons]/2
	{}

	template <typename Rep2, typename Period2,
		typename = hamon::enable_if_t<
			// [time.duration.cons]/3
			treat_as_floating_point<rep>::value ||
			(hamon::ratio_divide<Period2, period>::den == 1 &&
			 !treat_as_floating_point<Rep2>::value)>>
	HAMON_CXX11_CONSTEXPR
	duration(duration<Rep2, Period2> const& d) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<Rep>::value && hamon::is_arithmetic<Rep2>::value)
		: m_rep(duration_cast<duration>(d).count())	// [time.duration.cons]/4
	{}

	~duration() = default;

	duration(duration const&) = default;

	duration& operator=(duration const&) = default;

	// [time.duration.observer], observer
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	rep count() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.observer]/1
		return m_rep;
	}

	// [time.duration.arithmetic], arithmetic
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::common_type_t<duration>
	operator+() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.arithmetic]/1
		return hamon::common_type_t<duration>(*this);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::common_type_t<duration>
	operator-() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.arithmetic]/2
		return hamon::common_type_t<duration>(-m_rep);
	}

	HAMON_CXX14_CONSTEXPR duration&
	operator++() HAMON_NOEXCEPT_IF(			// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.arithmetic]/3
		++m_rep;
		// [time.duration.arithmetic]/4
		return *this;
	}

	HAMON_CXX14_CONSTEXPR duration
	operator++(int) HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.arithmetic]/5
		return duration(m_rep++);
	}

	HAMON_CXX14_CONSTEXPR duration&
	operator--() HAMON_NOEXCEPT_IF(			// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.arithmetic]/6
		--m_rep;
		// [time.duration.arithmetic]/7
		return *this;
	}

	HAMON_CXX14_CONSTEXPR duration
	operator--(int) HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.arithmetic]/8
		return duration(m_rep--);
	}

	HAMON_CXX14_CONSTEXPR duration&
	operator+=(duration const& d) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.arithmetic]/9
		m_rep += d.count();
		// [time.duration.arithmetic]/10
		return *this;
	}

	HAMON_CXX14_CONSTEXPR duration&
	operator-=(duration const& d) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.arithmetic]/11
		m_rep -= d.count();
		// [time.duration.arithmetic]/12
		return *this;
	}

	HAMON_CXX14_CONSTEXPR duration&
	operator*=(rep const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.arithmetic]/13
		m_rep *= rhs;
		// [time.duration.arithmetic]/14
		return *this;
	}

	HAMON_CXX14_CONSTEXPR duration&
	operator/=(rep const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.arithmetic]/15
		m_rep /= rhs;
		// [time.duration.arithmetic]/16
		return *this;
	}

	HAMON_CXX14_CONSTEXPR duration&
	operator%=(rep const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.arithmetic]/17
		m_rep %= rhs;
		// [time.duration.arithmetic]/18
		return *this;
	}

	HAMON_CXX14_CONSTEXPR duration&
	operator%=(duration const& rhs) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_arithmetic<Rep>::value)
	{
		// [time.duration.arithmetic]/19
		m_rep %= rhs.count();
		// [time.duration.arithmetic]/20
		return *this;
	}

	// [time.duration.special], special values
	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	duration zero() HAMON_NOEXCEPT
	{
		// [time.duration.special]/1
		return duration(duration_values<rep>::zero());
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	duration min() HAMON_NOEXCEPT
	{
		// [time.duration.special]/2
		return duration(duration_values<rep>::min());
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	duration max() HAMON_NOEXCEPT
	{
		// [time.duration.special]/3
		return duration(duration_values<rep>::max());
	}
};

namespace detail {

// is_specialization_of_duration の特殊化
template <typename Rep, typename Period>
struct is_specialization_of_duration<hamon::chrono::duration<Rep, Period>>
	: public hamon::true_type {};

}	// namespace detail

// [time.duration.nonmember], duration arithmetic

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>
operator+(duration<Rep1, Period1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.nonmember]/1
	using CD = hamon::common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>;
	// [time.duration.nonmember]/2
	return CD(CD(lhs).count() + CD(rhs).count());
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>
operator-(duration<Rep1, Period1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.nonmember]/1
	using CD = hamon::common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>;
	// [time.duration.nonmember]/3
	return CD(CD(lhs).count() - CD(rhs).count());
}

template <typename Rep1, typename Period, typename Rep2,
	typename = hamon::enable_if_t<
		// [time.duration.nonmember]/4
		hamon::is_convertible<Rep2 const&, hamon::common_type_t<Rep1, Rep2>>::value>>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
duration<hamon::common_type_t<Rep1, Rep2>, Period>
operator*(duration<Rep1, Period> const& d, Rep2 const& s)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.nonmember]/1
	using CD = duration<hamon::common_type_t<Rep1, Rep2>, Period>;
	// [time.duration.nonmember]/5
	return CD(CD(d).count() * s);
}

template <typename Rep1, typename Rep2, typename Period,
	typename = hamon::enable_if_t<
		// [time.duration.nonmember]/6
		hamon::is_convertible<Rep1 const&, hamon::common_type_t<Rep1, Rep2>>::value>>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
duration<hamon::common_type_t<Rep1, Rep2>, Period>
operator*(Rep1 const& s, duration<Rep2, Period> const& d)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.nonmember]/7
	return d * s;
}

template <typename Rep1, typename Period, typename Rep2,
	typename = hamon::enable_if_t<
		// [time.duration.nonmember]/8
		hamon::is_convertible<Rep2 const&, hamon::common_type_t<Rep1, Rep2>>::value &&
		!hamon::chrono::detail::is_specialization_of_duration<Rep2>::value>>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
duration<hamon::common_type_t<Rep1, Rep2>, Period>
operator/(duration<Rep1, Period> const& d, Rep2 const& s)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.nonmember]/1
	using CD = duration<hamon::common_type_t<Rep1, Rep2>, Period>;
	// [time.duration.nonmember]/9
	return CD(CD(d).count() / s);
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::common_type_t<Rep1, Rep2>
operator/(duration<Rep1, Period1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.nonmember]/10
	using CD = hamon::common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>;
	// [time.duration.nonmember]/11
	return CD(lhs).count() / CD(rhs).count();
}

template <typename Rep1, typename Period, typename Rep2,
	typename = hamon::enable_if_t<
		// [time.duration.nonmember]/12
		hamon::is_convertible<Rep2 const&, hamon::common_type_t<Rep1, Rep2>>::value &&
		!hamon::chrono::detail::is_specialization_of_duration<Rep2>::value>>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
duration<hamon::common_type_t<Rep1, Rep2>, Period>
operator%(duration<Rep1, Period> const& d, Rep2 const& s)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.nonmember]/1
	using CD = duration<hamon::common_type_t<Rep1, Rep2>, Period>;
	// [time.duration.nonmember]/13
	return CD(CD(d).count() % s);
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>
operator%(duration<Rep1, Period1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.nonmember]/1
	using CD = hamon::common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>;
	// [time.duration.nonmember]/14
	return CD(CD(lhs).count() % CD(rhs).count());
}

// [time.duration.comparisons], duration comparisons

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator==(duration<Rep1, Period1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.comparisons]/1
	using CT = hamon::common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>;
	// [time.duration.comparisons]/2
	return CT(lhs).count() == CT(rhs).count();
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename Rep1, typename Period1, typename Rep2, typename Period2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator!=(duration<Rep1, Period1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	return !(lhs == rhs);
}
#endif

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<(duration<Rep1, Period1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.comparisons]/1
	using CT = hamon::common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>;
	// [time.duration.comparisons]/3
	return CT(lhs).count() < CT(rhs).count();
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>(duration<Rep1, Period1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.comparisons]/4
	return rhs < lhs;
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator<=(duration<Rep1, Period1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.comparisons]/5
	return !(rhs < lhs);
}

template <typename Rep1, typename Period1, typename Rep2, typename Period2>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
operator>=(duration<Rep1, Period1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.comparisons]/6
	return !(lhs < rhs);
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename Rep1, typename Period1, typename Rep2, typename Period2,
	// [time.duration.comparisons]/1
	typename CT = hamon::common_type_t<duration<Rep1, Period1>, duration<Rep2, Period2>>>
requires hamon::three_way_comparable<typename CT::rep>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
operator<=>(duration<Rep1, Period1> const& lhs, duration<Rep2, Period2> const& rhs)
	HAMON_NOEXCEPT_IF(hamon::is_arithmetic<Rep1>::value && hamon::is_arithmetic<Rep2>::value)	// noexcept as an extension
{
	// [time.duration.comparisons]/7
	return CT(lhs).count() <=> CT(rhs).count();
}
#endif

// 29.5.11 I/O[time.duration.io]

template <typename charT, typename traits, typename Rep, typename Period>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, duration<Rep, Period> const& d)
{
	// [time.duration.io]/1
	std::basic_ostringstream<charT, traits> s;
	s.flags(os.flags());
	s.imbue(os.getloc());
	s.precision(os.precision());
	s << d.count();
	detail::units_suffix<typename Period::type>::invoke(s);
	return os << s.str();
}

}	// namespace chrono
}	// namespace hamon

#endif

#include <hamon/chrono/duration/common_type.hpp>

#endif // HAMON_CHRONO_DURATION_DURATION_HPP
