/**
 *	@file	propagate_allocator_on_swap.hpp
 *
 *	@brief	propagate_allocator_on_swap を定義
 */

#ifndef HAMON_MEMORY_DETAIL_PROPAGATE_ALLOCATOR_ON_SWAP_HPP
#define HAMON_MEMORY_DETAIL_PROPAGATE_ALLOCATOR_ON_SWAP_HPP

#include <hamon/memory/allocator_traits.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Allocator,
	typename AllocTraits = hamon::allocator_traits<Allocator>,
	hamon::enable_if_t<
		AllocTraits::propagate_on_container_swap::value
	>* = nullptr>
HAMON_CXX14_CONSTEXPR void
propagate_allocator_on_swap(Allocator& x, Allocator& y)
{
	hamon::swap(x, y);
}

template <typename Allocator,
	typename AllocTraits = hamon::allocator_traits<Allocator>,
	hamon::enable_if_t<
		!AllocTraits::propagate_on_container_swap::value
	>* = nullptr>
HAMON_CXX14_CONSTEXPR void
propagate_allocator_on_swap(Allocator&, Allocator&)
{
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_PROPAGATE_ALLOCATOR_ON_SWAP_HPP
