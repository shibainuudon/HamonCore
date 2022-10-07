/**
 *	@file	ln2.hpp
 *
 *	@brief	2の自然対数log(2)
 */

#ifndef HAMON_NUMBERS_LN2_HPP
#define HAMON_NUMBERS_LN2_HPP

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

using std::numbers::ln2_v;
using std::numbers::ln2;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T ln2_fn() HAMON_NOEXCEPT
{
	return std::numbers::ln2_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T ln2_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(0.693147180559945309417232121458176568L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T ln2_v = ln2_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double ln2 = ln2_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_LN2_HPP
