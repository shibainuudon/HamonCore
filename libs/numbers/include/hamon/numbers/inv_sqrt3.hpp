/**
 *	@file	inv_sqrt3.hpp
 *
 *	@brief	3の平方根の逆数1/√3
 */

#ifndef HAMON_NUMBERS_INV_SQRT3_HPP
#define HAMON_NUMBERS_INV_SQRT3_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T inv_sqrt3_v = static_cast<T>(0.577350269189625764509148780501957456L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double inv_sqrt3 = inv_sqrt3_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_INV_SQRT3_HPP
