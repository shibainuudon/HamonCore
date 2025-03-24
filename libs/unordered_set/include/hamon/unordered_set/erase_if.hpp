/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_UNORDERED_SET_ERASE_IF_HPP
#define HAMON_UNORDERED_SET_ERASE_IF_HPP

#include <hamon/unordered_set/config.hpp>
#include <unordered_set>

#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002) && \
	defined(HAMON_USE_STD_UNORDERED_SET) && defined(HAMON_USE_STD_UNORDERED_MULTISET)

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

// 23.5.6.3 Erasure[unord.set.erasure]

template <typename K, typename H, typename P, typename A, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename unordered_set<K, H, P, A>::size_type
erase_if(unordered_set<K, H, P, A>& c, Predicate pred)
{
	// [unord.set.erasure]/1
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

// 23.5.7.3 Erasure[unord.multiset.erasure]

template <typename K, typename H, typename P, typename A, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename unordered_multiset<K, H, P, A>::size_type
erase_if(unordered_multiset<K, H, P, A>& c, Predicate pred)
{
	// [unord.multiset.erasure]/1
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

#endif // HAMON_UNORDERED_SET_ERASE_IF_HPP
