/**
 *	@file	units_suffix.hpp
 *
 *	@brief	units-suffix の定義
 */

#ifndef HAMON_CHRONO_DURATION_DETAIL_UNITS_SUFFIX_HPP
#define HAMON_CHRONO_DURATION_DETAIL_UNITS_SUFFIX_HPP

#include <hamon/chrono/detail/statically_widen.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/ratio.hpp>
#include <sstream>	// basic_ostringstream

namespace hamon {
namespace chrono {

namespace detail {

// 29.5.11 I/O[time.duration.io]

// units-suffix

template <hamon::intmax_t N, hamon::intmax_t D>
struct units_suffix_impl
{
	// [time.duration.io]/1.22
	template <typename CharT, typename Traits>
	static void invoke(std::basic_ostringstream<CharT, Traits>& s)
	{
		s << HAMON_STATICALLY_WIDEN(CharT, "[")
		  << N
		  << HAMON_STATICALLY_WIDEN(CharT, "/")
		  << D
		  << HAMON_STATICALLY_WIDEN(CharT, "]s");
	}
};

template <hamon::intmax_t N>
struct units_suffix_impl<N, 1>
{
	// [time.duration.io]/1.21
	template <typename CharT, typename Traits>
	static void invoke(std::basic_ostringstream<CharT, Traits>& s)
	{
		s << HAMON_STATICALLY_WIDEN(CharT, "[")
		  << N
		  << HAMON_STATICALLY_WIDEN(CharT, "]s");
	}
};

template <typename Period>
using units_suffix = units_suffix_impl<Period::num, Period::den>;

#define HAMON_UNITS_SUFFIX(PERIOD, S)                              \
template <>                                                        \
struct units_suffix_impl<PERIOD::num, PERIOD::den>                 \
{                                                                  \
	template <typename CharT, typename Traits>                     \
	static void invoke(std::basic_ostringstream<CharT, Traits>& s) \
	{                                                              \
		s << HAMON_STATICALLY_WIDEN(CharT, S);                     \
	}                                                              \
}

// [time.duration.io]/1.1-1.20
HAMON_UNITS_SUFFIX(hamon::atto,         "as");
HAMON_UNITS_SUFFIX(hamon::femto,        "fs");
HAMON_UNITS_SUFFIX(hamon::pico,         "ps");
HAMON_UNITS_SUFFIX(hamon::nano,         "ns");
HAMON_UNITS_SUFFIX(hamon::micro,        "us");
HAMON_UNITS_SUFFIX(hamon::milli,        "ms");
HAMON_UNITS_SUFFIX(hamon::centi,        "cs");
HAMON_UNITS_SUFFIX(hamon::deci,         "ds");
HAMON_UNITS_SUFFIX(hamon::ratio<1>,     "s");
HAMON_UNITS_SUFFIX(hamon::deca,         "das");
HAMON_UNITS_SUFFIX(hamon::hecto,        "hs");
HAMON_UNITS_SUFFIX(hamon::kilo,         "ks");
HAMON_UNITS_SUFFIX(hamon::mega,         "Ms");
HAMON_UNITS_SUFFIX(hamon::giga,         "Gs");
HAMON_UNITS_SUFFIX(hamon::tera,         "Ts");
HAMON_UNITS_SUFFIX(hamon::peta,         "Ps");
HAMON_UNITS_SUFFIX(hamon::exa,          "Es");
HAMON_UNITS_SUFFIX(hamon::ratio<60>,    "min");
HAMON_UNITS_SUFFIX(hamon::ratio<3600>,  "h");
HAMON_UNITS_SUFFIX(hamon::ratio<86400>, "d");

#undef HAMON_UNITS_SUFFIX

}	// namespace detail

}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DURATION_DETAIL_UNITS_SUFFIX_HPP
