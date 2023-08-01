/**
 *	@file	unit_test_bigint_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

GTEST_TEST(BigIntTest, CtorDefaultTest)
{
	{
		hamon::bigint x{};
		EXPECT_EQ("0", x.to_string());
	}
	{
		hamon::bigint x = {};
		EXPECT_EQ("0", x.to_string());
	}
}
