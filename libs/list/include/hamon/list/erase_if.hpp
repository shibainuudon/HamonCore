/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_LIST_ERASE_IF_HPP
#define HAMON_LIST_ERASE_IF_HPP

#include <list>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

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
#if defined(__cpp_lib_list_remove_return_type) && (__cpp_lib_list_remove_return_type >= 201806)
	// [list.erasure]/2
	return c.remove_if(pred);
#else
	auto const sz = c.size();
	c.remove_if(pred);
	return sz - c.size();
#endif
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_LIST_ERASE_IF_HPP
