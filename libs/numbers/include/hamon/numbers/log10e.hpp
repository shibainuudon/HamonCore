/**
 *	@file	log10e.hpp
 *
 *	@brief	eに対する10を底とする対数log10(e)
 */

#ifndef HAMON_NUMBERS_LOG10E_HPP
#define HAMON_NUMBERS_LOG10E_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#if HAMON_HAS_INCLUDE(<numbers>) && (HAMON_CXX_STANDARD >= 20)
#include <numbers>
#endif

namespace hamon
{
namespace numbers
{

#if defined(__cpp_lib_math_constants) && (__cpp_lib_math_constants >= 201907L)

using std::numbers::log10e_v;
using std::numbers::log10e;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T log10e_fn() HAMON_NOEXCEPT
{
	return std::numbers::log10e_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T log10e_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(0.434294481903251827651128918916605082L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T log10e_v = log10e_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double log10e = log10e_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_LOG10E_HPP
