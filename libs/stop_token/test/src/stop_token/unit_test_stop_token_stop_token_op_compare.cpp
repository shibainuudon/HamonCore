/**
 *	@file	unit_test_stop_token_stop_token_op_compare.cpp
 *
 *	@brief	operator== のテスト
 *
 *	bool operator==(const stop_token& rhs) noexcept = default;
 */

#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/stop_source.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_token_test
{

namespace op_compare_test
{

GTEST_TEST(StopTokenTest, OpCompareTest)
{
	// both no state
	{
		const hamon::stop_token st1;
		const hamon::stop_token st2;

		static_assert(noexcept(st1 == st2), "");
		static_assert(noexcept(st1 != st2), "");
		static_assert(hamon::is_same_v<decltype(st1 == st2), bool>, "");
		static_assert(hamon::is_same_v<decltype(st1 != st2), bool>, "");

		EXPECT_TRUE (st1 == st2);
		EXPECT_FALSE(st1 != st2);
	}

	// only one has no state
	{
		hamon::stop_source ss;
		const hamon::stop_token st1;
		const auto st2 = ss.get_token();
		EXPECT_FALSE(st1 == st2);
		EXPECT_TRUE (st1 != st2);
	}

	// both has states. same source
	{
		hamon::stop_source ss;
		const auto st1 = ss.get_token();
		const auto st2 = ss.get_token();
		EXPECT_TRUE (st1 == st2);
		EXPECT_FALSE(st1 != st2);
	}

	// both has states. different sources with same states
	{
		hamon::stop_source ss1;
		auto ss2 = ss1;
		const auto st1 = ss1.get_token();
		const auto st2 = ss2.get_token();
		EXPECT_TRUE (st1 == st2);
		EXPECT_FALSE(st1 != st2);
	}

	// both has states. different sources with different states
	{
		hamon::stop_source ss1;
		hamon::stop_source ss2;
		const auto st1 = ss1.get_token();
		const auto st2 = ss2.get_token();
		EXPECT_FALSE(st1 == st2);
		EXPECT_TRUE (st1 != st2);
	}
}

}	// namespace op_compare_test

}	// namespace hamon_stop_token_test
