/**
 *	@file	information.hpp
 *
 *	@brief	information_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_INFORMATION_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_INFORMATION_HPP

#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>

namespace hamon
{

namespace units
{

struct information_dimension_tag;

/**
 *	@brief	情報量
 */
using information_dimension =
	derived_dimension<
		dimension_holder<information_dimension_tag>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_INFORMATION_HPP
