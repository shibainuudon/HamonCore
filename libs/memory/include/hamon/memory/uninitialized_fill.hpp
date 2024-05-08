/**
 *	@file	uninitialized_fill.hpp
 *
 *	@brief	uninitialized_fill を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_FILL_HPP
#define HAMON_MEMORY_UNINITIALIZED_FILL_HPP

#if 0

#include <memory>

namespace hamon
{

using std::uninitialized_fill;

}	// namespace hamon

#else

#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/algorithm/fill.hpp>

namespace hamon
{

namespace detail
{

template <typename ForwardIterator, typename T,
	typename RefType = hamon::iter_reference_t<ForwardIterator>,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_assignable<RefType, T const&>::value &&
		hamon::is_trivially_constructible<ValueType, T const&>::value
	>
>
inline void
uninitialized_fill_impl(
	ForwardIterator first, ForwardIterator last, T const& x,
	hamon::detail::overload_priority<1>)
{
	hamon::fill(first, last, x);
}

template <typename ForwardIterator, typename T>
inline void
uninitialized_fill_impl(
	ForwardIterator first, ForwardIterator last, T const& x,
	hamon::detail::overload_priority<0>)
{
	ForwardIterator current = first;
	try
	{
		for (; current != last; ++current)
		{
			hamon::construct_at(hamon::addressof(*current), x);
		}
	}
	catch(...)
	{
		hamon::destroy(first, current);
		throw;
	}
}

}	// namespace detail

template <typename ForwardIterator, typename T>
inline void
uninitialized_fill(ForwardIterator first, ForwardIterator last, T const& x)
{
	return hamon::detail::uninitialized_fill_impl(
		first, last, x,
		hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_FILL_HPP
