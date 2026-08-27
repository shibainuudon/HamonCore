/**
 *	@file	inv_pi.hpp
 *
 *	@brief	円周率の逆数1/π
 */

#ifndef HAMON_NUMBERS_INV_PI_HPP
#define HAMON_NUMBERS_INV_PI_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T inv_pi_v = static_cast<T>(0.318309886183790671537767526745028724L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double inv_pi = inv_pi_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_INV_PI_HPP
