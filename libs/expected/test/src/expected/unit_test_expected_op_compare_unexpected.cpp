/**
 *	@file	unit_test_expected_op_compare_unexpected.cpp
 *
 *	@brief	operator== のテスト
 *
 *	template<class E2> friend constexpr bool operator==(const expected& x, const unexpected<E2>& e);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace op_compare_unexpected_test
{

struct NonComparable
{
};

struct Comparable
{
	bool operator==(Comparable const&) const;
};

struct ComparableWithInt
{
	friend bool operator==(ComparableWithInt const&, int);
	friend bool operator==(int, ComparableWithInt const&);
};

struct NonConvertibleToBool
{
	void operator==(NonConvertibleToBool const&) const;
};

struct NothrowComparable
{
	bool operator==(NothrowComparable const&) const noexcept;
};

#if !defined(HAMON_USE_STD_EXPECTED) || \
	(defined(__cpp_lib_constrained_equality) && (__cpp_lib_constrained_equality >= 202411L))

template <typename T, typename U, typename = void, typename = void, typename = void, typename = void>
struct can_compare
	: hamon::false_type{};

template <typename T, typename U>
struct can_compare<T, U,
	hamon::void_t<decltype(hamon::declval<T const&>() == hamon::declval<U const&>())>,
	hamon::void_t<decltype(hamon::declval<T const&>() != hamon::declval<U const&>())>,
	hamon::void_t<decltype(hamon::declval<U const&>() == hamon::declval<T const&>())>,
	hamon::void_t<decltype(hamon::declval<U const&>() != hamon::declval<T const&>())>>
	: hamon::true_type{};

static_assert( can_compare<hamon::expected<int, int>, hamon::unexpected<int>>::value, "");
static_assert( can_compare<hamon::expected<int, int>, hamon::unexpected<short>>::value, "");
static_assert(!can_compare<hamon::expected<int, int>, hamon::unexpected<Comparable>>::value, "");
static_assert( can_compare<hamon::expected<int, int>, hamon::unexpected<ComparableWithInt>>::value, "");
static_assert( can_compare<hamon::expected<int, Comparable>, hamon::unexpected<Comparable>>::value, "");
static_assert(!can_compare<hamon::expected<Comparable, int>, hamon::unexpected<Comparable>>::value, "");
static_assert(!can_compare<hamon::expected<int, NonComparable>, hamon::unexpected<NonComparable>>::value, "");
static_assert(!can_compare<hamon::expected<int, NonConvertibleToBool>, hamon::unexpected<NonConvertibleToBool>>::value, "");
static_assert( can_compare<hamon::expected<NonComparable, int>, hamon::unexpected<int>>::value, "");
static_assert( can_compare<hamon::expected<NonComparable, int>, hamon::unexpected<ComparableWithInt>>::value, "");

#endif

#if !defined(HAMON_USE_STD_EXPECTED)
template <typename T, typename U>
using nothrow_compare = hamon::bool_constant<
	noexcept(hamon::declval<T const&>() == hamon::declval<U const&>()) &&
	noexcept(hamon::declval<T const&>() != hamon::declval<U const&>()) &&
	noexcept(hamon::declval<U const&>() == hamon::declval<T const&>()) &&
	noexcept(hamon::declval<U const&>() != hamon::declval<T const&>())>;

static_assert(!nothrow_compare<hamon::expected<Comparable,        Comparable>,        hamon::unexpected<Comparable>>::value, "");
static_assert( nothrow_compare<hamon::expected<Comparable,        NothrowComparable>, hamon::unexpected<NothrowComparable>>::value, "");
static_assert(!nothrow_compare<hamon::expected<NothrowComparable, Comparable>,        hamon::unexpected<Comparable>>::value, "");
static_assert( nothrow_compare<hamon::expected<NothrowComparable, NothrowComparable>, hamon::unexpected<NothrowComparable>>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	hamon::expected<T, E> e1{hamon::in_place, T{10}};
	hamon::expected<T, E> e2{hamon::unexpect, E{20}};

#if !defined(HAMON_USE_STD_EXPECTED)
	static_assert( noexcept(e1 == hamon::unexpected<E>{E{0}}), "");
	static_assert( noexcept(e1 != hamon::unexpected<E>{E{0}}), "");
#endif

	VERIFY(!(e1 == hamon::unexpected<E>{E{10}}));
	VERIFY(!(e1 == hamon::unexpected<E>{E{20}}));
	VERIFY(!(e2 == hamon::unexpected<E>{E{10}}));
	VERIFY( (e2 == hamon::unexpected<E>{E{20}}));

	VERIFY( (e1 != hamon::unexpected<E>{E{10}}));
	VERIFY( (e1 != hamon::unexpected<E>{E{20}}));
	VERIFY( (e2 != hamon::unexpected<E>{E{10}}));
	VERIFY(!(e2 != hamon::unexpected<E>{E{20}}));

	VERIFY(!(hamon::unexpected<E>{E{10}} == e1));
	VERIFY(!(hamon::unexpected<E>{E{20}} == e1));
	VERIFY(!(hamon::unexpected<E>{E{10}} == e2));
	VERIFY( (hamon::unexpected<E>{E{20}} == e2));

	VERIFY( (hamon::unexpected<E>{E{10}} != e1));
	VERIFY( (hamon::unexpected<E>{E{20}} != e1));
	VERIFY( (hamon::unexpected<E>{E{10}} != e2));
	VERIFY(!(hamon::unexpected<E>{E{20}} != e2));

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, OpCompareUnexpectedTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

}	// namespace op_compare_unexpected_test

}	// namespace hamon_expected_test
