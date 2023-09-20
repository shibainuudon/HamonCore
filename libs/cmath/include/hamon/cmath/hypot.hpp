/**
 *	@file	hypot.hpp
 *
 *	@brief	hypot 関数の定義
 */

#ifndef HAMON_CMATH_HYPOT_HPP
#define HAMON_CMATH_HYPOT_HPP

#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/fmax.hpp>
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
hypot_unchecked(float x, float y) HAMON_NOEXCEPT
{
	return __builtin_hypotf(x, y);
}

inline HAMON_CXX11_CONSTEXPR double
hypot_unchecked(double x, double y) HAMON_NOEXCEPT
{
	return __builtin_hypot(x, y);
}

inline HAMON_CXX11_CONSTEXPR long double
hypot_unchecked(long double x, long double y) HAMON_NOEXCEPT
{
	return __builtin_hypotl(x, y);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
hypot_unchecked_ct_2(T x, T y, T a) HAMON_NOEXCEPT
{
	return a * hamon::sqrt(x * x + y * y);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
hypot_unchecked_ct_2(T x, T y, T z, T a) HAMON_NOEXCEPT
{
	return a * hamon::sqrt(x * x + y * y + z * z);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
hypot_unchecked_ct_1(T x, T y, T a) HAMON_NOEXCEPT
{
	return hypot_unchecked_ct_2(x / a, y / a, a);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
hypot_unchecked_ct_1(T x, T y, T z, T a) HAMON_NOEXCEPT
{
	return hypot_unchecked_ct_2(x / a, y / a, z / a, a);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
hypot_unchecked_ct(T x, T y) HAMON_NOEXCEPT
{
	return hypot_unchecked_ct_1(x, y, hamon::fmax(hamon::fabs(x), hamon::fabs(y)));
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
hypot_unchecked_ct(T x, T y, T z) HAMON_NOEXCEPT
{
	return hypot_unchecked_ct_1(x, y, z, hamon::fmax(hamon::fabs(x), hamon::fmax(hamon::fabs(y), hamon::fabs(z))));
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
hypot_unchecked(T x, T y) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::hypot(x, y);
	}
#endif
	return hypot_unchecked_ct(x, y);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
hypot_unchecked(T x, T y, T z) HAMON_NOEXCEPT
{
// Apple Clang の std::hypot はオーバーフローを避けるように実装されていないので使わない
#if !defined(HAMON_APPLE_CLANG)
#if defined(__cpp_lib_hypot) && (__cpp_lib_hypot >= 201603)
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::hypot(x, y, z);
	}
#endif
#endif
#endif
	return hypot_unchecked_ct(x, y, z);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
hypot_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			hamon::fabs(y) :
		hamon::iszero(y) ?
			hamon::fabs(x) :
		hamon::isinf(x) || hamon::isinf(y) ?
			hamon::numeric_limits<FloatType>::infinity() :
		hamon::isnan(x) || hamon::isnan(y) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hypot_unchecked(x, y);
}

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
hypot_impl(FloatType x, FloatType y, FloatType z) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) && hamon::iszero(y) ?
			hamon::fabs(z) :
		hamon::iszero(y) && hamon::iszero(z) ?
			hamon::fabs(x) :
		hamon::iszero(z) && hamon::iszero(x) ?
			hamon::fabs(y) :
		hamon::isinf(x) || hamon::isinf(y) || hamon::isinf(z) ?
			hamon::numeric_limits<FloatType>::infinity() :
		hamon::isnan(x) || hamon::isnan(y) || hamon::isnan(z) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hypot_unchecked(x, y, z);
}

}	// namespace detail

/**
 *	@brief	平方和の平方根を求める
 *
 *	@param	x
 *	@param	y
 *
 *	@return	引数 x と引数 y の平方和の平方根を返す。この際、余計なオーバーフロー、アンダーフローを起こさない。
 *
 *	x が ±0の場合、fabs(y) を返す
 *	y が ±0の場合、fabs(x) を返す
 *	x と y のどちらか一方でも±∞の場合（もう一方が NaN であっても）、+∞を返す
 *	上記を満たさずに、x と y のどちらか一方でもNaNの場合、NaNを返す
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
hypot(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::hypot_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
hypotf(float x, float y) HAMON_NOEXCEPT
{
	return detail::hypot_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
hypotl(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::hypot_impl(x, y);
}

/**
 *	@brief	平方和の平方根を求める(任意の算術型版)
 *
 *	@tparam	Arithmetic1	算術型
 *	@tparam	Arithmetic2	算術型
 *
 *	@note	引数が整数型の場合、doubleにキャストされる
 *
 *	@note	引数にlong doubleが含まれる場合、戻り値の型はlong double
 *			そうでない場合、戻り値の型はdouble
 */
template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
hypot(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::hypot_impl(static_cast<type>(x), static_cast<type>(y));
}

/**
 *	@brief	平方和の平方根を求める(3引数版)
 *
 *	@param	x
 *	@param	y
 *	@param	z
 *
 *	@return	x, y, z の平方和の平方根を返す。この際、余計なオーバーフロー、アンダーフローを起こさない。
 *
 *	x と y が ±0の場合、fabs(z) を返す
 *	y と z が ±0の場合、fabs(x) を返す
 *	z と x が ±0の場合、fabs(y) を返す
 *	引数のどれか1個でも ±∞ の場合（他の引数が NaN であっても）、+∞を返す
 *	上記を満たさずに、引数のどれか1個でも NaN の場合、NaN を返す
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
hypot(FloatType x, FloatType y, FloatType z) HAMON_NOEXCEPT
{
	return detail::hypot_impl(x, y, z);
}

/**
 *	@brief	平方和の平方根を求める(3引数、任意の算術型版)
 *
 *	@tparam	Arithmetic1	算術型
 *	@tparam	Arithmetic2	算術型
 *	@tparam	Arithmetic3	算術型
 */
template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic3)
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>
hypot(Arithmetic1 x, Arithmetic2 y, Arithmetic3 z) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>;
	return detail::hypot_impl(static_cast<type>(x), static_cast<type>(y), static_cast<type>(z));
}

}	// namespace hamon

#endif // HAMON_CMATH_HYPOT_HPP
