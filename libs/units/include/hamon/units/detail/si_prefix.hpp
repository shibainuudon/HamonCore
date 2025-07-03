/**
 *	@file	si_prefix.hpp
 *
 *	@brief
 */

#ifndef HAMON_UNITS_DETAIL_SI_PREFIX_HPP
#define HAMON_UNITS_DETAIL_SI_PREFIX_HPP

#include <hamon/ratio.hpp>
#include <cstdint>	// INTMAX_MAX

#define HAMON_UNITS_SI_PREFIX_2(Name, Ratio) \
	template <typename T> using Ratio ## Name = decltype(Name<T>() * hamon::Ratio())

#if (INTMAX_MAX / 1000000000) >= 1000000000000		// INTMAX_MAX >= (1000000000000000000000)
#define HAMON_UNITS_SI_PREFIX_ZEPTO(Name)	HAMON_UNITS_SI_PREFIX_2(Name, zepto);
#define HAMON_UNITS_SI_PREFIX_ZETTA(Name)	HAMON_UNITS_SI_PREFIX_2(Name, zetta);
#else
#define HAMON_UNITS_SI_PREFIX_ZEPTO(Name)
#define HAMON_UNITS_SI_PREFIX_ZETTA(Name)
#endif

#if (INTMAX_MAX / 1000000000) >= 1000000000000000	// INTMAX_MAX >= (1000000000000000000000000)
#define HAMON_UNITS_SI_PREFIX_YOCTO(Name)	HAMON_UNITS_SI_PREFIX_2(Name, yocto);
#define HAMON_UNITS_SI_PREFIX_YOTTA(Name)	HAMON_UNITS_SI_PREFIX_2(Name, yotta);
#else
#define HAMON_UNITS_SI_PREFIX_YOCTO(Name)
#define HAMON_UNITS_SI_PREFIX_YOTTA(Name)
#endif

/**
 *	@brief	SI接頭辞
 */
#define HAMON_UNITS_SI_PREFIX(Name)       \
	HAMON_UNITS_SI_PREFIX_YOCTO(Name)     \
	HAMON_UNITS_SI_PREFIX_ZEPTO(Name)     \
	HAMON_UNITS_SI_PREFIX_ZETTA(Name)     \
	HAMON_UNITS_SI_PREFIX_YOTTA(Name)     \
	HAMON_UNITS_SI_PREFIX_2(Name, atto);  \
	HAMON_UNITS_SI_PREFIX_2(Name, femto); \
	HAMON_UNITS_SI_PREFIX_2(Name, pico);  \
	HAMON_UNITS_SI_PREFIX_2(Name, nano);  \
	HAMON_UNITS_SI_PREFIX_2(Name, micro); \
	HAMON_UNITS_SI_PREFIX_2(Name, milli); \
	HAMON_UNITS_SI_PREFIX_2(Name, centi); \
	HAMON_UNITS_SI_PREFIX_2(Name, deci);  \
	HAMON_UNITS_SI_PREFIX_2(Name, deca);  \
	HAMON_UNITS_SI_PREFIX_2(Name, hecto); \
	HAMON_UNITS_SI_PREFIX_2(Name, kilo);  \
	HAMON_UNITS_SI_PREFIX_2(Name, mega);  \
	HAMON_UNITS_SI_PREFIX_2(Name, giga);  \
	HAMON_UNITS_SI_PREFIX_2(Name, tera);  \
	HAMON_UNITS_SI_PREFIX_2(Name, peta);  \
	HAMON_UNITS_SI_PREFIX_2(Name, exa)

#endif // HAMON_UNITS_DETAIL_SI_PREFIX_HPP
