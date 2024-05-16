﻿/**
 *	@file	uninitialized_copy_n.hpp
 *
 *	@brief	uninitialized_copy_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_COPY_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_COPY_N_HPP

#if 0

#include <memory>

namespace hamon
{

using std::uninitialized_copy_n;

}	// namespace hamon

#else

#include <hamon/memory/detail/uninitialized_copy_n_impl.hpp>

namespace hamon
{

template <typename InputIterator, typename Size, typename ForwardIterator>
inline ForwardIterator
uninitialized_copy_n(InputIterator first, Size n, ForwardIterator result)
{
	return hamon::detail::uninitialized_copy_n_impl(first, n, result);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_COPY_N_HPP
