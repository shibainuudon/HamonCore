/**
 *	@file	negate.hpp
 *
 *	@brief	negate クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_NEGATE_HPP
#define HAMON_FUNCTIONAL_NEGATE_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_FUNCTIONAL_OPERATORS)

namespace hamon
{

using std::negate;

}	// namespace hamon

#else

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	符号反転を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct negate
{
	HAMON_CONSTEXPR T operator()(T const& arg) const
		HAMON_NOEXCEPT_IF_EXPR(-arg)
	{
		return -arg;
	}
};

/**
 *	@brief	negate のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct negate<void>
{
	using is_transparent = void;

	template <typename T>
	HAMON_CONSTEXPR auto operator()(T&& arg) const
		HAMON_NOEXCEPT_IF_EXPR(-hamon::forward<T>(arg))
	->decltype(-hamon::forward<T>(arg))
	{
		return -hamon::forward<T>(arg);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_NEGATE_HPP
