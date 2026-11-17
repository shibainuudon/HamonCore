/**
 *	@file	is_lteq.hpp
 *
 *	@brief	is_lteq の定義
 */

#ifndef HAMON_COMPARE_IS_LTEQ_HPP
#define HAMON_COMPARE_IS_LTEQ_HPP

#include <hamon/compare/partial_ordering.hpp>
#include <hamon/config.hpp>

namespace hamon
{

HAMON_CONSTEXPR bool
is_lteq(hamon::partial_ordering cmp) HAMON_NOEXCEPT
{
	return cmp <= 0;
}

}	// namespace hamon

#endif // HAMON_COMPARE_IS_LTEQ_HPP
