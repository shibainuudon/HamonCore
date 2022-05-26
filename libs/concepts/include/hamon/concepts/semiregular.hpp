﻿/**
 *	@file	semiregular.hpp
 *
 *	@brief	semiregular の定義
 */

#ifndef HAMON_CONCEPTS_SEMIREGULAR_HPP
#define HAMON_CONCEPTS_SEMIREGULAR_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::semiregular;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept semiregular =
	hamon::copyable<T> &&
	hamon::default_initializable<T>;

#else

template <typename T>
using semiregular =
	hamon::conjunction<
		hamon::copyable<T>,
		hamon::default_initializable<T>
	>;

#endif

}	// namespace hamon

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T>
using semiregular_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::semiregular<T>>;
#else
	hamon::semiregular<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_SEMIREGULAR_HPP