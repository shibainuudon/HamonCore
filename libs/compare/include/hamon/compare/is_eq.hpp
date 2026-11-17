/**
 *	@file	is_eq.hpp
 *
 *	@brief	is_eq の定義
 */

#ifndef HAMON_COMPARE_IS_EQ_HPP
#define HAMON_COMPARE_IS_EQ_HPP

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

#endif // HAMON_COMPARE_IS_EQ_HPP
