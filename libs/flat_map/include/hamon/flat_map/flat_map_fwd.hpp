/**
 *	@file	flat_map_fwd.hpp
 *
 *	@brief	flat_map の前方宣言
 */

#ifndef HAMON_FLAT_MAP_FLAT_MAP_FWD_HPP
#define HAMON_FLAT_MAP_FLAT_MAP_FWD_HPP

#include <hamon/functional/less.hpp>
#include <hamon/vector.hpp>

namespace hamon
{

template <
	typename Key,
	typename T,
	typename Compare = hamon::less<Key>,
	typename KeyContainer = hamon::vector<Key>,
	typename MappedContainer = hamon::vector<T>
>
class flat_map;

}	// namespace hamon

#endif // HAMON_FLAT_MAP_FLAT_MAP_FWD_HPP
