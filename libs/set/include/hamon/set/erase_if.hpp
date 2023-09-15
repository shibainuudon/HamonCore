/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_SET_ERASE_IF_HPP
#define HAMON_SET_ERASE_IF_HPP

#include <set>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

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

template <typename Key, typename Compare, typename Alloc, typename Predicate>
inline HAMON_CXX14_CONSTEXPR
typename hamon::set<Key, Compare, Alloc>::size_type
erase_if(hamon::set<Key, Compare, Alloc>& c, Predicate pred)
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

template <typename Key, typename Compare, typename Alloc, typename Predicate>
inline HAMON_CXX14_CONSTEXPR
typename hamon::multiset<Key, Compare, Alloc>::size_type
erase_if(hamon::multiset<Key, Compare, Alloc>& c, Predicate pred)
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

#endif // HAMON_SET_ERASE_IF_HPP
