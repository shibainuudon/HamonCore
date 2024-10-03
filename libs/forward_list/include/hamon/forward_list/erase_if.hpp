/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_FORWARD_LIST_ERASE_IF_HPP
#define HAMON_FORWARD_LIST_ERASE_IF_HPP

#include <forward_list>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

namespace hamon
{

using std::erase_if;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.3.10.7 Erasure[forward.list.erasure]

template <typename T, typename Allocator, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hamon::forward_list<T, Allocator>::size_type
erase_if(hamon::forward_list<T, Allocator>& c, Predicate pred)
{
#if defined(__cpp_lib_list_remove_return_type) && (__cpp_lib_list_remove_return_type >= 201806)
	// [forward.list.erasure]/2
	return c.remove_if(pred);
#else
	using size_type = typename hamon::forward_list<T, Allocator>::size_type;
	auto const sz = hamon::distance(c.begin(), c.end());
	c.remove_if(pred);
	return static_cast<size_type>(sz - hamon::distance(c.begin(), c.end()));
#endif
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_FORWARD_LIST_ERASE_IF_HPP
