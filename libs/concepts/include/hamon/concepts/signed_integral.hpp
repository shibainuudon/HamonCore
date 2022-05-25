﻿/**
 *	@file	signed_integral.hpp
 *
 *	@brief	signed_integral の定義
 */

#ifndef HAMON_CONCEPTS_SIGNED_INTEGRAL_HPP
#define HAMON_CONCEPTS_SIGNED_INTEGRAL_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/integral.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <type_traits>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::signed_integral;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept signed_integral = hamon::integral<T> && std::is_signed<T>::value;

#else

template <typename T>
using signed_integral =
	hamon::conjunction<
		hamon::integral<T>, std::is_signed<T>
	>;

#endif

}	// namespace hamon

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T>
using signed_integral_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::signed_integral<T>>;
#else
	hamon::signed_integral<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_SIGNED_INTEGRAL_HPP