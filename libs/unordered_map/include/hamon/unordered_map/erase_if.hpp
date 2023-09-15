/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_UNORDERED_MAP_ERASE_IF_HPP
#define HAMON_UNORDERED_MAP_ERASE_IF_HPP

#include <unordered_map>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

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

template <typename Key, typename T, typename Hash, typename CPred, typename Alloc, typename Predicate>
inline HAMON_CXX14_CONSTEXPR
typename hamon::unordered_map<Key, T, Hash, CPred, Alloc>::size_type
erase_if(hamon::unordered_map<Key, T, Hash, CPred, Alloc>& c, Predicate pred)
{
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

template <typename Key, typename T, typename Hash, typename CPred, typename Alloc, typename Predicate>
inline HAMON_CXX14_CONSTEXPR
typename hamon::unordered_multimap<Key, T, Hash, CPred, Alloc>::size_type
erase_if(hamon::unordered_multimap<Key, T, Hash, CPred, Alloc>& c, Predicate pred)
{
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

#endif // HAMON_UNORDERED_MAP_ERASE_IF_HPP
