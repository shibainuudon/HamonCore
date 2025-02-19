/**
 *	@file	bessel_jn.hpp
 *
 *	@brief	bessel_jn 関数の実装
 */

#ifndef HAMON_CMATH_DETAIL_BESSEL_JN_HPP
#define HAMON_CMATH_DETAIL_BESSEL_JN_HPP

#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/cmath/sinh.hpp>
#include <hamon/cmath/cosh.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/cmath/copysign.hpp>
#include <hamon/cmath/detail/gamma_temme.hpp>
#include <hamon/algorithm/max.hpp>
//#include <hamon/stdexcept/runtime_error.hpp>
#include <hamon/limits.hpp>
#include <hamon/numbers.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR void
bessel_jn(T nu, T x, T& Jnu, T& Nnu, T& Jpnu, T& Npnu)
{
	if (x == T(0))
	{
		if (nu == T(0))
		{
			Jnu = T(1);
			Jpnu = T(0);
		}
		else if (nu == T(1))
		{
			Jnu = T(0);
			Jpnu = T(0.5L);
		}
		else
		{
			Jnu = T(0);
			Jpnu = T(0);
		}
		Nnu = -hamon::numeric_limits<T>::infinity();
		Npnu = hamon::numeric_limits<T>::infinity();
		return;
	}

	const T eps = hamon::numeric_limits<T>::epsilon();
	//  When the multiplier is N i.e.
	//  fp_min = N * min()
	//  Then J_0 and N_0 tank at x = 8 * N (J_0 = 0 and N_0 = nan)!
	//const T fp_min = T(20) * hamon::numeric_limits<T>::min();
	const T fp_min = hamon::sqrt(hamon::numeric_limits<T>::min());
	const int max_iter = 15000;
	const T x_min = T(2);

	const int nl = (x < x_min
		? static_cast<int>(nu + T(0.5L))
		: hamon::max(0, static_cast<int>(nu - x + T(1.5L))));

	const T mu = nu - nl;
	const T mu2 = mu * mu;
	const T xi = T(1) / x;
	const T xi2 = T(2) * xi;
	T w = xi2 / hamon::numbers::pi_fn<T>();
	int isign = 1;
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
			d = b - d;
			if (hamon::abs(d) < fp_min)
			{
				d = fp_min;
			}
			c = b - T(1) / c;
			if (hamon::abs(c) < fp_min)
			{
				c = fp_min;
			}
			d = T(1) / d;
			const T del = c * d;
			h *= del;
			if (d < T(0))
			{
				isign = -isign;
			}
			if (hamon::abs(del - T(1)) < eps)
			{
				break;
			}
		}
		//if (i > max_iter)
		//{
		//	hamon::detail::throw_runtime_error("Argument x too large in bessel_jn; try asymptotic expansion.");
		//}
	}

	T Jnul = isign * fp_min;
	T Jpnul = h * Jnul;
	T Jnul1 = Jnul;
	T Jpnu1 = Jpnul;
	T fact = nu * xi;
	for (int l = nl; l >= 1; --l)
	{
		const T Jnutemp = fact * Jnul + Jpnul;
		fact -= xi;
		Jpnul = fact * Jnutemp - Jnul;
		Jnul = Jnutemp;
	}
	if (Jnul == T(0))
	{
		Jnul = eps;
	}
	T f = Jpnul / Jnul;
	T Nmu, Nnu1, Npmu, Jmu;
	if (x < x_min)
	{
		const T x2 = x / T(2);
		const T pimu = hamon::numbers::pi_fn<T>() * mu;
		T fact1 = (hamon::abs(pimu) < eps ? T(1) : pimu / hamon::sin(pimu));
		T d = -hamon::log(x2);
		T e = mu * d;
		T fact2 = (hamon::abs(e) < eps ? T(1) : hamon::sinh(e) / e);
		T gam1, gam2, gampl, gammi;
		hamon::detail::gamma_temme(mu, gam1, gam2, gampl, gammi);
		T ff = (T(2) / hamon::numbers::pi_fn<T>()) * fact1 * (gam1 * hamon::cosh(e) + gam2 * fact2 * d);
		e = hamon::exp(e);
		T p = e / (hamon::numbers::pi_fn<T>() * gampl);
		T q = T(1) / (e * hamon::numbers::pi_fn<T>() * gammi);
		const T pimu2 = pimu / T(2);
		T fact3 = (hamon::abs(pimu2) < eps ? T(1) : hamon::sin(pimu2) / pimu2);
		T r = hamon::numbers::pi_fn<T>() * pimu2 * fact3 * fact3;
		T c = T(1);
		d = -x2 * x2;
		T sum = ff + r * q;
		T sum1 = p;
		for (int i = 1; i <= max_iter; ++i)
		{
			ff = (i * ff + p + q) / (T(i) * T(i) - mu2);
			c *= d / T(i);
			p /= T(i) - mu;
			q /= T(i) + mu;
			const T del = c * (ff + r * q);
			sum += del;
			const T del1 = c * p - i * del;
			sum1 += del1;
			if (hamon::abs(del) < eps * (T(1) + hamon::abs(sum)))
			{
				break;
			}
		}
		//if (i > max_iter)
		//{
		//	hamon::detail::throw_runtime_error("Bessel y series failed to converge in bessel_jn.");
		//}
		Nmu = -sum;
		Nnu1 = -sum1 * xi2;
		Npmu = mu * xi * Nmu - Nnu1;
		Jmu = w / (Npmu - f * Nmu);
	}
	else
	{
		T a = T(0.25L) - mu2;
		T q = T(1);
		T p = -xi / T(2);
		T br = T(2) * x;
		T bi = T(2);
		T fact1 = a * xi / (p * p + q * q);
		T cr = br + q * fact1;
		T ci = bi + p * fact1;
		T den = br * br + bi * bi;
		T dr = br / den;
		T di = -bi / den;
		T dlr = cr * dr - ci * di;
		T dli = cr * di + ci * dr;
		T temp = p * dlr - q * dli;
		q = p * dli + q * dlr;
		p = temp;
		for (int i = 2; i <= max_iter; ++i)
		{
			a += (T(2) * (i - T(1)));
			bi += T(2);
			dr = a * dr + br;
			di = a * di + bi;
			if (hamon::abs(dr) + hamon::abs(di) < fp_min)
			{
				dr = fp_min;
			}
			fact1 = a / (cr * cr + ci * ci);
			cr = br + cr * fact1;
			ci = bi - ci * fact1;
			if (hamon::abs(cr) + hamon::abs(ci) < fp_min)
			{
				cr = fp_min;
			}
			den = dr * dr + di * di;
			dr /= den;
			di /= -den;
			dlr = cr * dr - ci * di;
			dli = cr * di + ci * dr;
			temp = p * dlr - q * dli;
			q = p * dli + q * dlr;
			p = temp;
			if (hamon::abs(dlr - T(1)) + hamon::abs(dli) < eps)
			{
				break;
			}
		}
		//if (i > max_iter)
		//{
		//	hamon::detail::throw_runtime_error("Lentz's method failed in bessel_jn.");
		//}
		const T gam = (p - f) / q;
		Jmu = hamon::sqrt(w / ((p - f) * gam + q));
		Jmu = hamon::copysign(Jmu, Jnul);
		Nmu = gam * Jmu;
		Npmu = (p + q / gam) * Nmu;
		Nnu1 = mu * xi * Nmu - Npmu;
	}
	fact = Jmu / Jnul;
	Jnu = fact * Jnul1;
	Jpnu = fact * Jpnu1;
	for (int i = 1; i <= nl; ++i)
	{
		const T Nnutemp = (mu + i) * xi2 * Nnu1 - Nmu;
		Nmu = Nnu1;
		Nnu1 = Nnutemp;
	}
	Nnu = Nmu;
	Npnu = nu * xi * Nmu - Nnu1;
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CMATH_DETAIL_BESSEL_JN_HPP
