/**
 *	@file	unsigned_integral.hpp
 *
 *	@brief	unsigned_integral の定義
 */

#ifndef HAMON_CONCEPTS_UNSIGNED_INTEGRAL_HPP
#define HAMON_CONCEPTS_UNSIGNED_INTEGRAL_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/signed_integral.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.7 Arithmetic concepts	[concepts.arithmetic]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::unsigned_integral;

#else

template <typename T>
HAMON_CONCEPT_OR_BOOL unsigned_integral = hamon::integral<T> && !hamon::signed_integral<T>;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_UNSIGNED_INTEGRAL_HPP
