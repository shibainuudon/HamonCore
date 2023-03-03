/**
 *	@file	cpp17_destructible.hpp
 *
 *	@brief	cpp17_destructible の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CPP17_DESTRUCTIBLE_HPP
#define HAMON_CONCEPTS_DETAIL_CPP17_DESTRUCTIBLE_HPP

#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept cpp17_destructible =
	std::is_object_v<T> &&
	std::is_destructible_v<T> &&
	!hamon::is_array_v<T>;

#else

template <typename T>
using cpp17_destructible =
	hamon::conjunction<
		std::is_object<T>,
		std::is_destructible<T>,
		hamon::negation<hamon::is_array<T>>
	>;

#endif

template <typename T>
using cpp17_destructible_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_destructible<T>>;
#else
	hamon::detail::cpp17_destructible<T>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CPP17_DESTRUCTIBLE_HPP
