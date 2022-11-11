/**
 *	@file	specific_heat_capacity.hpp
 *
 *	@brief	specific_heat_capacity の定義
 */

#ifndef HAMON_UNITS_SPECIFIC_HEAT_CAPACITY_HPP
#define HAMON_UNITS_SPECIFIC_HEAT_CAPACITY_HPP

#include <hamon/units/joule.hpp>
#include <hamon/units/gram.hpp>
#include <hamon/units/kelvin.hpp>

namespace hamon
{

namespace units
{

// ジュール毎キログラム毎ケルビン(比熱容量の単位)
template <typename T> using joule_per_kilogram_kelvin  = decltype(joule<T>() / kilogram<T>() / kelvin<T>());
template <typename T> using joules_per_kilogram_kelvin = joule_per_kilogram_kelvin<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_SPECIFIC_HEAT_CAPACITY_HPP
