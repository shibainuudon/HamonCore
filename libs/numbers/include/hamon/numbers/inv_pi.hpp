/**
 *	@file	inv_pi.hpp
 *
 *	@brief	円周率の逆数1/π
 */

#ifndef HAMON_NUMBERS_INV_PI_HPP
#define HAMON_NUMBERS_INV_PI_HPP

#include <hamon/numbers/config.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

#if defined(HAMON_USE_STD_NUMBERS)

using std::numbers::inv_pi_v;
using std::numbers::inv_pi;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T inv_pi_fn() HAMON_NOEXCEPT
{
	return std::numbers::inv_pi_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T inv_pi_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(0.318309886183790671537767526745028724L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T inv_pi_v = inv_pi_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double inv_pi = inv_pi_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_INV_PI_HPP
