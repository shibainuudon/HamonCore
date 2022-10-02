/**
 *	@file	strong_order.hpp
 *
 *	@brief	strong_order の定義
 */

#ifndef HAMON_COMPARE_STRONG_ORDER_HPP
#define HAMON_COMPARE_STRONG_ORDER_HPP

#include <hamon/compare/config.hpp>

#if defined(HAMON_USE_STD_COMPARE)

#include <compare>

namespace hamon
{

using std::strong_order;

}	// namespace hamon

#else

#include <hamon/compare/detail/strong_order_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

inline namespace compare_cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::strong_order_t strong_order{};

}	// inline namespace compare_cpo

}	// namespace hamon

#endif

#endif // HAMON_COMPARE_STRONG_ORDER_HPP
