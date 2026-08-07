/**
 *	@file	integral_constant.hpp
 *
 *	@brief	integral_constant の定義
 */

#ifndef HAMON_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define HAMON_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

#include <hamon/config.hpp>

namespace hamon
{

// 21.3.4 Helper classes[meta.help]

/**
 *	@brief	整数定数
 *
 *	@tparam	T	定数の型
 *	@tparam	v	定数の値
 *
 *	integral_constant は基本となる整数型と定数を合わせ，型として整数定数を表す。
 */
template <typename T, T v>
struct integral_constant
{
	using value_type = T;
	using type = integral_constant<T, v>;

	HAMON_STATIC_CONSTEXPR T value = v;

	HAMON_CONSTEXPR operator value_type() const HAMON_NOEXCEPT { return value; }
	HAMON_CONSTEXPR value_type operator()() const HAMON_NOEXCEPT { return value; }
};

#if !defined(HAMON_HAS_CXX17_INLINE_VARIABLES)

template <typename T, T v>
constexpr T integral_constant<T, v>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
