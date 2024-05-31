/**
 *	@file	uninitialized_move_n_impl.hpp
 *
 *	@brief	uninitialized_move_n_impl を定義
 */

#ifndef HAMON_MEMORY_DETAIL_UNINITIALIZED_MOVE_N_IMPL_HPP
#define HAMON_MEMORY_DETAIL_UNINITIALIZED_MOVE_N_IMPL_HPP

#include <hamon/memory/addressof.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/pair.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Iter, typename Size, typename Out,
	typename SrcType = hamon::iter_rvalue_reference_t<Iter>,
	typename RefType = hamon::iter_reference_t<Out>,
	typename ValueType = hamon::iter_value_t<Out>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_assignable<RefType, SrcType>::value &&
		hamon::is_trivially_constructible<ValueType, SrcType>::value
	>
>
HAMON_CXX20_CONSTEXPR hamon::pair<Iter, Out>
uninitialized_move_n_impl(
	Iter first, Size n, Out result,
	hamon::detail::overload_priority<2>)
{
	// constexprの文脈で未初期化領域に代入することはできない。
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
#endif
	{
		// ranges::move_n(first, n, result); は無いので
		for (; n > 0; --n)
		{
			*result = hamon::move(*first);
			++result;
			++first;
		}
		return {first, result};
	}

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	return uninitialized_move_n_impl(
		first, n, result, hamon::detail::overload_priority<1>{});
#endif
}

template <typename Iter, typename Size, typename Out,
	typename SrcType = hamon::iter_rvalue_reference_t<Iter>,
	typename ValueType = hamon::iter_value_t<Out>,
	typename = hamon::enable_if_t<
		hamon::is_nothrow_constructible<ValueType, SrcType>::value
	>
>
HAMON_CXX20_CONSTEXPR hamon::pair<Iter, Out>
uninitialized_move_n_impl(
	Iter first, Size n, Out result,
	hamon::detail::overload_priority<1>)
{
	// コンストラクタが例外を投げないのであれば、try-catchなどを省略できる。
	for (; n > 0; --n)
	{
		hamon::construct_at(hamon::addressof(*result), hamon::move(*first));
		++result;
		++first;
	}
	return {first, result};
}

template <typename Iter, typename Size, typename Out>
HAMON_CXX20_CONSTEXPR hamon::pair<Iter, Out>
uninitialized_move_n_impl(
	Iter first, Size n, Out result,
	hamon::detail::overload_priority<0>)
{
	Out current = result;
#if !defined(HAMON_NO_EXCEPTIONS)
	try
#endif
	{
		for (; n > 0; --n)
		{
			hamon::construct_at(hamon::addressof(*current), hamon::move(*first));
			++current;
			++first;
		}
		return {first, current};
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	catch (...)
	{
		hamon::destroy(result, current);
		throw;
	}
#endif
}

template <typename Iter, typename Size, typename Out>
HAMON_CXX20_CONSTEXPR hamon::pair<Iter, Out>
uninitialized_move_n_impl(
	Iter first, Size count, Out result)
{
	return hamon::detail::uninitialized_move_n_impl(
		first, count, result,
		hamon::detail::overload_priority<2>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_UNINITIALIZED_MOVE_N_IMPL_HPP
