/**
 *	@file	deque_fwd.hpp
 *
 *	@brief	deque の前方宣言
 */

#ifndef HAMON_DEQUE_DEQUE_FWD_HPP
#define HAMON_DEQUE_DEQUE_FWD_HPP

#include <hamon/deque/config.hpp>

#if defined(HAMON_USE_STD_DEQUE)

#include <deque>

namespace hamon
{

using std::deque;

}	// namespace hamon

#else

#include <hamon/memory/allocator.hpp>

namespace hamon
{

// 24.3.3 Header <deque> synopsis[deque.syn]

template <typename T, typename Allocator = hamon::allocator<T>>
class deque;

}	// namespace hamon

#endif

#include <hamon/memory_resource/polymorphic_allocator.hpp>

namespace hamon {
namespace pmr {

template <typename T>
using deque = hamon::deque<T, hamon::pmr::polymorphic_allocator<T>>;

}	// namespace pmr
}	// namespace hamon

#endif // HAMON_DEQUE_DEQUE_HPP
