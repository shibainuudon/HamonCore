/**
 *	@file	e.hpp
 *
 *	@brief	ネイピア数e
 */

#ifndef HAMON_NUMBERS_E_HPP
#define HAMON_NUMBERS_E_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T e_v = static_cast<T>(2.718281828459045235360287471352662498L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double e = e_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_E_HPP
