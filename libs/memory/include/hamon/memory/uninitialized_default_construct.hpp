/**
 *	@file	uninitialized_default_construct.hpp
 *
 *	@brief	uninitialized_default_construct を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP
#define HAMON_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP

#include <hamon/memory/detail/uninitialized_default_construct_impl.hpp>

namespace hamon
{

// 27.11.3 uninitialized_default_construct[uninitialized.construct.default]

template <typename NoThrowForwardIterator>
inline void
uninitialized_default_construct(NoThrowForwardIterator first, NoThrowForwardIterator last)
{
	hamon::detail::uninitialized_default_construct_impl(first, last);
}

}	// namespace hamon

#endif // HAMON_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP
