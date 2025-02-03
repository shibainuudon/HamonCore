/**
 *	@file	remquo.hpp
 *
 *	@brief	remquo
 */

#ifndef HAMON_CMATH_REMQUO_HPP
#define HAMON_CMATH_REMQUO_HPP

#include <cmath>

#if defined(__cpp_lib_constexpr_cmath) && (__cpp_lib_constexpr_cmath >= 202202L)

namespace hamon
{

using std::remquo;
using std::remquof;
using std::remquol;

}	// namespace hamon

#else

#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/ilogb.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/scalbn.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

#include <hamon/pair.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
remquo_unchecked(float x, float y, int* quo) HAMON_NOEXCEPT
{
	return __builtin_remquof(x, y, quo);
}

inline HAMON_CXX11_CONSTEXPR double
remquo_unchecked(double x, double y, int* quo) HAMON_NOEXCEPT
{
	return __builtin_remquo(x, y, quo);
}

inline HAMON_CXX11_CONSTEXPR long double
remquo_unchecked(long double x, long double y, int* quo) HAMON_NOEXCEPT
{
	return __builtin_remquol(x, y, quo);
}

#else

template <typename T>
HAMON_CXX14_CONSTEXPR T
remquo_unchecked_impl(T x, T y, int* quo)
{
	T const x1 = hamon::fabs(x);
	T const y1 = hamon::fabs(y);
	int const k = (hamon::signbit(x) ^ hamon::signbit(y) ? -1 : 1);
	int const iscx = hamon::ilogb(x1);
	int const iscy = hamon::ilogb(y1);
	int const idiff = iscx - iscy;

	T result = x1;
	int iquo = 0;
	if (idiff >= 0)
	{
		T x2 = hamon::scalbn(x1, -iscx);
		T y2 = hamon::scalbn(y1, -iscy);
		for (int i = 0; i != idiff; ++i)
		{
			T z = x2 - y2;
			if (z >= 0)
			{
				iquo += (iquo + 2);
				x2 = z + z;
			}
			else
			{
				iquo += iquo;
				x2 = x2 + x2;
			}
		}
		result = hamon::scalbn(x2, iscy);
	}

	if (result >= y1)
	{
		result -= y1;
		++iquo;
	}

	T const z = result + result;
	if ((z > y1) || ((z == y1) && ((iquo & 1) != 0)))
	{
		result -= y1;
		++iquo;
	}

	*quo = (iquo & 0x7) * k;
	return (x < 0) ? -result : result;
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
remquo_unchecked(T x, T y, int* quo) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::remquo(x, y, quo);
	}
#endif

	return remquo_unchecked_impl(x, y, quo);
}

#endif

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
remquo_impl(FloatType x, FloatType y, int* quo) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ||
		hamon::isnan(y) ||
		hamon::isinf(x) ||
		hamon::iszero(y) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		remquo_unchecked(x, y, quo);
}

}	// namespace detail

/**
 *	@brief	商と剰余を求める
 *
 *	@param		x
 *	@param		y
 *	@param		quo
 *
 *	@return		remainder(x, y) と同じ値
 *
 *	*quo にセットされる値は、 x / y と同じ符号を持ち、x / y の整数の商の絶対値と
 *	2^Nを法として合同である絶対値を持つ値(N は 3以上の処理系定義の整数)
 *
 *	x が ±∞ かつ、y が NaN でない場合、NaN を返し、quoが指す値は未規定となる。
 *	y が ±0 かつ、x が NaN でない場合、NaN を返し、quoが指す値は未規定となる。
 *	x か y が NaN の場合、NaN を返し、quoが指す値は未規定となる。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_CXX11_CONSTEXPR FloatType
remquo(FloatType x, FloatType y, int* quo) HAMON_NOEXCEPT
{
	return detail::remquo_impl(x, y, quo);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
remquo(Arithmetic1 x, Arithmetic2 y, int* quo) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::remquo_impl(static_cast<type>(x), static_cast<type>(y), quo);
}

inline HAMON_CXX11_CONSTEXPR float
remquof(float x, float y, int* quo) HAMON_NOEXCEPT
{
	return detail::remquo_impl(x, y, quo);
}

inline HAMON_CXX11_CONSTEXPR long double
remquol(long double x, long double y, int* quo) HAMON_NOEXCEPT
{
	return detail::remquo_impl(x, y, quo);
}

}	// namespace hamon

#endif

#endif // HAMON_CMATH_REMQUO_HPP
