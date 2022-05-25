/**
 *	@file	primary_traits_iter.hpp
 *
 *	@brief	primary_traits_iter の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_PRIMARY_TRAITS_ITER_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_PRIMARY_TRAITS_ITER_HPP

#include <hamon/iterator/concepts/detail/is_iterator_traits_specialized.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept primary_traits_iter =
	!detail::is_iterator_traits_specialized<Iter>::value;

#else

template <typename Iter>
using primary_traits_iter =
	hamon::bool_constant<!detail::is_iterator_traits_specialized<Iter>::value>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_PRIMARY_TRAITS_ITER_HPP
