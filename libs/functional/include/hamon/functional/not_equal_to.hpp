/**
 *	@file	not_equal_to.hpp
 *
 *	@brief	not_equal_to クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_NOT_EQUAL_TO_HPP
#define HAMON_FUNCTIONAL_NOT_EQUAL_TO_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_FUNCTIONAL_OPERATORS)

namespace hamon
{

using std::not_equal_to;

}	// namespace hamon

#else

#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

/**
 *	@brief	非等値比較を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct not_equal_to
{
	HAMON_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs != rhs;
	}
};

/**
 *	@brief	not_equal_to のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct not_equal_to<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	->decltype(std::forward<T>(lhs) != std::forward<U>(rhs))
	{
		return std::forward<T>(lhs) != std::forward<U>(rhs);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_NOT_EQUAL_TO_HPP
