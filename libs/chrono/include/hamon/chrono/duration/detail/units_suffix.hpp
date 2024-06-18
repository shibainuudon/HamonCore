﻿/**
 *	@file	units_suffix.hpp
 *
 *	@brief	units-suffix の定義
 */

#ifndef HAMON_CHRONO_DURATION_DETAIL_UNITS_SUFFIX_HPP
#define HAMON_CHRONO_DURATION_DETAIL_UNITS_SUFFIX_HPP

#include <hamon/chrono/detail/statically_widen.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <sstream>	// basic_ostringstream
#include <ratio>

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
HAMON_UNITS_SUFFIX(std::atto,         "as");
HAMON_UNITS_SUFFIX(std::femto,        "fs");
HAMON_UNITS_SUFFIX(std::pico,         "ps");
HAMON_UNITS_SUFFIX(std::nano,         "ns");
HAMON_UNITS_SUFFIX(std::micro,        "us");
HAMON_UNITS_SUFFIX(std::milli,        "ms");
HAMON_UNITS_SUFFIX(std::centi,        "cs");
HAMON_UNITS_SUFFIX(std::deci,         "ds");
HAMON_UNITS_SUFFIX(std::ratio<1>,     "s");
HAMON_UNITS_SUFFIX(std::deca,         "das");
HAMON_UNITS_SUFFIX(std::hecto,        "hs");
HAMON_UNITS_SUFFIX(std::kilo,         "ks");
HAMON_UNITS_SUFFIX(std::mega,         "Ms");
HAMON_UNITS_SUFFIX(std::giga,         "Gs");
HAMON_UNITS_SUFFIX(std::tera,         "Ts");
HAMON_UNITS_SUFFIX(std::peta,         "Ps");
HAMON_UNITS_SUFFIX(std::exa,          "Es");
HAMON_UNITS_SUFFIX(std::ratio<60>,    "min");
HAMON_UNITS_SUFFIX(std::ratio<3600>,  "h");
HAMON_UNITS_SUFFIX(std::ratio<86400>, "d");

#undef HAMON_UNITS_SUFFIX

}	// namespace detail

}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DURATION_DETAIL_UNITS_SUFFIX_HPP
