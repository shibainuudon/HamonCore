/**
 *	@file	list_fwd.hpp
 *
 *	@brief	list の前方宣言
 */

#ifndef HAMON_LIST_LIST_FWD_HPP
#define HAMON_LIST_LIST_FWD_HPP

#include <hamon/memory/allocator.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>

namespace hamon
{

// [list], class template list
template <typename T, typename Allocator = hamon::allocator<T>>
class list;

namespace pmr {

template <typename T>
using list = hamon::list<T, hamon::pmr::polymorphic_allocator<T>>;

}	// namespace pmr

}	// namespace hamon

#endif // HAMON_LIST_LIST_FWD_HPP
