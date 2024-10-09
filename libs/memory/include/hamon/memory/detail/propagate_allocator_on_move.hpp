/**
 *	@file	propagate_allocator_on_move.hpp
 *
 *	@brief	propagate_allocator_on_move を定義
 */

#ifndef HAMON_MEMORY_DETAIL_PROPAGATE_ALLOCATOR_ON_MOVE_HPP
#define HAMON_MEMORY_DETAIL_PROPAGATE_ALLOCATOR_ON_MOVE_HPP

#include <hamon/memory/allocator_traits.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Allocator,
	typename AllocTraits = hamon::allocator_traits<Allocator>,
	hamon::enable_if_t<
		AllocTraits::propagate_on_container_move_assignment::value
	>* = nullptr>
HAMON_CXX14_CONSTEXPR void
propagate_allocator_on_move(Allocator& x, Allocator& y)
{
	x = hamon::move(y);
}

template <typename Allocator,
	typename AllocTraits = hamon::allocator_traits<Allocator>,
	hamon::enable_if_t<
		!AllocTraits::propagate_on_container_move_assignment::value
	>* = nullptr>
HAMON_CXX14_CONSTEXPR void
propagate_allocator_on_move(Allocator&, Allocator&)
{
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_PROPAGATE_ALLOCATOR_ON_MOVE_HPP
