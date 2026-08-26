/**
 *	@file	uninitialized_move.hpp
 *
 *	@brief	uninitialized_move を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_MOVE_HPP
#define HAMON_MEMORY_UNINITIALIZED_MOVE_HPP

#include <hamon/memory/detail/uninitialized_move_impl.hpp>

namespace hamon
{

// 27.11.6 uninitialized_move[uninitialized.move]

template <typename InputIterator, typename NoThrowForwardIterator>
inline NoThrowForwardIterator
uninitialized_move(InputIterator first, InputIterator last, NoThrowForwardIterator result)
{
	return hamon::detail::uninitialized_move_impl(first, last, result).out;
}

}	// namespace hamon

#endif // HAMON_MEMORY_UNINITIALIZED_MOVE_HPP
