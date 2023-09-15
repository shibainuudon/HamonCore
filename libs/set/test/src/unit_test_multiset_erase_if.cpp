/**
 *	@file	unit_test_multiset_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 */

#include <hamon/set/erase_if.hpp>
#include <hamon/set/multiset.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace erase_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline /*HAMON_CXX14_CONSTEXPR*/ bool
EraseIfTest()
{
	{
		hamon::multiset<int> v = {3,1,4,5,2};
		auto r = hamon::erase_if(v, [](int x) { return x % 2 == 0; });
		VERIFY(r == 2);
		const int v2[] = {1,3,5,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		hamon::multiset<int> v = {3,1,4,1,5,9,2,6,5,3,5,};
		auto r = hamon::erase_if(v, [](int x) { return x >= 5; });
		VERIFY(r == 5);
		const int v2[] = {1,1,2,3,3,4,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

GTEST_TEST(MultiSetTest, EraseIfTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest());
}

#undef VERIFY

}	// namespace erase_if_test

}	// namespace hamon_multiset_test
