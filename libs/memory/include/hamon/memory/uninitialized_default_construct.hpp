/**
 *	@file	uninitialized_default_construct.hpp
 *
 *	@brief	uninitialized_default_construct を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP
#define HAMON_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP

#include <memory>

#if defined(__cpp_lib_raw_memory_algorithms) && (__cpp_lib_raw_memory_algorithms >= 201606)

namespace hamon
{

using std::uninitialized_default_construct;

}	// namespace hamon

#else

#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>

namespace hamon
{

namespace detail
{

template <typename ForwardIterator,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_default_constructible<ValueType>::value
	>
>
inline void
uninitialized_default_construct_impl(
	ForwardIterator first, ForwardIterator last,
	hamon::detail::overload_priority<1>)
{
	(void)first;
	(void)last;
}

template <typename ForwardIterator>
inline void
uninitialized_default_construct_impl(
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
uninitialized_default_construct(
	ForwardIterator first, ForwardIterator last)
{
	return hamon::detail::uninitialized_default_construct_impl(
		first, last,
		hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP
