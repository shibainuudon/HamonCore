/**
 *	@file	sph_bessel_jn.hpp
 *
 *	@brief	sph_bessel_jn 関数の実装
 */

#ifndef HAMON_CMATH_DETAIL_SPH_BESSEL_JN_HPP
#define HAMON_CMATH_DETAIL_SPH_BESSEL_JN_HPP

#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/detail/bessel_jn.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR void
sph_bessel_jn(unsigned int n, T x, T& j_n, T& n_n, T& jp_n, T& np_n)
{
	const T nu = T(n) + T(0.5L);

	T J_nu, N_nu, Jp_nu, Np_nu;
	hamon::detail::bessel_jn(nu, x, J_nu, N_nu, Jp_nu, Np_nu);

	const T factor = hamon::sqrt(hamon::numbers::pi_fn<T>() / 2) / hamon::sqrt(x);

	j_n = factor * J_nu;
	n_n = factor * N_nu;
	jp_n = factor * Jp_nu - j_n / (T(2) * x);
	np_n = factor * Np_nu - n_n / (T(2) * x);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CMATH_DETAIL_SPH_BESSEL_JN_HPP
