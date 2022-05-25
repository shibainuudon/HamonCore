/**
 *	@file	iter_without_nested_types.hpp
 *
 *	@brief	iter_without_nested_types の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_WITHOUT_NESTED_TYPES_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_WITHOUT_NESTED_TYPES_HPP

#include <hamon/iterator/concepts/detail/iter_with_nested_types.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept iter_without_nested_types = !iter_with_nested_types<Iter>;

#else

template <typename Iter>
using iter_without_nested_types = hamon::negation<iter_with_nested_types<Iter>>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_WITHOUT_NESTED_TYPES_HPP
