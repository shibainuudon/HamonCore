/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_UNORDERED_SET_ERASE_IF_HPP
#define HAMON_UNORDERED_SET_ERASE_IF_HPP

#include <unordered_set>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

namespace hamon
{

using std::erase_if;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename Key, typename Hash, typename CPred, typename Alloc, typename Predicate>
inline HAMON_CXX14_CONSTEXPR
typename hamon::unordered_set<Key, Hash, CPred, Alloc>::size_type
erase_if(hamon::unordered_set<Key, Hash, CPred, Alloc>& c, Predicate pred)
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

template <typename Key, typename Hash, typename CPred, typename Alloc, typename Predicate>
inline HAMON_CXX14_CONSTEXPR
typename hamon::unordered_multiset<Key, Hash, CPred, Alloc>::size_type
erase_if(hamon::unordered_multiset<Key, Hash, CPred, Alloc>& c, Predicate pred)
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

#endif // HAMON_UNORDERED_SET_ERASE_IF_HPP
