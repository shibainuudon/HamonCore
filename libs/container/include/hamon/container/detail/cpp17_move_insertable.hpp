/**
 *	@file	cpp17_move_insertable.hpp
 *
 *	@brief	cpp17_move_insertable の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_CPP17_MOVE_INSERTABLE_HPP
#define HAMON_CONTAINER_DETAIL_CPP17_MOVE_INSERTABLE_HPP

#include <hamon/memory/allocator_traits.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// [container.alloc.reqmts]/2.3

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename A>
concept cpp17_move_insertable =
	requires(A& m, T* p, T&& rv)
	{
		{ hamon::allocator_traits<A>::construct(m, p, hamon::move(rv)) };
	};

#else

template <typename T, typename A>
struct cpp17_move_insertable_impl
{
private:
	template <typename U, typename UA,
		typename = decltype(hamon::allocator_traits<UA>::construct(
			hamon::declval<UA&>(), hamon::declval<U*>(), hamon::declval<U&&>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U, typename UA>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, A>(0));
};

template <typename T, typename A>
using cpp17_move_insertable =
	typename cpp17_move_insertable_impl<T, A>::type;

#endif

template <typename T, typename A>
using cpp17_move_insertable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_move_insertable<T, A>>;
#else
	hamon::detail::cpp17_move_insertable<T, A>;
#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_CPP17_MOVE_INSERTABLE_HPP
