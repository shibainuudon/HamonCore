/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_VECTOR_ERASE_HPP
#define HAMON_VECTOR_ERASE_HPP

#include <hamon/vector/config.hpp>

#if defined(HAMON_USE_STD_VECTOR) && \
	defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <vector>

namespace hamon
{

using std::erase;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/vector/vector.hpp>
#include <hamon/algorithm/remove.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [vector.erasure], erasure
template <typename T, typename Allocator, typename U = T>
HAMON_CXX14_CONSTEXPR
typename hamon::vector<T, Allocator>::size_type
erase(hamon::vector<T, Allocator>& c, U const& value)
{
	// [vector.erasure]/1
	auto it = hamon::remove(c.begin(), c.end(), value);
	auto r = hamon::distance(it, c.end());
	c.erase(it, c.end());
	return static_cast<typename hamon::vector<T, Allocator>::size_type>(r);
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_VECTOR_ERASE_HPP
