/**
 *	@file	uninitialized_copy.hpp
 *
 *	@brief	uninitialized_copy を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_COPY_HPP
#define HAMON_MEMORY_UNINITIALIZED_COPY_HPP

#if 0

#include <memory>

namespace hamon
{

using std::uninitialized_copy;

}	// namespace hamon

#else

#include <hamon/memory/addressof.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_const_reference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/algorithm/copy.hpp>

namespace hamon
{

namespace detail
{

template <typename InputIterator, typename ForwardIterator,
	typename SrcType = hamon::iter_const_reference_t<InputIterator>,
	typename RefType = hamon::iter_reference_t<ForwardIterator>,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_assignable<RefType, SrcType>::value &&
		hamon::is_trivially_constructible<ValueType, SrcType>::value
	>
>
inline ForwardIterator
uninitialized_copy_impl(
	InputIterator first, InputIterator last, ForwardIterator result,
	hamon::detail::overload_priority<1>)
{
	return hamon::copy(first, last, result);
}

template <typename InputIterator, typename ForwardIterator>
inline ForwardIterator
uninitialized_copy_impl(
	InputIterator first, InputIterator last, ForwardIterator result,
	hamon::detail::overload_priority<0>)
{
	ForwardIterator current = result;
	try
	{
		for (; first != last; ++first)
		{
			hamon::construct_at(hamon::addressof(*current), *first);
			++current;
		}
		return current;
	}
	catch (...)
	{
		hamon::destroy(result, current);
		throw;
	}
}

}	// namespace detail

template <typename InputIterator, typename ForwardIterator>
inline ForwardIterator
uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
{
	return hamon::detail::uninitialized_copy_impl(
		first, last, result,
		hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_COPY_HPP
