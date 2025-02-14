/**
 *	@file	llrint.hpp
 *
 *	@brief	llrint 関数の定義
 */

#ifndef HAMON_CMATH_LLRINT_HPP
#define HAMON_CMATH_LLRINT_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR long long
llrint_unchecked(T x) HAMON_NOEXCEPT
{
	return std::llrint(x);
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR long long
llrint_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			0LL :
		hamon::isinf(x) ?
			hamon::signbit(x) ?
				hamon::numeric_limits<long long>::min() :
				hamon::numeric_limits<long long>::max() :
		llrint_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	現在の丸めモードで整数値に丸めた値を得る
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg を現在の丸めモードで整数値に丸めた値
 *
 *	arg が ±∞  の場合、argをそのまま返す。
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が NaN の場合、NaNを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR long long
llrint(FloatType arg) HAMON_NOEXCEPT
{
	return detail::llrint_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
llrint(IntegralType arg) HAMON_NOEXCEPT
->decltype(detail::llrint_impl(static_cast<double>(arg)))
{
	return detail::llrint_impl(static_cast<double>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long long
llrintf(float arg) HAMON_NOEXCEPT
{
	return detail::llrint_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long long
llrintl(long double arg) HAMON_NOEXCEPT
{
	return detail::llrint_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_LLRINT_HPP
