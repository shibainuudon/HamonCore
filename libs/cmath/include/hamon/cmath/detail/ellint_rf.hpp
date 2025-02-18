/**
 *	@file	ellint_rf.hpp
 *
 *	@brief	ellint_rf 関数の実装
 */

#ifndef HAMON_CMATH_DETAIL_ELLINT_RF_HPP
#define HAMON_CMATH_DETAIL_ELLINT_RF_HPP

#include <hamon/cmath/pow.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
ellint_rf(T x, T y, T z)
{
	T const lolim = T(5) * hamon::numeric_limits<T>::min();

	if (x < T(0) || y < T(0) || z < T(0))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}
	else if (x + y < lolim || x + z < lolim || y + z < lolim)
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}
	else
	{
		T const c0 = T(1) / T(4);
		T const c1 = T(1) / T(24);
		T const c2 = T(1) / T(10);
		T const c3 = T(3) / T(44);
		T const c4 = T(1) / T(14);

		T xn = x;
		T yn = y;
		T zn = z;

		T const eps = hamon::numeric_limits<T>::epsilon();
		T const errtol = hamon::pow(eps, T(1) / T(6));
		T mu{};
		T xndev{};
		T yndev{};
		T zndev{};

		const unsigned int max_iter = 100;
		for (unsigned int iter = 0; iter < max_iter; ++iter)
		{
			mu = (xn + yn + zn) / T(3);
			xndev = 2 - (mu + xn) / mu;
			yndev = 2 - (mu + yn) / mu;
			zndev = 2 - (mu + zn) / mu;
			T const epsilon = hamon::max(
				{hamon::abs(xndev), hamon::abs(yndev), hamon::abs(zndev)});
			if (epsilon < errtol)
			{
				break;
			}
			T const xnroot = hamon::sqrt(xn);
			T const ynroot = hamon::sqrt(yn);
			T const znroot = hamon::sqrt(zn);
			T const lambda = xnroot * (ynroot + znroot) + ynroot * znroot;
			xn = c0 * (xn + lambda);
			yn = c0 * (yn + lambda);
			zn = c0 * (zn + lambda);
		}

		T const e2 = xndev * yndev - zndev * zndev;
		T const e3 = xndev * yndev * zndev;
		T const s  = T(1) + (c1 * e2 - c2 - c3 * e3) * e2 + c4 * e3;

		return s / hamon::sqrt(mu);
	}
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CMATH_DETAIL_ELLINT_RF_HPP
