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
using invoke_hash = decltype(std::hash<T>{}(hamon::declval<T const&>()));

struct S1 {};
struct S2 {};

}	// namespace hash_test

}	// namespace hamon_optional_test

namespace std
{

template <>
struct hash<hamon_optional_test::hash_test::S1>
{
	hamon::size_t operator()(hamon_optional_test::hash_test::S1 const&) const
	{
		return 42;
	}
};

}	// namespace std

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

static_assert( hamon::is_default_constructible<std::hash<hamon::optional<S1>>>::value, "");
static_assert( hamon::is_copy_constructible<std::hash<hamon::optional<S1>>>::value, "");
static_assert( hamon::is_move_constructible<std::hash<hamon::optional<S1>>>::value, "");
static_assert( hamon::is_copy_assignable<std::hash<hamon::optional<S1>>>::value, "");
static_assert( hamon::is_move_assignable<std::hash<hamon::optional<S1>>>::value, "");

static_assert(!hamon::is_default_constructible<std::hash<hamon::optional<S2>>>::value, "");
static_assert(!hamon::is_copy_constructible<std::hash<hamon::optional<S2>>>::value, "");
static_assert(!hamon::is_move_constructible<std::hash<hamon::optional<S2>>>::value, "");
static_assert(!hamon::is_copy_assignable<std::hash<hamon::optional<S2>>>::value, "");
static_assert(!hamon::is_move_assignable<std::hash<hamon::optional<S2>>>::value, "");

GTEST_TEST(OptionalTest, HashTest)
{
	{
		int i = 13;
		hamon::optional<int> o(i);
		EXPECT_EQ(std::hash<int>{}(i), std::hash<hamon::optional<int>>{}(o));
	}
	{
		float f = 2.5f;
		hamon::optional<float> o(f);
		EXPECT_EQ(std::hash<float>{}(f), std::hash<hamon::optional<float>>{}(o));
	}
	{
		S1 x;
		hamon::optional<S1> o(x);
		EXPECT_EQ(std::hash<S1>{}(x), std::hash<hamon::optional<S1>>{}(o));
		EXPECT_EQ(42u, std::hash<hamon::optional<S1>>{}(o));
	}
}

}	// namespace hash_test

}	// namespace hamon_optional_test
