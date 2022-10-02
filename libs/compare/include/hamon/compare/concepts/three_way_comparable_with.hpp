/**
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
#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/concepts/detail/weakly_eq_cmp_with.hpp>
#include <hamon/concepts/detail/partially_ordered_with.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U, typename Cat = hamon::partial_ordering>
concept three_way_comparable_with =
	hamon::three_way_comparable<T, Cat> &&
	hamon::three_way_comparable<U, Cat> &&
	hamon::common_reference_with<
		hamon::remove_reference_t<T> const&,
		hamon::remove_reference_t<U> const&> &&
	hamon::three_way_comparable<
		hamon::common_reference_t<
			hamon::remove_reference_t<T> const&,
			hamon::remove_reference_t<U> const&
		>, Cat> &&
	detail::weakly_eq_cmp_with<T, U> &&
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
		typename = hamon::enable_if_t<hamon::three_way_comparable<T2, C2>>,
		typename = hamon::enable_if_t<hamon::three_way_comparable<U2, C2>>,
		typename = hamon::enable_if_t<hamon::common_reference_with<
			hamon::remove_reference_t<T2> const&,
			hamon::remove_reference_t<U2> const&> &&
		typename = hamon::enable_if_t<hamon::three_way_comparable<
			hamon::common_reference_t<
				hamon::remove_reference_t<T2> const&,
				hamon::remove_reference_t<U2> const&
			>, C2>>,
		typename = hamon::enable_if_t<detail::weakly_eq_cmp_with<T2, U2>>,
		typename = hamon::enable_if_t<detail::partially_ordered_with<T2, U2>>,
		typename A = hamon::remove_reference_t<T2>,
		typename B = hamon::remove_reference_t<U2>,
		typename R1 = decltype(std::declval<A const&>() <=> std::declval<B const&>()),
		typename R2 = decltype(std::declval<B const&>() <=> std::declval<A const&>())
	>
	static auto test(int) -> hamon::conjunction<
		detail::compares_as<R1, C2>,
		detail::compares_as<R2, C2>
	>;

	template <typename T2, typename U2, typename C2>
	static auto test(...) -> std::false_type;

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

#endif	// defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

#endif // HAMON_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_WITH_HPP
