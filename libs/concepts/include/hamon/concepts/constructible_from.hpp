/**
 *	@file	constructible_from.hpp
 *
 *	@brief	constructible_from の定義
 */

#ifndef HAMON_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
#define HAMON_CONCEPTS_CONSTRUCTIBLE_FROM_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/destructible.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::constructible_from;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename... Args>
concept constructible_from =
	hamon::destructible<T> &&
	hamon::is_constructible<T, Args...>::value;

#else

template <typename T, typename... Args>
using constructible_from =
	hamon::conjunction<
		hamon::destructible<T>,
		hamon::is_constructible<T, Args...>
	>;

#endif

template <typename T, typename... Args>
using constructible_from_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::constructible_from<T, Args...>>;
#else
	hamon::constructible_from<T, Args...>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_CONSTRUCTIBLE_FROM_HPP
