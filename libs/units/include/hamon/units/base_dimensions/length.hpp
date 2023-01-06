/**
 *	@file	length.hpp
 *
 *	@brief	length_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_LENGTH_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_LENGTH_HPP

#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>

namespace hamon
{

namespace units
{

struct length_dimension_tag;

/**
 *	@brief	長さ: L
 */
using length_dimension =
	derived_dimension<
		dimension_holder<length_dimension_tag>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_LENGTH_HPP
