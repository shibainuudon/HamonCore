/**
 *	@file	gamma_temme.hpp
 *
 *	@brief	gamma_temme 関数の実装
 */

#ifndef HAMON_CMATH_DETAIL_GAMMA_TEMME_HPP
#define HAMON_CMATH_DETAIL_GAMMA_TEMME_HPP

#include <hamon/cmath/tgamma.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/numbers/egamma.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR void
gamma_temme(T mu, T& gam1, T& gam2, T& gampl, T& gammi)
{
	gampl = T(1) / hamon::tgamma(T(1) + mu);
	gammi = T(1) / hamon::tgamma(T(1) - mu);

	if (hamon::abs(mu) < hamon::numeric_limits<T>::epsilon())
	{
		gam1 = -T(hamon::numbers::egamma_fn<T>());
	}
	else
	{
		gam1 = (gammi - gampl) / (T(2) * mu);
	}

	gam2 = (gammi + gampl) / (T(2));

	return;
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CMATH_DETAIL_GAMMA_TEMME_HPP
