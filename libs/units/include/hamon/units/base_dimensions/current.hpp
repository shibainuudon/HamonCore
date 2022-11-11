/**
 *	@file	current.hpp
 *
 *	@brief	current_base_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_CURRENT_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_CURRENT_HPP

#include <hamon/units/detail/base_dimension_traits.hpp>
#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace units
{

struct current_base_dimension;

template <>
struct base_dimension_traits<current_base_dimension>
{
	HAMON_STATIC_CONSTEXPR int order = 4;
};

/**
 *	@brief	電流: I
 */
using current_dimension =
	derived_dimension<
		dimension_holder<current_base_dimension>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_CURRENT_HPP
