/**
 *	@file	ptr_traits_diff.hpp
 *
 *	@brief	ptr_traits_diff を定義
 */

#ifndef HAMON_MEMORY_DETAIL_PTR_TRAITS_DIFF_HPP
#define HAMON_MEMORY_DETAIL_PTR_TRAITS_DIFF_HPP

#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/void_t.hpp>

namespace hamon
{

namespace detail
{

// 20.2.3.2 Member types[pointer.traits.types]/5

template <typename T, typename = void>
struct ptr_traits_diff
{
	using type = hamon::ptrdiff_t;
};

template <typename T>
struct ptr_traits_diff<T, hamon::void_t<typename T::difference_type>>
{
	using type = typename T::difference_type;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_PTR_TRAITS_DIFF_HPP
