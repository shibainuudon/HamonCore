/**
 *	@file	fmaximum_num.hpp
 *
 *	@brief	fmaximum_num 関数の定義
 */

#ifndef HAMON_CMATH_FMAXIMUM_NUM_HPP
#define HAMON_CMATH_FMAXIMUM_NUM_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
fmaximum_num_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ? y :
		hamon::isnan(y) ? x :
		hamon::iszero(x) && hamon::iszero(y) ?
			hamon::signbit(x) ? y : x :
		x < y ? y : x;
}

}	// namespace detail

template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
FloatType fmaximum_num(FloatType x, FloatType y) HAMON_NOEXCEPT	// noexcept as an extension
{
	return detail::fmaximum_num_impl(x, y);
}

template <
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::float_promote_t<Arithmetic1, Arithmetic2>
fmaximum_num(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT	// noexcept as an extension
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::fmaximum_num_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace hamon

#endif // HAMON_CMATH_FMAXIMUM_NUM_HPP
