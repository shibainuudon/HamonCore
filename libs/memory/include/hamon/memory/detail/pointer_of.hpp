/**
 *	@file	pointer_of.hpp
 *
 *	@brief	POINTER_OF を定義
 */

#ifndef HAMON_MEMORY_DETAIL_POINTER_OF_HPP
#define HAMON_MEMORY_DETAIL_POINTER_OF_HPP

#include <hamon/memory/pointer_traits.hpp>
#include <hamon/detail/overload_priority.hpp>

namespace hamon
{

namespace detail
{

// 20.2.2 Header <memory> synopsis[memory.syn]

// [memory.syn]/2.1
template <typename T, typename Ret = typename T::pointer>
Ret pointer_of_impl(hamon::detail::overload_priority<2>);

// [memory.syn]/2.2
template <typename T, typename Ret = typename T::element_type*>
Ret pointer_of_impl(hamon::detail::overload_priority<1>);

// [memory.syn]/2.3
template <typename T, typename Ret = typename hamon::pointer_traits<T>::element_type*>
Ret pointer_of_impl(hamon::detail::overload_priority<0>);

// [memory.syn]/2
template <typename T>
using POINTER_OF = decltype(pointer_of_impl<T>(hamon::detail::overload_priority<2>{}));

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_POINTER_OF_HPP
