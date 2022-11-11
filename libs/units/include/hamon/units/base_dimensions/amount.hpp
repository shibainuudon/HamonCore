/**
 *	@file	amount.hpp
 *
 *	@brief	amount_base_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_AMOUNT_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_AMOUNT_HPP

#include <hamon/units/detail/base_dimension_traits.hpp>
#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace units
{

struct amount_base_dimension;

template <>
struct base_dimension_traits<amount_base_dimension>
{
	HAMON_STATIC_CONSTEXPR int order = 6;
};

/**
 *	@brief	物質量: N
 */
using amount_dimension =
	derived_dimension<
		dimension_holder<amount_base_dimension>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_AMOUNT_HPP
