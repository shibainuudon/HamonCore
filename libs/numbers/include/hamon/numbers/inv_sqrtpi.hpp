/**
 *	@file	inv_sqrtpi.hpp
 *
 *	@brief	円周率の平方根の逆数1/√π
 */

#ifndef HAMON_NUMBERS_INV_SQRTPI_HPP
#define HAMON_NUMBERS_INV_SQRTPI_HPP

#include <hamon/numbers/config.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

#if defined(HAMON_USE_STD_NUMBERS)

using std::numbers::inv_sqrtpi_v;
using std::numbers::inv_sqrtpi;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T inv_sqrtpi_fn() HAMON_NOEXCEPT
{
	return std::numbers::inv_sqrtpi_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T inv_sqrtpi_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(0.564189583547756286948079451560772586L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T inv_sqrtpi_v = inv_sqrtpi_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double inv_sqrtpi = inv_sqrtpi_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_INV_SQRTPI_HPP
