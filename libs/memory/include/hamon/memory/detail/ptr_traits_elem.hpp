/**
 *	@file	ptr_traits_elem.hpp
 *
 *	@brief	ptr_traits_elem を定義
 */

#ifndef HAMON_MEMORY_DETAIL_PTR_TRAITS_ELEM_HPP
#define HAMON_MEMORY_DETAIL_PTR_TRAITS_ELEM_HPP

#include <hamon/type_traits/void_t.hpp>

namespace hamon
{

namespace detail
{

// 20.2.3.2 Member types[pointer.traits.types]/1

template <typename T, typename = void>
struct ptr_traits_elem_impl
{};

template <template <typename...> class SomePointer, typename T, typename... Args>
struct ptr_traits_elem_impl<SomePointer<T, Args...>>
{
	using type = T;
};

template <typename T, typename = void>
struct ptr_traits_elem
	: public ptr_traits_elem_impl<T>
{};

template <typename T>
struct ptr_traits_elem<T, hamon::void_t<typename T::element_type>>
{
	using type = typename T::element_type;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_PTR_TRAITS_ELEM_HPP
