/**
 *	@file	binary_prefix.hpp
 *
 *	@brief
 */

#ifndef HAMON_UNITS_DETAIL_BINARY_PREFIX_HPP
#define HAMON_UNITS_DETAIL_BINARY_PREFIX_HPP

#include <hamon/ratio/ratio.hpp>
#include <cstdint>	// INTMAX_MAX

namespace hamon
{

namespace units
{

/**
 *	@brief	2進接頭辞
 */
using kibi = hamon::ratio<(1LL << 10)>;
using mebi = hamon::ratio<(1LL << 20)>;
using gibi = hamon::ratio<(1LL << 30)>;
using tebi = hamon::ratio<(1LL << 40)>;
using pebi = hamon::ratio<(1LL << 50)>;
using exbi = hamon::ratio<(1LL << 60)>;
#if INTMAX_MAX / (1LL << 30) >= (1LL << 40)	// INTMAX_MAX >= (1LL << 70)
using zebi = hamon::ratio<(1LL << 70)>;
#define HAMON_UNITS_HAS_ZEBI
#endif
#if INTMAX_MAX / (1LL << 30) >= (1LL << 50)	// INTMAX_MAX >= (1LL << 80)
using yobi = hamon::ratio<(1LL << 80)>;
#define HAMON_UNITS_HAS_YOBI
#endif

}	// namespace units

}	// namespace hamon

#define HAMON_UNITS_BINARY_PREFIX_2(Name, Ratio) \
	template <typename T> using Ratio ## Name = decltype(Name<T>() * Ratio())

#if defined(HAMON_UNITS_HAS_ZEBI)
#define HAMON_UNITS_BINARY_PREFIX_ZEBI(Name)	HAMON_UNITS_BINARY_PREFIX_2(Name, zebi);
#else
#define HAMON_UNITS_BINARY_PREFIX_ZEBI(Name)
#endif

#if defined(HAMON_UNITS_HAS_YOBI)
#define HAMON_UNITS_BINARY_PREFIX_YOBI(Name)	HAMON_UNITS_BINARY_PREFIX_2(Name, yobi);
#else
#define HAMON_UNITS_BINARY_PREFIX_YOBI(Name)
#endif

#define HAMON_UNITS_BINARY_PREFIX(Name)      \
	HAMON_UNITS_BINARY_PREFIX_ZEBI(Name)	 \
	HAMON_UNITS_BINARY_PREFIX_YOBI(Name)     \
	HAMON_UNITS_BINARY_PREFIX_2(Name, kibi); \
	HAMON_UNITS_BINARY_PREFIX_2(Name, mebi); \
	HAMON_UNITS_BINARY_PREFIX_2(Name, gibi); \
	HAMON_UNITS_BINARY_PREFIX_2(Name, tebi); \
	HAMON_UNITS_BINARY_PREFIX_2(Name, pebi); \
	HAMON_UNITS_BINARY_PREFIX_2(Name, exbi)

#endif // HAMON_UNITS_DETAIL_BINARY_PREFIX_HPP
