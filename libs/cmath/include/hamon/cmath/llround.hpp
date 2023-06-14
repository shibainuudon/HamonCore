/**
 *	@file	llround.hpp
 *
 *	@brief	llround 関数の定義
 */

#ifndef HAMON_CMATH_LLROUND_HPP
#define HAMON_CMATH_LLROUND_HPP

#include <hamon/cmath/round.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <limits>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR long long
llround_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_llroundf(x);
}

inline HAMON_CXX11_CONSTEXPR long long
llround_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_llround(x);
}

inline HAMON_CXX11_CONSTEXPR long long
llround_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_llroundl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR long long
llround_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::llround(x);
	}
#endif
	return static_cast<long long>(round_unchecked(x));
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR long long
llround_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			std::numeric_limits<long long>::min() :
		x < (FloatType)std::numeric_limits<long long>::min() ?
			std::numeric_limits<long long>::min() :
		x > (FloatType)std::numeric_limits<long long>::max() ?
			std::numeric_limits<long long>::max() :
		llround_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	四捨五入により丸めた整数値をlong long型として得る。
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x を四捨五入により丸めた整数値を、long long型の範囲に収めて返す。
 *
 *	ここで引数 x の四捨五入とは、x を最も近い整数に丸めるが、
 *	x の小数部分が 0.5 の場合には、x の符号が正負のいずれであってもゼロから遠い方向に丸めることを指す。
 *
 *	x が numeric_limits<long long>::min() より小さい場合、numeric_limits<long long>::min() を返す。
 *	x が numeric_limits<long long>::max() より大きい場合、numeric_limits<long long>::max() を返す。
 *	x が NaN の場合、numeric_limits<long long>::min() を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long long
llround(Arithmetic arg) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::llround_impl(static_cast<type>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long long
llroundf(float arg) HAMON_NOEXCEPT
{
	return detail::llround_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long long
llroundl(long double arg) HAMON_NOEXCEPT
{
	return detail::llround_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_LLROUND_HPP
