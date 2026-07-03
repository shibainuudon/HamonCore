/**
 *	@file	iszero.hpp
 *
 *	@brief	iszero
 */

#ifndef HAMON_CMATH_ISZERO_HPP
#define HAMON_CMATH_ISZERO_HPP

#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief
 */
template <HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
iszero(Arithmetic arg) HAMON_NOEXCEPT
{
	return arg == Arithmetic(0);
}

}	// namespace hamon

#endif // HAMON_CMATH_ISZERO_HPP
