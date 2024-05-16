/**
 *	@file	uninitialized_default_construct_n.hpp
 *
 *	@brief	uninitialized_default_construct_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_N_HPP

#include <memory>

#if defined(__cpp_lib_raw_memory_algorithms) && (__cpp_lib_raw_memory_algorithms >= 201606)

namespace hamon
{

using std::uninitialized_default_construct_n;

}	// namespace hamon

#else

#include <hamon/memory/detail/uninitialized_default_construct_n_impl.hpp>

namespace hamon
{

template <typename ForwardIterator, typename Size>
inline ForwardIterator
uninitialized_default_construct_n(ForwardIterator first, Size n)
{
	return hamon::detail::uninitialized_default_construct_n_impl(first, n);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_N_HPP
