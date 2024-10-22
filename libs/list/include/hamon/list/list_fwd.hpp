/**
 *	@file	list_fwd.hpp
 *
 *	@brief	list の前方宣言
 */

#ifndef HAMON_LIST_LIST_FWD_HPP
#define HAMON_LIST_LIST_FWD_HPP

#include <hamon/list/config.hpp>

#if defined(HAMON_USE_STD_LIST)

#include <list>

namespace hamon
{

using std::list;

}	// namespace hamon

#else

#include <hamon/memory/allocator.hpp>

namespace hamon
{

// [list], class template list
template <typename T, typename Allocator = hamon::allocator<T>>
class list;

}	// namespace hamon

#endif

#endif // HAMON_LIST_LIST_FWD_HPP
