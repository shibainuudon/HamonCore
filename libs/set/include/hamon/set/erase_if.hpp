/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_SET_ERASE_IF_HPP
#define HAMON_SET_ERASE_IF_HPP

#include <set>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002) && \
	defined(HAMON_USE_STD_SET) && defined(HAMON_USE_STD_MULTISET)

namespace hamon
{

using std::erase_if;

}	// namespace hamon

#else	// __cpp_lib_erase_if

#include <hamon/set/set.hpp>
#include <hamon/set/multiset.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 23.4.6.3 Erasure[set.erasure]

template <typename Key, typename Compare, typename Alloc, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hamon::set<Key, Compare, Alloc>::size_type
erase_if(hamon::set<Key, Compare, Alloc>& c, Predicate pred)
{
	// [set.erasure]/1
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

// 23.4.7.3 Erasure[multiset.erasure]

template <typename Key, typename Compare, typename Alloc, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hamon::multiset<Key, Compare, Alloc>::size_type
erase_if(hamon::multiset<Key, Compare, Alloc>& c, Predicate pred)
{
	// [multiset.erasure]/1
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

#endif // HAMON_SET_ERASE_IF_HPP
