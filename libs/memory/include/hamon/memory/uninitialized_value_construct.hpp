/**
 *	@file	uninitialized_value_construct.hpp
 *
 *	@brief	uninitialized_value_construct を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_HPP
#define HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_HPP

#include <memory>

#if defined(__cpp_lib_raw_memory_algorithms) && (__cpp_lib_raw_memory_algorithms >= 201606)

namespace hamon
{

using std::uninitialized_value_construct;

}	// namespace hamon

#else

#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/algorithm/fill.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_trivial.hpp>

namespace hamon
{

namespace detail
{

template <typename ForwardIterator,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivial<ValueType>::value &&
		hamon::is_copy_assignable<ValueType>::value
	>
>
inline void
uninitialized_value_construct_impl(
	ForwardIterator first, ForwardIterator last,
	hamon::detail::overload_priority<1>)
{
	if (first == last)
	{
		return;
	}

	auto* val = hamon::addressof(*first);
	hamon::construct_at(val);
	if (++first != last)
	{
		hamon::fill(first, last, *val);
	}
}

template <typename ForwardIterator>
inline void
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

}	// namespace detail

template <typename ForwardIterator>
inline void
uninitialized_value_construct(
	ForwardIterator first, ForwardIterator last)
{
	return hamon::detail::uninitialized_value_construct_impl(
		first, last,
		hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_HPP
