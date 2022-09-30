﻿/**
 *	@file	is_invocable_impl.hpp
 *
 *	@brief	is_invocable_impl の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_INVOCABLE_IMPL_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_INVOCABLE_IMPL_HPP

#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename Result, typename Ret, typename = hamon::void_t<>>
struct is_invocable_impl
	: public std::false_type
{};

template <typename Result, typename Ret>
struct is_invocable_impl<Result, Ret, hamon::void_t<typename Result::type>>
	: public hamon::disjunction<
		std::is_void<Ret>,
		std::is_convertible<typename Result::type, Ret>
	>::type
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_INVOCABLE_IMPL_HPP
