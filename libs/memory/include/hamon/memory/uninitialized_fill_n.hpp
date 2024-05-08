/**
 *	@file	uninitialized_fill_n.hpp
 *
 *	@brief	uninitialized_fill_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_FILL_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_FILL_N_HPP

#if 0

#include <memory>

namespace hamon
{

using std::uninitialized_fill_n;

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
#include <hamon/algorithm/fill_n.hpp>

namespace hamon
{

namespace detail
{

template <typename ForwardIterator, typename Size, typename T,
	typename RefType = hamon::iter_reference_t<ForwardIterator>,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_assignable<RefType, T const&>::value &&
		hamon::is_trivially_constructible<ValueType, T const&>::value
	>
>
inline ForwardIterator
uninitialized_fill_n_impl(
	ForwardIterator first, Size n, T const& x,
	hamon::detail::overload_priority<1>)
{
	return hamon::fill_n(first, n, x);
}

template <typename ForwardIterator, typename Size, typename T>
inline ForwardIterator
uninitialized_fill_n_impl(
	ForwardIterator first, Size n, T const& x,
	hamon::detail::overload_priority<0>)
{
	ForwardIterator current = first;
	try
	{
		for (; n > 0; --n)
		{
			hamon::construct_at(hamon::addressof(*current), x);
			++current;
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

template <typename ForwardIterator, typename Size, typename T>
inline ForwardIterator
uninitialized_fill_n(ForwardIterator first, Size n, T const& x)
{
	return hamon::detail::uninitialized_fill_n_impl(
		first, n, x,
		hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_FILL_N_HPP
