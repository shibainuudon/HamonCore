/**
 *	@file	ellint_rj.hpp
 *
 *	@brief	ellint_rj 関数の実装
 */

#ifndef HAMON_CMATH_DETAIL_ELLINT_RJ_HPP
#define HAMON_CMATH_DETAIL_ELLINT_RJ_HPP

#include <hamon/cmath/pow.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/detail/ellint_rc.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
ellint_rj(T x, T y, T z, T p)
{
	T const min = hamon::numeric_limits<T>::min();
	T const lolim = hamon::pow(T(5) * min, T(1) / T(3));

	if (x < T(0) || y < T(0) || z < T(0))
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}
	else if (x + y < lolim || x + z < lolim || y + z < lolim || p < lolim)
	{
		return hamon::numeric_limits<T>::quiet_NaN();
	}
	else
	{
		T const c0 = T(1) / T(4);
		T const c1 = T(3) / T(14);
		T const c2 = T(1) / T(3);
		T const c3 = T(3) / T(22);
		T const c4 = T(3) / T(26);

		T xn = x;
		T yn = y;
		T zn = z;
		T pn = p;
		T sigma = T(0);
		T power4 = T(1);

		T const eps = hamon::numeric_limits<T>::epsilon();
		T const errtol = hamon::pow(eps / T(8), T(1) / T(6));

		T mu{};
		T xndev{};
		T yndev{};
		T zndev{};
		T pndev{};

		unsigned int const max_iter = 100;
		for (unsigned int iter = 0; iter < max_iter; ++iter)
		{
			mu = (xn + yn + zn + T(2) * pn) / T(5);
			xndev = (mu - xn) / mu;
			yndev = (mu - yn) / mu;
			zndev = (mu - zn) / mu;
			pndev = (mu - pn) / mu;
			T const epsilon = hamon::max({
				hamon::abs(xndev),
				hamon::abs(yndev),
				hamon::abs(zndev),
				hamon::abs(pndev)});
			if (epsilon < errtol)
			{
				break;
			}
			T const xnroot = hamon::sqrt(xn);
			T const ynroot = hamon::sqrt(yn);
			T const znroot = hamon::sqrt(zn);
			T const lambda = xnroot * (ynroot + znroot) + ynroot * znroot;
			T const alpha1 = pn * (xnroot + ynroot + znroot) + xnroot * ynroot * znroot;
			T const alpha2 = alpha1 * alpha1;
			T const beta = pn * (pn + lambda) * (pn + lambda);
			sigma += power4 * hamon::detail::ellint_rc(alpha2, beta);
			power4 *= c0;
			xn = c0 * (xn + lambda);
			yn = c0 * (yn + lambda);
			zn = c0 * (zn + lambda);
			pn = c0 * (pn + lambda);
		}

		T const ea = xndev * (yndev + zndev) + yndev * zndev;
		T const eb = xndev * yndev * zndev;
		T const ec = pndev * pndev;
		T const e2 = ea - T(3) * ec;
		T const e3 = eb + T(2) * pndev * (ea - ec);
		T const s1 = T(1) + e2 * (-c1 + T(3) * c3 * e2 / T(4) - T(3) * c4 * e3 / T(2));
		T const s2 = eb * (c2 / T(2) + pndev * (-c3 - c3 + pndev * c4));
		T const s3 = pndev * ea * (c2 - pndev * c3) - c2 * pndev * ec;

		return T(3) * sigma + power4 * (s1 + s2 + s3) / (mu * hamon::sqrt(mu));
	}
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CMATH_DETAIL_ELLINT_RJ_HPP
