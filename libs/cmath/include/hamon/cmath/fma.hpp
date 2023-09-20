/**
 *	@file	fma.hpp
 *
 *	@brief	fma 関数の定義
 */

#ifndef HAMON_CMATH_FMA_HPP
#define HAMON_CMATH_FMA_HPP

#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
fma_unchecked(float x, float y, float z) HAMON_NOEXCEPT
{
	return __builtin_fmaf(x, y, z);
}

inline HAMON_CXX11_CONSTEXPR double
fma_unchecked(double x, double y, double z) HAMON_NOEXCEPT
{
	return __builtin_fma(x, y, z);
}

inline HAMON_CXX11_CONSTEXPR long double
fma_unchecked(long double x, long double y, long double z) HAMON_NOEXCEPT
{
	return __builtin_fmal(x, y, z);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
fma_unchecked(T x, T y, T z) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::fma(x, y, z);
	}
#endif
	return x * y + z;
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
fma_impl(FloatType x, FloatType y, FloatType z) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ||
		hamon::isnan(y) ||
		hamon::isnan(z) ||
		(hamon::isinf(x) && hamon::iszero(y)) ||
		(hamon::iszero(x) && hamon::isinf(y)) ||
		((hamon::isinf(x) || hamon::isinf(y)) && hamon::isinf(z) && (hamon::signbit(x) ^ hamon::signbit(y) ^ hamon::signbit(z))) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		fma_unchecked(x, y, z);
}

}	// namespace detail

/**
 *	@brief	和積演算(FMA; fused multiply-add)
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *	@tparam	ArithmeticType3	算術型
 *
 *	@param	x	算術型の値
 *	@param	y	算術型の値
 *	@param	z	算術型の値
 *
 *	@return	関数に成功すると、(x * y) + z を返す。
 *			丸めは乗算と加算の後に1回だけ行われる。
 *
 *	xが±0でyが±∞の場合、NaNを返す。
 *	xが±∞でyが±0の場合、NaNを返す。
 *	x*y の結果が±∞になり、zがそれとは逆の符号の∞の場合、NaNを返す。
 *	xかyがNaNの場合、NaNを返す。
 *	zがNaNで、x*y が 0*inf または inf*0 でない場合、NaNを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
fma(FloatType x, FloatType y, FloatType z) HAMON_NOEXCEPT
{
	return detail::fma_impl(x, y, z);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
fmaf(float x, float y, float z) HAMON_NOEXCEPT
{
	return detail::fma_impl(x, y, z);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
fmal(long double x, long double y, long double z) HAMON_NOEXCEPT
{
	return detail::fma_impl(x, y, z);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic3)
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>
fma(Arithmetic1 x, Arithmetic2 y, Arithmetic3 z) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>;
	return detail::fma_impl(static_cast<type>(x), static_cast<type>(y), static_cast<type>(z));
}

}	// namespace hamon

#endif // HAMON_CMATH_FMA_HPP
