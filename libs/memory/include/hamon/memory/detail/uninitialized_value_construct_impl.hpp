/**
 *	@file	uninitialized_value_construct_impl.hpp
 *
 *	@brief	uninitialized_value_construct_impl を定義
 */

#ifndef HAMON_MEMORY_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_IMPL_HPP
#define HAMON_MEMORY_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_IMPL_HPP

#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename ForwardIterator,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_nothrow_default_constructible<ValueType>::value
	>
>
HAMON_CXX20_CONSTEXPR void
uninitialized_value_construct_impl(
	ForwardIterator first, ForwardIterator last,
	hamon::detail::overload_priority<1>)
{
	// コンストラクタが例外を投げないのであれば、try-catchなどを省略できる。
	for (; first != last; ++first)
	{
		hamon::construct_at(hamon::addressof(*first));
	}
}

template <typename ForwardIterator>
HAMON_CXX20_CONSTEXPR void
uninitialized_value_construct_impl(
	ForwardIterator first, ForwardIterator last,
	hamon::detail::overload_priority<0>)
{
	ForwardIterator current = first;
	try
	{
		for (; current != last; ++current)
		{
			hamon::construct_at(hamon::addressof(*current));
		}
	}
	catch(...)
	{
		hamon::destroy(first, current);
		throw;
	}
}

template <typename ForwardIterator>
HAMON_CXX20_CONSTEXPR void
uninitialized_value_construct_impl(
	ForwardIterator first, ForwardIterator last)
{
	return hamon::detail::uninitialized_value_construct_impl(
		first, last,
		hamon::detail::overload_priority<1>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_IMPL_HPP
