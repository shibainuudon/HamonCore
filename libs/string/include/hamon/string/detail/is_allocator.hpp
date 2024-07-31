/**
 *	@file	is_allocator.hpp
 *
 *	@brief	is_allocator の定義
 */

#ifndef HAMON_STRING_DETAIL_IS_ALLOCATOR_HPP
#define HAMON_STRING_DETAIL_IS_ALLOCATOR_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

namespace detail
{

template <typename Alloc, typename = void, typename = void>
struct is_allocator : hamon::false_type {};

template <typename A>
struct is_allocator<A,
	hamon::void_t<typename A::value_type>,	// [container.reqmts]/69.1
	hamon::void_t<decltype(hamon::declval<A&>().allocate(hamon::size_t{}))>>// [container.reqmts]/69.2
	: hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_STRING_DETAIL_IS_ALLOCATOR_HPP
