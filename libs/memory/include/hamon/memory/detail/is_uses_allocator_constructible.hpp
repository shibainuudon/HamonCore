/**
 *	@file	is_uses_allocator_constructible.hpp
 *
 *	@brief	is_uses_allocator_constructible を定義
 */

#ifndef HAMON_MEMORY_DETAIL_IS_USES_ALLOCATOR_CONSTRUCTIBLE_HPP
#define HAMON_MEMORY_DETAIL_IS_USES_ALLOCATOR_CONSTRUCTIBLE_HPP

#include <hamon/memory/detail/uses_allocator_construction_type.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename Alloc, typename... Args>
using is_uses_allocator_constructible =
	hamon::negation<hamon::is_same<
		hamon::detail::uses_allocator_construction_type_t<T, Alloc, Args...>,
		hamon::detail::uses_allocator_construction_type::Invalid
	>>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_IS_USES_ALLOCATOR_CONSTRUCTIBLE_HPP
