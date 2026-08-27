/**
 *	@file	sqrt2.hpp
 *
 *	@brief	2の平方根√2
 */

#ifndef HAMON_NUMBERS_SQRT2_HPP
#define HAMON_NUMBERS_SQRT2_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T sqrt2_v = static_cast<T>(1.414213562373095048801688724209698079L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double sqrt2 = sqrt2_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_SQRT2_HPP
