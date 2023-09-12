/**
 *	@file	calorie.hpp
 *
 *	@brief	calorie の定義
 */

#ifndef HAMON_UNITS_CALORIE_HPP
#define HAMON_UNITS_CALORIE_HPP

#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/joule.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// カロリー(正確に4.184ジュール)
template <typename T> using calorie  = decltype(joule<T>() * hamon::ratio<4184, 1000>());
template <typename T> using calories = calorie<T>;
HAMON_UNITS_SI_PREFIX(calorie);
HAMON_UNITS_SI_PREFIX(calories);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_CALORIE_HPP
