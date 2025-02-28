/**
 *	@file	cyl_bessel_ij_series.hpp
 *
 *	@brief	cyl_bessel_ij_series 関数の実装
 */

#ifndef HAMON_CMATH_DETAIL_CYL_BESSEL_IJ_SERIES_HPP
#define HAMON_CMATH_DETAIL_CYL_BESSEL_IJ_SERIES_HPP

#include <hamon/cmath/log.hpp>
#include <hamon/cmath/lgamma.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
cyl_bessel_ij_series(T nu, T x, T sgn, unsigned int max_iter)
{
	if (x == T(0))
	{
		return nu == T(0) ? T(1) : T(0);
	}

	const T x2 = x / T(2);
	T fact = nu * hamon::log(x2);
	fact -= std::lgamma(nu + T(1));		// TODO hamon::lgamma
	fact = std::exp(fact);				// TODO hamon::exp
	const T xx4 = sgn * x2 * x2;
	T Jn = T(1);
	T term = T(1);

	for (unsigned int i = 1; i < max_iter; ++i)
	{
		term *= xx4 / (T(i) * (nu + T(i)));
		Jn += term;
		if (hamon::abs(term / Jn) < hamon::numeric_limits<T>::epsilon())
		{
			break;
		}
	}

	return fact * Jn;
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CMATH_DETAIL_CYL_BESSEL_IJ_SERIES_HPP
