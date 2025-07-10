/**
 *	@file	map_fwd.hpp
 *
 *	@brief	map の前方宣言
 */

#ifndef HAMON_MAP_MAP_FWD_HPP
#define HAMON_MAP_MAP_FWD_HPP

#include <hamon/map/config.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/pair/pair_fwd.hpp>

#if defined(HAMON_USE_STD_MAP)

#include <map>

namespace hamon
{

using std::map;

}	// namespace hamon

#else

#include <hamon/memory/allocator.hpp>

namespace hamon
{

// [map], class template map
template <
	typename Key, typename T,
	typename Compare = hamon::less<Key>,
	typename Allocator = hamon::allocator<hamon::pair<Key const, T>>>
class map;

}	// namespace hamon

#endif

#include <hamon/memory_resource/polymorphic_allocator.hpp>

namespace hamon {
namespace pmr {

template <typename Key, typename T, typename Compare = hamon::less<Key>>
using map = hamon::map<Key, T, Compare, hamon::pmr::polymorphic_allocator<hamon::pair<Key const, T>>>;

}	// namespace pmr
}	// namespace hamon

#endif // HAMON_MAP_MAP_FWD_HPP
