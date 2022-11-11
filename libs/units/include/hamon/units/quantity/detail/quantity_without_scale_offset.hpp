/**
 *	@file	quantity_without_scale_offset.hpp
 *
 *	@brief	quantity_without_scale_offset の定義
 */

#ifndef HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_WITHOUT_SCALE_OFFSET_HPP
#define HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_WITHOUT_SCALE_OFFSET_HPP

#include <hamon/units/quantity/quantity_fwd.hpp>

namespace hamon
{

namespace units
{

namespace detail
{

template <typename Q>
struct quantity_without_scale_offset;

template <typename Q>
using quantity_without_scale_offset_t =
	typename quantity_without_scale_offset<Q>::type;

template <typename T, typename D, typename S, typename O>
struct quantity_without_scale_offset<quantity<T, D, S, O>>
{
	using type = quantity<T, D>;
};

}	// namespace detail

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_WITHOUT_SCALE_OFFSET_HPP
