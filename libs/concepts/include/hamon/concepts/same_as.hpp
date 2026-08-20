/**
 *	@file	same_as.hpp
 *
 *	@brief	same_as の定義
 */

#ifndef HAMON_CONCEPTS_SAME_AS_HPP
#define HAMON_CONCEPTS_SAME_AS_HPP

#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.2 Concept same_as [concept.same]

namespace detail
{

template <typename T, typename U>
HAMON_CONCEPT_OR_BOOL same_as_impl = hamon::is_same<T, U>::value;

}	// namespace detail

template <typename T, typename U>
HAMON_CONCEPT_OR_BOOL same_as =
	detail::same_as_impl<T, U> &&
	detail::same_as_impl<U, T>;

}	// namespace hamon

#endif // HAMON_CONCEPTS_SAME_AS_HPP
