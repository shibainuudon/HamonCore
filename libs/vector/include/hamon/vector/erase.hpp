/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_VECTOR_ERASE_HPP
#define HAMON_VECTOR_ERASE_HPP

#include <vector>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

namespace hamon
{

using std::erase;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/vector/vector.hpp>
#include <hamon/algorithm/remove.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T, typename Alloc, typename U>
inline HAMON_CXX14_CONSTEXPR
typename hamon::vector<T, Alloc>::size_type
erase(hamon::vector<T, Alloc>& c, U const& value)
{
	auto const sz = c.size();
	c.erase(hamon::remove(c.begin(), c.end(), value), c.end());
	return sz - c.size();
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_VECTOR_ERASE_HPP
