/**
 *	@file	uninitialized_copy_n.hpp
 *
 *	@brief	uninitialized_copy_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_COPY_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_COPY_N_HPP

#include <hamon/memory/detail/uninitialized_copy_n_impl.hpp>

namespace hamon
{

// 27.11.5 uninitialized_copy[uninitialized.copy]

template <typename InputIterator, typename Size, typename NoThrowForwardIterator >
inline NoThrowForwardIterator 
uninitialized_copy_n(InputIterator first, Size n, NoThrowForwardIterator  result)
{
	return hamon::detail::uninitialized_copy_n_impl(first, n, result);
}

}	// namespace hamon

#endif // HAMON_MEMORY_UNINITIALIZED_COPY_N_HPP
