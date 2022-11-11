/**
 *	@file	time.hpp
 *
 *	@brief	time_base_dimension の定義
 */

#ifndef HAMON_UNITS_BASE_DIMENSIONS_TIME_HPP
#define HAMON_UNITS_BASE_DIMENSIONS_TIME_HPP

#include <hamon/units/detail/base_dimension_traits.hpp>
#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace units
{

struct time_base_dimension;

template <>
struct base_dimension_traits<time_base_dimension>
{
	HAMON_STATIC_CONSTEXPR int order = 3;
};

/**
 *	@brief	時間: T
 */
using time_dimension =
	derived_dimension<
		dimension_holder<time_base_dimension>
	>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BASE_DIMENSIONS_TIME_HPP
