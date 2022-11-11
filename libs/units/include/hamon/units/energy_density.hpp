/**
 *	@file	energy_density.hpp
 *
 *	@brief	energy_density の定義
 */

#ifndef HAMON_UNITS_ENERGY_DENSITY_HPP
#define HAMON_UNITS_ENERGY_DENSITY_HPP

#include <hamon/units/joule.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// ジュール毎立方メートル(エネルギー密度の単位)
template <typename T> using joule_per_cubic_metre  = decltype(joule<T>() / metre<T>() / metre<T>() / metre<T>());
template <typename T> using joules_per_cubic_metre = joule_per_cubic_metre<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_ENERGY_DENSITY_HPP
