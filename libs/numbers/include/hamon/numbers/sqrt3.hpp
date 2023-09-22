/**
 *	@file	sqrt3.hpp
 *
 *	@brief	3の平方根√3
 */

#ifndef HAMON_NUMBERS_SQRT3_HPP
#define HAMON_NUMBERS_SQRT3_HPP

#include <hamon/numbers/config.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

#if defined(HAMON_USE_STD_NUMBERS)

using std::numbers::sqrt3_v;
using std::numbers::sqrt3;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T sqrt3_fn() HAMON_NOEXCEPT
{
	return std::numbers::sqrt3_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T sqrt3_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(1.732050807568877293527446341505872367L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T sqrt3_v = sqrt3_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double sqrt3 = sqrt3_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_SQRT3_HPP
