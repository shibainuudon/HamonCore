/**
 *	@file	multimap_fwd.hpp
 *
 *	@brief	multimap の前方宣言
 */

#ifndef HAMON_MAP_MULTIMAP_FWD_HPP
#define HAMON_MAP_MULTIMAP_FWD_HPP

#include <hamon/map/config.hpp>

#if defined(HAMON_USE_STD_MULTIMAP)

#include <map>

namespace hamon
{

using std::multimap;

}	// namespace hamon

#else

#include <hamon/functional/less.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/pair/pair_fwd.hpp>

namespace hamon
{

// [multimap], class template multimap
template <
	typename Key, typename T,
	typename Compare = hamon::less<Key>,
	typename Allocator = hamon::allocator<hamon::pair<const Key, T>>>
class multimap;

}	// namespace hamon

#endif

#endif // HAMON_MAP_MULTIMAP_FWD_HPP
