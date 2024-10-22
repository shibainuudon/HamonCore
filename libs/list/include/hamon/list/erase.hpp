/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_LIST_ERASE_HPP
#define HAMON_LIST_ERASE_HPP

#include <hamon/list/config.hpp>

#if defined(HAMON_USE_STD_LIST) && \
	defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <list>

namespace hamon
{

using std::erase;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/list/list.hpp>
#include <hamon/list/erase_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 24.3.11.6 Erasure[list.erasure]

template <typename T, typename Allocator, typename U = T>
HAMON_CXX14_CONSTEXPR
typename hamon::list<T, Allocator>::size_type
erase(hamon::list<T, Allocator>& c, U const& value)
{
	// [list.erasure]/1
	using elem_type = typename hamon::list<T, Allocator>::value_type;
	return hamon::erase_if(c, [&](elem_type& elem) { return elem == value; });
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_LIST_ERASE_HPP
