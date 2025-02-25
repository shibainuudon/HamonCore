/**
 *	@file	sph_legendre.hpp
 *
 *	@brief	sph_legendre 関数の定義
 */

#ifndef HAMON_CMATH_SPH_LEGENDRE_HPP
#define HAMON_CMATH_SPH_LEGENDRE_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/cos.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/log1p.hpp>
#include <hamon/cmath/lgamma.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/cmath/legendre.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
sph_legendre_unchecked_2(unsigned int l, unsigned int m, T theta)
{
	const T x = std::cos(theta);	// hamon::cos(theta);	// TODO

	if (m > l)
	{
		return T(0);
	}
	else if (m == 0)
	{
		T p = hamon::detail::legendre_unchecked(l, x);
		T fact = hamon::sqrt((T(2) * l + T(1)) / (T(4) * hamon::numbers::pi_fn<T>()));
		p *= fact;
		return p;
	}
	else if (x == T(1) || x == -T(1))
	{
		//  m > 0 here
		return T(0);
	}
	else
	{
		// m > 0 and |x| < 1 here

		// Starting value for recursion.
		// Y_m^m(x) = sqrt( (2m+1)/(4pi m) gamma(m+1/2)/gamma(m) )
		//             (-1)^m (1-x^2)^(m/2) / pi^(1/4)
		const T sgn = (m % 2 == 1 ? -T(1) : T(1));
		const T y_mp1m_factor = x * hamon::sqrt(T(2) * m + T(3));
		const T lncirc = hamon::log1p(-x * x);

		//  Gamma(m+1/2) / Gamma(m)
		const T lnpoch = hamon::lgamma(T(m + T(0.5L))) - hamon::lgamma(T(m));
		const T lnpre_val =
			-T(0.25L) * hamon::log(hamon::numbers::pi_fn<T>())
			+ T(0.5L) * (lnpoch + m * lncirc);
		const T sr = hamon::sqrt((T(2) + T(1) / m) / (T(4) * hamon::numbers::pi_fn<T>()));
		T y_mm = sgn * sr * std::exp(lnpre_val);	// hamon::exp(lnpre_val);	// TODO
		T y_mp1m = y_mp1m_factor * y_mm;

		if (l == m)
		{
			return y_mm;
		}
		else if (l == m + 1)
		{
			return y_mp1m;
		}
		else
		{
			T y_lm = T(0);

			// Compute Y_l^m, l > m+1, upward recursion on l.
			for (unsigned int ll = m + 2; ll <= l; ++ll)
			{
				const T rat1 = (T(ll) - T(m)) / (T(ll) + T(m));
				const T rat2 = (T(ll) - T(m) - T(1)) / (T(ll) + T(m) - T(1));
				const T fact1 = hamon::sqrt(rat1 * (T(2) * ll + T(1)) * (T(2) * ll - T(1)));
				const T fact2 = hamon::sqrt(rat1 * rat2 * (T(2) * ll + T(1)) / (T(2) * ll - T(3)));
				y_lm = (x * y_mp1m * fact1 - (T(ll) + m - T(1)) * y_mm * fact2) / (T(ll) - T(m));
				y_mm = y_mp1m;
				y_mp1m = y_lm;
			}

			return y_lm;
		}
	}
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
sph_legendre_unchecked(unsigned int l, unsigned int m, T theta)
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)
	if (!hamon::is_constant_evaluated())
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
		return std::sph_legendre(l, m, theta);
HAMON_WARNING_POP()
	}
#endif
#endif

	using value_type = hamon::float_promote_t<double, T>;
	return static_cast<T>(sph_legendre_unchecked_2(l, m, static_cast<value_type>(theta)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
sph_legendre_impl(unsigned int l, unsigned int m, T theta)
{
	if (hamon::isnan(theta))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}

	return sph_legendre_unchecked(l, m, theta);
}

}	// namespace detail

/**
 *	@brief	球面調和関数 (spherical harmonic function) の θ 成分を求める
 *
 *	@param	l
 *	@param	m
 *	@param	theta
 *
 *	@return	引数 l, m, theta の球面調和関数の θ 成分を求める
 *
 *	theta が NaN のとき、NaN を返す
 *	l >= 128 の場合、この関数の呼び出しの効果は実装定義である
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR FloatType
sph_legendre(unsigned int l, unsigned int m, FloatType theta) HAMON_NOEXCEPT
{
	return detail::sph_legendre_impl(l, m, theta);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR double
sph_legendre(unsigned int l, unsigned int m, IntegralType theta) HAMON_NOEXCEPT
{
	return detail::sph_legendre_impl(l, m, static_cast<double>(theta));
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR float
sph_legendref(unsigned int l, unsigned int m, float theta) HAMON_NOEXCEPT
{
	return detail::sph_legendre_impl(l, m, theta);
}

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR long double
sph_legendrel(unsigned int l, unsigned int m, long double theta) HAMON_NOEXCEPT
{
	return detail::sph_legendre_impl(l, m, theta);
}

}	// namespace hamon

#endif // HAMON_CMATH_SPH_LEGENDRE_HPP
