/**
 *	@file	angle.hpp
 *
 *	@brief	angle_base_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_ANGLE_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_ANGLE_HPP

#include <hamon/units/detail/base_dimension_traits.hpp>
#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace units
{

struct angle_base_dimension;

template <>
struct base_dimension_traits<angle_base_dimension>
{
	HAMON_STATIC_CONSTEXPR int order = 8;
};

/**
 *	@brief	平面角
 */
using angle_dimension =
	derived_dimension<
		dimension_holder<angle_base_dimension>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_ANGLE_HPP
