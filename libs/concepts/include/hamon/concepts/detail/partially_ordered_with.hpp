﻿/**
 *	@file	partially_ordered_with.hpp
 *
 *	@brief	partially_ordered_with の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_PARTIALLY_ORDERED_WITH_HPP
#define HAMON_CONCEPTS_DETAIL_PARTIALLY_ORDERED_WITH_HPP

#include <hamon/concepts/detail/cref.hpp>
#include <hamon/concepts/detail/boolean_testable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept partially_ordered_with =
	requires(detail::cref<T> t, detail::cref<U> u)
	{
		{ t <  u } -> detail::boolean_testable;
		{ t >  u } -> detail::boolean_testable;
		{ t <= u } -> detail::boolean_testable;
		{ t >= u } -> detail::boolean_testable;
		{ u <  t } -> detail::boolean_testable;
		{ u >  t } -> detail::boolean_testable;
		{ u <= t } -> detail::boolean_testable;
		{ u >= t } -> detail::boolean_testable;
	};

#else

template <typename T, typename U>
struct partially_ordered_with_impl
{
private:
	template <
		typename T2, typename U2,
		typename TR = detail::cref<T2>,
		typename UR = detail::cref<U2>,
		typename B1 = decltype(std::declval<TR>() <  std::declval<UR>()),
		typename B2 = decltype(std::declval<TR>() >  std::declval<UR>()),
		typename B3 = decltype(std::declval<TR>() <= std::declval<UR>()),
		typename B4 = decltype(std::declval<TR>() >= std::declval<UR>()),
		typename B5 = decltype(std::declval<UR>() <  std::declval<TR>()),
		typename B6 = decltype(std::declval<UR>() >  std::declval<TR>()),
		typename B7 = decltype(std::declval<UR>() <= std::declval<TR>()),
		typename B8 = decltype(std::declval<UR>() >= std::declval<TR>())
	>
	static auto test(int) -> hamon::conjunction<
		boolean_testable<B1>,
		boolean_testable<B2>,
		boolean_testable<B3>,
		boolean_testable<B4>,
		boolean_testable<B5>,
		boolean_testable<B6>,
		boolean_testable<B7>,
		boolean_testable<B8>
	>;

	template <typename T2, typename U2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T, U>(0));
};

template <typename T, typename U>
using partially_ordered_with =
	typename partially_ordered_with_impl<T, U>::type;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_PARTIALLY_ORDERED_WITH_HPP
