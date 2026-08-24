/**
 *	@file	multiset_fwd.hpp
 *
 *	@brief	multiset の前方宣言
 */

#ifndef HAMON_SET_MULTISET_FWD_HPP
#define HAMON_SET_MULTISET_FWD_HPP

#include <hamon/functional/less.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>

namespace hamon
{

// [multiset], class template multiset
template <
	typename Key,
	typename Compare = hamon::less<Key>,
	typename Allocator = hamon::allocator<Key>>
class multiset;

namespace pmr {

template <typename Key, typename Compare = hamon::less<Key>>
using multiset = hamon::multiset<Key, Compare, hamon::pmr::polymorphic_allocator<Key>>;

}	// namespace pmr

}	// namespace hamon

#endif // HAMON_SET_MULTISET_FWD_HPP
