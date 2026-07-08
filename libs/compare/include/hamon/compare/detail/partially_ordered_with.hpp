/**
 *	@file	partially_ordered_with.hpp
 *
 *	@brief	partially_ordered_with の定義
 */

#ifndef HAMON_COMPARE_DETAIL_PARTIALLY_ORDERED_WITH_HPP
#define HAMON_COMPARE_DETAIL_PARTIALLY_ORDERED_WITH_HPP

#include <hamon/concepts/detail/boolean_testable.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
HAMON_CONCEPT_OR_BOOL partially_ordered_with =
	requires(hamon::remove_reference_t<T> const& t, hamon::remove_reference_t<U> const& u)
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

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wordered-compare-function-pointers")

template <typename T, typename U>
struct partially_ordered_with_impl
{
private:
	template <
		typename T2, typename U2,
		typename TR = hamon::remove_reference_t<T2> const&,
		typename UR = hamon::remove_reference_t<U2> const&,
		typename = hamon::enable_if_t<
			boolean_testable<decltype(hamon::declval<TR>() <  hamon::declval<UR>())> &&
			boolean_testable<decltype(hamon::declval<TR>() >  hamon::declval<UR>())> &&
			boolean_testable<decltype(hamon::declval<TR>() <= hamon::declval<UR>())> &&
			boolean_testable<decltype(hamon::declval<TR>() >= hamon::declval<UR>())> &&
			boolean_testable<decltype(hamon::declval<UR>() <  hamon::declval<TR>())> &&
			boolean_testable<decltype(hamon::declval<UR>() >  hamon::declval<TR>())> &&
			boolean_testable<decltype(hamon::declval<UR>() <= hamon::declval<TR>())> &&
			boolean_testable<decltype(hamon::declval<UR>() >= hamon::declval<TR>())>
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename T2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U>(0));
};

HAMON_WARNING_POP()

template <typename T, typename U>
HAMON_CONCEPT_OR_BOOL partially_ordered_with =
	partially_ordered_with_impl<T, U>::type::value;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_PARTIALLY_ORDERED_WITH_HPP
