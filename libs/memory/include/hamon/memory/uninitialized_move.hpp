/**
 *	@file	uninitialized_move.hpp
 *
 *	@brief	uninitialized_move を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_MOVE_HPP
#define HAMON_MEMORY_UNINITIALIZED_MOVE_HPP

#include <memory>

#if defined(__cpp_lib_raw_memory_algorithms) && (__cpp_lib_raw_memory_algorithms >= 201606)

namespace hamon
{

using std::uninitialized_move;

}	// namespace hamon

#else

#include <hamon/memory/detail/uninitialized_move_impl.hpp>

namespace hamon
{

template <typename InputIterator, typename ForwardIterator>
inline ForwardIterator
uninitialized_move(InputIterator first, InputIterator last, ForwardIterator result)
{
	return hamon::detail::uninitialized_move_impl(first, last, result);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_UNINITIALIZED_MOVE_HPP
