/**
 *	@file	unordered_map_fwd.hpp
 *
 *	@brief	unordered_map の前方宣言
 */

#ifndef HAMON_UNORDERED_MAP_UNORDERED_MAP_FWD_HPP
#define HAMON_UNORDERED_MAP_UNORDERED_MAP_FWD_HPP

#include <hamon/unordered_map/config.hpp>

#if defined(HAMON_USE_STD_UNORDERED_MAP)

#include <unordered_map>

namespace hamon
{

using std::unordered_map;

}	// namespace hamon

#else

#include <hamon/functional/hash.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/pair/pair_fwd.hpp>

namespace hamon
{

// [unord.map], class template unordered_map
template <
	typename Key,
	typename T,
	typename Hash = hamon::hash<Key>,
	typename Pred = hamon::equal_to<Key>,
	typename Alloc = hamon::allocator<hamon::pair<Key const, T>>
>
class unordered_map;

}	// namespace hamon

#endif

#endif // HAMON_UNORDERED_MAP_UNORDERED_MAP_FWD_HPP
