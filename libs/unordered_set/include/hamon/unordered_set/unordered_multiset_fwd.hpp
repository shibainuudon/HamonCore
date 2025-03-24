/**
 *	@file	unordered_multiset_fwd.hpp
 *
 *	@brief	unordered_multiset の前方宣言
 */

#ifndef HAMON_UNORDERED_SET_UNORDERED_MULTISET_FWD_HPP
#define HAMON_UNORDERED_SET_UNORDERED_MULTISET_FWD_HPP

#include <hamon/unordered_set/config.hpp>

#if defined(HAMON_USE_STD_UNORDERED_MULTISET)

#include <unordered_set>

namespace hamon
{

using std::unordered_multiset;

}	// namespace hamon

#else

#include <hamon/functional/hash.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/memory/allocator.hpp>

namespace hamon
{

// [unord.multiset], class template unordered_multiset
template <
	typename Key,
	typename Hash = hamon::hash<Key>,
	typename Pred = hamon::equal_to<Key>,
	typename Alloc = hamon::allocator<Key>
>
class unordered_multiset;

}	// namespace hamon

#endif

#endif // HAMON_UNORDERED_SET_UNORDERED_MULTISET_FWD_HPP
