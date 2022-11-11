/**
 *	@file	length.hpp
 *
 *	@brief	length_base_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_LENGTH_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_LENGTH_HPP

#include <hamon/units/detail/base_dimension_traits.hpp>
#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace units
{

struct length_base_dimension;

template <>
struct base_dimension_traits<length_base_dimension>
{
	HAMON_STATIC_CONSTEXPR int order = 1;
};

/**
 *	@brief	長さ: L
 */
using length_dimension =
	derived_dimension<
		dimension_holder<length_base_dimension>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_LENGTH_HPP
