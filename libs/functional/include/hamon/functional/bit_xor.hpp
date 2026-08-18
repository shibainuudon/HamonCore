/**
 *	@file	bit_xor.hpp
 *
 *	@brief	bit_xor クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_BIT_XOR_HPP
#define HAMON_FUNCTIONAL_BIT_XOR_HPP

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	ビットごとの排他的論理和(XOR)をとる関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct bit_xor
{
	HAMON_CONSTEXPR T operator()(T const& lhs, T const& rhs) const
		HAMON_NOEXCEPT_IF_EXPR(lhs ^ rhs)
	{
		return lhs ^ rhs;
	}
};

/**
 *	@brief	bit_xor のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct bit_xor<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
		HAMON_NOEXCEPT_IF_EXPR(hamon::forward<T>(lhs) ^ hamon::forward<U>(rhs))
	->decltype(hamon::forward<T>(lhs) ^ hamon::forward<U>(rhs))
	{
		return hamon::forward<T>(lhs) ^ hamon::forward<U>(rhs);
	}
};

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_BIT_XOR_HPP
