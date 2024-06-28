/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_DEQUE_ERASE_HPP
#define HAMON_DEQUE_ERASE_HPP

#include <hamon/deque/config.hpp>

#if defined(HAMON_USE_STD_DEQUE) && defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

#include <deque>

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
HAMON_CXX14_CONSTEXPR
typename hamon::deque<T, Alloc>::size_type
erase(hamon::deque<T, Alloc>& c, U const& value)
{
	auto const sz = c.size();
	c.erase(hamon::remove(c.begin(), c.end(), value), c.end());
	return sz - c.size();
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_DEQUE_ERASE_HPP
