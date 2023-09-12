/**
 *	@file	bar.hpp
 *
 *	@brief	bar の定義
 */

#ifndef HAMON_UNITS_BAR_HPP
#define HAMON_UNITS_BAR_HPP

#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/pascal.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// バール = 100000 パスカル
template <typename T> using bar  = decltype(pascals<T>() * hamon::ratio<100000>());
template <typename T> using bars = bar<T>;
HAMON_UNITS_SI_PREFIX(bar);
HAMON_UNITS_SI_PREFIX(bars);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BAR_HPP
