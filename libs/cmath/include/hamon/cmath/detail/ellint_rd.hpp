/**
 *	@file	ellint_rd.hpp
 *
 *	@brief	ellint_rd 関数の実装
 */

#ifndef HAMON_CMATH_DETAIL_ELLINT_RD_HPP
#define HAMON_CMATH_DETAIL_ELLINT_RD_HPP

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
ellint_rd(T x, T y, T z)
{
	T const eps = hamon::numeric_limits<T>::epsilon();
	T const errtol = hamon::pow(eps / T(8), T(1) / T(6));
	T const max = hamon::numeric_limits<T>::max();
	T const lolim = T(2) / hamon::pow(max, T(2) / T(3));

	if (x < T(0) || y < T(0))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}
	else if (x + y < lolim || z < lolim)
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}
	else
	{
		T const c0 = T(1) / T(4);
		T const c1 = T(3) / T(14);
		T const c2 = T(1) / T(6);
		T const c3 = T(9) / T(22);
		T const c4 = T(3) / T(26);

		T xn = x;
		T yn = y;
		T zn = z;
		T sigma = T(0);
		T power4 = T(1);

		T mu{};
		T xndev{};
		T yndev{};
		T zndev{};

		const unsigned int max_iter = 100;
		for (unsigned int iter = 0; iter < max_iter; ++iter)
		{
			mu = (xn + yn + T(3) * zn) / T(5);
			xndev = (mu - xn) / mu;
			yndev = (mu - yn) / mu;
			zndev = (mu - zn) / mu;
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
			sigma += power4 / (znroot * (zn + lambda));
			power4 *= c0;
			xn = c0 * (xn + lambda);
			yn = c0 * (yn + lambda);
			zn = c0 * (zn + lambda);
		}

		T const ea = xndev * yndev;
		T const eb = zndev * zndev;
		T const ec = ea - eb;
		T const ed = ea - T(6) * eb;
		T const ef = ed + ec + ec;
		T const s1 = ed * (-c1 + c3 * ed / T(3) - T(3) * c4 * zndev * ef / T(2));
		T const s2 = zndev * (c2 * ef + zndev * (-c3 * ec - zndev * c4 - ea));

		return T(3) * sigma + power4 * (T(1) + s1 + s2) / (mu * hamon::sqrt(mu));
	}
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CMATH_DETAIL_ELLINT_RD_HPP
