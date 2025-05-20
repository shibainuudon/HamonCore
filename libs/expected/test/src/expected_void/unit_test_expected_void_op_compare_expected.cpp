/**
 *	@file	unit_test_expected_void_op_compare_expected.cpp
 *
 *	@brief	operator== のテスト
 *
 *	template<class T2, class E2> requires is_void_v<T2>
 *	friend constexpr bool operator==(const expected& x, const expected<T2, E2>& y);
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
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

static_assert( can_compare<hamon::expected<void, int>, hamon::expected<void, int>>::value, "");
static_assert( can_compare<hamon::expected<void, int>, hamon::expected<void, short>>::value, "");
static_assert(!can_compare<hamon::expected<void, int>, hamon::expected<int, int>>::value, "");
static_assert(!can_compare<hamon::expected<void, NonComparable>, hamon::expected<void, NonComparable>>::value, "");
static_assert( can_compare<hamon::expected<void, Comparable>, hamon::expected<void, Comparable>>::value, "");
static_assert(!can_compare<hamon::expected<void, ComparableWithInt>, hamon::expected<void, ComparableWithInt>>::value, "");
static_assert(!can_compare<hamon::expected<void, NonConvertibleToBool>, hamon::expected<void, NonConvertibleToBool>>::value, "");
static_assert(!can_compare<hamon::expected<void, NonComparable>, hamon::expected<void, int>>::value, "");
static_assert(!can_compare<hamon::expected<void, Comparable>, hamon::expected<void, int>>::value, "");
static_assert( can_compare<hamon::expected<void, ComparableWithInt>, hamon::expected<void, int>>::value, "");
static_assert(!can_compare<hamon::expected<void, NonConvertibleToBool>, hamon::expected<void, int>>::value, "");

#endif

#if !defined(HAMON_USE_STD_EXPECTED)
template <typename T, typename U>
using nothrow_compare = hamon::bool_constant<
	noexcept(hamon::declval<T const&>() == hamon::declval<U const&>()) &&
	noexcept(hamon::declval<T const&>() != hamon::declval<U const&>()) &&
	noexcept(hamon::declval<U const&>() == hamon::declval<T const&>()) &&
	noexcept(hamon::declval<U const&>() != hamon::declval<T const&>())>;

static_assert(!nothrow_compare<hamon::expected<void, Comparable>,        hamon::expected<void, Comparable>>::value, "");
static_assert( nothrow_compare<hamon::expected<void, NothrowComparable>, hamon::expected<void, NothrowComparable>>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");

	hamon::expected<Void, E> e1{hamon::in_place};
	hamon::expected<Void, E> e2{hamon::in_place};
	hamon::expected<Void, E> e3{hamon::unexpect, E{5}};
	hamon::expected<Void, E> e4{hamon::unexpect, E{10}};
	hamon::expected<Void, E> e5{hamon::unexpect, E{5}};

#if !defined(HAMON_USE_STD_EXPECTED)
	static_assert( noexcept(e1 == e1), "");
	static_assert( noexcept(e1 != e1), "");
#endif

	VERIFY( (e1 == e1));
	VERIFY( (e1 == e2));
	VERIFY(!(e1 == e3));
	VERIFY(!(e1 == e4));
	VERIFY(!(e1 == e5));

	VERIFY(!(e3 == e1));
	VERIFY(!(e3 == e2));
	VERIFY( (e3 == e3));
	VERIFY(!(e3 == e4));
	VERIFY( (e3 == e5));

	VERIFY(!(e1 != e1));
	VERIFY(!(e1 != e2));
	VERIFY( (e1 != e3));
	VERIFY( (e1 != e4));
	VERIFY( (e1 != e5));

	VERIFY( (e3 != e1));
	VERIFY( (e3 != e2));
	VERIFY(!(e3 != e3));
	VERIFY( (e3 != e4));
	VERIFY(!(e3 != e5));

	return true;
}

template <typename Void>
HAMON_CXX14_CONSTEXPR bool test2()
{
	hamon::expected<Void, ComparableWithInt> e1{hamon::in_place};
	hamon::expected<Void, ComparableWithInt> e2{hamon::unexpect, ComparableWithInt{1}};
	hamon::expected<Void, int>               e3{hamon::in_place};
	hamon::expected<Void, int>               e4{hamon::unexpect, 2};
	hamon::expected<Void, int>               e5{hamon::unexpect, 1};

	VERIFY( (e1 == e3));
	VERIFY(!(e1 == e4));
	VERIFY(!(e1 == e5));
	VERIFY(!(e2 == e3));
	VERIFY(!(e2 == e4));
	VERIFY( (e2 == e5));

	VERIFY(!(e1 != e3));
	VERIFY( (e1 != e4));
	VERIFY( (e1 != e5));
	VERIFY( (e2 != e3));
	VERIFY( (e2 != e4));
	VERIFY(!(e2 != e5));

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedVoidTest, OpCompareExpectedTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, double>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, short>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<void>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<void const>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<void volatile>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<void const volatile>()));
}

}	// namespace op_compare_expected_test

}	// namespace hamon_expected_void_test
