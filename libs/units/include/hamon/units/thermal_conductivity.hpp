/**
 *	@file	thermal_conductivity.hpp
 *
 *	@brief	thermal_conductivity の定義
 */

#ifndef HAMON_UNITS_THERMAL_CONDUCTIVITY_HPP
#define HAMON_UNITS_THERMAL_CONDUCTIVITY_HPP

#include <hamon/units/watt.hpp>
#include <hamon/units/metre.hpp>
#include <hamon/units/kelvin.hpp>

namespace hamon
{

namespace units
{

// ワット毎メートル毎ケルビン(熱伝導率の単位)
template <typename T> using watt_per_metre_kelvin  = decltype(watt<T>() / metre<T>() / kelvin<T>());
template <typename T> using watt_per_meter_kelvin  = watt_per_metre_kelvin<T>;
template <typename T> using watts_per_metre_kelvin = watt_per_metre_kelvin<T>;
template <typename T> using watts_per_meter_kelvin = watt_per_metre_kelvin<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_THERMAL_CONDUCTIVITY_HPP
