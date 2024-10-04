/**
 *	@file	equals_allocator.hpp
 *
 *	@brief	equals_allocator を定義
 */

#ifndef HAMON_MEMORY_DETAIL_EQUALS_ALLOCATOR_HPP
#define HAMON_MEMORY_DETAIL_EQUALS_ALLOCATOR_HPP

#include <hamon/memory/allocator_traits.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Allocator,
	hamon::enable_if_t<
		hamon::allocator_traits<Allocator>::is_always_equal::value
	>* = nullptr>
HAMON_CXX11_CONSTEXPR bool
equals_allocator(Allocator const&, Allocator const&)
{
	return true;
}

template <typename Allocator,
	hamon::enable_if_t<
		!hamon::allocator_traits<Allocator>::is_always_equal::value
	>* = nullptr>
HAMON_CXX11_CONSTEXPR bool
equals_allocator(Allocator const& x, Allocator const& y)
{
	return x == y;
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_EQUALS_ALLOCATOR_HPP
