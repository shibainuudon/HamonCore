/**
 *	@file	weak_fallback_t.hpp
 *
 *	@brief	weak_fallback_t の定義
 */

#ifndef HAMON_COMPARE_DETAIL_WEAK_FALLBACK_T_HPP
#define HAMON_COMPARE_DETAIL_WEAK_FALLBACK_T_HPP

#include <hamon/compare/weak_ordering.hpp>
#include <hamon/compare/detail/weak_order_t.hpp>
#include <hamon/compare/detail/op_eq_lt.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/forward.hpp>
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

class weak_fallback_t
{
private:
	// weak_order(e, f)
	template <typename T, typename U>
	static HAMON_CONSTEXPR auto
	impl(T&& e, U&& f, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		detail::weak_order_t{}(hamon::forward<T>(e), hamon::forward<U>(f)))

	// e == f, e < f
	template <typename T, typename U,
		typename = hamon::enable_if_t<detail::op_eq_lt<T, U>::value>
	>
	static HAMON_CONSTEXPR hamon::weak_ordering
	impl(T&& e, U&& f, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_IF(
			HAMON_NOEXCEPT_EXPR(bool(std::declval<T>() == std::declval<U>())) &&
			HAMON_NOEXCEPT_EXPR(bool(std::declval<T>() <  std::declval<U>())))
	{
		return
			hamon::forward<T>(e) == hamon::forward<U>(f) ? hamon::weak_ordering::equivalent :
			hamon::forward<T>(e) <  hamon::forward<U>(f) ? hamon::weak_ordering::less       :
				                                       hamon::weak_ordering::greater;
	}

public:
	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& e, U&& f) const
		HAMON_NOEXCEPT_IF_EXPR(impl(hamon::forward<T>(e), hamon::forward<U>(f), hamon::detail::overload_priority<1>{}))
	->decltype((impl(hamon::forward<T>(e), hamon::forward<U>(f), hamon::detail::overload_priority<1>{})))
	{
		static_assert(hamon::same_as_t<hamon::decay_t<T>, hamon::decay_t<U>>::value, "");

		return impl(hamon::forward<T>(e), hamon::forward<U>(f), hamon::detail::overload_priority<1>{});
	}
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_WEAK_FALLBACK_T_HPP
