/**
 *	@file	signed_integral.hpp
 *
 *	@brief	signed_integral の定義
 */

#ifndef HAMON_CONCEPTS_SIGNED_INTEGRAL_HPP
#define HAMON_CONCEPTS_SIGNED_INTEGRAL_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/integral.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_signed.hpp>
#endif

namespace hamon
{

// 18.4.7 Arithmetic concepts	[concepts.arithmetic]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::signed_integral;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept signed_integral = hamon::integral<T> && hamon::is_signed<T>::value;

#else

template <typename T>
using signed_integral =
	hamon::conjunction<
		hamon::integral<T>, hamon::is_signed<T>
	>;

#endif

template <typename T>
using signed_integral_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::signed_integral<T>>;
#else
	hamon::signed_integral<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_SIGNED_INTEGRAL_HPP
