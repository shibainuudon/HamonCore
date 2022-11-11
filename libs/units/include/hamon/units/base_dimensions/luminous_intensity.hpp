/**
 *	@file	luminous_intensity.hpp
 *
 *	@brief	luminous_intensity_base_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_LUMINOUS_INTENSITY_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_LUMINOUS_INTENSITY_HPP

#include <hamon/units/detail/base_dimension_traits.hpp>
#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace units
{

struct luminous_intensity_base_dimension;

template <>
struct base_dimension_traits<luminous_intensity_base_dimension>
{
	HAMON_STATIC_CONSTEXPR int order = 7;
};

/**
 *	@brief	光度: J
 */
using luminous_intensity_dimension =
	derived_dimension<
		dimension_holder<luminous_intensity_base_dimension>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_LUMINOUS_INTENSITY_HPP
