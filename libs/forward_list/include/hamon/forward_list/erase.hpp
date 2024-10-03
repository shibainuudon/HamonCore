/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_FORWARD_LIST_ERASE_HPP
#define HAMON_FORWARD_LIST_ERASE_HPP

#include <forward_list>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

namespace hamon
{

using std::erase;

}	// namespace hamon

#else	// __cpp_lib_erase_if

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

#endif	// __cpp_lib_erase_if

#endif // HAMON_FORWARD_LIST_ERASE_HPP
