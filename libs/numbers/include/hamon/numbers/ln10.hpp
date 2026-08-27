/**
 *	@file	ln10.hpp
 *
 *	@brief	10の自然対数log(10)
 */

#ifndef HAMON_NUMBERS_LN10_HPP
#define HAMON_NUMBERS_LN10_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T ln10_v = static_cast<T>(2.302585092994045684017991454684364208L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double ln10 = ln10_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_LN10_HPP
