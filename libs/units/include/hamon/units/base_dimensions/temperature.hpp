/**
 *	@file	temperature.hpp
 *
 *	@brief	temperature_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_TEMPERATURE_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_TEMPERATURE_HPP

#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>

namespace hamon
{

namespace units
{

struct temperature_dimension_tag;

/**
 *	@brief	温度: Θ
 */
using temperature_dimension =
	derived_dimension<
		dimension_holder<temperature_dimension_tag>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_TEMPERATURE_HPP
