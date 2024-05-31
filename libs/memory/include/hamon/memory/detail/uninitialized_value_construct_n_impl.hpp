/**
 *	@file	uninitialized_value_construct_n_impl.hpp
 *
 *	@brief	uninitialized_value_construct_n_impl を定義
 */

#ifndef HAMON_MEMORY_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_N_IMPL_HPP
#define HAMON_MEMORY_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_N_IMPL_HPP

#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Iter, typename Size,
	typename ValueType = hamon::iter_value_t<Iter>,
	typename = hamon::enable_if_t<
		hamon::is_nothrow_default_constructible<ValueType>::value
	>
>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_value_construct_n_impl(
	Iter first, Size n,
	hamon::detail::overload_priority<1>)
{
	// コンストラクタが例外を投げないのであれば、try-catchなどを省略できる。
	for (; n > 0; --n)
	{
		hamon::construct_at(hamon::addressof(*first));
		++first;
	}
	return first;
}

template <typename Iter, typename Size>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_value_construct_n_impl(
	Iter first, Size n,
	hamon::detail::overload_priority<0>)
{
	Iter current = first;
#if !defined(HAMON_NO_EXCEPTIONS)
	try
#endif
	{
		for (; n > 0; --n)
		{
			hamon::construct_at(hamon::addressof(*current));
			++current;
		}
		return current;
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	catch(...)
	{
		hamon::destroy(first, current);
		throw;
	}
#endif
}

template <typename Iter, typename Size>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_value_construct_n_impl(Iter first, Size n)
{
	return hamon::detail::uninitialized_value_construct_n_impl(
		first, n,
		hamon::detail::overload_priority<1>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_UNINITIALIZED_VALUE_CONSTRUCT_N_IMPL_HPP
