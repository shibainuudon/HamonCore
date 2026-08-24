/**
 *	@file	unordered_multiset_fwd.hpp
 *
 *	@brief	unordered_multiset の前方宣言
 */

#ifndef HAMON_UNORDERED_SET_UNORDERED_MULTISET_FWD_HPP
#define HAMON_UNORDERED_SET_UNORDERED_MULTISET_FWD_HPP

#include <hamon/functional/hash.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>

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

namespace pmr {

template <
	typename Key,
	typename Hash = hamon::hash<Key>,
	typename Pred = hamon::equal_to<Key>>
using unordered_multiset =
	hamon::unordered_multiset<Key, Hash, Pred, hamon::pmr::polymorphic_allocator<Key>>;

}	// namespace pmr

}	// namespace hamon

#endif // HAMON_UNORDERED_SET_UNORDERED_MULTISET_FWD_HPP
