/**
 *	@file	unit_test_expected_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	constexpr ~expected();
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace dtor_test
{

struct Destructible
{
	~Destructible();
};
static_assert( hamon::is_destructible<Destructible>::value, "");
static_assert(!hamon::is_trivially_destructible<Destructible>::value, "");

struct TriviallyDestructible
{
};
static_assert( hamon::is_destructible<TriviallyDestructible>::value, "");
static_assert( hamon::is_trivially_destructible<TriviallyDestructible>::value, "");

static_assert( hamon::is_destructible<hamon::expected<int, int>>::value, "");
static_assert( hamon::is_destructible<hamon::expected<Destructible,          Destructible>>::value, "");
static_assert( hamon::is_destructible<hamon::expected<Destructible,          TriviallyDestructible>>::value, "");
static_assert( hamon::is_destructible<hamon::expected<TriviallyDestructible, Destructible>>::value, "");
static_assert( hamon::is_destructible<hamon::expected<TriviallyDestructible, TriviallyDestructible>>::value, "");

static_assert( hamon::is_trivially_destructible<hamon::expected<int, int>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::expected<Destructible,          Destructible>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::expected<Destructible,          TriviallyDestructible>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::expected<TriviallyDestructible, Destructible>>::value, "");
static_assert( hamon::is_trivially_destructible<hamon::expected<TriviallyDestructible, TriviallyDestructible>>::value, "");

struct S1
{
	static int s_dtor_count;

	~S1() { ++s_dtor_count; }
};
int S1::s_dtor_count = 0;

struct S2
{
	static int s_dtor_count;

	~S2() { ++s_dtor_count; }
};
int S2::s_dtor_count = 0;

GTEST_TEST(ExpectedTest, DtortTest)
{
	S1::s_dtor_count = 0;
	S2::s_dtor_count = 0;
	{
		hamon::expected<S1, S2> e;
	}
	EXPECT_EQ(1, S1::s_dtor_count);
	EXPECT_EQ(0, S2::s_dtor_count);

	S1::s_dtor_count = 0;
	S2::s_dtor_count = 0;
	{
		hamon::expected<S1, S2> e{hamon::unexpect};
	}
	EXPECT_EQ(0, S1::s_dtor_count);
	EXPECT_EQ(1, S2::s_dtor_count);
}

}	// namespace dtor_test

}	// namespace hamon_expected_test
