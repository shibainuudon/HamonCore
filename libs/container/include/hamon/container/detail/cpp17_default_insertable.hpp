/**
 *	@file	cpp17_default_insertable.hpp
 *
 *	@brief	cpp17_default_insertable の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_CPP17_DEFAULT_INSERTABLE_HPP
#define HAMON_CONTAINER_DETAIL_CPP17_DEFAULT_INSERTABLE_HPP

#include <hamon/container/detail/cpp17_move_insertable.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// [container.alloc.reqmts]/2.1

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename A>
concept cpp17_default_insertable =
	requires(A& m, T* p)
	{
		{ hamon::allocator_traits<A>::construct(m, p) };
	};

#else

template <typename T, typename A>
struct cpp17_default_insertable_impl
{
private:
	template <typename T2, typename A2,
		typename = decltype(hamon::allocator_traits<A2>::construct(
			hamon::declval<A2&>(), hamon::declval<T2*>()))
	>
	static auto test(int) -> hamon::true_type;

	template <typename T2, typename A2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, A>(0));
};

template <typename T, typename A>
using cpp17_default_insertable =
	typename cpp17_default_insertable_impl<T, A>::type;

#endif

template <typename T, typename A>
using cpp17_default_insertable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_default_insertable<T, A>>;
#else
	hamon::detail::cpp17_default_insertable<T, A>;
#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_CPP17_DEFAULT_INSERTABLE_HPP
