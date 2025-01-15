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

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

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

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wconversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-float-conversion")

/**
 *	@brief	greater のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct greater<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	->decltype(hamon::forward<T>(lhs) > hamon::forward<U>(rhs))
	{
		return hamon::forward<T>(lhs) > hamon::forward<U>(rhs);
	}
};

HAMON_WARNING_POP()

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_GREATER_HPP
