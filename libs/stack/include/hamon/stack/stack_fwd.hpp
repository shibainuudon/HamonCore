/**
 *	@file	stack_fwd.hpp
 *
 *	@brief	stack の前方宣言
 */

#ifndef HAMON_STACK_STACK_FWD_HPP
#define HAMON_STACK_STACK_FWD_HPP

#include <hamon/stack/config.hpp>

#if defined(HAMON_USE_STD_STACK)

#include <stack>

namespace hamon
{

using std::stack;

}	// namespace hamon

#else

#include <hamon/deque.hpp>

namespace hamon
{

// [stack], class template stack
template <typename T, typename Container = hamon::deque<T>>
class stack;

}	// namespace hamon

#endif

#endif // HAMON_STACK_STACK_FWD_HPP
