/**
 *	@file	log2.hpp
 *
 *	@brief	log2 関数の定義
 */

#ifndef HAMON_CMATH_LOG2_HPP
#define HAMON_CMATH_LOG2_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/bit/has_single_bit.hpp>
#include <hamon/bit/countr_zero.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/numbers/ln2.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
log2_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return hamon::log(x) / hamon::numbers::ln2_v<T>;
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
log2_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::log2(x);
}

inline HAMON_CXX11_CONSTEXPR float
log2_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_log2f(x);
#elif HAMON_HAS_BUILTIN(__builtin_log2f)
	return hamon::is_constant_evaluated() ? log2_unchecked_ct(x) : __builtin_log2f(x);
#else
	return hamon::is_constant_evaluated() ? log2_unchecked_ct(x) : log2_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
log2_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_log2(x);
#elif HAMON_HAS_BUILTIN(__builtin_log2)
	return hamon::is_constant_evaluated() ? log2_unchecked_ct(x) : __builtin_log2(x);
#else
	return hamon::is_constant_evaluated() ? log2_unchecked_ct(x) : log2_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
log2_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_log2l(x);
#elif HAMON_HAS_BUILTIN(__builtin_log2l)
	return hamon::is_constant_evaluated() ? log2_unchecked_ct(x) : __builtin_log2l(x);
#else
	return hamon::is_constant_evaluated() ? log2_unchecked_ct(x) : log2_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
log2_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::iszero(x) ?
			-hamon::numeric_limits<FloatType>::infinity() :
		x == FloatType(1) ?
			FloatType(0) :
		x < FloatType(0) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::isinf(x) ?
			hamon::numeric_limits<FloatType>::infinity() :
		log2_unchecked(x);
}

template <typename IntegralType>
HAMON_CXX11_CONSTEXPR double
log2_integral(IntegralType x) HAMON_NOEXCEPT
{
	using UT = hamon::make_unsigned_t<IntegralType>;
	return
		x == 0 ?
			-hamon::numeric_limits<double>::infinity() :
		x == 1 ?
			0.0 :
		x < 0 ?
			hamon::numeric_limits<double>::quiet_NaN() :
		hamon::has_single_bit(static_cast<UT>(x)) ?	// ２のべき乗のときは、正確に計算できる
			static_cast<double>(hamon::countr_zero(static_cast<UT>(x))) :
		log2_unchecked(static_cast<double>(x));
}

}	// namespace detail

/**
 *	@brief	2 を底とする二進対数を求める
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x の 2 を底とする二進対数
 *
 *	x が ±0  だった場合、-∞ を返す。
 *	x が 1   だった場合、+0  を返す。
 *	x < 0    だった場合、NaN を返す。
 *	x が +∞  だった場合、+∞ を返す。
 *	x が NaN だった場合、NaN を返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
log2(FloatType arg) HAMON_NOEXCEPT
{
	return detail::log2_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
log2f(float arg) HAMON_NOEXCEPT
{
	return detail::log2_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
log2l(long double arg) HAMON_NOEXCEPT
{
	return detail::log2_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
log2(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::log2_integral(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_LOG2_HPP
