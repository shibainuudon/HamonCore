/**
 *	@file	uninitialized_value_construct_n_md.hpp
 *
 *	@brief	uninitialized_value_construct_n_md を定義
 */

#ifndef HAMON_MEMORY_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_N_MD_HPP
#define HAMON_MEMORY_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_N_MD_HPP

#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/extent.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR void
uninitialized_value_construct_n_md(T* dst, hamon::size_t n);

template <typename T, typename = hamon::enable_if_t<hamon::is_array<T>::value>>
HAMON_CXX14_CONSTEXPR void
uninitialized_value_construct_n_md_impl(T* dst, hamon::size_t n, hamon::detail::overload_priority<1>)
{
	for (hamon::size_t i = 0; i < n; ++i)
	{
		uninitialized_value_construct_n_md(dst[i], hamon::extent<T>::value);
	}
}

template <typename T>
HAMON_CXX14_CONSTEXPR void
uninitialized_value_construct_n_md_impl(T* dst, hamon::size_t n, hamon::detail::overload_priority<0>)
{
	hamon::detail::uninitialized_value_construct_n_impl(dst, n);
}

template <typename T>
HAMON_CXX14_CONSTEXPR void
uninitialized_value_construct_n_md(T* dst, hamon::size_t n)
{
	uninitialized_value_construct_n_md_impl(dst, n, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_N_MD_HPP
