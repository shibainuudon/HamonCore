/**
 *	@file	weakly_equality_comparable_with.hpp
 *
 *	@brief	weakly_equality_comparable_with の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_WEAKLY_EQUALITY_COMPARABLE_WITH_HPP
#define HAMON_CONCEPTS_DETAIL_WEAKLY_EQUALITY_COMPARABLE_WITH_HPP

#include <hamon/concepts/detail/boolean_testable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// [concept.equalitycomparable]/1

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept weakly_equality_comparable_with =
	requires(
		hamon::remove_reference_t<T> const& t,
		hamon::remove_reference_t<U> const& u)
	{
		{ t == u } -> detail::boolean_testable;
		{ t != u } -> detail::boolean_testable;
		{ u == t } -> detail::boolean_testable;
		{ u != t } -> detail::boolean_testable;
	};

#else

template <typename T, typename U>
struct weakly_equality_comparable_with_impl
{
private:
	template <
		typename T2, typename U2,
		typename TR = hamon::remove_reference_t<T2> const&,
		typename UR = hamon::remove_reference_t<U2> const&,
		typename B1 = decltype(hamon::declval<TR>() == hamon::declval<UR>()),
		typename B2 = decltype(hamon::declval<TR>() != hamon::declval<UR>()),
		typename B3 = decltype(hamon::declval<UR>() == hamon::declval<TR>()),
		typename B4 = decltype(hamon::declval<UR>() != hamon::declval<TR>())
	>
	static auto test(int) -> hamon::conjunction<
		boolean_testable<B1>,
		boolean_testable<B2>,
		boolean_testable<B3>,
		boolean_testable<B4>
	>;

	template <typename T2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U>(0));
};

template <typename T, typename U>
using weakly_equality_comparable_with =
	typename weakly_equality_comparable_with_impl<T, U>::type;

#endif

template <typename T, typename U>
using weakly_equality_comparable_with_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::weakly_equality_comparable_with<T, U>>;
#else
	hamon::detail::weakly_equality_comparable_with<T, U>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_WEAKLY_EQUALITY_COMPARABLE_WITH_HPP
