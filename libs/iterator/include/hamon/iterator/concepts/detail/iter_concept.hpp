/**
 *	@file	iter_concept.hpp
 *
 *	@brief	iter_concept の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_CONCEPT_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_CONCEPT_HPP

#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/concepts/detail/iter_traits.hpp>
#include <hamon/iterator/detail/is_iterator_traits_primary.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/config.hpp>

// 25.3.4.1 General[iterator.concepts.general]

namespace hamon
{

namespace detail
{

template <typename I>
struct iter_concept_impl
{
private:
	// [iterator.concepts.general]/1.1
	template <typename I2,
		typename R = typename hamon::detail::iter_traits<I2>::iterator_concept>
	static auto test(hamon::detail::overload_priority<2>)
		-> hamon::type_identity<R>;

	// [iterator.concepts.general]/1.2
	template <typename I2,
		typename R = typename hamon::detail::iter_traits<I2>::iterator_category>
	static auto test(hamon::detail::overload_priority<1>)
		-> hamon::type_identity<R>;

	// [iterator.concepts.general]/1.3
	template <typename I2,
		typename = typename hamon::enable_if_t<
			detail::is_iterator_traits_primary<I2>::value>>
	static auto test(hamon::detail::overload_priority<0>)
		-> hamon::type_identity<hamon::random_access_iterator_tag>;

	// [iterator.concepts.general]/1.4
	// does not denote a type.

public:
	using type = typename decltype(test<I>(hamon::detail::overload_priority<2>{}))::type;
};

// ITER_CONCEPT(I)
template <typename I>
using iter_concept = typename iter_concept_impl<I>::type;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_CONCEPT_HPP
