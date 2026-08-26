/**
 *	@file	uninitialized_default_construct_n.hpp
 *
 *	@brief	uninitialized_default_construct_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_N_HPP

#include <hamon/memory/detail/uninitialized_default_construct_n_impl.hpp>

namespace hamon
{

// 27.11.3 uninitialized_default_construct[uninitialized.construct.default]

template <typename NoThrowForwardIterator, typename Size>
inline NoThrowForwardIterator
uninitialized_default_construct_n(NoThrowForwardIterator first, Size n)
{
	return hamon::detail::uninitialized_default_construct_n_impl(first, n);
}

}	// namespace hamon

#endif // HAMON_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_N_HPP
