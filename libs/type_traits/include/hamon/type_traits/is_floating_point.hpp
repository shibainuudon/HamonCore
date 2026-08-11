/**
 *	@file	is_floating_point.hpp
 *
 *	@brief	is_floating_point の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_FLOATING_POINT_HPP
#define HAMON_TYPE_TRAITS_IS_FLOATING_POINT_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.2 Primary type categories[meta.unary.cat]

namespace detail
{

template <typename T>
struct is_floating_point_impl : public hamon::false_type{};

template <>
struct is_floating_point_impl<float> : public hamon::true_type{};
template <>
struct is_floating_point_impl<double> : public hamon::true_type{};
template <>
struct is_floating_point_impl<long double> : public hamon::true_type{};

}	// namespace detail

/**
 *	@brief	型Tが浮動小数点型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_floating_pointは、型Tが浮動小数点型(cv修飾を許容する)であれば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_floating_point
	: public hamon::detail::is_floating_point_impl<hamon::remove_cv_t<T>> {};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_floating_point_v = is_floating_point<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_FLOATING_POINT_HPP
