/**
 *	@file	uninitialized_copy_impl.hpp
 *
 *	@brief	uninitialized_copy_impl を定義
 */

#ifndef HAMON_MEMORY_DETAIL_UNINITIALIZED_COPY_IMPL_HPP
#define HAMON_MEMORY_DETAIL_UNINITIALIZED_COPY_IMPL_HPP

#include <hamon/memory/addressof.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_const_reference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
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

template <typename I, typename S1, typename O, typename S2,
	typename SrcType = hamon::iter_const_reference_t<I>,
	typename RefType = hamon::iter_reference_t<O>,
	typename ValueType = hamon::iter_value_t<O>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_assignable<RefType, SrcType>::value &&
		hamon::is_trivially_constructible<ValueType, SrcType>::value
	>
>
HAMON_CXX20_CONSTEXPR hamon::ranges::in_out_result<I, O>
uninitialized_copy_impl(
	I ifirst, S1 ilast, O ofirst, S2 olast,
	hamon::detail::overload_priority<2>)
{
	// copy関数であれば、可能ならmemmoveを使う等の最適化が期待できるが、
	// constexprの文脈で未初期化領域に代入することはできない。
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
#endif
	{
		(void)olast;
		return hamon::ranges::copy(ifirst, ilast, ofirst);
	}

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	return uninitialized_copy_impl(
		ifirst, ilast, ofirst, olast, hamon::detail::overload_priority<1>{});
#endif
}

template <typename I, typename S1, typename O, typename S2,
	typename SrcType = hamon::iter_const_reference_t<I>,
	typename ValueType = hamon::iter_value_t<O>,
	typename = hamon::enable_if_t<
		hamon::is_nothrow_constructible<ValueType, SrcType>::value
	>
>
HAMON_CXX20_CONSTEXPR hamon::ranges::in_out_result<I, O>
uninitialized_copy_impl(
	I ifirst, S1 ilast, O ofirst, S2 olast,
	hamon::detail::overload_priority<1>)
{
	// コンストラクタが例外を投げないのであれば、try-catchなどを省略できる。
	for (; ifirst != ilast && ofirst != olast; ++ifirst)
	{
		hamon::construct_at(hamon::addressof(*ofirst), *ifirst);
		++ofirst;
	}
	return {hamon::move(ifirst), ofirst};
}

template <typename I, typename S1, typename O, typename S2>
HAMON_CXX20_CONSTEXPR hamon::ranges::in_out_result<I, O>
uninitialized_copy_impl(
	I ifirst, S1 ilast, O ofirst, S2 olast,
	hamon::detail::overload_priority<0>)
{
	O current = ofirst;
#if !defined(HAMON_NO_EXCEPTIONS)
	try
#endif
	{
		for (; ifirst != ilast && current != olast; ++ifirst)
		{
			hamon::construct_at(hamon::addressof(*current), *ifirst);
			++current;
		}
		return {hamon::move(ifirst), current};
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	catch (...)
	{
		hamon::destroy(ofirst, current);
		throw;
	}
#endif
}

template <typename I, typename S1, typename O, typename S2>
HAMON_CXX20_CONSTEXPR hamon::ranges::in_out_result<I, O>
uninitialized_copy_impl(
	I ifirst, S1 ilast, O ofirst, S2 olast)
{
	return hamon::detail::uninitialized_copy_impl(
		ifirst, ilast, ofirst, olast,
		hamon::detail::overload_priority<2>{});
}

template <typename I, typename S1, typename O>
HAMON_CXX20_CONSTEXPR hamon::ranges::in_out_result<I, O>
uninitialized_copy_impl(
	I ifirst, S1 ilast, O ofirst)
{
	return hamon::detail::uninitialized_copy_impl(
		ifirst, ilast, ofirst, hamon::unreachable_sentinel,
		hamon::detail::overload_priority<2>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_UNINITIALIZED_COPY_IMPL_HPP
