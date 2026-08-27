/**
 *	@file	log10e.hpp
 *
 *	@brief	eに対する10を底とする対数log10(e)
 */

#ifndef HAMON_NUMBERS_LOG10E_HPP
#define HAMON_NUMBERS_LOG10E_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T log10e_v = static_cast<T>(0.434294481903251827651128918916605082L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double log10e = log10e_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_LOG10E_HPP
