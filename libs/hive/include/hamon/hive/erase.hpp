/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_HIVE_ERASE_HPP
#define HAMON_HIVE_ERASE_HPP

#include <hamon/hive/config.hpp>

#if defined(HAMON_USE_STD_HIVE)

#include <hive>

namespace hamon
{

using std::erase;

}	// namespace hamon

#else

#include <hamon/hive/hive.hpp>
#include <hamon/hive/erase_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 23.3.9.6 Erasure[hive.erasure]

template <typename T, typename Allocator, typename U = T>
HAMON_CXX14_CONSTEXPR
typename hamon::hive<T, Allocator>::size_type
erase(hamon::hive<T, Allocator>& c, const U& value)
{
	// [hive.erasure]/1
	using const_reference = typename hamon::hive<T, Allocator>::const_reference;
	return hamon::erase_if(c, [&](const_reference elem) -> bool { return elem == value; });
}

}	// namespace hamon

#endif

#endif // HAMON_HIVE_ERASE_HPP
