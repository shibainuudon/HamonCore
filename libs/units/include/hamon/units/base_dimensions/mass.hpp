/**
 *	@file	mass.hpp
 *
 *	@brief	mass_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_MASS_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_MASS_HPP

#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>

namespace hamon
{

namespace units
{

struct mass_dimension_tag;

/**
 *	@brief	質量: M
 */
using mass_dimension =
	derived_dimension<
		dimension_holder<mass_dimension_tag>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_MASS_HPP
