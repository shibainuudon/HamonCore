/**
 *	@file	pi.hpp
 *
 *	@brief	円周率π
 */

#ifndef HAMON_NUMBERS_PI_HPP
#define HAMON_NUMBERS_PI_HPP

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

using std::numbers::pi_v;
using std::numbers::pi;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T pi_fn() HAMON_NOEXCEPT
{
	return std::numbers::pi_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T pi_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(3.141592653589793238462643383279502884L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T pi_v = pi_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double pi = pi_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_PI_HPP
