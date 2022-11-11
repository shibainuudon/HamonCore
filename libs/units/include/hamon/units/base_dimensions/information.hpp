/**
 *	@file	information.hpp
 *
 *	@brief	information_base_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_INFORMATION_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_INFORMATION_HPP

#include <hamon/units/detail/base_dimension_traits.hpp>
#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace units
{

struct information_base_dimension;

template <>
struct base_dimension_traits<information_base_dimension>
{
	HAMON_STATIC_CONSTEXPR int order = 10;
};

/**
 *	@brief	情報量
 */
using information_dimension =
	derived_dimension<
		dimension_holder<information_base_dimension>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_INFORMATION_HPP
