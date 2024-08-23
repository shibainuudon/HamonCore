/**
 *	@file	uninitialized_copy_n_md.hpp
 *
 *	@brief	uninitialized_copy_n_md を定義
 */

#ifndef HAMON_MEMORY_DETAIL_UNINITIALIZED_COPY_N_MD_HPP
#define HAMON_MEMORY_DETAIL_UNINITIALIZED_COPY_N_MD_HPP

#include <hamon/memory/detail/uninitialized_copy_n_impl.hpp>
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
uninitialized_copy_n_md(T const* src, hamon::size_t n, T* dst);

template <typename T, typename = hamon::enable_if_t<hamon::is_array<T>::value>>
HAMON_CXX14_CONSTEXPR void
uninitialized_copy_n_md_impl(T const* src, hamon::size_t n, T* dst, hamon::detail::overload_priority<1>)
{
	for (hamon::size_t i = 0; i < n; ++i)
	{
		uninitialized_copy_n_md(src[i], hamon::extent<T>::value, dst[i]);
	}
}

template <typename T>
HAMON_CXX14_CONSTEXPR void
uninitialized_copy_n_md_impl(T const* src, hamon::size_t n, T* dst, hamon::detail::overload_priority<0>)
{
	hamon::detail::uninitialized_copy_n_impl(src, n, dst);
}

template <typename T>
HAMON_CXX14_CONSTEXPR void
uninitialized_copy_n_md(T const* src, hamon::size_t n, T* dst)
{
	uninitialized_copy_n_md_impl(src, n, dst, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_UNINITIALIZED_COPY_N_MD_HPP
