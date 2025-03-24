/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_UNORDERED_MAP_ERASE_IF_HPP
#define HAMON_UNORDERED_MAP_ERASE_IF_HPP

#include <hamon/unordered_map/config.hpp>
#include <unordered_map>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002) && \
	defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_USE_STD_UNORDERED_MULTIMAP)

namespace hamon
{

using std::erase_if;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 23.5.3.5 Erasure[unord.map.erasure]

template <typename K, typename T, typename H, typename P, typename A, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename unordered_map<K, T, H, P, A>::size_type
erase_if(unordered_map<K, T, H, P, A>& c, Predicate pred)
{
	// [unord.map.erasure]/1
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

// 23.5.4.4 Erasure[unord.multimap.erasure]

template <typename K, typename T, typename H, typename P, typename A, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename unordered_multimap<K, T, H, P, A>::size_type
erase_if(unordered_multimap<K, T, H, P, A>& c, Predicate pred)
{
	// [unord.multimap.erasure]/1
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

#endif	// __cpp_lib_erase_if

#endif // HAMON_UNORDERED_MAP_ERASE_IF_HPP
