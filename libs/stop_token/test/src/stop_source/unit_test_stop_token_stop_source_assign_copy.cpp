/**
 *	@file	unit_test_stop_token_stop_source_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 */

#include <hamon/stop_token/stop_source.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_source_test
{

namespace assign_copy_test
{

static_assert(hamon::is_copy_assignable_v<hamon::stop_source>, "");
static_assert(hamon::is_nothrow_copy_assignable_v<hamon::stop_source>, "");
static_assert(!hamon::is_trivially_copy_assignable_v<hamon::stop_source>, "");

GTEST_TEST(StopSourceTest, AssignCopyTest)
{
	// have two different states
	{
		hamon::stop_source ss1;
		hamon::stop_source ss2;

		EXPECT_TRUE(ss1 != ss2);

		ss2.request_stop();

		EXPECT_FALSE(ss1.stop_requested());
		EXPECT_TRUE(ss2.stop_requested());

		auto& ref = ss1 = ss2;
		static_assert(hamon::is_same_v<decltype(ref), hamon::stop_source&>, "");
		EXPECT_TRUE(&ref == &ss1);

		EXPECT_TRUE(ss1 == ss2);
		EXPECT_TRUE(ss1.stop_requested());
		EXPECT_TRUE(ss2.stop_requested());
	}

	// this has no state
	{
		hamon::stop_source ss1{ hamon::nostopstate };
		hamon::stop_source ss2;

		EXPECT_TRUE(ss1 != ss2);

		ss2.request_stop();

		EXPECT_FALSE(ss1.stop_requested());
		EXPECT_FALSE(ss1.stop_possible());
		EXPECT_TRUE(ss2.stop_requested());
		EXPECT_TRUE(ss2.stop_possible());

		auto& ref = ss1 = ss2;
		static_assert(hamon::is_same_v<decltype(ref), hamon::stop_source&>, "");
		EXPECT_TRUE(&ref == &ss1);

		EXPECT_TRUE(ss1 == ss2);
		EXPECT_TRUE(ss1.stop_requested());
		EXPECT_TRUE(ss1.stop_possible());
		EXPECT_TRUE(ss2.stop_requested());
		EXPECT_TRUE(ss2.stop_possible());
	}

	// other has no state
	{
		hamon::stop_source ss1;
		hamon::stop_source ss2{ hamon::nostopstate };

		EXPECT_TRUE(ss1 != ss2);

		ss1.request_stop();

		EXPECT_TRUE(ss1.stop_requested());
		EXPECT_TRUE(ss1.stop_possible());
		EXPECT_FALSE(ss2.stop_requested());
		EXPECT_FALSE(ss2.stop_possible());

		auto& ref = ss1 = ss2;
		static_assert(hamon::is_same_v<decltype(ref), hamon::stop_source&>, "");
		EXPECT_TRUE(&ref == &ss1);

		EXPECT_TRUE(ss1 == ss2);
		EXPECT_FALSE(ss1.stop_requested());
		EXPECT_FALSE(ss1.stop_possible());
		EXPECT_FALSE(ss2.stop_requested());
		EXPECT_FALSE(ss2.stop_possible());
	}

	// both no state
	{
		hamon::stop_source ss1{ hamon::nostopstate };
		hamon::stop_source ss2{ hamon::nostopstate };

		EXPECT_TRUE(ss1 == ss2);

		EXPECT_FALSE(ss1.stop_requested());
		EXPECT_FALSE(ss1.stop_possible());
		EXPECT_FALSE(ss2.stop_requested());
		EXPECT_FALSE(ss2.stop_possible());

		auto& ref = ss1 = ss2;
		static_assert(hamon::is_same_v<decltype(ref), hamon::stop_source&>, "");
		EXPECT_TRUE(&ref == &ss1);

		EXPECT_TRUE(ss1 == ss2);
		EXPECT_FALSE(ss1.stop_requested());
		EXPECT_FALSE(ss1.stop_possible());
		EXPECT_FALSE(ss2.stop_requested());
		EXPECT_FALSE(ss2.stop_possible());
	}

	// self assignment
	{
		hamon::stop_source ss;
		auto& self = ss;

		EXPECT_FALSE(ss.stop_requested());

		auto& ref = ss = self;
		static_assert(hamon::is_same_v<decltype(ref), hamon::stop_source&>, "");
		EXPECT_TRUE(&ref == &ss);

		EXPECT_FALSE(ss.stop_requested());

		ss.request_stop();
		EXPECT_TRUE(ss.stop_requested());
	}
}

}	// namespace assign_copy_test

}	// namespace hamon_stop_token_test
