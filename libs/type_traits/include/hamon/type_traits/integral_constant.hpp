/**
 *	@file	integral_constant.hpp
 *
 *	@brief	integral_constant の定義
 */

#ifndef HAMON_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define HAMON_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

#include <type_traits>

#if defined(__cpp_lib_integral_constant_callable) && (__cpp_lib_integral_constant_callable >= 201304)

namespace hamon
{

using std::integral_constant;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

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

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
