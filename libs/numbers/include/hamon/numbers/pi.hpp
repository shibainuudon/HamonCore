/**
 *	@file	pi.hpp
 *
 *	@brief	円周率π
 */

#ifndef HAMON_NUMBERS_PI_HPP
#define HAMON_NUMBERS_PI_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T pi_v = static_cast<T>(3.141592653589793238462643383279502884L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double pi = pi_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_PI_HPP
