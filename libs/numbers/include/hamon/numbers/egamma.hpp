/**
 *	@file	egamma.hpp
 *
 *	@brief	オイラー定数 γ
 */

#ifndef HAMON_NUMBERS_EGAMMA_HPP
#define HAMON_NUMBERS_EGAMMA_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace numbers
{

template <HAMON_CONSTRAINT(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T egamma_v = static_cast<T>(0.577215664901532860606512090082402431L);

HAMON_INLINE_VAR HAMON_CONSTEXPR double egamma = egamma_v<double>;

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_EGAMMA_HPP
