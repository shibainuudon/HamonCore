﻿/**
 *	@file	destructible.hpp
 *
 *	@brief	destructible の定義
 */

#ifndef HAMON_CONCEPTS_DESTRUCTIBLE_HPP
#define HAMON_CONCEPTS_DESTRUCTIBLE_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/type_traits/is_nothrow_destructible.hpp>
#endif

namespace hamon
{

// 18.4.10 Concept destructible	[concept.destructible]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::destructible;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept destructible = hamon::is_nothrow_destructible<T>::value;

#else

template <typename T>
using destructible = hamon::is_nothrow_destructible<T>;

#endif

template <typename T>
using destructible_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::destructible<T>>;
#else
	hamon::destructible<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_DESTRUCTIBLE_HPP
