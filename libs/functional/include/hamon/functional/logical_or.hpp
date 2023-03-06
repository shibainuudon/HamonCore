/**
 *	@file	logical_or.hpp
 *
 *	@brief	logical_or クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_LOGICAL_OR_HPP
#define HAMON_FUNCTIONAL_LOGICAL_OR_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_FUNCTIONAL_OPERATORS)

namespace hamon
{

using std::logical_or;

}	// namespace hamon

#else

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	論理和(OR)を計算する関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct logical_or
{
	HAMON_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs || rhs;
	}
};

/**
 *	@brief	logical_or のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct logical_or<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	->decltype(hamon::forward<T>(lhs) || hamon::forward<U>(rhs))
	{
		return hamon::forward<T>(lhs) || hamon::forward<U>(rhs);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_LOGICAL_OR_HPP
