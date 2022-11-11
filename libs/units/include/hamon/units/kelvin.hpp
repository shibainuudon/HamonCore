/**
 *	@file	kelvin.hpp
 *
 *	@brief	kelvin の定義
 */

#ifndef HAMON_UNITS_KELVIN_HPP
#define HAMON_UNITS_KELVIN_HPP

#include <hamon/units/base_dimensions/temperature.hpp>
#include <hamon/units/quantity.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// ケルビン
template <typename T> using kelvin  = quantity<T, temperature_dimension>;
template <typename T> using kelvins = kelvin<T>;
HAMON_UNITS_SI_PREFIX(kelvin);
HAMON_UNITS_SI_PREFIX(kelvins);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_KELVIN_HPP
