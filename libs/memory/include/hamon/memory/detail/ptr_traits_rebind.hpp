/**
 *	@file	ptr_traits_rebind.hpp
 *
 *	@brief	ptr_traits_rebind を定義
 */

#ifndef HAMON_MEMORY_DETAIL_PTR_TRAITS_REBIND_HPP
#define HAMON_MEMORY_DETAIL_PTR_TRAITS_REBIND_HPP

#include <hamon/memory/detail/replace_first_arg.hpp>
#include <hamon/type_traits/void_t.hpp>

namespace hamon
{

namespace detail
{

// 20.2.3.2 Member types[pointer.traits.types]/6

template <typename T, typename U, typename = void>
struct ptr_traits_rebind
{
	using type = typename hamon::detail::replace_first_arg<T, U>::type;
};

template <typename T, typename U>
struct ptr_traits_rebind<T, U, hamon::void_t<typename T::template rebind<U>>>
{
	using type = typename T::template rebind<U>;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_PTR_TRAITS_REBIND_HPP
