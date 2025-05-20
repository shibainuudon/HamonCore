/**
 *	@file	unit_test_expected_op_compare_val.cpp
 *
 *	@brief	operator== のテスト
 *
 *	template<class T2> friend constexpr bool operator==(const expected& x, const T2& v);
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

namespace op_compare_val_test
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

struct NothrowComparableWithInt
{
	friend bool operator==(NothrowComparableWithInt const&, int) noexcept;
	friend bool operator==(int, NothrowComparableWithInt const&) noexcept;
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

static_assert( can_compare<hamon::expected<int, int>, int>::value, "");
static_assert( can_compare<hamon::expected<int, int>, short>::value, "");
static_assert(!can_compare<hamon::expected<int, int>, Comparable>::value, "");
static_assert( can_compare<hamon::expected<int, int>, ComparableWithInt>::value, "");
static_assert(!can_compare<hamon::expected<NonComparable, int>, NonComparable>::value, "");
static_assert( can_compare<hamon::expected<Comparable, int>, Comparable>::value, "");
static_assert(!can_compare<hamon::expected<int, Comparable>, Comparable>::value, "");
static_assert(!can_compare<hamon::expected<NonConvertibleToBool, int>, NonConvertibleToBool>::value, "");
static_assert( can_compare<hamon::expected<int, NonComparable>, int>::value, "");
static_assert( can_compare<hamon::expected<int, NonComparable>, ComparableWithInt>::value, "");

#endif

#if !defined(HAMON_USE_STD_EXPECTED)
template <typename T, typename U>
using nothrow_compare = hamon::bool_constant<
	noexcept(hamon::declval<T const&>() == hamon::declval<U const&>()) &&
	noexcept(hamon::declval<T const&>() != hamon::declval<U const&>()) &&
	noexcept(hamon::declval<U const&>() == hamon::declval<T const&>()) &&
	noexcept(hamon::declval<U const&>() != hamon::declval<T const&>())>;

static_assert(!nothrow_compare<hamon::expected<ComparableWithInt,        ComparableWithInt>,        int>::value, "");
static_assert(!nothrow_compare<hamon::expected<ComparableWithInt,        NothrowComparableWithInt>, int>::value, "");
static_assert( nothrow_compare<hamon::expected<NothrowComparableWithInt, ComparableWithInt>,        int>::value, "");
static_assert( nothrow_compare<hamon::expected<NothrowComparableWithInt, NothrowComparableWithInt>, int>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	hamon::expected<T, E> e1{hamon::in_place, T{10}};
	hamon::expected<T, E> e2{hamon::unexpect, E{20}};

#if !defined(HAMON_USE_STD_EXPECTED)
	static_assert( noexcept(e1 == T{0}), "");
	static_assert( noexcept(e1 != T{0}), "");
#endif

	VERIFY( (e1 == T{10}));
	VERIFY(!(e1 == T{20}));
	VERIFY(!(e2 == T{10}));
	VERIFY(!(e2 == T{20}));

	VERIFY(!(e1 != T{10}));
	VERIFY( (e1 != T{20}));
	VERIFY( (e2 != T{10}));
	VERIFY( (e2 != T{20}));

	VERIFY( (T{10} == e1));
	VERIFY(!(T{20} == e1));
	VERIFY(!(T{10} == e2));
	VERIFY(!(T{20} == e2));

	VERIFY(!(T{10} != e1));
	VERIFY( (T{20} != e1));
	VERIFY( (T{10} != e2));
	VERIFY( (T{20} != e2));

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, OpCompareValTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

}	// namespace op_compare_val_test

}	// namespace hamon_expected_test
