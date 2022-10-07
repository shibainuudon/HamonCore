/**
 *	@file	inv_sqrt3.hpp
 *
 *	@brief	3の平方根の逆数1/√3
 */

#ifndef HAMON_NUMBERS_INV_SQRT3_HPP
#define HAMON_NUMBERS_INV_SQRT3_HPP

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

using std::numbers::inv_sqrt3_v;
using std::numbers::inv_sqrt3;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T inv_sqrt3_fn() HAMON_NOEXCEPT
{
	return std::numbers::inv_sqrt3_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T inv_sqrt3_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(0.577350269189625764509148780501957456L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T inv_sqrt3_v = inv_sqrt3_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double inv_sqrt3 = inv_sqrt3_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_INV_SQRT3_HPP
