/**
 *	@file	uninitialized_fill_n_md.hpp
 *
 *	@brief	uninitialized_fill_n_md を定義
 */

#ifndef HAMON_MEMORY_DETAIL_UNINITIALIZED_FILL_N_MD_HPP
#define HAMON_MEMORY_DETAIL_UNINITIALIZED_FILL_N_MD_HPP

#include <hamon/memory/detail/uninitialized_copy_n_md.hpp>
#include <hamon/memory/detail/uninitialized_fill_n_impl.hpp>
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

template <typename T, typename = hamon::enable_if_t<hamon::is_array<T>::value>>
HAMON_CXX14_CONSTEXPR void
uninitialized_fill_n_md_impl(T* dst, hamon::size_t n, T const& x, hamon::detail::overload_priority<1>)
{
	for (hamon::size_t i = 0; i < n; ++i)
	{
		hamon::detail::uninitialized_copy_n_md(x, hamon::extent<T>::value, dst[i]);
	}
}

template <typename T>
HAMON_CXX14_CONSTEXPR void
uninitialized_fill_n_md_impl(T* dst, hamon::size_t n, T const& x, hamon::detail::overload_priority<0>)
{
	hamon::detail::uninitialized_fill_n_impl(dst, n, x);
}

template <typename T>
HAMON_CXX14_CONSTEXPR void
uninitialized_fill_n_md(T* dst, hamon::size_t n, T const& x)
{
	uninitialized_fill_n_md_impl(dst, n, x, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_UNINITIALIZED_FILL_N_MD_HPP
