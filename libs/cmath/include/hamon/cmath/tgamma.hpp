/**
 *	@file	tgamma.hpp
 *
 *	@brief	tgamma 関数の定義
 */

#ifndef HAMON_CMATH_TGAMMA_HPP
#define HAMON_CMATH_TGAMMA_HPP

#include <hamon/algorithm/clamp.hpp>
#include <hamon/cmath/factorial.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/is_integer.hpp>
#include <hamon/cmath/round.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/limits.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>

#include <hamon/cmath/is_odd.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/numbers.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
tgamma_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_tgammaf(x);
}

inline HAMON_CXX11_CONSTEXPR double
tgamma_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_tgamma(x);
}

inline HAMON_CXX11_CONSTEXPR long double
tgamma_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_tgammal(x);
}

#else

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_y(T w)
{
	return static_cast<T>(((((((((((((
		-1.99542863674e-7      * w + 1.337767384067e-6)    * w +
		-2.591225267689e-6)    * w - 1.7545539395205e-5)   * w +
		 1.45596568617526e-4)  * w - 3.60837876648255e-4)  * w +
		-8.04329819255744e-4)  * w + 0.008023273027855346) * w +
		-0.017645244547851414) * w - 0.024552490005641278) * w +
		 0.19109110138763841)  * w - 0.233093736421782878) * w +
		-0.422784335098466784) * w + 0.99999999999999999);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_t_pos(T x, int n, int last)
{
	return last - n == 1 ?
		x - static_cast<T>(n) :
		tgamma_unchecked_ct_t_pos(x, n, n + (last - n) / 2) *
		tgamma_unchecked_ct_t_pos(x, n + (last - n) / 2, last);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_t_neg(T x, int n, int last)
{
	return last - n == 1 ?
		x + static_cast<T>(n) :
		tgamma_unchecked_ct_t_neg(x, n, n + (last - n) / 2) *
		tgamma_unchecked_ct_t_neg(x, n + (last - n) / 2, last);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_t_pos_rec(T x, int n, int last)
{
	return last - n == 1 ?
		T(1) / (x - static_cast<T>(n)) :
		tgamma_unchecked_ct_t_pos_rec(x, n, n + (last - n) / 2) *
		tgamma_unchecked_ct_t_pos_rec(x, n + (last - n) / 2, last);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_t_neg_rec(T x, int n, int last)
{
	return last - n == 1 ?
		T(1) / (x + static_cast<T>(n)) :
		tgamma_unchecked_ct_t_neg_rec(x, n, n + (last - n) / 2) *
		tgamma_unchecked_ct_t_neg_rec(x, n + (last - n) / 2, last);
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_2_pos_rec(T x, T y, T t)
{
	return t == 0 ? hamon::numeric_limits<T>::infinity() :
		(x - T(1)) / y / t;
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct_1(T x, int n)
{
	return
		n == 1 ?
			(x - T(1)) / tgamma_unchecked_ct_y(x - T(n + 2)) :
		n == 0 ?
			T(1) / tgamma_unchecked_ct_y(x - T(n + 2)) :
		n == static_cast<int>(hamon::detail::max_factorial<T>()) ?
			tgamma_unchecked_ct_2_pos_rec(x, tgamma_unchecked_ct_y(x - T(n + 2)), tgamma_unchecked_ct_t_pos_rec(x, 2, n + 1)) :
		n == -static_cast<int>(hamon::detail::max_factorial<T>()) ?
			T(1) / tgamma_unchecked_ct_y(x - T(n + 2)) * tgamma_unchecked_ct_t_neg_rec(x, 0, -n) :
		n > 1 ?
			(x - T(1)) / tgamma_unchecked_ct_y(x - T(n + 2)) * tgamma_unchecked_ct_t_pos(x, 2, n + 1) :
			T(1) / tgamma_unchecked_ct_y(x - T(n + 2)) / tgamma_unchecked_ct_t_neg(x, 0, -n);
}

template <class T>
HAMON_CXX11_CONSTEXPR T sinpx(T z)
{
	// Ad hoc function calculates x * sin(pi * x),
	// taking extra care near when x is near a whole number.
	int sign = 1;
	if (z < 0)
	{
		z = -z;
	}
	T fl = floor(z);
	T dist;  // LCOV_EXCL_LINE
	if (hamon::is_odd(fl))
	{
		fl += 1;
		dist = fl - z;
		sign = -sign;
	}
	else
	{
		dist = z - fl;
	}
//	BOOST_MATH_ASSERT(fl >= 0);
	if (dist > T(0.5))
	{
		dist = 1 - dist;
	}

	T result = sin(dist * hamon::numbers::pi_fn<T>());
	return sign * z * result;
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
root_epsilon()
{
	return hamon::sqrt(hamon::numeric_limits<T>::epsilon());
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
log_max_value()
{
	return hamon::log(hamon::numeric_limits<T>::max());
}

template <class T, class U, class V>
HAMON_CXX11_CONSTEXPR V
evaluate_rational_imp(const T* num, const U* denom, V z, hamon::size_t count)
{
	V s1{}, s2{};
	if (z <= 1)
	{
		s1 = static_cast<V>(num[count - 1]);
		s2 = static_cast<V>(denom[count - 1]);
		for (int i = (int)count - 2; i >= 0; --i)
		{
			s1 *= z;
			s2 *= z;
			s1 += num[i];
			s2 += denom[i];
		}
	}
	else
	{
		z = 1 / z;
		s1 = static_cast<V>(num[0]);
		s2 = static_cast<V>(denom[0]);
		for (unsigned i = 1; i < count; ++i)
		{
			s1 *= z;
			s2 *= z;
			s1 += num[i];
			s2 += denom[i];
		}
	}
	return s1 / s2;
}

template <hamon::size_t N, class T, class U, class V>
HAMON_CXX11_CONSTEXPR V
evaluate_rational(const T(&a)[N], const U(&b)[N], V z)
{
   return evaluate_rational_imp(a, b, z, N);
}

namespace Lanczos
{

template <class T>
HAMON_CXX11_CONSTEXPR T lanczos_sum(T z)
{
	const T num[13] =
	{
		static_cast<T>(23531376880.41075968857200767445163675473L),
		static_cast<T>(42919803642.64909876895789904700198885093L),
		static_cast<T>(35711959237.35566804944018545154716670596L),
		static_cast<T>(17921034426.03720969991975575445893111267L),
		static_cast<T>(6039542586.35202800506429164430729792107L),
		static_cast<T>(1439720407.311721673663223072794912393972L),
		static_cast<T>(248874557.8620541565114603864132294232163L),
		static_cast<T>(31426415.58540019438061423162831820536287L),
		static_cast<T>(2876370.628935372441225409051620849613599L),
		static_cast<T>(186056.2653952234950402949897160456992822L),
		static_cast<T>(8071.672002365816210638002902272250613822L),
		static_cast<T>(210.8242777515793458725097339207133627117L),
		static_cast<T>(2.506628274631000270164908177133837338626L)
	};

	const hamon::uint32_t denom[13] =
	{
		static_cast<hamon::uint32_t>(0u),
		static_cast<hamon::uint32_t>(39916800u),
		static_cast<hamon::uint32_t>(120543840u),
		static_cast<hamon::uint32_t>(150917976u),
		static_cast<hamon::uint32_t>(105258076u),
		static_cast<hamon::uint32_t>(45995730u),
		static_cast<hamon::uint32_t>(13339535u),
		static_cast<hamon::uint32_t>(2637558u),
		static_cast<hamon::uint32_t>(357423u),
		static_cast<hamon::uint32_t>(32670u),
		static_cast<hamon::uint32_t>(1925u),
		static_cast<hamon::uint32_t>(66u),
		static_cast<hamon::uint32_t>(1u)
	};

	return evaluate_rational(num, denom, z);
}

HAMON_CXX11_CONSTEXPR double g(){ return 6.024680040776729583740234375; }

}	// namespace Lanczos

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_imp_final(T z)
{
	T result = 1;

	if (z <= 0)
	{
		// shift z to > 1:
		while (z < 0)
		{
			result /= z;
			z += 1;
		}
	}

	if ((floor(z) == z) && (z < hamon::detail::max_factorial<T>()))
	{
		result *= hamon::detail::unchecked_factorial<T>(static_cast<unsigned>(hamon::trunc(z) - 1));
	}
	else if (z < root_epsilon<T>())
	{
		//if (z < 1 / hamon::numeric_limits<T>::max())
		//{
		//	result = policies::raise_overflow_error<T>(function, nullptr, pol);
		//}
		result *= 1 / z - hamon::numbers::egamma_fn<T>();
	}
	else
	{
		result *= Lanczos::lanczos_sum(z);
		T zgh = (z + static_cast<T>(Lanczos::g()) - T(0.5));
		T lzgh = log(zgh);
		if (z * lzgh > log_max_value<T>())
		{
			// we're going to overflow unless this is done with care:
			//if (lzgh * z / 2 > tools::log_max_value<T>())
			//{
			//	return boost::math::sign(result) * policies::raise_overflow_error<T>(function, "Result of tgamma is too large to represent.", pol);
			//}
			T hp = pow(zgh, T((z / 2) - T(0.25)));
			result *= hp / exp(zgh);
			//if (tools::max_value<T>() / hp < result)
			//{
			//	return boost::math::sign(result) * policies::raise_overflow_error<T>(function, "Result of tgamma is too large to represent.", pol);
			//}
			result *= hp;
		}
		else
		{
			result *= pow(zgh, T(z - T(0.5))) / exp(zgh);
		}
	}
	return result;
}

template<typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked_ct(T x)
{
	//if (x <= -20)
	//{
	//	T result = tgamma_imp_final(-x) * sinpx(x);
	//	result = -hamon::numbers::pi_fn<T>() / result;
	//	return result;
	//}

	return tgamma_unchecked_ct_1(
		x,
		hamon::clamp(
			static_cast<int>(hamon::round(x - T(2))),
			-static_cast<int>(hamon::detail::max_factorial<T>()),
			 static_cast<int>(hamon::detail::max_factorial<T>())));
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
tgamma_unchecked(T x) HAMON_NOEXCEPT
{
	return hamon::is_constant_evaluated() ?
		tgamma_unchecked_ct(x) : std::tgamma(x);
}

#endif

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
tgamma_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::iszero(x) ?
			hamon::numeric_limits<FloatType>::infinity() :
		(x < 0 && hamon::is_integer(x)) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::isinf(x)  ?
			hamon::signbit(x) ?
				hamon::numeric_limits<FloatType>::quiet_NaN() :
			hamon::numeric_limits<FloatType>::infinity() :
		tgamma_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	ガンマ関数を計算します．
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x
 *
 *	@return	x のガンマ関数を返します。
 *
 *	x が ±0      の場合、+∞ を返す。
 *	x が 負の整数 の場合、NaN を返す。
 *	x が -∞      の場合、NaN を返す。
 *	x が +∞      の場合、+∞ を返す。
 *	x が NaN     の場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
tgamma(FloatType arg) HAMON_NOEXCEPT
{
	return detail::tgamma_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
tgamma(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::tgamma_impl(static_cast<double>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
tgammaf(float arg) HAMON_NOEXCEPT
{
	return detail::tgamma_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
tgammal(long double arg) HAMON_NOEXCEPT
{
	return detail::tgamma_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_TGAMMA_HPP
