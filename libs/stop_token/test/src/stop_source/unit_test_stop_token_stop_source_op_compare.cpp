/**
 *	@file	unit_test_stop_token_stop_source_op_compare.cpp
 *
 *	@brief	operator==のテスト
 *
 *	bool operator==(const stop_source& rhs) noexcept = default;
 */

#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/nostopstate_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_source_test
{

namespace op_compare_test
{

GTEST_TEST(StopSourceTest, OpCompareTest)
{
	// both no state
	{
		const hamon::stop_source ss1(hamon::nostopstate);
		const hamon::stop_source ss2(hamon::nostopstate);

		static_assert(noexcept(ss1 == ss2), "");
		static_assert(noexcept(ss1 != ss2), "");
		static_assert(hamon::is_same_v<decltype(ss1 == ss2), bool>, "");
		static_assert(hamon::is_same_v<decltype(ss1 != ss2), bool>, "");

		EXPECT_TRUE (ss1 == ss2);
		EXPECT_FALSE(ss1 != ss2);
	}

	// only one has no state
	{
		const hamon::stop_source ss1(hamon::nostopstate);
		const hamon::stop_source ss2;
		EXPECT_FALSE(ss1 == ss2);
		EXPECT_TRUE (ss1 != ss2);
	}

	// both has states. same state
	{
		const hamon::stop_source ss1;
		const hamon::stop_source ss2(ss1);
		EXPECT_TRUE (ss1 == ss2);
		EXPECT_FALSE(ss1 != ss2);
	}

	// both has states. different states
	{
		const hamon::stop_source ss1;
		const hamon::stop_source ss2;
		EXPECT_FALSE(ss1 == ss2);
		EXPECT_TRUE (ss1 != ss2);
	}
}

}	// namespace op_compare_test

}	// namespace hamon_stop_token_test
