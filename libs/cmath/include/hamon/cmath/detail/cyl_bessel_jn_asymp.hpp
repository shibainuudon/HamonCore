/**
 *	@file	cyl_bessel_jn_asymp.hpp
 *
 *	@brief	cyl_bessel_jn_asymp 関数の実装
 */

#ifndef HAMON_CMATH_DETAIL_CYL_BESSEL_JN_ASYMP_HPP
#define HAMON_CMATH_DETAIL_CYL_BESSEL_JN_ASYMP_HPP

#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/cos.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/limits.hpp>
#include <hamon/numbers.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR void
cyl_bessel_jn_asymp(T nu, T x, T& Jnu, T& Nnu)
{
	const T mu = T(4) * nu * nu;
	const T x8 = T(8) * x;

	T P = T(0);
	T Q = T(0);

	T k = T(0);
	T term = T(1);

	int epsP = 0;
	int epsQ = 0;

	T eps = hamon::numeric_limits<T>::epsilon();

	do
	{
		term *= (k == 0
			? T(1)
			: -(mu - (2 * k - 1) * (2 * k - 1)) / (k * x8));

		epsP = hamon::abs(term) < eps * hamon::abs(P);
		P += term;

		k++;

		term *= (mu - (2 * k - 1) * (2 * k - 1)) / (k * x8);
		epsQ = hamon::abs(term) < eps * hamon::abs(Q);
		Q += term;

		if (epsP && epsQ && k > (nu / 2.))
		{
			break;
		}

		k++;
	}
	while (k < 1000);

	const T chi = x - (nu + T(0.5L)) * (hamon::numbers::pi_fn<T>() / 2);

	const T c = hamon::cos(chi);
	const T s = hamon::sin(chi);

	const T coef = hamon::sqrt(T(2) / (hamon::numbers::pi_fn<T>() * x));

	Jnu = coef * (c * P - s * Q);
	Nnu = coef * (s * P + c * Q);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CMATH_DETAIL_CYL_BESSEL_JN_ASYMP_HPP
