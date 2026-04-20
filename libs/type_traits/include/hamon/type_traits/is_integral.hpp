/**
 *	@file	is_integral.hpp
 *
 *	@brief	is_integral の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_INTEGRAL_HPP
#define HAMON_TYPE_TRAITS_IS_INTEGRAL_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct is_integral_impl : public hamon::false_type{};

template <> struct is_integral_impl<bool>               : public hamon::true_type{};
template <> struct is_integral_impl<char>               : public hamon::true_type{};
template <> struct is_integral_impl<signed char>        : public hamon::true_type{};
template <> struct is_integral_impl<unsigned char>      : public hamon::true_type{};
template <> struct is_integral_impl<wchar_t>            : public hamon::true_type{};
#if defined(HAMON_HAS_CXX20_CHAR8_T)
template <> struct is_integral_impl<char8_t>            : public hamon::true_type{};
#endif
template <> struct is_integral_impl<char16_t>           : public hamon::true_type{};
template <> struct is_integral_impl<char32_t>           : public hamon::true_type{};
template <> struct is_integral_impl<short>              : public hamon::true_type{};
template <> struct is_integral_impl<unsigned short>     : public hamon::true_type{};
template <> struct is_integral_impl<int>                : public hamon::true_type{};
template <> struct is_integral_impl<unsigned int>       : public hamon::true_type{};
template <> struct is_integral_impl<long>               : public hamon::true_type{};
template <> struct is_integral_impl<unsigned long>      : public hamon::true_type{};
template <> struct is_integral_impl<long long>          : public hamon::true_type{};
template <> struct is_integral_impl<unsigned long long> : public hamon::true_type{};

#if defined(HAMON_HAS_INT128)
template <> struct is_integral_impl<__int128_t>  : public hamon::true_type{};
template <> struct is_integral_impl<__uint128_t> : public hamon::true_type{};
#endif

}	// namespace detail

/**
 *	@brief	型Tが整数型かを調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_integralは、型Tが整数型(cv修飾も許容される)であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	以下のような型が、整数型として判定される：
 *	・bool
 *	・char
 *	・char8_t
 *	・char16_t
 *	・char32_t
 *	・wchar_t
 *	・short
 *	・int
 *	・long
 *	・long long
 *	enumは整数型とは判定されない。
 */
template <typename T>
struct is_integral
	: public hamon::detail::is_integral_impl<hamon::remove_cv_t<T>> {};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_integral_v = is_integral<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_INTEGRAL_HPP
