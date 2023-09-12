/**
 *	@file	quantity_divide_result.hpp
 *
 *	@brief	quantity_divide_result の定義
 */

#ifndef HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_DIVIDE_RESULT_HPP
#define HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_DIVIDE_RESULT_HPP

#include <hamon/units/quantity/quantity_fwd.hpp>
#include <hamon/units/detail/dimension_divide.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/ratio/ratio_divide.hpp>

namespace hamon
{

namespace units
{

namespace detail
{

template <typename Q1, typename Q2>
struct quantity_divide_result;

template <
	typename T1, typename D1, typename S1,
	typename T2, typename D2, typename S2>
struct quantity_divide_result<
	quantity<T1, D1, S1>,
	quantity<T2, D2, S2>>
{
	using type = quantity<
		hamon::common_type_t<T1, T2>,
		dimension_divide<D1, D2>,
		hamon::ratio_divide<S1, S2>
	>;
};

template <typename Q1, typename Q2>
using quantity_divide_result_t =
	typename quantity_divide_result<Q1, Q2>::type;

}	// namespace detail

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_DIVIDE_RESULT_HPP
