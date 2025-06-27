/**
 *	@file	ratio_greater.hpp
 *
 *	@brief	ratio_greater の定義
 */

#ifndef HAMON_RATIO_RATIO_GREATER_HPP
#define HAMON_RATIO_RATIO_GREATER_HPP

#include <hamon/ratio/config.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_USE_STD_RATIO)

#include <ratio>

namespace hamon
{

using std::ratio_greater;

}	// namespace hamon

#else

namespace hamon
{

// TODO

}	// namespace hamon

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

namespace hamon
{

template <typename R1, typename R2>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool ratio_greater_v = hamon::ratio_greater<R1, R2>::value;

}	// namespace hamon

#endif

#endif // HAMON_RATIO_RATIO_GREATER_HPP
