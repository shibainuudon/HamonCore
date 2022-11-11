/**
 *	@file	steradian.hpp
 *
 *	@brief	steradian の定義
 */

#ifndef HAMON_UNITS_STERADIAN_HPP
#define HAMON_UNITS_STERADIAN_HPP

#include <hamon/units/base_dimensions/solid_angle.hpp>
#include <hamon/units/quantity.hpp>

namespace hamon
{

namespace units
{

// ステラジアン
template <typename T> using steradian  = quantity<T, solid_angle_dimension>;
template <typename T> using steradians = steradian<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_STERADIAN_HPP
