/**
 *	@file	uninitialized_copy.hpp
 *
 *	@brief	uninitialized_copy を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_COPY_HPP
#define HAMON_MEMORY_UNINITIALIZED_COPY_HPP

#include <hamon/memory/detail/uninitialized_copy_impl.hpp>

namespace hamon
{

// 27.11.5 uninitialized_copy[uninitialized.copy]

template <typename InputIterator, typename NoThrowForwardIterator>
inline NoThrowForwardIterator
uninitialized_copy(InputIterator first, InputIterator last, NoThrowForwardIterator result)
{
	return hamon::detail::uninitialized_copy_impl(first, last, result).out;
}

}	// namespace hamon

#endif // HAMON_MEMORY_UNINITIALIZED_COPY_HPP
