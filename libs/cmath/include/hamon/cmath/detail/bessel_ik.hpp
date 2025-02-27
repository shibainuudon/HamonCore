/**
 *	@file	bessel_ik.hpp
 *
 *	@brief	bessel_ik 関数の実装
 */

#ifndef HAMON_CMATH_DETAIL_BESSEL_IK_HPP
#define HAMON_CMATH_DETAIL_BESSEL_IK_HPP

#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/cmath/sinh.hpp>
#include <hamon/cmath/cosh.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/detail/gamma_temme.hpp>
#include <hamon/limits.hpp>
#include <hamon/numbers.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR void
bessel_ik(T nu, T x, T& Inu, T& Knu, T& Ipnu, T& Kpnu)
{
	if (x == T(0))
	{
		if (nu == T(0))
		{
			Inu = T(1);
			Ipnu = T(0);
		}
		else if (nu == T(1))
		{
			Inu = T(0);
			Ipnu = T(0.5L);
		}
		else
		{
			Inu = T(0);
			Ipnu = T(0);
		}

		Knu  =  hamon::numeric_limits<T>::infinity();
		Kpnu = -hamon::numeric_limits<T>::infinity();
		return;
	}

	const T eps = hamon::numeric_limits<T>::epsilon();
	const T fp_min = T(10) * hamon::numeric_limits<T>::epsilon();
	const int max_iter = 15000;
	const T x_min = T(2);

	const int nl = static_cast<int>(nu + T(0.5L));

	const T mu = nu - nl;
	const T mu2 = mu * mu;
	const T xi = T(1) / x;
	const T xi2 = T(2) * xi;
	T h = nu * xi;
	if (h < fp_min)
	{
		h = fp_min;
	}

	{
		T b = xi2 * nu;
		T d = T(0);
		T c = h;
		for (int i = 1; i <= max_iter; ++i)
		{
			b += xi2;
			d = T(1) / (b + d);
			c = b + T(1) / c;
			const T del = c * d;
			h *= del;
			if (hamon::abs(del - T(1)) < eps)
			{
				break;
			}
		}
	}

	T Inul = fp_min;
	T Ipnul = h * Inul;
	T Inul1 = Inul;
	T Ipnu1 = Ipnul;
	{
		T fact = nu * xi;
		for (int l = nl; l >= 1; --l)
		{
			const T Inutemp = fact * Inul + Ipnul;
			fact -= xi;
			Ipnul = fact * Inutemp + Inul;
			Inul = Inutemp;
		}
	}
	T f = Ipnul / Inul;
	T Kmu{};
	T Knu1{};

	if (x < x_min)
	{
		const T x2 = x / T(2);
		const T pimu = hamon::numbers::pi_fn<T>() * mu;
		const T fact = (hamon::abs(pimu) < eps ? T(1) : pimu / hamon::sin(pimu));
		T d = -hamon::log(x2);
		T e = mu * d;
		const T fact2 = (hamon::abs(e) < eps ? T(1) : hamon::sinh(e) / e);
		T gam1{}, gam2{}, gampl{}, gammi{};
		hamon::detail::gamma_temme(mu, gam1, gam2, gampl, gammi);
		T ff = fact * (gam1 * hamon::cosh(e) + gam2 * fact2 * d);
		T sum = ff;
		e = hamon::exp(e);
		T p = e / (T(2) * gampl);
		T q = T(1) / (T(2) * e * gammi);
		T c = T(1);
		d = x2 * x2;
		T sum1 = p;
		for (int i = 1; i <= max_iter; ++i)
		{
			ff = (i * ff + p + q) / (T(i) * T(i) - mu2);
			c *= d / i;
			p /= i - mu;
			q /= i + mu;
			const T del = c * ff;
			sum += del;
			const T del1 = c * (p - i * ff);
			sum1 += del1;
			if (hamon::abs(del) < eps * hamon::abs(sum))
			{
				break;
			}
		}

		Kmu = sum;
		Knu1 = sum1 * xi2;
	}
	else
	{
		T b = T(2) * (T(1) + x);
		T d = T(1) / b;
		T delh = d;
		T h2 = delh;
		T q1 = T(0);
		T q2 = T(1);
		T a1 = T(0.25L) - mu2;
		T q = a1;
		T c = a1;
		T a = -a1;
		T s = T(1) + q * delh;
		for (int i = 2; i <= max_iter; ++i)
		{
			a -= T(2) * (i - T(1));
			c = -a * c / i;
			const T qnew = (q1 - b * q2) / a;
			q1 = q2;
			q2 = qnew;
			q += c * qnew;
			b += T(2);
			d = T(1) / (b + a * d);
			delh = (b * d - T(1)) * delh;
			h2 += delh;
			const T dels = q * delh;
			s += dels;
			if (hamon::abs(dels / s) < eps)
			{
				break;
			}
		}

		h2 = a1 * h2;
		Kmu = hamon::sqrt(hamon::numbers::pi_fn<T>() / (T(2) * x)) * std::exp(-x) / s;	// TODO hamon::exp
		Knu1 = Kmu * (mu + x + T(0.5L) - h2) * xi;
	}

	T Kpmu = mu * xi * Kmu - Knu1;
	T Inumu = xi / (f * Kmu - Kpmu);
	Inu = Inumu * Inul1 / Inul;
	Ipnu = Inumu * Ipnu1 / Inul;
	for (int i = 1; i <= nl; ++i)
	{
		const T Knutemp = (mu + i) * xi2 * Knu1 + Kmu;
		Kmu = Knu1;
		Knu1 = Knutemp;
	}
	Knu = Kmu;
	Kpnu = nu * xi * Kmu - Knu1;
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CMATH_DETAIL_BESSEL_IK_HPP
