/**
 *	@file	is_gteq.hpp
 *
 *	@brief	is_gteq の定義
 */

#ifndef HAMON_COMPARE_IS_GTEQ_HPP
#define HAMON_COMPARE_IS_GTEQ_HPP

#include <hamon/compare/partial_ordering.hpp>
#include <hamon/config.hpp>

namespace hamon
{

HAMON_CONSTEXPR bool
is_gteq(hamon::partial_ordering cmp) HAMON_NOEXCEPT
{
	return cmp >= 0;
}

}	// namespace hamon

#endif // HAMON_COMPARE_IS_GTEQ_HPP
