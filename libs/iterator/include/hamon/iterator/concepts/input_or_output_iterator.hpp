﻿/**
 *	@file	input_or_output_iterator.hpp
 *
 *	@brief	input_or_output_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INPUT_OR_OUTPUT_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_INPUT_OR_OUTPUT_ITERATOR_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/detail/can_reference.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::input_or_output_iterator;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept input_or_output_iterator =
	requires(Iter i) { { *i } -> hamon::detail::can_reference; } &&
	hamon::weakly_incrementable<Iter>;

#else

namespace detail
{

template <typename Iter>
struct input_or_output_iterator_impl
{
private:
	template <typename I2,
		typename T = decltype(*hamon::declval<I2&>()),
		typename = hamon::enable_if_t<hamon::detail::can_reference<T>::value>,
		typename = hamon::enable_if_t<hamon::weakly_incrementable<I2>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using input_or_output_iterator =
	typename detail::input_or_output_iterator_impl<Iter>::type;

#endif

template <typename Iter>
using input_or_output_iterator_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::input_or_output_iterator<Iter>>;
#else
	hamon::input_or_output_iterator<Iter>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INPUT_OR_OUTPUT_ITERATOR_HPP
