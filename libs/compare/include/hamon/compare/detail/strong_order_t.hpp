/**
 *	@file	strong_order_t.hpp
 *
 *	@brief	strong_order_t の定義
 */

#ifndef HAMON_COMPARE_DETAIL_STRONG_ORDER_T_HPP
#define HAMON_COMPARE_DETAIL_STRONG_ORDER_T_HPP

#include <hamon/compare/strong_ordering.hpp>
#include <hamon/compare/compare_three_way.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype((__VA_ARGS__))              \
	{ return __VA_ARGS__; }

#if defined(HAMON_MSVC) && (HAMON_MSVC < 1920)
template <typename T, typename U>
void strong_order(T&&, U&&);
#else
template <typename T, typename U>
void strong_order(T&&, U&&) = delete;
#endif

class strong_order_t
{
private:
	friend class weak_order_t;
	friend class strong_fallback_t;

private:
	// strong_ordering(strong_order(e, f))
	template <typename T, typename U>
	static HAMON_CONSTEXPR auto
	impl(T&& e, U&& f, hamon::detail::overload_priority<2>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::strong_ordering(strong_order(hamon::forward<T>(e), hamon::forward<U>(f))))

#if 0
	// floating_point
	template <typename T, typename U>
	requires hamon::floating_point<hamon::decay_t<T>>
	static HAMON_CONSTEXPR hamon::strong_ordering
	impl(T&& e, U&& f, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT
	{
		// 未実装
		return detail::fp_strong_order(e, f);
	}
#endif

#if defined(HAMON_HAS_STD_COMPARE) && defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	// strong_ordering(e <=> f)
	template <typename T, typename U>
	static HAMON_CONSTEXPR auto
	impl(T&& e, U&& f, hamon::detail::overload_priority<0>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::strong_ordering(hamon::compare_three_way()(hamon::forward<T>(e), hamon::forward<U>(f))))
#endif

public:
	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& e, U&& f) const
		HAMON_NOEXCEPT_IF_EXPR(impl(hamon::forward<T>(e), hamon::forward<U>(f), hamon::detail::overload_priority<2>{}))
	->decltype((impl(hamon::forward<T>(e), hamon::forward<U>(f), hamon::detail::overload_priority<2>{})))
	{
		static_assert(hamon::same_as_t<hamon::decay_t<T>, hamon::decay_t<U>>::value, "");

		return impl(hamon::forward<T>(e), hamon::forward<U>(f), hamon::detail::overload_priority<2>{});
	}
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_STRONG_ORDER_T_HPP
