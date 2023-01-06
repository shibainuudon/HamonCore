/**
 *	@file	dimension_multiply.hpp
 *
 *	@brief	dimension_multiply の定義
 */

#ifndef HAMON_UNITS_DETAIL_DIMENSION_MULTIPLY_HPP
#define HAMON_UNITS_DETAIL_DIMENSION_MULTIPLY_HPP

#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/make_derived_dimension.hpp>

namespace hamon
{

namespace units
{

namespace detail
{

template <typename D1, typename D2>
struct dimension_multiply_impl;

template <typename... D1, typename... D2>
struct dimension_multiply_impl<derived_dimension<D1...>, derived_dimension<D2...>>
	: public make_derived_dimension<D1..., D2...>
{};

}	// namespace detail

/**
 *	@brief	derived_dimension同士を乗算して新しいderived_dimensionを得る
 */
template <typename D1, typename D2>
using dimension_multiply = typename detail::dimension_multiply_impl<D1, D2>::type;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_DETAIL_DIMENSION_MULTIPLY_HPP
