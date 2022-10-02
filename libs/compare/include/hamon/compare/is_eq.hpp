/**
 *	@file	is_eq.hpp
 *
 *	@brief	is_eq の定義
 */

#ifndef HAMON_COMPARE_IS_EQ_HPP
#define HAMON_COMPARE_IS_EQ_HPP

#include <hamon/compare/config.hpp>

#if defined(HAMON_USE_STD_COMPARE)

#include <compare>

namespace hamon
{

using std::is_eq;

}	// namespace hamon

#else

#include <hamon/compare/partial_ordering.hpp>
#include <hamon/config.hpp>

namespace hamon
{

HAMON_CONSTEXPR bool
is_eq(hamon::partial_ordering cmp) HAMON_NOEXCEPT
{
	return cmp == 0;
}

}	// namespace hamon

#endif

#endif // HAMON_COMPARE_IS_EQ_HPP
