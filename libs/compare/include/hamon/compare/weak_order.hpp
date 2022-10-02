/**
 *	@file	weak_order.hpp
 *
 *	@brief	weak_order の定義
 */

#ifndef HAMON_COMPARE_WEAK_ORDER_HPP
#define HAMON_COMPARE_WEAK_ORDER_HPP

#include <hamon/compare/config.hpp>

#if defined(HAMON_USE_STD_COMPARE)

#include <compare>

namespace hamon
{

using std::weak_order;

}	// namespace hamon

#else

#include <hamon/compare/detail/weak_order_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

inline namespace compare_cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::weak_order_t weak_order{};

}	// inline namespace compare_cpo

}	// namespace hamon

#endif

#endif // HAMON_COMPARE_WEAK_ORDER_HPP
