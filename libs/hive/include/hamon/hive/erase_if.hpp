/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_HIVE_ERASE_IF_HPP
#define HAMON_HIVE_ERASE_IF_HPP

#include <hamon/hive/config.hpp>

#if defined(HAMON_USE_STD_HIVE)

#include <hive>

namespace hamon
{

using std::erase_if;

}	// namespace hamon

#else

#include <hamon/hive/hive.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 23.3.9.6 Erasure[hive.erasure]

template <typename T, typename Allocator, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hamon::hive<T, Allocator>::size_type
erase_if(hamon::hive<T, Allocator>& c, Predicate pred)
{
	// [hive.erasure]/2
	auto original_size = c.size();
	for (auto i = c.begin(), last = c.end(); i != last; )
	{
		if (pred(*i))
		{
			i = c.erase(i);
		}
		else
		{
			++i;
		}
	}
	return original_size - c.size();
}

}	// namespace hamon

#endif

#endif // HAMON_HIVE_ERASE_IF_HPP
