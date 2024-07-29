/**
 *	@file	uninitialized_fill.hpp
 *
 *	@brief	uninitialized_fill を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_FILL_HPP
#define HAMON_MEMORY_UNINITIALIZED_FILL_HPP

#if 0

#include <memory>

namespace hamon
{

using std::uninitialized_fill;

}	// namespace hamon

#else

#include <hamon/memory/detail/uninitialized_fill_impl.hpp>

namespace hamon
{

// 27.11.7 uninitialized_fill[uninitialized.fill]

template <typename NoThrowForwardIterator, typename T>
inline void
uninitialized_fill(NoThrowForwardIterator first, NoThrowForwardIterator last, T const& x)
{
	hamon::detail::uninitialized_fill_impl(first, last, x);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_FILL_HPP
