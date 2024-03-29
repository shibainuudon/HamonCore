﻿/**
 *	@file	integral.hpp
 *
 *	@brief	integral の定義
 */

#ifndef HAMON_CONCEPTS_INTEGRAL_HPP
#define HAMON_CONCEPTS_INTEGRAL_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/type_traits/is_integral.hpp>
#endif

namespace hamon
{

// 18.4.7 Arithmetic concepts	[concepts.arithmetic]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::integral;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept integral = hamon::is_integral<T>::value;

#else

template <typename T>
using integral = hamon::is_integral<T>;

#endif

template <typename T>
using integral_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::integral<T>>;
#else
	hamon::integral<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_INTEGRAL_HPP
