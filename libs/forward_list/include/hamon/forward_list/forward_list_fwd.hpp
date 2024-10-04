/**
 *	@file	forward_list_fwd.hpp
 *
 *	@brief	forward_list の前方宣言
 */

#ifndef HAMON_FORWARD_LIST_FORWARD_LIST_FWD_HPP
#define HAMON_FORWARD_LIST_FORWARD_LIST_FWD_HPP

#include <hamon/forward_list/config.hpp>

#if defined(HAMON_USE_STD_FORWARD_LIST)

#include <forward_list>

namespace hamon
{

using std::forward_list;

}	// namespace hamon

#else

#include <hamon/memory/allocator.hpp>

namespace hamon
{

template <typename T, typename Allocator = hamon::allocator<T>>
class forward_list;

}	// namespace hamon

#endif

#endif // HAMON_FORWARD_LIST_FORWARD_LIST_FWD_HPP
