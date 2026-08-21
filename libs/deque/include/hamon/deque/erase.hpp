/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_DEQUE_ERASE_HPP
#define HAMON_DEQUE_ERASE_HPP

#include <hamon/deque/deque.hpp>
#include <hamon/algorithm/remove.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.3.9.5 Erasure[deque.erasure]

template <typename T, typename Allocator, typename U = T>
HAMON_CXX14_CONSTEXPR
typename hamon::deque<T, Allocator>::size_type
erase(hamon::deque<T, Allocator>& c, U const& value)
{
	// [deque.erasure]/1
	auto it = hamon::remove(c.begin(), c.end(), value);
	auto r = hamon::distance(it, c.end());
	c.erase(it, c.end());
	return static_cast<typename hamon::deque<T, Allocator>::size_type>(r);
}

}	// namespace hamon

#endif // HAMON_DEQUE_ERASE_HPP
