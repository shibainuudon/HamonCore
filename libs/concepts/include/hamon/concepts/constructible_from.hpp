﻿/**
 *	@file	constructible_from.hpp
 *
 *	@brief	constructible_from の定義
 */

#ifndef HAMON_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
#define HAMON_CONCEPTS_CONSTRUCTIBLE_FROM_HPP

#include <hamon/concepts/config.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::constructible_from;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

#include <hamon/concepts/destructible.hpp>
#include <hamon/type_traits/is_constructible.hpp>

namespace hamon
{

template <typename T, typename... Args>
concept constructible_from =
	hamon::destructible<T> &&
	hamon::is_constructible<T, Args...>::value;

}	// namespace hamon

#else

#include <hamon/concepts/destructible.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_constructible.hpp>

namespace hamon
{

template <typename T, typename... Args>
using constructible_from =
	hamon::conjunction<
		hamon::destructible<T>,
		hamon::is_constructible<T, Args...>
	>;

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T, typename... Args>
using constructible_from_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::constructible_from<T, Args...>>;
#else
	hamon::constructible_from<T, Args...>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
