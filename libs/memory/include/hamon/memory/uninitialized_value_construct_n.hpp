/**
 *	@file	uninitialized_value_construct_n.hpp
 *
 *	@brief	uninitialized_value_construct_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP

#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>

namespace hamon
{

// 27.11.4 uninitialized_value_construct[uninitialized.construct.value]

template <typename NoThrowForwardIterator, typename Size>
inline NoThrowForwardIterator
uninitialized_value_construct_n(NoThrowForwardIterator first, Size n)
{
	return hamon::detail::uninitialized_value_construct_n_impl(first, n);
}

}	// namespace hamon

#endif // HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP
