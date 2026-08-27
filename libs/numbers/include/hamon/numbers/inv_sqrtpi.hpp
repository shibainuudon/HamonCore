/**
 *	@file	inv_sqrtpi.hpp
 *
 *	@brief	円周率の平方根の逆数1/√π
 */

#ifndef HAMON_NUMBERS_INV_SQRTPI_HPP
#define HAMON_NUMBERS_INV_SQRTPI_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T inv_sqrtpi_v = static_cast<T>(0.564189583547756286948079451560772586L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double inv_sqrtpi = inv_sqrtpi_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_INV_SQRTPI_HPP
