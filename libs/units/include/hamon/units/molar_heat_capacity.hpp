/**
 *	@file	molar_heat_capacity.hpp
 *
 *	@brief	molar_heat_capacity の定義
 */

#ifndef HAMON_UNITS_MOLAR_HEAT_CAPACITY_HPP
#define HAMON_UNITS_MOLAR_HEAT_CAPACITY_HPP

#include <hamon/units/joule.hpp>
#include <hamon/units/kelvin.hpp>
#include <hamon/units/mole.hpp>

namespace hamon
{

namespace units
{

// ジュール毎モル毎ケルビン(モルエントロピー・モル熱容量の単位)
template <typename T> using joule_per_kelvin_mole  = decltype(joule<T>() / (kelvin<T>() * mole<T>()));
template <typename T> using joules_per_kelvin_mole = joule_per_kelvin_mole<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_MOLAR_HEAT_CAPACITY_HPP
