/**
 *	@file	phi.hpp
 *
 *	@brief	黄金比φ
 */

#ifndef HAMON_NUMBERS_PHI_HPP
#define HAMON_NUMBERS_PHI_HPP

#include <hamon/numbers/config.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

#if defined(HAMON_USE_STD_NUMBERS)

using std::numbers::phi_v;
using std::numbers::phi;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T phi_fn() HAMON_NOEXCEPT
{
	return std::numbers::phi_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T phi_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(1.618033988749894848204586834365638118L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T phi_v = phi_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double phi = phi_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_PHI_HPP
