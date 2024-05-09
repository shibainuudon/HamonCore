﻿/**
 *	@file	uninitialized_value_construct_n.hpp
 *
 *	@brief	uninitialized_value_construct_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP

#include <memory>

#if defined(__cpp_lib_raw_memory_algorithms) && (__cpp_lib_raw_memory_algorithms >= 201606)

namespace hamon
{

using std::uninitialized_value_construct_n;

}	// namespace hamon

#else

#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/algorithm/fill_n.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_trivial.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>

namespace hamon
{

namespace detail
{

template <typename ForwardIterator, typename Size,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivial<ValueType>::value &&
		hamon::is_copy_assignable<ValueType>::value
	>
>
inline ForwardIterator
uninitialized_value_construct_n_impl(
	ForwardIterator first, Size n,
	hamon::detail::overload_priority<1>)
{
	if (n > 0)
	{
		auto* val = hamon::addressof(*first);
		hamon::construct_at(val);
		++first;
		first = hamon::fill_n(first, n - 1, *val);
	}
	return first;
}

template <typename ForwardIterator, typename Size>
inline ForwardIterator
uninitialized_value_construct_n_impl(
	ForwardIterator first, Size n,
	hamon::detail::overload_priority<0>)
{
	ForwardIterator current = first;
	try
	{
		for (; n > 0; --n, (void)++current)
		{
			hamon::construct_at(hamon::addressof(*current));
		}
		return current;
	}
	catch(...)
	{
		hamon::destroy(first, current);
		throw;
	}
}

}	// namespace detail

template <typename ForwardIterator, typename Size>
inline ForwardIterator
uninitialized_value_construct_n(ForwardIterator first, Size count)
{
	return hamon::detail::uninitialized_value_construct_n_impl(
		first, count,
		hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP
