/**
 *	@file	logical_not.hpp
 *
 *	@brief	logical_not クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_LOGICAL_NOT_HPP
#define HAMON_FUNCTIONAL_LOGICAL_NOT_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_FUNCTIONAL_OPERATORS)

namespace hamon
{

using std::logical_not;

}	// namespace hamon

#else

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	論理否定(NOT)を計算する関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct logical_not
{
	HAMON_CONSTEXPR T operator()(T const& arg) const
	{
		return !arg;
	}
};

/**
 *	@brief	logical_not のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct logical_not<void>
{
	using is_transparent = void;

	template <typename T>
	HAMON_CONSTEXPR auto operator()(T&& arg) const
	->decltype(!hamon::forward<T>(arg))
	{
		return !hamon::forward<T>(arg);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_LOGICAL_NOT_HPP
