/**
 *	@file	unit_test_unordered_multiset_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 */

#include <hamon/unordered_set/erase_if.hpp>
#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace erase_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline /*HAMON_CXX14_CONSTEXPR*/ bool
EraseIfTest()
{
	{
		hamon::unordered_multiset<int> v = {3,1,4,5,2};
		auto r = hamon::erase_if(v, [](int x) { return x % 2 == 0; });
		VERIFY(r == 2);
		hamon::unordered_multiset<int> v2 = {3,1,5};
		VERIFY(v == v2);
	}
	{
		hamon::unordered_multiset<int> v = {3,1,4,1,5,9,2,6,5,3,5,};
		auto r = hamon::erase_if(v, [](int x) { return x >= 5; });
		VERIFY(r == 5);
		hamon::unordered_multiset<int> v2 = {3,1,4,1,2,3,};
		VERIFY(v == v2);
	}
	return true;
}

GTEST_TEST(UnorderedMultiSetTest, EraseIfTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest());
}

#undef VERIFY

}	// namespace erase_if_test

}	// namespace hamon_unordered_multiset_test
