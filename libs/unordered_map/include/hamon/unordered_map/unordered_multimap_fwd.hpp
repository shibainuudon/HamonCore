/**
 *	@file	unordered_multimap_fwd.hpp
 *
 *	@brief	unordered_multimap の前方宣言
 */

#ifndef HAMON_UNORDERED_MAP_UNORDERED_MULTIMAP_FWD_HPP
#define HAMON_UNORDERED_MAP_UNORDERED_MULTIMAP_FWD_HPP

#include <hamon/unordered_map/config.hpp>

#if defined(HAMON_USE_STD_UNORDERED_MULTIMAP)

#include <unordered_map>

namespace hamon
{

using std::unordered_multimap;

}	// namespace hamon

#else

#include <hamon/functional/hash.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/pair/pair_fwd.hpp>

namespace hamon
{

// [unord.multimap], class template unordered_multimap
template <
	typename Key,
	typename T,
	typename Hash = hamon::hash<Key>,
	typename Pred = hamon::equal_to<Key>,
	typename Alloc = hamon::allocator<hamon::pair<Key const, T>>
>
class unordered_multimap;

}	// namespace hamon

#endif

#endif // HAMON_UNORDERED_MAP_UNORDERED_MULTIMAP_FWD_HPP
