/**
 *	@file	modulus.hpp
 *
 *	@brief	modulus クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_MODULUS_HPP
#define HAMON_FUNCTIONAL_MODULUS_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_FUNCTIONAL_OPERATORS)

namespace hamon
{

using std::modulus;

}	// namespace hamon

#else

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	剰余算を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct modulus
{
	HAMON_CONSTEXPR T operator()(T const& lhs, T const& rhs) const
		HAMON_NOEXCEPT_IF_EXPR(lhs % rhs)
	{
		return lhs % rhs;
	}
};

/**
 *	@brief	modulus のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct modulus<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
		HAMON_NOEXCEPT_IF_EXPR(hamon::forward<T>(lhs) % hamon::forward<U>(rhs))
	->decltype(hamon::forward<T>(lhs) % hamon::forward<U>(rhs))
	{
		return hamon::forward<T>(lhs) % hamon::forward<U>(rhs);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_MODULUS_HPP
