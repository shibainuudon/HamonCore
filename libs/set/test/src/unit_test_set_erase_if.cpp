/**
 *	@file	unit_test_set_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 */

#include <hamon/set/erase_if.hpp>
#include <hamon/set/set.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace erase_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline /*HAMON_CXX14_CONSTEXPR*/ bool
EraseIfTest()
{
	{
		hamon::set<int> v = {3,1,4,5,2};
		auto r = hamon::erase_if(v, [](int x) { return x % 2 == 0; });
		VERIFY(r == 2);
		const int v2[] = {1,3,5,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		hamon::set<int> v = {3,1,4,5,9,2,6,};
		auto r = hamon::erase_if(v, [](int x) { return x >= 5; });
		VERIFY(r == 3);
		const int v2[] = {1,2,3,4,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

GTEST_TEST(SetTest, EraseIfTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest());
}

#undef VERIFY

}	// namespace erase_if_test

}	// namespace hamon_set_test
