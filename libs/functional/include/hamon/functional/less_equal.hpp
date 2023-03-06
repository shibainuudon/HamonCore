/**
 *	@file	less_equal.hpp
 *
 *	@brief	less_equal クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_LESS_EQUAL_HPP
#define HAMON_FUNCTIONAL_LESS_EQUAL_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_FUNCTIONAL_OPERATORS)

namespace hamon
{

using std::less_equal;

}	// namespace hamon

#else

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	左辺が右辺以下かの比較を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct less_equal
{
	HAMON_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs <= rhs;
	}
};

/**
 *	@brief	less_equal のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct less_equal<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	->decltype(hamon::forward<T>(lhs) <= hamon::forward<U>(rhs))
	{
		return hamon::forward<T>(lhs) <= hamon::forward<U>(rhs);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_LESS_EQUAL_HPP
