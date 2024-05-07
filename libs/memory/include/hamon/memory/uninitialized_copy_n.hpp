/**
 *	@file	uninitialized_copy_n.hpp
 *
 *	@brief	uninitialized_copy_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_COPY_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_COPY_N_HPP

#if 0

#include <memory>

namespace hamon
{

using std::uninitialized_copy_n;

}	// namespace hamon

#else

#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/memory/uninitialized_copy.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/algorithm/copy_n.hpp>

namespace hamon
{

namespace detail
{

template <typename InputIterator, typename Size, typename ForwardIterator,
	typename SrcType = hamon::iter_const_reference_t<InputIterator>,
	typename RefType = hamon::iter_reference_t<ForwardIterator>,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_assignable<RefType, SrcType>::value &&
		hamon::is_trivially_constructible<ValueType, SrcType>::value
	>
>
inline ForwardIterator
uninitialized_copy_n_impl(
	InputIterator first, Size n, ForwardIterator result,
	hamon::detail::overload_priority<1>)
{
	return hamon::copy_n(first, n, result);
}

template <typename InputIterator, typename Size, typename ForwardIterator>
inline ForwardIterator
uninitialized_copy_n_impl(
	InputIterator first, Size n, ForwardIterator result,
	hamon::detail::overload_priority<0>)
{
	ForwardIterator current = result;
	try
	{
		for (; n > 0; --n)
		{
			hamon::construct_at(hamon::addressof(*current), *first);
			++first;
			++current;
		}
		return current;
	}
	catch(...)
	{
		hamon::destroy(result, current);
		throw;
	}
}

}	// namespace detail

template <typename InputIterator, typename Size, typename ForwardIterator>
inline ForwardIterator
uninitialized_copy_n(InputIterator first, Size n, ForwardIterator result)
{
	return hamon::detail::uninitialized_copy_n_impl(
		first, n, result,
		hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_COPY_N_HPP
