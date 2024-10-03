/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_DEQUE_ERASE_IF_HPP
#define HAMON_DEQUE_ERASE_IF_HPP

#include <hamon/deque/config.hpp>

#if defined(HAMON_USE_STD_DEQUE) && \
	defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

#include <deque>

namespace hamon
{

using std::erase_if;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/deque/deque.hpp>
#include <hamon/algorithm/remove_if.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.3.9.5 Erasure[deque.erasure]

template <typename T, typename Allocator, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hamon::deque<T, Allocator>::size_type
erase_if(hamon::deque<T, Allocator>& c, Predicate pred)
{
	// [deque.erasure]/2
	auto it = hamon::remove_if(c.begin(), c.end(), pred);
	auto r = hamon::distance(it, c.end());
	c.erase(it, c.end());
	return static_cast<typename hamon::deque<T, Allocator>::size_type>(r);
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_DEQUE_ERASE_IF_HPP
