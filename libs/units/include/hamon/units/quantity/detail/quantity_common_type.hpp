/**
 *	@file	quantity_common_type.hpp
 *
 *	@brief	quantity_common_type の定義
 */

#ifndef HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_COMMON_TYPE_HPP
#define HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_COMMON_TYPE_HPP

#include <hamon/units/quantity/quantity_fwd.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/ratio/ratio_gcd.hpp>

namespace hamon
{

namespace units
{

namespace detail
{

template <typename Q1, typename Q2>
struct quantity_common_type;

template <
	typename T1, typename D, typename S1, typename O1,
	typename T2, typename S2, typename O2>
struct quantity_common_type<quantity<T1, D, S1, O1>, quantity<T2, D, S2, O2>>
{
	using type = quantity<
		hamon::common_type_t<T1, T2>,
		D,
		hamon::ratio_gcd<S1, S2>
	>;
};

template <typename Q1, typename Q2>
using quantity_common_type_t = typename quantity_common_type<Q1, Q2>::type;

}	// namespace detail

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_COMMON_TYPE_HPP
