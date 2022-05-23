﻿/**
 *	@file	same_as.hpp
 *
 *	@brief	same_as の定義
 */

#ifndef HAMON_CONCEPTS_SAME_AS_HPP
#define HAMON_CONCEPTS_SAME_AS_HPP

#include <hamon/concepts/config.hpp>
#include <type_traits>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::same_as;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

namespace hamon
{

namespace detail
{

template <typename T, typename U>
concept SameHelper = std::is_same<T, U>::value;

}	// namespace detail

template <typename T, typename U>
concept same_as =
	detail::SameHelper<T, U> &&
	detail::SameHelper<U, T>;

}	// namespace hamon

#else

#include <hamon/type_traits/conjunction.hpp>

namespace hamon
{

template <typename T, typename U>
using same_as =
	hamon::conjunction<
		std::is_same<T, U>,
		std::is_same<U, T>
	>;

}	// namespace hamon

#endif

namespace hamon
{

template <typename T, typename U>
using same_as_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	std::bool_constant<hamon::same_as<T, U>>;
#else
	hamon::same_as<T, U>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_SAME_AS_HPP