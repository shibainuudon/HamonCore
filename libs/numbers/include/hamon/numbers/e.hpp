/**
 *	@file	e.hpp
 *
 *	@brief	ネイピア数e
 */

#ifndef HAMON_NUMBERS_E_HPP
#define HAMON_NUMBERS_E_HPP

#include <hamon/numbers/config.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

#if defined(HAMON_USE_STD_NUMBERS)

using std::numbers::e_v;
using std::numbers::e;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T e_fn() HAMON_NOEXCEPT
{
	return std::numbers::e_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T e_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(2.718281828459045235360287471352662498L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T e_v = e_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double e = e_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_E_HPP
