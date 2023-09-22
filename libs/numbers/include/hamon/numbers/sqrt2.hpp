/**
 *	@file	sqrt2.hpp
 *
 *	@brief	2の平方根√2
 */

#ifndef HAMON_NUMBERS_SQRT2_HPP
#define HAMON_NUMBERS_SQRT2_HPP

#include <hamon/numbers/config.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

#if defined(HAMON_USE_STD_NUMBERS)

using std::numbers::sqrt2_v;
using std::numbers::sqrt2;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T sqrt2_fn() HAMON_NOEXCEPT
{
	return std::numbers::sqrt2_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T sqrt2_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(1.414213562373095048801688724209698079L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T sqrt2_v = sqrt2_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double sqrt2 = sqrt2_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_SQRT2_HPP
