/**
 *	@file	uninitialized_value_construct_impl.hpp
 *
 *	@brief	uninitialized_value_construct_impl を定義
 */

#ifndef HAMON_MEMORY_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_IMPL_HPP
#define HAMON_MEMORY_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_IMPL_HPP

#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/destroy_impl.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Allocator, typename Iter, typename Sent,
	typename ValueType = hamon::iter_value_t<Iter>,
	typename = hamon::enable_if_t<
		hamon::is_nothrow_default_constructible<ValueType>::value
	>
>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_value_construct_impl(
	Allocator& allocator, Iter first, Sent last,
	hamon::detail::overload_priority<1>)
{
	// コンストラクタが例外を投げないのであれば、try-catchなどを省略できる。
	for (; first != last; ++first)
	{
		hamon::allocator_traits<Allocator>::construct(allocator, hamon::addressof(*first));
	}
	return first;
}

template <typename Allocator, typename Iter, typename Sent>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_value_construct_impl(
	Allocator& allocator, Iter first, Sent last,
	hamon::detail::overload_priority<0>)
{
	Iter current = first;
#if !defined(HAMON_NO_EXCEPTIONS)
	try
#endif
	{
		for (; current != last; ++current)
		{
			hamon::allocator_traits<Allocator>::construct(allocator, hamon::addressof(*current));
		}
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	catch(...)
	{
		hamon::detail::destroy_impl(allocator, first, current);
		throw;
	}
#endif
	return current;
}

template <typename Allocator, typename Iter, typename Sent>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_value_construct_impl(Allocator& allocator, Iter first, Sent last)
{
	return hamon::detail::uninitialized_value_construct_impl(
		allocator, first, last,
		hamon::detail::overload_priority<1>{});
}

template <typename Iter, typename Sent>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_value_construct_impl(Iter first, Sent last)
{
	hamon::allocator<hamon::iter_value_t<Iter>> alloc;
	return hamon::detail::uninitialized_value_construct_impl(alloc, first, last);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_IMPL_HPP
