/**
 *	@file	pointer_of_or.hpp
 *
 *	@brief	POINTER_OF_OR を定義
 */

#ifndef HAMON_MEMORY_DETAIL_POINTER_OF_OR_HPP
#define HAMON_MEMORY_DETAIL_POINTER_OF_OR_HPP

#include <hamon/memory/detail/pointer_of.hpp>
#include <hamon/detail/overload_priority.hpp>

namespace hamon
{

namespace detail
{

// 20.2.2 Header <memory> synopsis[memory.syn]

// [memory.syn]/3.1
template <typename T, typename U, typename Ret = POINTER_OF<T>>
Ret pointer_of_or_impl(hamon::detail::overload_priority<1>);

// [memory.syn]/3.2
template <typename T, typename U>
U pointer_of_or_impl(hamon::detail::overload_priority<0>);

// [memory.syn]/3
template <typename T, typename U>
using POINTER_OF_OR = decltype(pointer_of_or_impl<T, U>(hamon::detail::overload_priority<1>{}));

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_POINTER_OF_OR_HPP
