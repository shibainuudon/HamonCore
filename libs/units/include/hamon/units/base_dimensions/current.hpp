/**
 *	@file	current.hpp
 *
 *	@brief	current_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_CURRENT_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_CURRENT_HPP

#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>

namespace hamon
{

namespace units
{

struct current_dimension_tag;

/**
 *	@brief	電流: I
 */
using current_dimension =
	derived_dimension<
		dimension_holder<current_dimension_tag>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_CURRENT_HPP
