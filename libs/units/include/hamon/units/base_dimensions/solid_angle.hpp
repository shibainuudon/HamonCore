/**
 *	@file	solid_angle.hpp
 *
 *	@brief	solid_angle_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_SOLID_ANGLE_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_SOLID_ANGLE_HPP

#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>

namespace hamon
{

namespace units
{

struct solid_angle_dimension_tag;

/**
 *	@brief	立体角
 */
using solid_angle_dimension =
	derived_dimension<
		dimension_holder<solid_angle_dimension_tag>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_SOLID_ANGLE_HPP
