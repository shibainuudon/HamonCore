/**
 *	@file	uninitialized_move_n.hpp
 *
 *	@brief	uninitialized_move_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_MOVE_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_MOVE_N_HPP

#include <memory>

#if defined(__cpp_lib_raw_memory_algorithms) && (__cpp_lib_raw_memory_algorithms >= 201606)

namespace hamon
{

using std::uninitialized_move_n;

}	// namespace hamon

#else

#include <hamon/memory/addressof.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/pair.hpp>

namespace hamon
{

namespace detail
{

template <typename InputIterator, typename Size, typename ForwardIterator,
	typename SrcType = hamon::iter_rvalue_reference_t<InputIterator>,
	typename RefType = hamon::iter_reference_t<ForwardIterator>,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_assignable<RefType, SrcType>::value &&
		hamon::is_trivially_constructible<ValueType, SrcType>::value
	>
>
inline hamon::pair<InputIterator, ForwardIterator>
uninitialized_move_n_impl(
	InputIterator first, Size count, ForwardIterator result,
	hamon::detail::overload_priority<1>)
{
	// move_n(first, count, result);
	for (; count > 0; --count)
	{
		*result = hamon::move(*first);
		++result;
		++first;
	}
	return {first, result};
}

template <typename InputIterator, typename Size, typename ForwardIterator>
inline hamon::pair<InputIterator, ForwardIterator>
uninitialized_move_n_impl(
	InputIterator first, Size count, ForwardIterator result,
	hamon::detail::overload_priority<0>)
{
	ForwardIterator current = result;
	try
	{
		for (; count > 0; --count)
		{
			hamon::construct_at(hamon::addressof(*current), hamon::move(*first));
			++current;
			++first;
		}
		return {first, current};
	}
	catch (...)
	{
		hamon::destroy(result, current);
		throw;
	}
}

}	// namespace detail

template <typename InputIterator, typename Size, typename ForwardIterator>
inline hamon::pair<InputIterator, ForwardIterator>
uninitialized_move_n(InputIterator first, Size count, ForwardIterator result)
{
	return hamon::detail::uninitialized_move_n_impl(
		first, count, result,
		hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_MOVE_N_HPP
