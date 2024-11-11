/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_MAP_ERASE_IF_HPP
#define HAMON_MAP_ERASE_IF_HPP

#include <map>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002) && \
	defined(HAMON_USE_STD_MAP) && defined(HAMON_USE_STD_MULTIMAP)

namespace hamon
{

using std::erase_if;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/map/map.hpp>
#include <hamon/map/multimap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 23.4.3.5 Erasure[map.erasure]

template <typename Key, typename T, typename Compare, typename Alloc, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hamon::map<Key, T, Compare, Alloc>::size_type
erase_if(hamon::map<Key, T, Compare, Alloc>& c, Predicate pred)
{
	// [map.erasure]/1
	auto const sz = c.size();
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
	return sz - c.size();
}

// 23.4.4.4 Erasure[multimap.erasure]

template <typename Key, typename T, typename Compare, typename Alloc, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hamon::multimap<Key, T, Compare, Alloc>::size_type
erase_if(hamon::multimap<Key, T, Compare, Alloc>& c, Predicate pred)
{
	// [multimap.erasure]/1
	auto const sz = c.size();
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
	return sz - c.size();
}

}	// namespace hamon

#endif	// __cpp_lib_erase_if

#endif // HAMON_MAP_ERASE_IF_HPP
