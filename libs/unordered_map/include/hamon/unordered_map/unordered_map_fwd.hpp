/**
 *	@file	unordered_map_fwd.hpp
 *
 *	@brief	unordered_map の前方宣言
 */

#ifndef HAMON_UNORDERED_MAP_UNORDERED_MAP_FWD_HPP
#define HAMON_UNORDERED_MAP_UNORDERED_MAP_FWD_HPP

#include <hamon/unordered_map/config.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/pair/pair_fwd.hpp>

#if defined(HAMON_USE_STD_UNORDERED_MAP)

#include <unordered_map>

namespace hamon
{

using std::unordered_map;

}	// namespace hamon

#else

#include <hamon/memory/allocator.hpp>

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

#include <hamon/memory_resource/polymorphic_allocator.hpp>

namespace hamon {
namespace pmr {

template <
	typename Key,
	typename T,
	typename Hash = hamon::hash<Key>,
	typename Pred = hamon::equal_to<Key>
>
using unordered_map =
	hamon::unordered_map<Key, T, Hash, Pred,
		hamon::pmr::polymorphic_allocator<hamon::pair<Key const, T>>>;

}	// namespace pmr
}	// namespace hamon

#endif // HAMON_UNORDERED_MAP_UNORDERED_MAP_FWD_HPP
