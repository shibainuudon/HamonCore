/**
 *	@file	ln2.hpp
 *
 *	@brief	2の自然対数log(2)
 */

#ifndef HAMON_NUMBERS_LN2_HPP
#define HAMON_NUMBERS_LN2_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T ln2_v = static_cast<T>(0.693147180559945309417232121458176568L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double ln2 = ln2_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_LN2_HPP
