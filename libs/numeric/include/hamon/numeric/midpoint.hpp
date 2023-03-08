/**
 *	@file	midpoint.hpp
 *
 *	@brief	midpoint の定義
 */

#ifndef HAMON_NUMERIC_MIDPOINT_HPP
#define HAMON_NUMERIC_MIDPOINT_HPP

#include <numeric>

#if defined(__cpp_lib_interpolate) && (__cpp_lib_interpolate >= 201902)

namespace hamon
{

using std::midpoint;

}	// namespace hamon

#else

#include <hamon/algorithm/max.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/config.hpp>
#include <limits>

namespace hamon
{

namespace detail
{

// integral

template <typename T, typename U>
inline HAMON_CXX11_CONSTEXPR T
midpoint_integral_impl(T a, U diff, U sign_bit, U bitshift) HAMON_NOEXCEPT
{
	return T(a + T(U((diff / 2) + (sign_bit << bitshift) + (sign_bit & diff))));
}

template <typename T, typename = hamon::enable_if_t<hamon::is_integral<T>::value>>
inline HAMON_CXX11_CONSTEXPR T
midpoint_impl(T a, T b, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	using U = hamon::make_unsigned_t<T>;
	return midpoint_integral_impl<T, U>(
		a,
		U(U(b) - U(a)),
		b < a,
		std::numeric_limits<U>::digits - 1);
}

// floating

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
midpoint_floating_impl(T a, T b, T abs_a, T abs_b, T lo, T hi) HAMON_NOEXCEPT
{
	return
		(abs_a <= hi && abs_b <= hi) ?
			(a + b) / 2 :
		(abs_a < lo) ?
			a + b/2 :
		(abs_b < lo) ?
			a/2 + b :
			a/2 + b/2;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
midpoint_impl(T a, T b, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
{
	return midpoint_floating_impl(
		a, b,
		hamon::abs(a),
		hamon::abs(b),
		std::numeric_limits<T>::min() * 2,
		std::numeric_limits<T>::max() / 2);
}

}	// namespace detail

/**
 *	@brief		数値型の中点を求める
 *
 *	@tparam		T	bool 以外の算術型
 *
 *	@param		a
 *	@param		b
 * 
 *	単純に計算する場合は(a + b) / 2となるが、
 *	この関数は、オーバーフローが起こりにくいよう計算式に工夫が入る
 * 
 *	aとbを合計した値の1/2の数値を返す
 *	・型Tが整数型で合計値が奇数の場合、a側に丸められる
 *	・型Tが浮動小数点数型の場合、最大一回の不正確 (inexact) 操作が発生し、オーバーフローは起こらない
 */
template <typename T>
inline HAMON_CXX11_CONSTEXPR
hamon::enable_if_t<
	hamon::conjunction<
		hamon::is_arithmetic<T>,
		hamon::is_same<hamon::remove_cv_t<T>, T>,
		hamon::negation<hamon::is_same<T, bool>>
	>::value,
	T
>
midpoint(T a, T b) HAMON_NOEXCEPT
{
	return detail::midpoint_impl(a, b, hamon::detail::overload_priority<1>{});
}

/**
 *	@brief		ポインタ型の中点を求める
 *
 *	@tparam		T	オブジェクト型
 * 
 *	型Tは完全型であること
 *
 *	@param		a
 *	@param		b
 * 
 *	事前条件:aとbはそれぞれ、同じ配列xのx[i]とx[j]要素を指していること
 * 
 *	aとbが同じ配列xのx[i]とx[j]を指しているとして、x[i + (j - i) / 2]を指すポインタを返す。
 *	除算の結果はゼロ方向に丸められる
 */
template <typename T>
inline HAMON_CXX11_CONSTEXPR hamon::enable_if_t<hamon::is_object<T>::value, T*>
midpoint(T* a, T* b) HAMON_NOEXCEPT
{
	static_assert(sizeof(T) != 0, "type must be complete");
	return a + hamon::midpoint(hamon::ptrdiff_t(0), b - a);
}

}	// namespace hamon

#endif

#endif // HAMON_NUMERIC_MIDPOINT_HPP
