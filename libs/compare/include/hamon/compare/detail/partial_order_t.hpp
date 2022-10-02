/**
 *	@file	partial_order_t.hpp
 *
 *	@brief	partial_order_t の定義
 */

#ifndef HAMON_COMPARE_DETAIL_PARTIAL_ORDER_T_HPP
#define HAMON_COMPARE_DETAIL_PARTIAL_ORDER_T_HPP

#include <hamon/compare/partial_ordering.hpp>
#include <hamon/compare/compare_three_way.hpp>
#include <hamon/compare/detail/weak_order_t.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/decay.hpp>
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

#if defined(HAMON_MSVC) && (HAMON_MSVC < 1920)
template <typename T, typename U>
void partial_order(T&&, U&&);
#else
template <typename T, typename U>
void partial_order(T&&, U&&) = delete;
#endif

class partial_order_t
{
private:
	friend class partial_fallback_t;

private:
	// partial_ordering(partial_order(e, f))
	template <typename T, typename U>
	static HAMON_CONSTEXPR auto
	impl(T&& e, U&& f, hamon::detail::overload_priority<2>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::partial_ordering(partial_order(std::forward<T>(e), std::forward<U>(f))))

#if defined(HAMON_HAS_STD_COMPARE) && defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	// partial_ordering(e <=> f)
	template <typename T, typename U>
	static HAMON_CONSTEXPR auto
	impl(T&& e, U&& f, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::partial_ordering(hamon::compare_three_way()(std::forward<T>(e), std::forward<U>(f))))
#endif

	// partial_ordering(weak_order(e, f))
	template <typename T, typename U>
	static HAMON_CONSTEXPR auto
	impl(T&& e, U&& f, hamon::detail::overload_priority<0>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::partial_ordering(detail::weak_order_t{}(std::forward<T>(e), std::forward<U>(f))))

public:
	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& e, U&& f) const
		HAMON_NOEXCEPT_IF_EXPR(impl(std::forward<T>(e), std::forward<U>(f), hamon::detail::overload_priority<2>{}))
	->decltype((impl(std::forward<T>(e), std::forward<U>(f), hamon::detail::overload_priority<2>{})))
	{
		static_assert(hamon::same_as_t<hamon::decay_t<T>, hamon::decay_t<U>>::value, "");

		return impl(std::forward<T>(e), std::forward<U>(f), hamon::detail::overload_priority<2>{});
	}
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_PARTIAL_ORDER_T_HPP
