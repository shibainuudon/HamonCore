/**
 *	@file	egamma.hpp
 *
 *	@brief	オイラー定数 γ
 */

#ifndef HAMON_NUMBERS_EGAMMA_HPP
#define HAMON_NUMBERS_EGAMMA_HPP

#include <hamon/numbers/config.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

#if defined(HAMON_USE_STD_NUMBERS)

using std::numbers::egamma_v;
using std::numbers::egamma;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T egamma_fn() HAMON_NOEXCEPT
{
	return std::numbers::egamma_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T egamma_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(0.577215664901532860606512090082402431L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T egamma_v = egamma_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double egamma = egamma_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_EGAMMA_HPP
