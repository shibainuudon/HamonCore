/**
 *	@file	uninitialized_move_n.hpp
 *
 *	@brief	uninitialized_move_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_MOVE_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_MOVE_N_HPP

#include <memory>

#if defined(__cpp_lib_raw_memory_algorithms) && (__cpp_lib_raw_memory_algorithms >= 201606)

namespace hamon
{

using std::uninitialized_move_n;

}	// namespace hamon

#else

#include <hamon/memory/detail/uninitialized_move_n_impl.hpp>
#include <hamon/pair.hpp>

namespace hamon
{

template <typename InputIterator, typename Size, typename ForwardIterator>
inline hamon::pair<InputIterator, ForwardIterator>
uninitialized_move_n(InputIterator first, Size count, ForwardIterator result)
{
	return hamon::detail::uninitialized_move_n_impl(first, count, result);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_MOVE_N_HPP
