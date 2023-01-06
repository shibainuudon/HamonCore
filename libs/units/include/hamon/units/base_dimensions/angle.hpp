/**
 *	@file	angle.hpp
 *
 *	@brief	angle_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_ANGLE_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_ANGLE_HPP

#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>

namespace hamon
{

namespace units
{

struct angle_dimension_tag;

/**
 *	@brief	平面角
 */
using angle_dimension =
	derived_dimension<
		dimension_holder<angle_dimension_tag>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_ANGLE_HPP
