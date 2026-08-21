/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_FORWARD_LIST_ERASE_HPP
#define HAMON_FORWARD_LIST_ERASE_HPP

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/forward_list/erase_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.3.10.7 Erasure[forward.list.erasure]

template <typename T, typename Allocator, typename U = T>
HAMON_CXX14_CONSTEXPR
typename hamon::forward_list<T, Allocator>::size_type
erase(hamon::forward_list<T, Allocator>& c, U const& value)
{
	// [forward.list.erasure]/1
	using elem_type = typename hamon::forward_list<T, Allocator>::value_type;
	return hamon::erase_if(c, [&](elem_type& elem) { return elem == value; });
}

}	// namespace hamon

#endif // HAMON_FORWARD_LIST_ERASE_HPP
