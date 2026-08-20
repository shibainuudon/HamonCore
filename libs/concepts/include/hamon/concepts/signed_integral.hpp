/**
 *	@file	signed_integral.hpp
 *
 *	@brief	signed_integral の定義
 */

#ifndef HAMON_CONCEPTS_SIGNED_INTEGRAL_HPP
#define HAMON_CONCEPTS_SIGNED_INTEGRAL_HPP

#include <hamon/concepts/integral.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.7 Arithmetic concepts	[concepts.arithmetic]

template <typename T>
HAMON_CONCEPT_OR_BOOL signed_integral = hamon::integral<T> && hamon::is_signed<T>::value;

}	// namespace hamon

#endif // HAMON_CONCEPTS_SIGNED_INTEGRAL_HPP
