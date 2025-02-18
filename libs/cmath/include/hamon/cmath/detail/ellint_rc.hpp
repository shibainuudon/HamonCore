/**
 *	@file	ellint_rc.hpp
 *
 *	@brief	ellint_rc 関数の実装
 */

#ifndef HAMON_CMATH_DETAIL_ELLINT_RC_HPP
#define HAMON_CMATH_DETAIL_ELLINT_RC_HPP

#include <hamon/cmath/pow.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
ellint_rc(T x, T y)
{
	T const lolim = T(5) * hamon::numeric_limits<T>::min();

	if (x < T(0) || y < T(0) || x + y < lolim)
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}
	else
	{
		T const c0 = T(1) / T(4);
		T const c1 = T(1) / T(7);
		T const c2 = T(9) / T(22);
		T const c3 = T(3) / T(10);
		T const c4 = T(3) / T(8);

		T xn = x;
		T yn = y;

		T const eps = hamon::numeric_limits<T>::epsilon();
		T const errtol = hamon::pow(eps / T(30), T(1) / T(6));
		T mu{};
		T sn{};

		const unsigned int max_iter = 100;
		for (unsigned int iter = 0; iter < max_iter; ++iter)
		{
			mu = (xn + T(2) * yn) / T(3);
			sn = (yn + mu) / mu - T(2);
			if (hamon::abs(sn) < errtol)
			{
				break;
			}
			T const lambda = T(2) * hamon::sqrt(xn) * hamon::sqrt(yn) + yn;
			xn = c0 * (xn + lambda);
			yn = c0 * (yn + lambda);
		}

		T const s = sn * sn * (c3 + sn*(c1 + sn * (c4 + sn * c2)));

		return (T(1) + s) / hamon::sqrt(mu);
	}
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CMATH_DETAIL_ELLINT_RC_HPP
