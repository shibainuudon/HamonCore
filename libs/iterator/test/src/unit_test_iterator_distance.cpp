/**
 *	@file	unit_test_iterator_distance.cpp
 *
 *	@brief	distance のテスト
 */

#include <hamon/iterator/distance.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_iterator_test
{

namespace distance_test
{

GTEST_TEST(IteratorTest, DistanceTest)
{
	{
		int a[] = {0,1,2};
		EXPECT_EQ(3, hamon::distance(hamon::begin(a), hamon::end(a)));
	}
	{
		const int a[] = {0,1,2};
		EXPECT_EQ(3, hamon::distance(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_CONSTEXPR int a[] = {0,1,2};
		HAMON_CXX14_CONSTEXPR auto d = hamon::distance(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(3, d);
	}
	{
		hamon::vector<float> v {3,1,4,1,5};
		EXPECT_EQ(5, hamon::distance(hamon::begin(v), hamon::end(v)));
	}
	{
		const hamon::vector<float> v {3,1,4,1,5};
		EXPECT_EQ(5, hamon::distance(hamon::begin(v), hamon::end(v)));
	}
	{
		std::list<int> l {2, 3, 4, 5};
		EXPECT_EQ(4, hamon::distance(hamon::begin(l), hamon::end(l)));
	}
	{
		const std::list<int> l {2, 3, 4, 5};
		EXPECT_EQ(4, hamon::distance(hamon::begin(l), hamon::end(l)));
	}
	{
		hamon::array<float, 2> a{{1, 2}};
		EXPECT_EQ(2, hamon::distance(hamon::begin(a), hamon::end(a)));
	}
	{
		const hamon::array<float, 3> a{{1, 2, 3}};
		EXPECT_EQ(3, hamon::distance(hamon::begin(a), hamon::end(a)));
	}
	{
		HAMON_CONSTEXPR hamon::array<float, 4> a{{1, 2, 3, 4}};
		HAMON_CXX14_CONSTEXPR auto d = hamon::distance(hamon::begin(a), hamon::end(a));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(4, d);
	}
}

}	// namespace distance_test

}	// namespace hamon_iterator_test
