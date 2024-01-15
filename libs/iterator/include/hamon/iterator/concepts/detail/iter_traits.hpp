/**
 *	@file	iter_traits.hpp
 *
 *	@brief	iter_traits の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_TRAITS_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_TRAITS_HPP

#include <hamon/iterator/detail/is_iterator_traits_primary.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

// 25.3.4.1 General[iterator.concepts.general]

namespace hamon
{

namespace detail
{

// [iterator.concepts.general]/1

template <typename I, typename = void>
struct iter_traits_impl
{
	using type = hamon::iterator_traits<I>;
};

template <typename I>
struct iter_traits_impl<I,
	hamon::enable_if_t<detail::is_iterator_traits_primary<I>::value>>
{
	using type = I;
};

// ITER_TRAITS(I)
template <typename I>
using iter_traits = typename iter_traits_impl<I>::type;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_TRAITS_HPP
