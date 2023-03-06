/**
 *	@file	swap.hpp
 *
 *	@brief	swap の定義
 */

#ifndef HAMON_CONCEPTS_SWAP_HPP
#define HAMON_CONCEPTS_SWAP_HPP

#include <hamon/concepts/config.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{
namespace ranges
{

using std::ranges::swap;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/detail/has_adl_swap.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <type_traits>
#include <utility>

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace hamon
{

namespace ranges
{

namespace swap_detail
{

struct swap_fn
{
private:
	template <
		typename T, typename U
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<
			has_adl_swap<T, U>::value
		>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires has_adl_swap<T, U>
#endif
	static HAMON_CXX14_CONSTEXPR auto
	impl(hamon::detail::overload_priority<2>, T&& t, U&& u)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(swap(std::forward<T>(t), std::forward<U>(u)))

	template <
		typename T, typename U, std::size_t N
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = decltype(std::declval<swap_fn const&>()(std::declval<T&>(), std::declval<U&>()))
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires requires(const swap_fn& fn, T& t, U& u)
	{
		fn(t, u);
	}
#endif
	static HAMON_CXX14_CONSTEXPR void
	impl(hamon::detail::overload_priority<1>, T (&t)[N], U (&u)[N])
		HAMON_NOEXCEPT_IF_EXPR(std::declval<swap_fn const&>()(*t, *u))
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			swap_fn{}(t[i], u[i]);
		}
	}

	template <
		typename T, typename U
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<
			hamon::same_as<T, U>::value &&
			hamon::is_lvalue_reference<T>::value &&
			hamon::move_constructible<hamon::remove_reference_t<T>>::value &&
			hamon::assignable_from<T, hamon::remove_reference_t<T>>::value
		>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires
		same_as<T, U> &&
		hamon::is_lvalue_reference<T>::value &&
		move_constructible<hamon::remove_reference_t<T>> &&
		assignable_from<T, hamon::remove_reference_t<T>>
#endif
	static HAMON_CXX14_CONSTEXPR void
	impl(hamon::detail::overload_priority<0>, T&& t, U&& u)
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_move_constructible<hamon::remove_reference_t<T>>::value &&
			std::is_nothrow_move_assignable<hamon::remove_reference_t<T>>::value)
	{
		auto tmp = static_cast<hamon::remove_reference_t<T>&&>(t);
		t = static_cast<hamon::remove_reference_t<T>&&>(u);
		u = static_cast<hamon::remove_reference_t<T>&&>(tmp);
	}

public:
	template <typename T, typename U>
	HAMON_CXX14_CONSTEXPR auto operator()(T&& t, U&& u) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::detail::overload_priority<2>{}, std::forward<T>(t), std::forward<U>(u)))
};

}	// namespace swap_detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR swap_detail::swap_fn swap{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

#endif // defined(HAMON_USE_STD_CONCEPTS)

#endif // HAMON_CONCEPTS_SWAP_HPP
