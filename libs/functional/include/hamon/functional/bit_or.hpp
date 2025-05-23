﻿/**
 *	@file	bit_or.hpp
 *
 *	@brief	bit_or クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_BIT_OR_HPP
#define HAMON_FUNCTIONAL_BIT_OR_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_FUNCTIONAL_OPERATORS)

namespace hamon
{

using std::bit_or;

}	// namespace hamon

#else

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	ビットごとの論理和(OR)をとる関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct bit_or
{
	HAMON_CONSTEXPR T operator()(T const& lhs, T const& rhs) const
		HAMON_NOEXCEPT_IF_EXPR(lhs | rhs)
	{
		return lhs | rhs;
	}
};

/**
 *	@brief	bit_or のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct bit_or<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
		HAMON_NOEXCEPT_IF_EXPR(hamon::forward<T>(lhs) | hamon::forward<U>(rhs))
	->decltype(hamon::forward<T>(lhs) | hamon::forward<U>(rhs))
	{
		return hamon::forward<T>(lhs) | hamon::forward<U>(rhs);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_BIT_OR_HPP
