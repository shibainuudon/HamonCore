/**
 *	@file	uninitialized_fill_impl.hpp
 *
 *	@brief	uninitialized_fill_impl を定義
 */

#ifndef HAMON_MEMORY_DETAIL_UNINITIALIZED_FILL_IMPL_HPP
#define HAMON_MEMORY_DETAIL_UNINITIALIZED_FILL_IMPL_HPP

#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/algorithm/fill.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename ForwardIterator, typename T,
	typename RefType = hamon::iter_reference_t<ForwardIterator>,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_assignable<RefType, T const&>::value &&
		hamon::is_trivially_constructible<ValueType, T const&>::value
	>
>
HAMON_CXX20_CONSTEXPR void
uninitialized_fill_impl(
	ForwardIterator first, ForwardIterator last, T const& x,
	hamon::detail::overload_priority<2>)
{
	// fill関数であれば、可能ならmemsetを使う等の最適化が期待できるが、
	// constexprの文脈で未初期化領域に代入することはできない。
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
#endif
	{
		hamon::fill(first, last, x);
		return;
	}

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	return uninitialized_fill_impl(
		first, last, x, hamon::detail::overload_priority<1>{});
#endif
}

template <typename ForwardIterator, typename T,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_nothrow_constructible<ValueType, T const&>::value
	>
>
HAMON_CXX20_CONSTEXPR void
uninitialized_fill_impl(
	ForwardIterator first, ForwardIterator last, T const& x,
	hamon::detail::overload_priority<1>)
{
	// コンストラクタが例外を投げないのであれば、try-catchなどを省略できる。
	for (; first != last; ++first)
	{
		hamon::construct_at(hamon::addressof(*first), x);
	}
}

template <typename ForwardIterator, typename T>
HAMON_CXX20_CONSTEXPR void
uninitialized_fill_impl(
	ForwardIterator first, ForwardIterator last, T const& x,
	hamon::detail::overload_priority<0>)
{
	ForwardIterator current = first;
#if !defined(HAMON_NO_EXCEPTIONS)
	try
#endif
	{
		for (; current != last; ++current)
		{
			hamon::construct_at(hamon::addressof(*current), x);
		}
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	catch(...)
	{
		hamon::destroy(first, current);
		throw;
	}
#endif
}

template <typename ForwardIterator, typename T>
HAMON_CXX20_CONSTEXPR void
uninitialized_fill_impl(
	ForwardIterator first, ForwardIterator last, T const& x)
{
	return hamon::detail::uninitialized_fill_impl(
		first, last, x,
		hamon::detail::overload_priority<2>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_UNINITIALIZED_FILL_IMPL_HPP
