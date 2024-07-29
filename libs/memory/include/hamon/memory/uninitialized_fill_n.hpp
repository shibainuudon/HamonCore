/**
 *	@file	uninitialized_fill_n.hpp
 *
 *	@brief	uninitialized_fill_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_FILL_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_FILL_N_HPP

#if 0

#include <memory>

namespace hamon
{

using std::uninitialized_fill_n;

}	// namespace hamon

#else

#include <hamon/memory/detail/uninitialized_fill_n_impl.hpp>

namespace hamon
{

// 27.11.7 uninitialized_fill[uninitialized.fill]

template <typename NoThrowForwardIterator, typename Size, typename T>
inline NoThrowForwardIterator
uninitialized_fill_n(NoThrowForwardIterator first, Size n, T const& x)
{
	return hamon::detail::uninitialized_fill_n_impl(first, n, x);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_FILL_N_HPP
