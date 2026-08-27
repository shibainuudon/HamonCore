/**
 *	@file	log2e.hpp
 *
 *	@brief	eに対する2を底とする対数log2(e)
 */

#ifndef HAMON_NUMBERS_LOG2E_HPP
#define HAMON_NUMBERS_LOG2E_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T log2e_v = static_cast<T>(1.442695040888963407359924681001892137L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double log2e = log2e_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_LOG2E_HPP
