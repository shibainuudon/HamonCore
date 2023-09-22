/**
 *	@file	same_as.hpp
 *
 *	@brief	same_as の定義
 */

#ifndef HAMON_CONCEPTS_SAME_AS_HPP
#define HAMON_CONCEPTS_SAME_AS_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_same.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::same_as;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

namespace detail
{

template <typename T, typename U>
concept SameHelper = hamon::is_same<T, U>::value;

}	// namespace detail

template <typename T, typename U>
concept same_as =
	detail::SameHelper<T, U> &&
	detail::SameHelper<U, T>;

#else

template <typename T, typename U>
using same_as =
	hamon::conjunction<
		hamon::is_same<T, U>,
		hamon::is_same<U, T>
	>;

#endif

template <typename T, typename U>
using same_as_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::same_as<T, U>>;
#else
	hamon::same_as<T, U>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_SAME_AS_HPP
