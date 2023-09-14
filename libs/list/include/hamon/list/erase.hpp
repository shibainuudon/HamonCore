/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_LIST_ERASE_HPP
#define HAMON_LIST_ERASE_HPP

#include <list>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

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

template <typename T, typename Alloc, typename U>
inline HAMON_CXX14_CONSTEXPR
typename hamon::list<T, Alloc>::size_type
erase(hamon::list<T, Alloc>& c, U const& value)
{
	using elem_type = typename hamon::list<T, Alloc>::value_type;
	return hamon::erase_if(c, [&](elem_type& elem) { return elem == value; });
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_LIST_ERASE_HPP
