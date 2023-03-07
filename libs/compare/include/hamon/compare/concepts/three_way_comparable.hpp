/**
 *	@file	three_way_comparable.hpp
 *
 *	@brief	three_way_comparable の定義
 */

#ifndef HAMON_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_HPP
#define HAMON_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_HPP

#include <hamon/compare/config.hpp>

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

#if defined(HAMON_USE_STD_COMPARE) && defined(HAMON_HAS_CXX20_CONCEPTS)

#include <compare>

namespace hamon
{

using std::three_way_comparable;

}	// namespace hamon

#else	// defined(HAMON_USE_STD_COMPARE)

#include <hamon/compare/partial_ordering.hpp>
#include <hamon/compare/detail/compares_as.hpp>
#include <hamon/concepts/detail/weakly_eq_cmp_with.hpp>
#include <hamon/concepts/detail/partially_ordered_with.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename Cat = hamon::partial_ordering>
concept three_way_comparable =
	detail::weakly_eq_cmp_with<T, T> &&
	detail::partially_ordered_with<T, T> &&
	requires(
		hamon::remove_reference_t<T> const& a,
		hamon::remove_reference_t<T> const& b)
	{
		{ a <=> b } -> detail::compares_as<Cat>;
	};

#else	// defined(HAMON_HAS_CXX20_CONCEPTS)

namespace detail
{

template <typename T, typename Cat>
struct three_way_comparable_impl
{
private:
	template <typename T2, typename C2,
		typename = hamon::enable_if_t<hamon::conjunction<
			detail::weakly_eq_cmp_with<T2, T2>,
			detail::partially_ordered_with<T2, T2>
		>::value>,
		typename A = hamon::remove_reference_t<T2>,
		typename R = decltype(
			hamon::declval<A const&>() <=> hamon::declval<A const&>())
	>
	static auto test(int) -> detail::compares_as<R, C2>;

	template <typename T2, typename C2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, Cat>(0));
};

}	// namespace detail

template <typename T, typename Cat = hamon::partial_ordering>
using three_way_comparable =
	typename detail::three_way_comparable_impl<T, Cat>::type;

#endif	// defined(HAMON_HAS_CXX20_CONCEPTS)

}	// namespace hamon

#endif	// defined(HAMON_USE_STD_COMPARE)

#endif	// defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

#endif // HAMON_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_HPP
