/**
 *	@file	multimap_fwd.hpp
 *
 *	@brief	multimap の前方宣言
 */

#ifndef HAMON_MAP_MULTIMAP_FWD_HPP
#define HAMON_MAP_MULTIMAP_FWD_HPP

#include <hamon/functional/less.hpp>
#include <hamon/pair/pair_fwd.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>

namespace hamon
{

// [multimap], class template multimap
template <
	typename Key, typename T,
	typename Compare = hamon::less<Key>,
	typename Allocator = hamon::allocator<hamon::pair<Key const, T>>>
class multimap;

namespace pmr {

template <typename Key, typename T, typename Compare = hamon::less<Key>>
using multimap = hamon::multimap<Key, T, Compare, hamon::pmr::polymorphic_allocator<hamon::pair<Key const, T>>>;

}	// namespace pmr

}	// namespace hamon

#endif // HAMON_MAP_MULTIMAP_FWD_HPP
