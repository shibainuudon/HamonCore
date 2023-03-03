/**
 *	@file	negation.hpp
 *
 *	@brief	negation の定義
 */

#ifndef HAMON_TYPE_TRAITS_NEGATION_HPP
#define HAMON_TYPE_TRAITS_NEGATION_HPP

#include <type_traits>

#if defined(__cpp_lib_logical_traits) && (__cpp_lib_logical_traits >= 201510)

namespace hamon
{

using std::negation;

}	// namespace hamon

#else

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

/**
 *	@brief		コンパイル時の論理否定
 *
 *	@tparam		B
 *
 *	integral_constant<bool, !B::value> と同じ
 */
template <typename B>
struct negation : public hamon::bool_constant<!B::value> {};

}	// namespace hamon

#endif

#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename B>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool negation_v = negation<B>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_NEGATION_HPP
