/**
 *	@file	minus.hpp
 *
 *	@brief	minus クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_MINUS_HPP
#define HAMON_FUNCTIONAL_MINUS_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_FUNCTIONAL_OPERATORS)

namespace hamon
{

using std::minus;

}	// namespace hamon

#else

#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	減算を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct minus
{
	HAMON_CONSTEXPR T operator()(T const& lhs, T const& rhs) const
	{
		return lhs - rhs;
	}
};

/**
 *	@brief	minus のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct minus<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	HAMON_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	->decltype(hamon::forward<T>(lhs) - hamon::forward<U>(rhs))
	{
		return hamon::forward<T>(lhs) - hamon::forward<U>(rhs);
	}
};

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_MINUS_HPP
