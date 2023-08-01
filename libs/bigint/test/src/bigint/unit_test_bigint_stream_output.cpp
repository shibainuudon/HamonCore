/**
 *	@file	unit_test_bigint_stream_output.cpp
 *
 *	@brief	ストリームへの出力のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(BigIntTest, StreamOutputTest)
{
	{
		hamon::bigint const x = 0;
		std::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "0");
	}
	{
		hamon::bigint const x = 123;
		std::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "123");
	}
	{
		hamon::bigint const x = -123;
		std::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "-123");
	}
	{
		hamon::bigint const x = 629968538327;
		std::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "629968538327");
	}
	{
		hamon::bigint const x = -629968538327;
		std::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "-629968538327");
	}
	{
		hamon::bigint const x {"314159265358979323846264338327950288419716939937510"};
		std::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "314159265358979323846264338327950288419716939937510");
	}
	{
		hamon::bigint const x {"-385335686481014111885846834642220016869768311067870000000000"};
		std::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "-385335686481014111885846834642220016869768311067870000000000");
	}
}
