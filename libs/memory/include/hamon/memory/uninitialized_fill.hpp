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

template <typename ForwardIterator, typename T>
inline void
uninitialized_fill(ForwardIterator first, ForwardIterator last, T const& x)
{
	return hamon::detail::uninitialized_fill_impl(first, last, x);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_FILL_HPP
