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
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/iter_const_reference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/algorithm/copy.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename InputIterator, typename ForwardIterator,
	typename SrcType = hamon::iter_const_reference_t<InputIterator>,
	typename RefType = hamon::iter_reference_t<ForwardIterator>,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_trivially_assignable<RefType, SrcType>::value &&
		hamon::is_trivially_constructible<ValueType, SrcType>::value
	>
>
HAMON_CXX20_CONSTEXPR ForwardIterator
uninitialized_copy_impl(
	InputIterator first, InputIterator last, ForwardIterator result,
	hamon::detail::overload_priority<2>)
{
	// copy関数であれば、可能ならmemmoveを使う等の最適化が期待できるが、
	// constexprの文脈で未初期化領域に代入することはできない。
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
#endif
	{
		return hamon::copy(first, last, result);
	}

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	return uninitialized_copy_impl(
		first, last, result, hamon::detail::overload_priority<1>{});
#endif
}

template <typename InputIterator, typename ForwardIterator,
	typename SrcType = hamon::iter_const_reference_t<InputIterator>,
	typename ValueType = hamon::iter_value_t<ForwardIterator>,
	typename = hamon::enable_if_t<
		hamon::is_nothrow_constructible<ValueType, SrcType>::value
	>
>
HAMON_CXX20_CONSTEXPR ForwardIterator
uninitialized_copy_impl(
	InputIterator first, InputIterator last, ForwardIterator result,
	hamon::detail::overload_priority<1>)
{
	// コンストラクタが例外を投げないのであれば、try-catchなどを省略できる。
	for (; first != last; ++first)
	{
		hamon::construct_at(hamon::addressof(*result), *first);
		++result;
	}
	return result;
}

template <typename InputIterator, typename ForwardIterator>
HAMON_CXX20_CONSTEXPR ForwardIterator
uninitialized_copy_impl(
	InputIterator first, InputIterator last, ForwardIterator result,
	hamon::detail::overload_priority<0>)
{
	ForwardIterator current = result;
	try
	{
		for (; first != last; ++first)
		{
			hamon::construct_at(hamon::addressof(*current), *first);
			++current;
		}
		return current;
	}
	catch (...)
	{
		hamon::destroy(result, current);
		throw;
	}
}

template <typename InputIterator, typename ForwardIterator>
HAMON_CXX20_CONSTEXPR ForwardIterator
uninitialized_copy_impl(
	InputIterator first, InputIterator last, ForwardIterator result)
{
	return hamon::detail::uninitialized_copy_impl(
		first, last, result,
		hamon::detail::overload_priority<2>{});
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_UNINITIALIZED_COPY_IMPL_HPP
