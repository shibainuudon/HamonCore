/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_DEQUE_ERASE_HPP
#define HAMON_DEQUE_ERASE_HPP

#include <deque>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

namespace hamon
{

using std::erase;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/deque/deque.hpp>
#include <hamon/algorithm/remove.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T, typename Alloc, typename U>
inline HAMON_CXX14_CONSTEXPR
typename hamon::deque<T, Alloc>::size_type
erase(hamon::deque<T, Alloc>& c, const U& value)
{
	auto const sz = c.size();
	c.erase(hamon::remove(c.begin(), c.end(), value), c.end());
	return sz - c.size();
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_DEQUE_ERASE_HPP
