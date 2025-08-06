/**
 *	@file	unit_test_hive_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~hive();
 */

#include <hamon/hive.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace dtor_test
{

struct S
{
	~S()
	{
		++s_dtor_count;
	}

	static int s_dtor_count;
};

int S::s_dtor_count = 0;

GTEST_TEST(HiveTest, DtorTest)
{
	S::s_dtor_count = 0;
	{
		hamon::hive<S> v;
	}
	EXPECT_EQ(0, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::hive<S> v(1u);
	}
	EXPECT_EQ(1, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::hive<S> v(3u);
	}
	EXPECT_EQ(3, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::hive<S> v;
		v.emplace();
		v.emplace();
		v.emplace();
		v.emplace();
	}
	EXPECT_EQ(4, S::s_dtor_count);
}

}	// namespace dtor_test

}	// namespace hamon_hive_test
