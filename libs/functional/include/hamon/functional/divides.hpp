﻿/**
 *	@file	divides.hpp
 *
 *	@brief	divides クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_DIVIDES_HPP
#define HAMON_FUNCTIONAL_DIVIDES_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_FUNCTIONAL_OPERATORS)

namespace hamon
{

using std::divides;

}	// namespace hamon

#else

#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

/**
 *	@brief	除算を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct divides
{
	HAMON_CONSTEXPR T operator()(T const& lhs, T const& rhs) const
	{
		return lhs / rhs;
	}
};

/**
 *	@brief	divides のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct divides<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	->decltype(std::forward<T>(lhs) / std::forward<U>(rhs))
	{
		return std::forward<T>(lhs) / std::forward<U>(rhs);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_DIVIDES_HPP