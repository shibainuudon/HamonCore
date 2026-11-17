/**
 *	@file	compare_strong_order_fallback.hpp
 *
 *	@brief	compare_strong_order_fallback の定義
 */

#ifndef HAMON_COMPARE_COMPARE_STRONG_ORDER_FALLBACK_HPP
#define HAMON_COMPARE_COMPARE_STRONG_ORDER_FALLBACK_HPP

#include <hamon/compare/detail/strong_fallback_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

inline namespace compare_cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::strong_fallback_t compare_strong_order_fallback{};

}	// inline namespace compare_cpo

}	// namespace hamon

#endif // HAMON_COMPARE_COMPARE_STRONG_ORDER_FALLBACK_HPP
