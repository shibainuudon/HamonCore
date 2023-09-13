/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_VECTOR_ERASE_IF_HPP
#define HAMON_VECTOR_ERASE_IF_HPP

#include <vector>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

namespace hamon
{

using std::erase_if;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/vector/vector.hpp>
#include <hamon/algorithm/remove_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T, typename Alloc, typename Predicate>
inline HAMON_CXX14_CONSTEXPR
typename hamon::vector<T, Alloc>::size_type
erase_if(hamon::vector<T, Alloc>& c, Predicate pred)
{
	auto const sz = c.size();
	c.erase(hamon::remove_if(c.begin(), c.end(), pred), c.end());
	return sz - c.size();
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_VECTOR_ERASE_IF_HPP
