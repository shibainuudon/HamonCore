/**
 *	@file	log10e.hpp
 *
 *	@brief	eに対する10を底とする対数log10(e)
 */

#ifndef HAMON_NUMBERS_LOG10E_HPP
#define HAMON_NUMBERS_LOG10E_HPP

#include <hamon/numbers/config.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

#if defined(HAMON_USE_STD_NUMBERS)

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
