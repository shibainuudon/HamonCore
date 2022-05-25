/**
 *	@file	iter_traits.hpp
 *
 *	@brief	iter_traits の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_TRAITS_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_TRAITS_HPP

#include <hamon/iterator/concepts/detail/primary_traits_iter.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Iter, typename T, typename = void>
struct iter_traits_impl
{
	using type = hamon::iterator_traits<Iter>;
};

template <typename Iter, typename T>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires detail::primary_traits_iter<Iter>
#endif
struct iter_traits_impl<Iter, T
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, hamon::enable_if_t<detail::primary_traits_iter<Iter>::value>
#endif
>
{
	using type = T;
};

// ITER_TRAITS
template <typename Iter, typename T = Iter>
using iter_traits = typename iter_traits_impl<Iter, T>::type;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_TRAITS_HPP
