/**
 *	@file	cpp17_erasable.hpp
 *
 *	@brief	cpp17_erasable の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_CPP17_ERASABLE_HPP
#define HAMON_CONTAINER_DETAIL_CPP17_ERASABLE_HPP

#include <hamon/memory/allocator_traits.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// [container.alloc.reqmts]/2.6

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename A>
concept cpp17_erasable =
	requires(A& m, T* p)
	{
		{ hamon::allocator_traits<A>::destroy(m, p) };
	};

#else

template <typename T, typename A>
struct cpp17_erasable_impl
{
private:
	template <typename U, typename UA,
		typename = decltype(hamon::allocator_traits<UA>::destroy(
			hamon::declval<UA&>(), hamon::declval<U*>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U, typename UA>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, A>(0));
};

template <typename T, typename A>
using cpp17_erasable =
	typename cpp17_erasable_impl<T, A>::type;

#endif

template <typename T, typename A>
using cpp17_erasable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_erasable<T, A>>;
#else
	hamon::detail::cpp17_erasable<T, A>;
#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_CPP17_ERASABLE_HPP
