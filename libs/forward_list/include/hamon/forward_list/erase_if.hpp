/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_FORWARD_LIST_ERASE_IF_HPP
#define HAMON_FORWARD_LIST_ERASE_IF_HPP

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.3.10.7 Erasure[forward.list.erasure]

template <typename T, typename Allocator, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hamon::forward_list<T, Allocator>::size_type
erase_if(hamon::forward_list<T, Allocator>& c, Predicate pred)
{
	// [forward.list.erasure]/2
	return c.remove_if(pred);
}

}	// namespace hamon

#endif // HAMON_FORWARD_LIST_ERASE_IF_HPP
