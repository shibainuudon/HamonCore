/**
 *	@file	ilogb.hpp
 *
 *	@brief	ilogb 関数の定義
 */

#ifndef HAMON_CMATH_ILOGB_HPP
#define HAMON_CMATH_ILOGB_HPP

#include <hamon/cmath/logb.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>	// FP_ILOGB0, FP_ILOGBNAN
#include <climits>	// INT_MAX

namespace hamon
{

#if !defined(FP_ILOGB0)
#	define FP_ILOGB0	INT_MIN
#endif

#if !defined(FP_ILOGBNAN)
#	define FP_ILOGBNAN	INT_MAX
#endif

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR int
ilogb_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return static_cast<int>(hamon::detail::logb_unchecked(x));
}

template <typename T>
HAMON_CXX11_CONSTEXPR int
ilogb_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::ilogb(x);
}

inline HAMON_CXX11_CONSTEXPR int
ilogb_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_ilogbf(x);
#elif HAMON_HAS_BUILTIN(__builtin_ilogbf)
	return hamon::is_constant_evaluated() ? ilogb_unchecked_ct(x) : __builtin_ilogbf(x);
#else
	return hamon::is_constant_evaluated() ? ilogb_unchecked_ct(x) : ilogb_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR int
ilogb_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_ilogb(x);
#elif HAMON_HAS_BUILTIN(__builtin_ilogb)
	return hamon::is_constant_evaluated() ? ilogb_unchecked_ct(x) : __builtin_ilogb(x);
#else
	return hamon::is_constant_evaluated() ? ilogb_unchecked_ct(x) : ilogb_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR int
ilogb_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_ilogbl(x);
#elif HAMON_HAS_BUILTIN(__builtin_ilogbl)
	return hamon::is_constant_evaluated() ? ilogb_unchecked_ct(x) : __builtin_ilogbl(x);
#else
	return hamon::is_constant_evaluated() ? ilogb_unchecked_ct(x) : ilogb_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR int
ilogb_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			FP_ILOGB0 :
		hamon::isinf(x) ?
			INT_MAX :
		hamon::isnan(x) ?
			FP_ILOGBNAN :
		ilogb_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	浮動小数点数の指数部をintとして返す
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg の 指数部
 *
 *	arg が ±0  だった場合、FP_ILOGB0   を返す。
 *	arg が ±∞  だった場合、INT_MAX     を返す。
 *	arg が NaN だった場合、FP_ILOGBNAN を返す。
 */
template <HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR int
ilogb(Arithmetic arg) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::ilogb_impl(static_cast<type>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR int
ilogbf(float arg) HAMON_NOEXCEPT
{
	return detail::ilogb_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR int
ilogbl(long double arg) HAMON_NOEXCEPT
{
	return detail::ilogb_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_ILOGB_HPP
