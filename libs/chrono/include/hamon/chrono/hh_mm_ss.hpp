/**
 *	@file	hh_mm_ss.hpp
 *
 *	@brief	hh_mm_ss の定義
 */

#ifndef HAMON_CHRONO_HH_MM_SS_HPP
#define HAMON_CHRONO_HH_MM_SS_HPP

#include <hamon/chrono/config.hpp>

#if defined(HAMON_USE_STD_CHRONO)

#include <chrono>

namespace hamon {
namespace chrono {

using std::chrono::hh_mm_ss;

}	// namespace chrono
}	// namespace hamon

#else

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <ostream>

namespace hamon {
namespace chrono {

// 30.9 Class template hh_mm_ss[time.hms]

template <typename Duration>
class hh_mm_ss
{
private:
	static HAMON_CXX11_CONSTEXPR hamon::uint64_t
	pow10(unsigned exp, hamon::uint64_t ret)
	{
		return exp == 0 ? ret : pow10(exp - 1, ret * 10);
	}

	static HAMON_CXX11_CONSTEXPR unsigned
	width(hamon::uint64_t n, hamon::uint64_t d = 10, unsigned w = 0)
	{
		return (n >= 2 && d != 0 && w <= 18) ?
			(1 + width(n, d % n * 10, w + 1)) :
			0;
	}

	using CommonType = hamon::common_type_t<Duration, chrono::seconds>;
	HAMON_CXX11_STATIC_CONSTEXPR unsigned fractional_w = width(CommonType::period::den);

public:
	// [time.hms.members]/1
	HAMON_CXX11_STATIC_CONSTEXPR unsigned fractional_width = ((fractional_w <= 18) ? fractional_w : 6u);

	// [time.hms.members]/2
	using precision = chrono::duration<
		typename CommonType::rep,
		hamon::ratio<1, static_cast<hamon::intmax_t>(pow10(fractional_width, 1))>>;

	HAMON_CXX11_CONSTEXPR
	hh_mm_ss() HAMON_NOEXCEPT
		: hh_mm_ss{ Duration::zero() }
	{}

	HAMON_CXX11_CONSTEXPR explicit
	hh_mm_ss(Duration d)
		// [time.hms.members]/3
		: is_neg(d < Duration::zero())
		, h(chrono::duration_cast<chrono::hours>(abs(d)))
		, m(chrono::duration_cast<chrono::minutes>(abs(d) - hours()))
		, s(chrono::duration_cast<chrono::seconds>(abs(d) - hours() - minutes()))
		, ss(chrono::duration_cast<precision>(abs(d) - hours() - minutes() - seconds()))
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	is_negative() const HAMON_NOEXCEPT
	{
		// [time.hms.members]/5
		return is_neg;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR chrono::hours
	hours() const HAMON_NOEXCEPT
	{
		// [time.hms.members]/6
		return h;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR chrono::minutes
	minutes() const HAMON_NOEXCEPT
	{
		// [time.hms.members]/7
		return m;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR chrono::seconds
	seconds() const HAMON_NOEXCEPT
	{
		// [time.hms.members]/8
		return s;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR precision
	subseconds() const HAMON_NOEXCEPT
	{
		// [time.hms.members]/9
		return ss;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR explicit
	operator precision() const HAMON_NOEXCEPT
	{
		// [time.hms.members]/11
		return to_duration();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR precision
	to_duration() const HAMON_NOEXCEPT
	{
		// [time.hms.members]/10
		return is_neg ?
			-(h + m + s + ss) :
			 (h + m + s + ss);
	}

private:
	bool            is_neg;
	chrono::hours   h;
	chrono::minutes m;
	chrono::seconds s;
	precision       ss;
};

// 30.9.3 Non-members[time.hms.nonmembers]

template <typename charT, typename traits, typename Duration>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, hh_mm_ss<Duration> const& hms);
#if 0	// TODO
{
	return os << format(os.getloc(), STATICALLY-WIDEN<charT>("{:L%T}"), hms);
}
#endif

}	// namespace chrono
}	// namespace hamon

#endif

#endif // HAMON_CHRONO_HH_MM_SS_HPP
