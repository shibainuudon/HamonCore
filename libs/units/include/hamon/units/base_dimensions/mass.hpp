/**
 *	@file	mass.hpp
 *
 *	@brief	mass_base_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_MASS_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_MASS_HPP

#include <hamon/units/detail/base_dimension_traits.hpp>
#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace units
{

struct mass_base_dimension;

template <>
struct base_dimension_traits<mass_base_dimension>
{
	HAMON_STATIC_CONSTEXPR int order = 2;
};

/**
 *	@brief	質量: M
 */
using mass_dimension =
	derived_dimension<
		dimension_holder<mass_base_dimension>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_MASS_HPP
