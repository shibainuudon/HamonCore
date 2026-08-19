/**
 *	@file	negation.hpp
 *
 *	@brief	negation の定義
 */

#ifndef HAMON_TYPE_TRAITS_NEGATION_HPP
#define HAMON_TYPE_TRAITS_NEGATION_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.9 Logical operator traits[meta.logical]

/**
 *	@brief		コンパイル時の論理否定
 *
 *	@tparam		B
 *
 *	integral_constant<bool, !B::value> と同じ
 */
template <typename B>
struct negation : public hamon::bool_constant<!B::value> {};

template <typename B>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool negation_v = negation<B>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_NEGATION_HPP
