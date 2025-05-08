﻿/**
 *	@file	cpp17_copy_insertable.hpp
 *
 *	@brief	cpp17_copy_insertable の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_CPP17_COPY_INSERTABLE_HPP
#define HAMON_CONTAINER_DETAIL_CPP17_COPY_INSERTABLE_HPP

#include <hamon/container/detail/cpp17_move_insertable.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// [container.alloc.reqmts]/2.4

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename A>
concept cpp17_copy_insertable =
	hamon::detail::cpp17_move_insertable<T, A> &&
	requires(A& m, T* p, T const& v)
	{
		{ hamon::allocator_traits<A>::construct(m, p, v) };
	};

#else

template <typename T, typename A>
struct cpp17_copy_insertable_impl
{
private:
	template <typename U, typename UA,
		typename = hamon::enable_if_t<hamon::detail::cpp17_move_insertable<U, UA>::value>,
		typename = decltype(hamon::allocator_traits<UA>::construct(
			hamon::declval<UA&>(), hamon::declval<U*>(), hamon::declval<U const&>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U, typename UA>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, A>(0));
};

template <typename T, typename A>
using cpp17_copy_insertable =
	typename cpp17_copy_insertable_impl<T, A>::type;

#endif

template <typename T, typename A>
using cpp17_copy_insertable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_copy_insertable<T, A>>;
#else
	hamon::detail::cpp17_copy_insertable<T, A>;
#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_CPP17_COPY_INSERTABLE_HPP
