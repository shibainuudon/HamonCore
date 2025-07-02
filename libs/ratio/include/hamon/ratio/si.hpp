/**
 *	@file	si.hpp
 *
 *	@brief	SI typedefs の定義
 */

#ifndef HAMON_RATIO_SI_HPP
#define HAMON_RATIO_SI_HPP

#include <hamon/ratio/ratio.hpp>
#include <cstdint>	// INTMAX_MAX

namespace hamon
{

// [ratio.si], convenience SI typedefs

#if (INTMAX_MAX / 1000000000000) >= 1000000000000000000	// INTMAX_MAX >= (1'000'000'000'000'000'000'000'000'000'000)
#define HAMON_HAS_RATIO_QUECTO
using quecto = hamon::ratio<1, 1000000000000000000000000000000>;
#endif
#if (INTMAX_MAX / 1000000000) >= 1000000000000000000	// INTMAX_MAX >= (1'000'000'000'000'000'000'000'000'000)
#define HAMON_HAS_RATIO_RONTO
using ronto  = hamon::ratio<1,    1000000000000000000000000000>;
#endif
#if (INTMAX_MAX / 1000000) >= 1000000000000000000		// INTMAX_MAX >= (1'000'000'000'000'000'000'000'000)
#define HAMON_HAS_RATIO_YOCTO
using yocto  = hamon::ratio<1,       1000000000000000000000000>;
#endif
#if (INTMAX_MAX / 1000) >= 1000000000000000000			// INTMAX_MAX >= (1'000'000'000'000'000'000'000)
#define HAMON_HAS_RATIO_ZEPTO
using zepto  = hamon::ratio<1,          1000000000000000000000>;
#endif
using atto   = hamon::ratio<1,             1000000000000000000>;
using femto  = hamon::ratio<1,                1000000000000000>;
using pico   = hamon::ratio<1,                   1000000000000>;
using nano   = hamon::ratio<1,                      1000000000>;
using micro  = hamon::ratio<1,                         1000000>;
using milli  = hamon::ratio<1,                            1000>;
using centi  = hamon::ratio<1,                             100>;
using deci   = hamon::ratio<1,                              10>;
using deca   = hamon::ratio<                             10, 1>;
using hecto  = hamon::ratio<                            100, 1>;
using kilo   = hamon::ratio<                           1000, 1>;
using mega   = hamon::ratio<                        1000000, 1>;
using giga   = hamon::ratio<                     1000000000, 1>;
using tera   = hamon::ratio<                  1000000000000, 1>;
using peta   = hamon::ratio<               1000000000000000, 1>;
using exa    = hamon::ratio<            1000000000000000000, 1>;
#if (INTMAX_MAX / 1000) >= 1000000000000000000			// INTMAX_MAX >= (1'000'000'000'000'000'000'000)
#define HAMON_HAS_RATIO_ZETTA
using zetta  = hamon::ratio<         1000000000000000000000, 1>;
#endif
#if (INTMAX_MAX / 1000000) >= 1000000000000000000		// INTMAX_MAX >= (1'000'000'000'000'000'000'000'000)
#define HAMON_HAS_RATIO_YOTTA
using yotta  = hamon::ratio<      1000000000000000000000000, 1>;
#endif
#if (INTMAX_MAX / 1000000000) >= 1000000000000000000	// INTMAX_MAX >= (1'000'000'000'000'000'000'000'000'000)
#define HAMON_HAS_RATIO_RONNA
using ronna  = hamon::ratio<   1000000000000000000000000000, 1>;
#endif
#if (INTMAX_MAX / 1000000000000) >= 1000000000000000000	// INTMAX_MAX >= (1'000'000'000'000'000'000'000'000'000'000)
#define HAMON_HAS_RATIO_QUETTA
using quetta = hamon::ratio<1000000000000000000000000000000, 1>;
#endif

}	// namespace hamon

#endif // HAMON_RATIO_SI_HPP
