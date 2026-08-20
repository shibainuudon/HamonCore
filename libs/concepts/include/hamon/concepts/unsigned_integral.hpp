/**
 *	@file	unsigned_integral.hpp
 *
 *	@brief	unsigned_integral の定義
 */

#ifndef HAMON_CONCEPTS_UNSIGNED_INTEGRAL_HPP
#define HAMON_CONCEPTS_UNSIGNED_INTEGRAL_HPP

#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/signed_integral.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.7 Arithmetic concepts	[concepts.arithmetic]

template <typename T>
HAMON_CONCEPT_OR_BOOL unsigned_integral = hamon::integral<T> && !hamon::signed_integral<T>;

}	// namespace hamon

#endif // HAMON_CONCEPTS_UNSIGNED_INTEGRAL_HPP
