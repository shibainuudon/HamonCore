﻿/**
 *	@file	iter_with_nested_types.hpp
 *
 *	@brief	iter_with_nested_types の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_WITH_NESTED_TYPES_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_WITH_NESTED_TYPES_HPP

#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept iter_with_nested_types =
	requires
	{
		typename Iter::iterator_category;
		typename Iter::value_type;
		typename Iter::difference_type;
		typename Iter::reference;
	};

#else

namespace iter_with_nested_types_detail
{

template <typename Iter>
struct iter_with_nested_types_impl
{
private:
	template <typename I2,
		typename = typename I2::iterator_category,
		typename = typename I2::value_type,
		typename = typename I2::difference_type,
		typename = typename I2::reference
	>
	static auto test(int) -> std::true_type;

	template <typename I2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace iter_with_nested_types_detail

template <typename Iter>
using iter_with_nested_types =
	typename iter_with_nested_types_detail::iter_with_nested_types_impl<Iter>::type;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_ITER_WITH_NESTED_TYPES_HPP
