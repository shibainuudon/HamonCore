/**
 *	@file	cpp17_emplace_constructible.hpp
 *
 *	@brief	cpp17_emplace_constructible の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_CPP17_EMPLACE_CONSTRUCTIBLE_HPP
#define HAMON_CONTAINER_DETAIL_CPP17_EMPLACE_CONSTRUCTIBLE_HPP

#include <hamon/memory/allocator_traits.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// [container.alloc.reqmts]/2.5

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename A, typename... Args>
concept cpp17_emplace_constructible =
	requires(A& m, T* p, Args&&... args)
	{
		{ hamon::allocator_traits<A>::construct(m, p, hamon::forward<Args>(args)...) };
	};

#else

template <typename T, typename A, typename... Args>
struct cpp17_emplace_constructible_impl
{
private:
	template <typename U, typename UA, typename... UArgs,
		typename = decltype(hamon::allocator_traits<UA>::construct(
			hamon::declval<UA&>(), hamon::declval<U*>(), hamon::declval<UArgs>()...))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U, typename UA, typename... UArgs>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, A, Args...>(0));
};

template <typename T, typename A, typename... Args>
using cpp17_emplace_constructible =
	typename cpp17_emplace_constructible_impl<T, A, Args...>::type;

#endif

template <typename T, typename A, typename... Args>
using cpp17_emplace_constructible_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_emplace_constructible<T, A, Args...>>;
#else
	hamon::detail::cpp17_emplace_constructible<T, A, Args...>;
#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_CPP17_EMPLACE_CONSTRUCTIBLE_HPP
