/**
 *	@file	partial_order.hpp
 *
 *	@brief	partial_order の定義
 */

#ifndef HAMON_COMPARE_PARTIAL_ORDER_HPP
#define HAMON_COMPARE_PARTIAL_ORDER_HPP

#include <hamon/compare/detail/partial_order_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

inline namespace compare_cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::partial_order_t partial_order{};

}	// inline namespace compare_cpo

}	// namespace hamon

#endif // HAMON_COMPARE_PARTIAL_ORDER_HPP
