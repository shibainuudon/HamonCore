/**
 *	@file	is_implicitly_uses_allocator_constructible.hpp
 *
 *	@brief	is_implicitly_uses_allocator_constructible を定義
 */

#ifndef HAMON_MEMORY_DETAIL_IS_IMPLICITLY_USES_ALLOCATOR_CONSTRUCTIBLE_HPP
#define HAMON_MEMORY_DETAIL_IS_IMPLICITLY_USES_ALLOCATOR_CONSTRUCTIBLE_HPP

#include <hamon/memory/detail/uses_allocator_construction_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace detail
{

namespace impl
{

template <typename T, typename Alloc, typename... Args>
struct is_implicitly_uses_allocator_constructible_impl
{
	using args_type = hamon::detail::uses_allocator_construction_type_t<T, Alloc, Args...>;

	using type =
		hamon::conditional_t<
			hamon::is_same<args_type, hamon::detail::uses_allocator_construction_type::NoAlloc>::value,
			hamon::is_implicitly_constructible<T, Args...>,
		hamon::conditional_t<
			hamon::is_same<args_type, hamon::detail::uses_allocator_construction_type::FirstAlloc>::value,
			hamon::is_implicitly_constructible<T, hamon::allocator_arg_t, Alloc const&, Args...>,
		hamon::conditional_t<
			hamon::is_same<args_type, hamon::detail::uses_allocator_construction_type::LastAlloc>::value,
			hamon::is_implicitly_constructible<T, Args..., Alloc const&>,
			hamon::false_type
		>>>;
};

}	// namespace impl

template <typename T, typename Alloc, typename... Args>
using is_implicitly_uses_allocator_constructible =
	typename impl::is_implicitly_uses_allocator_constructible_impl<T, Alloc, Args...>::type;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_IS_IMPLICITLY_USES_ALLOCATOR_CONSTRUCTIBLE_HPP
