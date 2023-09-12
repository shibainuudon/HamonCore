/**
 *	@file	degree_fahrenheit.hpp
 *
 *	@brief	degree_fahrenheit の定義
 */

#ifndef HAMON_UNITS_DEGREE_FAHRENHEIT_HPP
#define HAMON_UNITS_DEGREE_FAHRENHEIT_HPP

#include <hamon/units/base_dimensions/temperature.hpp>
#include <hamon/units/quantity.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// ファーレンハイト度
template <typename T> using degree_fahrenheit  = quantity<T, temperature_dimension, hamon::ratio<5, 9>, hamon::ratio<45967, 100>>;
template <typename T> using degrees_fahrenheit = degree_fahrenheit<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_DEGREE_FAHRENHEIT_HPP
