/**
 *	@file	forward_list_fwd.hpp
 *
 *	@brief	forward_list の前方宣言
 */

#ifndef HAMON_FORWARD_LIST_FORWARD_LIST_FWD_HPP
#define HAMON_FORWARD_LIST_FORWARD_LIST_FWD_HPP

#include <hamon/memory/allocator.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>

namespace hamon
{

template <typename T, typename Allocator = hamon::allocator<T>>
class forward_list;

namespace pmr {

template <typename T>
using forward_list = hamon::forward_list<T, hamon::pmr::polymorphic_allocator<T>>;

}	// namespace pmr

}	// namespace hamon

#endif // HAMON_FORWARD_LIST_FORWARD_LIST_FWD_HPP
