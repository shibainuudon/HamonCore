/**
 *	@file	uninitialized_move_n.hpp
 *
 *	@brief	uninitialized_move_n を定義
 */

#ifndef HAMON_MEMORY_UNINITIALIZED_MOVE_N_HPP
#define HAMON_MEMORY_UNINITIALIZED_MOVE_N_HPP

#include <hamon/memory/detail/uninitialized_move_n_impl.hpp>
#include <hamon/pair.hpp>

namespace hamon
{

template <typename InputIterator, typename Size, typename NoThrowForwardIterator>
inline hamon::pair<InputIterator, NoThrowForwardIterator>
uninitialized_move_n(InputIterator first, Size count, NoThrowForwardIterator result)
{
	return hamon::detail::uninitialized_move_n_impl(first, count, result);
}

}	// namespace hamon

#endif // HAMON_MEMORY_UNINITIALIZED_MOVE_N_HPP
