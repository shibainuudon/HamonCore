/**
 *	@file	unit_test_optional_hash.cpp
 *
 *	@brief	hash関数のテスト
 *
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace hash_test
{

template <typename T>
using invoke_hash = decltype(hamon::hash<T>{}(hamon::declval<T const&>()));

struct S1 {};
struct S2 {};

}	// namespace hash_test

}	// namespace hamon_optional_test

template <>
struct hamon::hash<hamon_optional_test::hash_test::S1>
{
	constexpr hamon::size_t operator()(hamon_optional_test::hash_test::S1 const&) const
	{
		return 42;
	}
};

namespace hamon_optional_test
{

namespace hash_test
{

static_assert( hamon::is_detected<invoke_hash, int>::value, "");
static_assert( hamon::is_detected<invoke_hash, float>::value, "");
static_assert( hamon::is_detected<invoke_hash, S1>::value, "");
static_assert(!hamon::is_detected<invoke_hash, S2>::value, "");

static_assert( hamon::is_detected<invoke_hash, hamon::optional<int>>::value, "");
static_assert( hamon::is_detected<invoke_hash, hamon::optional<float>>::value, "");
static_assert( hamon::is_detected<invoke_hash, hamon::optional<S1>>::value, "");
static_assert(!hamon::is_detected<invoke_hash, hamon::optional<S2>>::value, "");

static_assert( hamon::is_default_constructible<hamon::hash<hamon::optional<S1>>>::value, "");
static_assert( hamon::is_copy_constructible<hamon::hash<hamon::optional<S1>>>::value, "");
static_assert( hamon::is_move_constructible<hamon::hash<hamon::optional<S1>>>::value, "");
static_assert( hamon::is_copy_assignable<hamon::hash<hamon::optional<S1>>>::value, "");
static_assert( hamon::is_move_assignable<hamon::hash<hamon::optional<S1>>>::value, "");

static_assert(!hamon::is_default_constructible<hamon::hash<hamon::optional<S2>>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::hash<hamon::optional<S2>>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::hash<hamon::optional<S2>>>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::hash<hamon::optional<S2>>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::hash<hamon::optional<S2>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		int i = 13;
		hamon::optional<int> o(i);
		VERIFY(hamon::hash<hamon::optional<int>>{}(o) == hamon::hash<int>{}(i));
	}
	{
		float f = 2.5f;
		hamon::optional<float> o(f);
		VERIFY(hamon::hash<hamon::optional<float>>{}(o) == hamon::hash<float>{}(f));
	}
	{
		S1 x;
		hamon::optional<S1> o(x);
		VERIFY(hamon::hash<hamon::optional<S1>>{}(o) == hamon::hash<S1>{}(x));
		VERIFY(hamon::hash<hamon::optional<S1>>{}(o) == 42);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(OptionalTest, HashTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace hash_test

}	// namespace hamon_optional_test
