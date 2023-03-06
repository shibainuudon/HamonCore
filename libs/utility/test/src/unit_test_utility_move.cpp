/**
 *	@file	unit_test_utility_move.cpp
 *
 *	@brief	move のテスト
 */

#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_utility_test
{

namespace move_test
{

HAMON_CXX11_CONSTEXPR
int func(const int&)
{
	return 0;
}

HAMON_CXX11_CONSTEXPR
int func(const int&&)
{
	return 1;
}

GTEST_TEST(UtilityTest, MoveTest)
{
	{
		int i = 3;
		EXPECT_EQ(0, func(i));
		EXPECT_EQ(1, func(hamon::move(i)));
		EXPECT_EQ(1, func(0));
	}
	{
		HAMON_CXX11_CONSTEXPR int i = 42;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, func(i));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, func(hamon::move(i)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, func(0));
	}
}

}	// namespace move_test

}	// namespace hamon_utility_test
