/**
 *	@file	compare_weak_order_fallback.hpp
 *
 *	@brief	compare_weak_order_fallback の定義
 */

#ifndef HAMON_COMPARE_COMPARE_WEAK_ORDER_FALLBACK_HPP
#define HAMON_COMPARE_COMPARE_WEAK_ORDER_FALLBACK_HPP

#include <hamon/compare/config.hpp>

#if defined(HAMON_USE_STD_COMPARE)

#include <compare>

namespace hamon
{

using std::compare_weak_order_fallback;

}	// namespace hamon

#else

#include <hamon/compare/detail/weak_fallback_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

inline namespace compare_cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::weak_fallback_t compare_weak_order_fallback{};

}	// inline namespace compare_cpo

}	// namespace hamon

#endif

#endif // HAMON_COMPARE_COMPARE_WEAK_ORDER_FALLBACK_HPP
