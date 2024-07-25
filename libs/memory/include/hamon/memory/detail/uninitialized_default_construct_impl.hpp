﻿/**
 *	@file	uninitialized_default_construct_impl.hpp
 *
 *	@brief	uninitialized_default_construct_impl を定義
 */

#ifndef HAMON_MEMORY_DETAIL_UNINITIALIZED_DEFAULT_CONSTRUCT_IMPL_HPP
#define HAMON_MEMORY_DETAIL_UNINITIALIZED_DEFAULT_CONSTRUCT_IMPL_HPP

#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/ranges/advance.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Iter, typename Sent,
	typename ValueType = hamon::iter_value_t<Iter>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_default_constructible<ValueType>::value
	>
>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_default_construct_impl(
	Iter first, Sent last,
	hamon::detail::overload_priority<2>)
{
	hamon::ranges::advance(first, last);
	return first;
}

template <typename Iter, typename Sent,
	typename ValueType = hamon::iter_value_t<Iter>,
	typename = hamon::enable_if_t<
		hamon::is_nothrow_default_constructible<ValueType>::value
	>
>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_default_construct_impl(
	Iter first, Sent last,
	hamon::detail::overload_priority<1>)
{
	// コンストラクタが例外を投げないのであれば、try-catchなどを省略できる。
	for (; first != last; ++first)
	{
		hamon::construct_at(hamon::addressof(*first));
	}
	return first;
}

template <typename Iter, typename Sent>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_default_construct_impl(
	Iter first, Sent last,
	hamon::detail::overload_priority<0>)
{
	Iter current = first;
#if !defined(HAMON_NO_EXCEPTIONS)
	try
#endif
	{
		for (; current != last; ++current)
		{
			hamon::construct_at(hamon::addressof(*current));
		}
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	catch(...)
	{
		hamon::destroy(first, current);
		throw;
	}
#endif
	return current;
}

template <typename Iter, typename Sent>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_default_construct_impl(
	Iter first, Sent last)
{
	return hamon::detail::uninitialized_default_construct_impl(
		first, last,
		hamon::detail::overload_priority<2>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_UNINITIALIZED_DEFAULT_CONSTRUCT_IMPL_HPP
