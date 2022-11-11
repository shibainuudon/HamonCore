/**
 *	@file	degree_celsius.hpp
 *
 *	@brief	degree_celsius の定義
 */

#ifndef HAMON_UNITS_DEGREE_CELSIUS_HPP
#define HAMON_UNITS_DEGREE_CELSIUS_HPP

#include <hamon/units/base_dimensions/temperature.hpp>
#include <hamon/units/quantity.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

// セルシウス度
template <typename T> using degree_celsius  = quantity<T, temperature_dimension, std::ratio<1>, std::ratio<27315, 100>>;
template <typename T> using degrees_celsius = degree_celsius<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_DEGREE_CELSIUS_HPP
