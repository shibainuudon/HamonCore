/**
 *	@file	move_constructible.hpp
 *
 *	@brief	move_constructible の定義
 */

#ifndef HAMON_CONCEPTS_MOVE_CONSTRUCTIBLE_HPP
#define HAMON_CONCEPTS_MOVE_CONSTRUCTIBLE_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/conjunction.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::move_constructible;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept move_constructible =
	hamon::constructible_from<T, T> &&
	hamon::convertible_to<T, T>;

#else

template <typename T>
using move_constructible =
	hamon::conjunction<
		hamon::constructible_from<T, T>,
		hamon::convertible_to<T, T>
	>;

#endif

template <typename T>
using move_constructible_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::move_constructible<T>>;
#else
	hamon::move_constructible<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_MOVE_CONSTRUCTIBLE_HPP
