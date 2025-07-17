/**
 *	@file	uninitialized_fill_n_impl.hpp
 *
 *	@brief	uninitialized_fill_n_impl を定義
 */

#ifndef HAMON_MEMORY_DETAIL_UNINITIALIZED_FILL_N_IMPL_HPP
#define HAMON_MEMORY_DETAIL_UNINITIALIZED_FILL_N_IMPL_HPP

#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/destroy_impl.hpp>
#include <hamon/algorithm/ranges/fill_n.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Allocator, typename Iter, typename Size, typename T,
	typename RefType = hamon::iter_reference_t<Iter>,
	typename ValueType = hamon::iter_value_t<Iter>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_assignable<RefType, T const&>::value &&
		hamon::is_trivially_constructible<ValueType, T const&>::value
	>
>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_fill_n_impl(
	Allocator& allocator, Iter first, Size n, T const& x,
	hamon::detail::overload_priority<2>)
{
	(void)allocator;

	// fill_n関数であれば、可能ならmemsetを使う等の最適化が期待できるが、
	// constexprの文脈で未初期化領域に代入することはできない。
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
#endif
	{
		using DifferenceType = hamon::iter_difference_t<Iter>;
		return hamon::ranges::fill_n(first, static_cast<DifferenceType>(n), x);
	}

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	return uninitialized_fill_n_impl(
		allocator, first, n, x, hamon::detail::overload_priority<1>{});
#endif
}

template <typename Allocator, typename Iter, typename Size, typename T,
	typename ValueType = hamon::iter_value_t<Iter>,
	typename = hamon::enable_if_t<
		hamon::is_nothrow_constructible<ValueType, T const&>::value
	>
>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_fill_n_impl(
	Allocator& allocator, Iter first, Size n, T const& x,
	hamon::detail::overload_priority<1>)
{
	// コンストラクタが例外を投げないのであれば、try-catchなどを省略できる。
	for (; n > 0; --n)
	{
		hamon::allocator_traits<Allocator>::construct(allocator, hamon::addressof(*first), x);
		++first;
	}
	return first;
}

template <typename Allocator, typename Iter, typename Size, typename T>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_fill_n_impl(
	Allocator& allocator, Iter first, Size n, T const& x,
	hamon::detail::overload_priority<0>)
{
	Iter current = first;
#if !defined(HAMON_NO_EXCEPTIONS)
	try
#endif
	{
		for (; n > 0; --n)
		{
			hamon::allocator_traits<Allocator>::construct(allocator, hamon::addressof(*current), x);
			++current;
		}
		return current;
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	catch(...)
	{
		hamon::detail::destroy_impl(allocator, first, current);
		throw;
	}
#endif
}

template <typename Allocator, typename Iter, typename Size, typename T>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_fill_n_impl(Allocator& allocator, Iter first, Size n, T const& x)
{
	return hamon::detail::uninitialized_fill_n_impl(
		allocator, first, n, x,
		hamon::detail::overload_priority<2>{});
}

template <typename Iter, typename Size, typename T>
HAMON_CXX20_CONSTEXPR Iter
uninitialized_fill_n_impl(Iter first, Size n, T const& x)
{
	hamon::allocator<hamon::iter_value_t<Iter>> alloc;
	return hamon::detail::uninitialized_fill_n_impl(alloc, first, n, x);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_UNINITIALIZED_FILL_N_IMPL_HPP
