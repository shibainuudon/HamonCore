/**
 *	@file	log2e.hpp
 *
 *	@brief	eに対する2を底とする対数log2(e)
 */

#ifndef HAMON_NUMBERS_LOG2E_HPP
#define HAMON_NUMBERS_LOG2E_HPP

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

using std::numbers::log2e_v;
using std::numbers::log2e;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T log2e_fn() HAMON_NOEXCEPT
{
	return std::numbers::log2e_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T log2e_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(1.442695040888963407359924681001892137L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T log2e_v = log2e_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double log2e = log2e_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_LOG2E_HPP
