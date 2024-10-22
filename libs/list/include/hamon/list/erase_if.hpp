/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_LIST_ERASE_IF_HPP
#define HAMON_LIST_ERASE_IF_HPP

#include <hamon/list/config.hpp>

#if defined(HAMON_USE_STD_LIST) && \
	defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

#include <list>

namespace hamon
{

using std::erase_if;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/list/list.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.3.11.6 Erasure[list.erasure]

template <typename T, typename Allocator, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hamon::list<T, Allocator>::size_type
erase_if(hamon::list<T, Allocator>& c, Predicate pred)
{
	// [list.erasure]/2
	return c.remove_if(pred);
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_LIST_ERASE_IF_HPP
