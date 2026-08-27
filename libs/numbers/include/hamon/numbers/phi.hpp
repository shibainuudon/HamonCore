/**
 *	@file	phi.hpp
 *
 *	@brief	黄金比φ
 */

#ifndef HAMON_NUMBERS_PHI_HPP
#define HAMON_NUMBERS_PHI_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T phi_v = static_cast<T>(1.618033988749894848204586834365638118L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double phi = phi_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_PHI_HPP
