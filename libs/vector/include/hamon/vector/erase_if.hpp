/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_VECTOR_ERASE_IF_HPP
#define HAMON_VECTOR_ERASE_IF_HPP

#include <hamon/vector/config.hpp>

#if defined(HAMON_USE_STD_VECTOR) && defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

#include <vector>

namespace hamon
{

using std::erase_if;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/vector/vector.hpp>
#include <hamon/algorithm/remove_if.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [vector.erasure], erasure
template <typename T, typename Allocator, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hamon::vector<T, Allocator>::size_type
erase_if(hamon::vector<T, Allocator>& c, Predicate pred)
{
	// [vector.erasure]/2
	auto it = hamon::remove_if(c.begin(), c.end(), pred);
	auto r = hamon::distance(it, c.end());
	c.erase(it, c.end());
	return static_cast<typename hamon::vector<T, Allocator>::size_type>(r);
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_VECTOR_ERASE_IF_HPP
