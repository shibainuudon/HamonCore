﻿/**
 *	@file	indirect_binary_predicate.hpp
 *
 *	@brief	indirect_binary_predicate の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_INDIRECT_BINARY_PREDICATE_HPP
#define HAMON_ITERATOR_CONCEPTS_INDIRECT_BINARY_PREDICATE_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/detail/indirect_value_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_common_reference_t.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/predicate.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::indirect_binary_predicate;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename F, typename I1, typename I2>
concept indirect_binary_predicate =
	hamon::indirectly_readable<I1> &&
	hamon::indirectly_readable<I2> &&
	hamon::copy_constructible<F> &&
	hamon::predicate<F&, hamon::detail::indirect_value_t<I1>, hamon::detail::indirect_value_t<I2>> &&
	hamon::predicate<F&, hamon::detail::indirect_value_t<I1>, hamon::iter_reference_t<I2>> &&
	hamon::predicate<F&, hamon::iter_reference_t<I1>, hamon::detail::indirect_value_t<I2>> &&
	hamon::predicate<F&, hamon::iter_reference_t<I1>, hamon::iter_reference_t<I2>> &&
	hamon::predicate<F&, hamon::iter_common_reference_t<I1>, hamon::iter_common_reference_t<I2>>;

#else

namespace detail
{

template <typename F, typename I1, typename I2>
struct indirect_binary_predicate_impl
{
private:
	template <typename F2, typename J1, typename J2,
		typename = hamon::enable_if_t<hamon::indirectly_readable<J1>::value>,
		typename = hamon::enable_if_t<hamon::indirectly_readable<J2>::value>,
		typename = hamon::enable_if_t<hamon::copy_constructible<F2>::value>,
		typename V1 = hamon::detail::indirect_value_t<J1>,
		typename V2 = hamon::detail::indirect_value_t<J2>,
		typename R1 = hamon::iter_reference_t<J1>,
		typename R2 = hamon::iter_reference_t<J2>,
		typename C1 = hamon::iter_common_reference_t<J1>,
		typename C2 = hamon::iter_common_reference_t<J2>,
		typename = hamon::enable_if_t<hamon::predicate<F2&, V1, V2>::value>,
		typename = hamon::enable_if_t<hamon::predicate<F2&, V1, R2>::value>,
		typename = hamon::enable_if_t<hamon::predicate<F2&, R1, V2>::value>,
		typename = hamon::enable_if_t<hamon::predicate<F2&, R1, R2>::value>,
		typename = hamon::enable_if_t<hamon::predicate<F2&, C1, C2>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename F2, typename J1, typename J2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<F, I1, I2>(0));
};

}	// namespace detail

template <typename F, typename I1, typename I2>
using indirect_binary_predicate =
	typename detail::indirect_binary_predicate_impl<F, I1, I2>::type;

#endif

template <typename F, typename I1, typename I2>
using indirect_binary_predicate_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::indirect_binary_predicate<F, I1, I2>>;
#else
	hamon::indirect_binary_predicate<F, I1, I2>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_INDIRECT_BINARY_PREDICATE_HPP
