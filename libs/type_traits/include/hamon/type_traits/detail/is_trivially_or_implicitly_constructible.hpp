/**
 *	@file	is_trivially_or_implicitly_constructible.hpp
 *
 *	@brief	is_trivially_or_implicitly_constructible の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_OR_IMPLICITLY_CONSTRUCTIBLE_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_OR_IMPLICITLY_CONSTRUCTIBLE_HPP

#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>

namespace hamon
{

namespace detail
{

template <typename T, typename... Args>
using is_trivially_or_implicitly_constructible =
	hamon::disjunction<
		hamon::is_trivially_constructible<T, Args...>,
		hamon::is_implicitly_constructible<T, Args...>
	>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_TRIVIALLY_OR_IMPLICITLY_CONSTRUCTIBLE_HPP
