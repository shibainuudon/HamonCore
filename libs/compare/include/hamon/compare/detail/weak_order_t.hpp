/**
 *	@file	weak_order_t.hpp
 *
 *	@brief	weak_order_t の定義
 */

#ifndef HAMON_COMPARE_DETAIL_WEAK_ORDER_T_HPP
#define HAMON_COMPARE_DETAIL_WEAK_ORDER_T_HPP

#include <hamon/compare/weak_ordering.hpp>
#include <hamon/compare/compare_three_way.hpp>
#include <hamon/compare/detail/strong_order_t.hpp>
#include <hamon/compare/detail/fp_weak_ordering.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
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
void weak_order(T&&, U&&);
#else
template <typename T, typename U>
void weak_order(T&&, U&&) = delete;
#endif

class weak_order_t
{
private:
	friend class partial_order_t;
	friend class weak_fallback_t;

private:
	// weak_ordering(weak_order(e, f))
	template <typename T, typename U>
	static HAMON_CONSTEXPR auto
	impl(T&& e, U&& f, hamon::detail::overload_priority<3>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::weak_ordering(weak_order(hamon::forward<T>(e), hamon::forward<U>(f))))

	// floating_point
	template <typename T, typename U,
		typename = hamon::enable_if_t<hamon::is_floating_point<hamon::decay_t<T>>::value>>
	static HAMON_CONSTEXPR hamon::weak_ordering
	impl(T&& e, U&& f, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT
	{
		return detail::fp_weak_ordering(e, f);
	}

#if defined(HAMON_HAS_STD_COMPARE) && defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	// weak_ordering(e <=> f)
	template <typename T, typename U>
	static HAMON_CONSTEXPR auto
	impl(T&& e, U&& f, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::weak_ordering(hamon::compare_three_way()(hamon::forward<T>(e), hamon::forward<U>(f))))
#endif

	// weak_ordering(strong_order(e, f))
	template <typename T, typename U>
	static HAMON_CONSTEXPR auto
	impl(T&& e, U&& f, hamon::detail::overload_priority<0>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::weak_ordering(detail::strong_order_t{}(hamon::forward<T>(e), hamon::forward<U>(f))))

public:
	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& e, U&& f) const
		HAMON_NOEXCEPT_IF_EXPR(impl(hamon::forward<T>(e), hamon::forward<U>(f), hamon::detail::overload_priority<3>{}))
	->decltype((impl(hamon::forward<T>(e), hamon::forward<U>(f), hamon::detail::overload_priority<3>{})))
	{
		static_assert(hamon::same_as_t<hamon::decay_t<T>, hamon::decay_t<U>>::value, "");

		return impl(hamon::forward<T>(e), hamon::forward<U>(f), hamon::detail::overload_priority<3>{});
	}
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_WEAK_ORDER_T_HPP
