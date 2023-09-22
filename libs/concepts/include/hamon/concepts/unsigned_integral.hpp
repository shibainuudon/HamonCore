/**
 *	@file	unsigned_integral.hpp
 *
 *	@brief	unsigned_integral の定義
 */

#ifndef HAMON_CONCEPTS_UNSIGNED_INTEGRAL_HPP
#define HAMON_CONCEPTS_UNSIGNED_INTEGRAL_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/signed_integral.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::unsigned_integral;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept unsigned_integral = hamon::integral<T> && !hamon::signed_integral<T>;

#else

template <typename T>
using unsigned_integral =
	hamon::bool_constant<
		hamon::integral<T>::value && !hamon::signed_integral<T>::value
	>;

#endif

template <typename T>
using unsigned_integral_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::unsigned_integral<T>>;
#else
	hamon::unsigned_integral<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_UNSIGNED_INTEGRAL_HPP
