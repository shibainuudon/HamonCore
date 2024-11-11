/**
 *	@file	map_fwd.hpp
 *
 *	@brief	map の前方宣言
 */

#ifndef HAMON_MAP_MAP_FWD_HPP
#define HAMON_MAP_MAP_FWD_HPP

#include <hamon/map/config.hpp>

#if defined(HAMON_USE_STD_MAP)

#include <map>

namespace hamon
{

using std::map;

}	// namespace hamon

#else

#include <hamon/functional/less.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/pair/pair_fwd.hpp>

namespace hamon
{

// [map], class template map
template <
	typename Key, typename T,
	typename Compare = hamon::less<Key>,
	typename Allocator = hamon::allocator<hamon::pair<const Key, T>>>
class map;

}	// namespace hamon

#endif

#endif // HAMON_MAP_MAP_FWD_HPP
