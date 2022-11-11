/**
 *	@file	heat_capacity.hpp
 *
 *	@brief	heat_capacity の定義
 */

#ifndef HAMON_UNITS_HEAT_CAPACITY_HPP
#define HAMON_UNITS_HEAT_CAPACITY_HPP

#include <hamon/units/joule.hpp>
#include <hamon/units/kelvin.hpp>

namespace hamon
{

namespace units
{

// ジュール毎ケルビン(熱容量の単位)
template <typename T> using joule_per_kelvin  = decltype(joule<T>() / kelvin<T>());
template <typename T> using joules_per_kelvin = joule_per_kelvin<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_HEAT_CAPACITY_HPP
