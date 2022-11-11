/**
 *	@file	quantity_cast.hpp
 *
 *	@brief	quantity_cast の定義
 */

#ifndef HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_CAST_HPP
#define HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_CAST_HPP

#include <hamon/units/quantity/quantity_fwd.hpp>
#include <hamon/config.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

namespace detail
{

template <typename R>
inline HAMON_CONSTEXPR long double
ratio_to_float()
{
	return static_cast<long double>(R::num) / R::den;
}

HAMON_WARNING_PUSH();
#if defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION >= 100000)
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-float-conversion");
#endif

template <typename ToQuantity, typename T, typename D, typename S, typename O>
inline HAMON_CONSTEXPR ToQuantity
quantity_cast(quantity<T, D, S, O> const& q) HAMON_NOEXCEPT
{
	using T1 = typename ToQuantity::value_type;
	using S1 = typename ToQuantity::scale_type;
	using O1 = typename ToQuantity::offset_type;
	using S2 = std::ratio_divide<S, S1>;
	return ToQuantity(static_cast<T1>(
		(q.value() + ratio_to_float<O>()) * S2::num / S2::den - ratio_to_float<O1>()));
}

HAMON_WARNING_POP();

}	// namespace detail

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_QUANTITY_DETAIL_QUANTITY_CAST_HPP
