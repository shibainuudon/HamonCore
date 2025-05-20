/**
 *	@file	unit_test_expected_op_compare_expected.cpp
 *
 *	@brief	operator== のテスト
 *
 *	template<class T2, class E2> requires (!is_void_v<T2>)
 *	friend constexpr bool operator==(const expected& x, const expected<T2, E2>& y);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace op_compare_expected_test
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
	int v;

	friend constexpr bool operator==(ComparableWithInt const& lhs, int rhs)
	{
		return lhs.v == rhs;
	}

	friend constexpr bool operator==(int lhs, ComparableWithInt const& rhs)
	{
		return lhs == rhs.v;
	}
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

static_assert( can_compare<hamon::expected<int, int>, hamon::expected<int, int>>::value, "");
static_assert( can_compare<hamon::expected<int, int>, hamon::expected<short, short>>::value, "");
static_assert(!can_compare<hamon::expected<int, int>, hamon::expected<void, int>>::value, "");
static_assert(!can_compare<hamon::expected<void, int>, hamon::expected<int, int>>::value, "");
static_assert( can_compare<hamon::expected<void, int>, hamon::expected<void, int>>::value, "");
static_assert(!can_compare<hamon::expected<int, NonComparable>, hamon::expected<int, NonComparable>>::value, "");
static_assert(!can_compare<hamon::expected<NonComparable, int>, hamon::expected<NonComparable, int>>::value, "");
static_assert( can_compare<hamon::expected<int, Comparable>, hamon::expected<int, Comparable>>::value, "");
static_assert( can_compare<hamon::expected<Comparable, int>, hamon::expected<Comparable, int>>::value, "");
static_assert(!can_compare<hamon::expected<int, Comparable>, hamon::expected<Comparable, int>>::value, "");
static_assert(!can_compare<hamon::expected<Comparable, int>, hamon::expected<int, Comparable>>::value, "");
static_assert( can_compare<hamon::expected<int, int>, hamon::expected<ComparableWithInt, int>>::value, "");
static_assert( can_compare<hamon::expected<int, int>, hamon::expected<int, ComparableWithInt>>::value, "");
static_assert(!can_compare<hamon::expected<ComparableWithInt, int>, hamon::expected<ComparableWithInt, int>>::value, "");
static_assert(!can_compare<hamon::expected<int, ComparableWithInt>, hamon::expected<int, ComparableWithInt>>::value, "");
static_assert(!can_compare<hamon::expected<NonConvertibleToBool, int>, hamon::expected<NonConvertibleToBool, int>>::value, "");
static_assert(!can_compare<hamon::expected<int, NonConvertibleToBool>, hamon::expected<int, NonConvertibleToBool>>::value, "");

#endif

#if !defined(HAMON_USE_STD_EXPECTED)
template <typename T, typename U>
using nothrow_compare = hamon::bool_constant<
	noexcept(hamon::declval<T const&>() == hamon::declval<U const&>()) &&
	noexcept(hamon::declval<T const&>() != hamon::declval<U const&>()) &&
	noexcept(hamon::declval<U const&>() == hamon::declval<T const&>()) &&
	noexcept(hamon::declval<U const&>() != hamon::declval<T const&>())>;

static_assert(!nothrow_compare<hamon::expected<Comparable,        Comparable>,        hamon::expected<Comparable,        Comparable>>::value, "");
static_assert(!nothrow_compare<hamon::expected<Comparable,        NothrowComparable>, hamon::expected<Comparable,        NothrowComparable>>::value, "");
static_assert(!nothrow_compare<hamon::expected<NothrowComparable, Comparable>,        hamon::expected<NothrowComparable, Comparable>>::value, "");
static_assert( nothrow_compare<hamon::expected<NothrowComparable, NothrowComparable>, hamon::expected<NothrowComparable, NothrowComparable>>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	hamon::expected<T, E> e1{hamon::in_place, T{5}};
	hamon::expected<T, E> e2{hamon::in_place, T{10}};
	hamon::expected<T, E> e3{hamon::in_place, T{5}};
	hamon::expected<T, E> e4{hamon::unexpect, E{5}};
	hamon::expected<T, E> e5{hamon::unexpect, E{10}};
	hamon::expected<T, E> e6{hamon::unexpect, E{5}};

#if !defined(HAMON_USE_STD_EXPECTED)
	static_assert( noexcept(e1 == e1), "");
	static_assert( noexcept(e1 != e1), "");
#endif

	VERIFY( (e1 == e1));
	VERIFY(!(e1 == e2));
	VERIFY( (e1 == e3));
	VERIFY(!(e1 == e4));
	VERIFY(!(e1 == e5));
	VERIFY(!(e1 == e6));

	VERIFY(!(e4 == e1));
	VERIFY(!(e4 == e2));
	VERIFY(!(e4 == e3));
	VERIFY( (e4 == e4));
	VERIFY(!(e4 == e5));
	VERIFY( (e4 == e6));

	VERIFY(!(e1 != e1));
	VERIFY( (e1 != e2));
	VERIFY(!(e1 != e3));
	VERIFY( (e1 != e4));
	VERIFY( (e1 != e5));
	VERIFY( (e1 != e6));

	VERIFY( (e4 != e1));
	VERIFY( (e4 != e2));
	VERIFY( (e4 != e3));
	VERIFY(!(e4 != e4));
	VERIFY( (e4 != e5));
	VERIFY(!(e4 != e6));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test2()
{
	hamon::expected<ComparableWithInt, int> e1{hamon::in_place, ComparableWithInt{1}};
	hamon::expected<int, ComparableWithInt> e2{hamon::in_place, 2};
	hamon::expected<int, ComparableWithInt> e3{hamon::in_place, 1};
	hamon::expected<int, ComparableWithInt> e4{hamon::unexpect, ComparableWithInt{2}};
	hamon::expected<int, ComparableWithInt> e5{hamon::unexpect, ComparableWithInt{1}};

	VERIFY(!(e1 == e2));
	VERIFY( (e1 == e3));
	VERIFY(!(e1 == e4));
	VERIFY(!(e1 == e5));

	VERIFY( (e1 != e2));
	VERIFY(!(e1 != e3));
	VERIFY( (e1 != e4));
	VERIFY( (e1 != e5));

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, OpCompareExpectedTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2()));
}

}	// namespace op_compare_expected_test

}	// namespace hamon_expected_test
