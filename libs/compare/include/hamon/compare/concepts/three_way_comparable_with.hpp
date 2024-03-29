﻿/**
 *	@file	three_way_comparable_with.hpp
 *
 *	@brief	three_way_comparable_with の定義
 */

#ifndef HAMON_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_WITH_HPP
#define HAMON_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_WITH_HPP

#include <hamon/compare/config.hpp>

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

#if defined(HAMON_USE_STD_COMPARE) && defined(HAMON_HAS_CXX20_CONCEPTS)

#include <compare>

namespace hamon
{

using std::three_way_comparable_with;

}	// namespace hamon

#else	// defined(HAMON_USE_STD_COMPARE)

#include <hamon/compare/partial_ordering.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/compare/detail/compares_as.hpp>
#include <hamon/compare/detail/partially_ordered_with.hpp>
#include <hamon/concepts/detail/comparison_common_type_with.hpp>
#include <hamon/concepts/detail/weakly_equality_comparable_with.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U, typename Cat = hamon::partial_ordering>
concept three_way_comparable_with =
	hamon::three_way_comparable<T, Cat> &&
	hamon::three_way_comparable<U, Cat> &&
	detail::comparison_common_type_with<T, U> &&
	hamon::three_way_comparable<
		hamon::common_reference_t<
			hamon::remove_reference_t<T> const&,
			hamon::remove_reference_t<U> const&
		>, Cat> &&
	detail::weakly_equality_comparable_with<T, U> &&
	detail::partially_ordered_with<T, U> &&
	requires(
		hamon::remove_reference_t<T> const& t,
		hamon::remove_reference_t<U> const& u)
	{
		{ t <=> u } -> detail::compares_as<Cat>;
		{ u <=> t } -> detail::compares_as<Cat>;
	};

#else	// defined(HAMON_HAS_CXX20_CONCEPTS)

namespace detail
{

template <typename T, typename U, typename Cat>
struct three_way_comparable_with_impl
{
private:
	template <typename T2, typename U2, typename C2,
		typename = hamon::enable_if_t<hamon::three_way_comparable<T2, C2>::value>,
		typename = hamon::enable_if_t<hamon::three_way_comparable<U2, C2>::value>,
		typename = hamon::enable_if_t<detail::comparison_common_type_with<T2, U2>::value>,
		typename = hamon::enable_if_t<hamon::three_way_comparable<
			hamon::common_reference_t<
				hamon::remove_reference_t<T2> const&,
				hamon::remove_reference_t<U2> const&
			>, C2>::value>,
		typename = hamon::enable_if_t<detail::weakly_equality_comparable_with<T2, U2>::value>,
		typename = hamon::enable_if_t<detail::partially_ordered_with<T2, U2>::value>,
		typename A = hamon::remove_reference_t<T2>,
		typename B = hamon::remove_reference_t<U2>,
		typename R1 = decltype(hamon::declval<A const&>() <=> hamon::declval<B const&>()),
		typename R2 = decltype(hamon::declval<B const&>() <=> hamon::declval<A const&>())
	>
	static auto test(int) -> hamon::conjunction<
		detail::compares_as<R1, C2>,
		detail::compares_as<R2, C2>
	>;

	template <typename T2, typename U2, typename C2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U, Cat>(0));
};

}	// namespace detail

template <typename T, typename U, typename Cat = hamon::partial_ordering>
using three_way_comparable_with =
	typename detail::three_way_comparable_with_impl<T, U, Cat>::type;

#endif	// defined(HAMON_HAS_CXX20_CONCEPTS)

}	// namespace hamon

#endif	// defined(HAMON_USE_STD_COMPARE)

#include <hamon/compare/partial_ordering.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T, typename U, typename Cat = hamon::partial_ordering>
using three_way_comparable_with_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::three_way_comparable_with<T, U, Cat>>;
#else
	hamon::three_way_comparable_with<T, U, Cat>;
#endif

}	// namespace hamon

#endif	// defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

#endif // HAMON_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_WITH_HPP
