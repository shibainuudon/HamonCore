/**
 *	@file	uninitialized_value_construct_n.hpp
 *
 *	@brief	uninitialized_value_construct_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP

#include <memory>

#if defined(__cpp_lib_raw_memory_algorithms) && (__cpp_lib_raw_memory_algorithms >= 201606)

namespace hamon
{

using std::uninitialized_value_construct_n;

}	// namespace hamon

#else

#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>

namespace hamon
{

// 27.11.4 uninitialized_value_construct[uninitialized.construct.value]

template <typename NoThrowForwardIterator, typename Size>
inline NoThrowForwardIterator
uninitialized_value_construct_n(NoThrowForwardIterator first, Size n)
{
	return hamon::detail::uninitialized_value_construct_n_impl(first, n);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP
