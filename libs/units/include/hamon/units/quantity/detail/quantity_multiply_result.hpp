/**
 *	@file	quantity_multiply_result.hpp
 *
 *	@brief	quantity_multiply_result の定義
 */

#ifndef HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_MULTIPLY_RESULT_HPP
#define HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_MULTIPLY_RESULT_HPP

#include <hamon/units/quantity/quantity_fwd.hpp>
#include <hamon/units/detail/dimension_multiply.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

namespace detail
{

template <typename Q1, typename Q2>
struct quantity_multiply_result;

template <
	typename T1, typename D1, typename S1,
	typename T2, typename D2, typename S2>
struct quantity_multiply_result<
	quantity<T1, D1, S1>,
	quantity<T2, D2, S2>>
{
	using type = quantity<
		hamon::common_type_t<T1, T2>,
		dimension_multiply<D1, D2>,
		std::ratio_multiply<S1, S2>
	>;
};

template <typename Q1, typename Q2>
using quantity_multiply_result_t =
	typename quantity_multiply_result<Q1, Q2>::type;

}	// namespace detail

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_MULTIPLY_RESULT_HPP
