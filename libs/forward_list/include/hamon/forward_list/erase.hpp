/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_FORWARD_LIST_ERASE_HPP
#define HAMON_FORWARD_LIST_ERASE_HPP

#include <forward_list>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

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

template <typename T, typename Alloc, typename U>
inline HAMON_CXX14_CONSTEXPR
typename hamon::forward_list<T, Alloc>::size_type
erase(hamon::forward_list<T, Alloc>& c, U const& value)
{
	using elem_type = typename hamon::forward_list<T, Alloc>::value_type;
	return hamon::erase_if(c, [&](elem_type& elem) { return elem == value; });
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_FORWARD_LIST_ERASE_HPP
