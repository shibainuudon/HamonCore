/**
 *	@file	ln10.hpp
 *
 *	@brief	10の自然対数log(10)
 */

#ifndef HAMON_NUMBERS_LN10_HPP
#define HAMON_NUMBERS_LN10_HPP

#include <hamon/numbers/config.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

#if defined(HAMON_USE_STD_NUMBERS)

using std::numbers::ln10_v;
using std::numbers::ln10;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T ln10_fn() HAMON_NOEXCEPT
{
	return std::numbers::ln10_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T ln10_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(2.302585092994045684017991454684364208L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T ln10_v = ln10_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double ln10 = ln10_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_LN10_HPP
