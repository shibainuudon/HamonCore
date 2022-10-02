﻿/**
 *	@file	partial_fallback_t.hpp
 *
 *	@brief	partial_fallback_t の定義
 */

#ifndef HAMON_COMPARE_DETAIL_PARTIAL_FALLBACK_T_HPP
#define HAMON_COMPARE_DETAIL_PARTIAL_FALLBACK_T_HPP

#include <hamon/compare/partial_ordering.hpp>
#include <hamon/compare/detail/partial_order_t.hpp>
#include <hamon/compare/detail/op_eq_lt.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype((__VA_ARGS__))              \
	{ return __VA_ARGS__; }

class partial_fallback_t
{
private:
	// partial_order(e, f)
	template <typename T, typename U>
	static HAMON_CONSTEXPR auto
	impl(T&& e, U&& f, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		detail::partial_order_t{}(std::forward<T>(e), std::forward<U>(f)))

	// e == f, e < f
	template <typename T, typename U,
		typename = hamon::enable_if_t<detail::op_eq_lt<T, U>::value>
	>
	static HAMON_CONSTEXPR hamon::partial_ordering
	impl(T&& e, U&& f, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_IF(
			HAMON_NOEXCEPT_EXPR(bool(std::declval<T>() == std::declval<U>())) &&
			HAMON_NOEXCEPT_EXPR(bool(std::declval<T>() <  std::declval<U>())))
	{
		return
			std::forward<T>(e) == std::forward<U>(f) ? hamon::partial_ordering::equivalent :
			std::forward<T>(e) <  std::forward<U>(f) ? hamon::partial_ordering::less       :
			std::forward<U>(f) <  std::forward<T>(e) ? hamon::partial_ordering::greater    :
				                                       hamon::partial_ordering::unordered;
	}

public:
	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& e, U&& f) const
		HAMON_NOEXCEPT_IF_EXPR(impl(std::forward<T>(e), std::forward<U>(f), hamon::detail::overload_priority<1>{}))
	->decltype((impl(std::forward<T>(e), std::forward<U>(f), hamon::detail::overload_priority<1>{})))
	{
		static_assert(hamon::same_as_t<hamon::decay_t<T>, hamon::decay_t<U>>::value, "");

		return impl(std::forward<T>(e), std::forward<U>(f), hamon::detail::overload_priority<1>{});
	}
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_PARTIAL_FALLBACK_T_HPP