﻿/**
 *	@file	builtin_ptr_three_way.hpp
 *
 *	@brief	builtin_ptr_three_way の定義
 */

#ifndef HAMON_COMPARE_DETAIL_BUILTIN_PTR_THREE_WAY_HPP
#define HAMON_COMPARE_DETAIL_BUILTIN_PTR_THREE_WAY_HPP

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

// BUILTIN-PTR-THREE-WAY(T, U)
template <typename T, typename U>
concept builtin_ptr_three_way =
	requires(T&& t, U&& u)
	{
		static_cast<T&&>(t) <=> static_cast<U&&>(u);
	} &&
	hamon::convertible_to<T, void const volatile*> &&
	hamon::convertible_to<U, void const volatile*> &&
	!requires(T&& t, U&& u)
	{
		operator<=>(static_cast<T&&>(t), static_cast<U&&>(u));
	} &&
	!requires(T&& t, U&& u)
	{
		static_cast<T&&>(t).operator<=>(static_cast<U&&>(u));
	};

#else

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_BUILTIN_PTR_THREE_WAY_HPP
