/**
 *	@file	plus.hpp
 *
 *	@brief	plus クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_PLUS_HPP
#define HAMON_FUNCTIONAL_PLUS_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_FUNCTIONAL_OPERATORS)

namespace hamon
{

using std::plus;

}	// namespace hamon

#else

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	加算を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct plus
{
	HAMON_CONSTEXPR T operator()(T const& lhs, T const& rhs) const
		HAMON_NOEXCEPT_IF_EXPR(lhs + rhs)
	{
		return lhs + rhs;
	}
};

/**
 *	@brief	plus のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct plus<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
		HAMON_NOEXCEPT_IF_EXPR(hamon::forward<T>(lhs) + hamon::forward<U>(rhs))
	->decltype(hamon::forward<T>(lhs) + hamon::forward<U>(rhs))
	{
		return hamon::forward<T>(lhs) + hamon::forward<U>(rhs);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_PLUS_HPP
