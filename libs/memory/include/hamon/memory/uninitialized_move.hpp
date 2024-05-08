/**
 *	@file	uninitialized_move.hpp
 *
 *	@brief	uninitialized_move を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_MOVE_HPP
#define HAMON_MEMORY_UNINITIALIZED_MOVE_HPP

#include <memory>

#if defined(__cpp_lib_raw_memory_algorithms) && (__cpp_lib_raw_memory_algorithms >= 201606)

namespace hamon
{

using std::uninitialized_move;

}	// namespace hamon

#else

#include <hamon/memory/addressof.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/algorithm/move.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace detail
{

template <typename InputIterator, typename ForwardIterator,
	typename SrcType = hamon::iter_rvalue_reference_t<InputIterator>,
	typename RefType = hamon::iter_reference_t<ForwardIterator>,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_assignable<RefType, SrcType>::value &&
		hamon::is_trivially_constructible<ValueType, SrcType>::value
	>
>
inline ForwardIterator
uninitialized_move_impl(
	InputIterator first, InputIterator last, ForwardIterator result,
	hamon::detail::overload_priority<1>)
{
	return hamon::move(first, last, result);
}

template <typename InputIterator, typename ForwardIterator>
inline ForwardIterator
uninitialized_move_impl(
	InputIterator first, InputIterator last, ForwardIterator result,
	hamon::detail::overload_priority<0>)
{
	ForwardIterator current = result;
	try
	{
		for (; first != last; ++first)
		{
			hamon::construct_at(hamon::addressof(*current), hamon::move(*first));
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
uninitialized_move(InputIterator first, InputIterator last, ForwardIterator result)
{
	return hamon::detail::uninitialized_move_impl(
		first, last, result,
		hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_MOVE_HPP
