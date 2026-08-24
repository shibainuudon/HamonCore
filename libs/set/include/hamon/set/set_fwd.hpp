/**
 *	@file	set_fwd.hpp
 *
 *	@brief	set の前方宣言
 */

#ifndef HAMON_SET_SET_FWD_HPP
#define HAMON_SET_SET_FWD_HPP

#include <hamon/functional/less.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>

namespace hamon
{

// [set], class template set
template <
	typename Key,
	typename Compare = hamon::less<Key>,
	typename Allocator = hamon::allocator<Key>>
class set;

namespace pmr {

template <typename Key, typename Compare = hamon::less<Key>>
using set = hamon::set<Key, Compare, hamon::pmr::polymorphic_allocator<Key>>;

}	// namespace pmr

}	// namespace hamon

#endif // HAMON_SET_SET_FWD_HPP
