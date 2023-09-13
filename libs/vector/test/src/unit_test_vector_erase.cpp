/**
 *	@file	unit_test_vector_erase.cpp
 *
 *	@brief	erase のテスト
 */

#include <hamon/vector.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace erase_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline /*HAMON_CXX14_CONSTEXPR*/ bool
EraseTest()
{
	{
		hamon::vector<int> v = {3,1,4,5,2};
		auto r = hamon::erase(v, 1);
		VERIFY(r == 1);
		const int v2[] = {3,4,5,2,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		hamon::vector<int> v = {9,1,9,9,2,3,9,9,9,4,5,9,9,9,9,};
		auto r = hamon::erase(v, 9);
		VERIFY(r == 10);
		const int v2[] = {1,2,3,4,5};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

GTEST_TEST(VectorTest, EraseTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseTest());
}

#undef VERIFY

}	// namespace erase_test

}	// namespace hamon_vector_test
