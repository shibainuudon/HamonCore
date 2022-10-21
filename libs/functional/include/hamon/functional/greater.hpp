/**
 *	@file	greater.hpp
 *
 *	@brief	greater クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_GREATER_HPP
#define HAMON_FUNCTIONAL_GREATER_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_FUNCTIONAL_OPERATORS)

namespace hamon
{

using std::greater;

}	// namespace hamon

#else

#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

/**
 *	@brief	左辺が右辺より大きいかの比較を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct greater
{
	HAMON_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs > rhs;
	}
};

/**
 *	@brief	greater のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct greater<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	->decltype(std::forward<T>(lhs) > std::forward<U>(rhs))
	{
		return std::forward<T>(lhs) > std::forward<U>(rhs);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_GREATER_HPP
