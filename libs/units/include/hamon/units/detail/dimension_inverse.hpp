/**
 *	@file	dimension_inverse.hpp
 *
 *	@brief	dimension_inverse の定義
 */

#ifndef HAMON_UNITS_DETAIL_DIMENSION_INVERSE_HPP
#define HAMON_UNITS_DETAIL_DIMENSION_INVERSE_HPP

#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>
#include <hamon/units/detail/make_derived_dimension.hpp>

namespace hamon
{

namespace units
{

namespace detail
{

template <typename D>
struct dimension_inverse_impl;

template <typename... D>
struct dimension_inverse_impl<derived_dimension<D...>>
	: public make_derived_dimension<
		dimension_holder<typename D::type, -D::power>...
	>
{};

}	// namespace detail

/**
 *	@brief	derived_dimensionの逆数を得る
 */
template <typename D>
using dimension_inverse = typename detail::dimension_inverse_impl<D>::type;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_DETAIL_DIMENSION_INVERSE_HPP
