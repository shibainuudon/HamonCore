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

#include <hamon/memory/detail/uninitialized_copy_impl.hpp>

namespace hamon
{

template <typename InputIterator, typename ForwardIterator>
inline ForwardIterator
uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
{
	return hamon::detail::uninitialized_copy_impl(first, last, result);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_COPY_HPP
