/**
 *	@file	amount.hpp
 *
 *	@brief	amount_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_AMOUNT_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_AMOUNT_HPP

#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>

namespace hamon
{

namespace units
{

struct amount_dimension_tag;

/**
 *	@brief	物質量: N
 */
using amount_dimension =
	derived_dimension<
		dimension_holder<amount_dimension_tag>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_AMOUNT_HPP
