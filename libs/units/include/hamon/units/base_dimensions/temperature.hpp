/**
 *	@file	temperature.hpp
 *
 *	@brief	temperature_base_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_TEMPERATURE_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_TEMPERATURE_HPP

#include <hamon/units/detail/base_dimension_traits.hpp>
#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace units
{

struct temperature_base_dimension;

template <>
struct base_dimension_traits<temperature_base_dimension>
{
	HAMON_STATIC_CONSTEXPR int order = 5;
};

/**
 *	@brief	温度: Θ
 */
using temperature_dimension =
	derived_dimension<
		dimension_holder<temperature_base_dimension>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_TEMPERATURE_HPP
