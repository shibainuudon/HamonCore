/**
 *	@file	unit_test_unordered_set_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 */

#include <hamon/unordered_set/erase_if.hpp>
#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace erase_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline /*HAMON_CXX14_CONSTEXPR*/ bool
EraseIfTest()
{
	{
		hamon::unordered_set<int> v = {3,1,4,5,2};
		auto r = hamon::erase_if(v, [](int x) { return x % 2 == 0; });
		VERIFY(r == 2);
		hamon::unordered_set<int> v2 = {3,1,5};
		VERIFY(v == v2);
	}
	{
		hamon::unordered_set<int> v = {3,1,4,5,9,2,6,};
		auto r = hamon::erase_if(v, [](int x) { return x >= 5; });
		VERIFY(r == 3);
		hamon::unordered_set<int> v2 = {3,1,4,2,};
		VERIFY(v == v2);
	}
	return true;
}

GTEST_TEST(UnorderedSetTest, EraseIfTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest());
}

#undef VERIFY

}	// namespace erase_if_test

}	// namespace hamon_unordered_set_test
