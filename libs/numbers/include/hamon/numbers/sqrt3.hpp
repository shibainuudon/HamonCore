/**
 *	@file	sqrt3.hpp
 *
 *	@brief	3の平方根√3
 */

#ifndef HAMON_NUMBERS_SQRT3_HPP
#define HAMON_NUMBERS_SQRT3_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T sqrt3_v = static_cast<T>(1.732050807568877293527446341505872367L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double sqrt3 = sqrt3_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_SQRT3_HPP
