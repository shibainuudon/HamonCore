/**
 *	@file	bit_not.hpp
 *
 *	@brief	bit_not クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_BIT_NOT_HPP
#define HAMON_FUNCTIONAL_BIT_NOT_HPP

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	ビットごとの論理否定(NOT)をとる関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct bit_not
{
	HAMON_CONSTEXPR T operator()(T const& arg) const
		HAMON_NOEXCEPT_IF_EXPR(static_cast<T>(~arg))
	{
		return static_cast<T>(~arg);
	}
};

/**
 *	@brief	bit_not のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct bit_not<void>
{
	using is_transparent = void;

	template <typename T>
	HAMON_CONSTEXPR auto operator()(T&& arg) const
		HAMON_NOEXCEPT_IF_EXPR(~hamon::forward<T>(arg))
	->decltype(~hamon::forward<T>(arg))
	{
		return ~hamon::forward<T>(arg);
	}
};

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_BIT_NOT_HPP
