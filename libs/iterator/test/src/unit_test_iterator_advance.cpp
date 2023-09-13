/**
 *	@file	unit_test_iterator_advance.cpp
 *
 *	@brief	advance のテスト
 */

#include <hamon/iterator/advance.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>

namespace hamon_iterator_test
{

namespace advance_test
{

GTEST_TEST(IteratorTest, AdvanceTest)
{
	{
		int a[] = {0,1,2};

		auto it = hamon::begin(a);
		EXPECT_EQ(0, *it);
		hamon::advance(it, 1);
		EXPECT_EQ(1, *it);
		hamon::advance(it, 1);
		EXPECT_EQ(2, *it);
		hamon::advance(it, 1);
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		int a[] = {0,1,2};

		auto it = hamon::begin(a);
		EXPECT_EQ(0, *it);
		hamon::advance(it, 2);
		EXPECT_EQ(2, *it);
		hamon::advance(it, -1);
		EXPECT_EQ(1, *it);
		hamon::advance(it, 2);
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		hamon::vector<float> v {3,1,4,1,5};

		auto it = hamon::begin(v);
		EXPECT_EQ(3, *it);
		hamon::advance(it, 1);
		EXPECT_EQ(1, *it);
		hamon::advance(it, 1);
		EXPECT_EQ(4, *it);
		hamon::advance(it, 1);
		EXPECT_EQ(1, *it);
		hamon::advance(it, 1);
		EXPECT_EQ(5, *it);
		hamon::advance(it, 1);
		EXPECT_TRUE(it == hamon::end(v));
	}
	{
		hamon::vector<float> v {3,1,4,1,5};

		auto it = hamon::begin(v);
		EXPECT_EQ(3, *it);
		hamon::advance(it, 3);
		EXPECT_EQ(1, *it);
		hamon::advance(it, -1);
		EXPECT_EQ(4, *it);
		hamon::advance(it, 2);
		EXPECT_EQ(5, *it);
		hamon::advance(it, -4);
		EXPECT_EQ(3, *it);
		hamon::advance(it, 5);
		EXPECT_TRUE(it == hamon::end(v));
	}
	{
		std::list<int> l {2, 3, 4};

		auto it = hamon::begin(l);
		EXPECT_EQ(2, *it);
		hamon::advance(it, 1);
		EXPECT_EQ(3, *it);
		hamon::advance(it, 1);
		EXPECT_EQ(4, *it);
		hamon::advance(it, 1);
		EXPECT_TRUE(it == hamon::end(l));
	}
	{
		std::list<int> l {2, 3, 4};

		auto it = hamon::begin(l);
		EXPECT_EQ(2, *it);
		hamon::advance(it, 2);
		EXPECT_EQ(4, *it);
		hamon::advance(it, -2);
		EXPECT_EQ(2, *it);
		hamon::advance(it, 3);
		EXPECT_TRUE(it == hamon::end(l));
	}
	{
		hamon::array<float, 4> a{{1, 2, 3, 4}};

		auto it = hamon::begin(a);
		EXPECT_EQ(1, *it);
		hamon::advance(it, 1);
		EXPECT_EQ(2, *it);
		hamon::advance(it, 1);
		EXPECT_EQ(3, *it);
		hamon::advance(it, 1);
		EXPECT_EQ(4, *it);
		hamon::advance(it, 1);
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		hamon::array<float, 4> a{{1, 2, 3, 4}};

		auto it = hamon::begin(a);
		EXPECT_EQ(1, *it);
		hamon::advance(it, 2);
		EXPECT_EQ(3, *it);
		hamon::advance(it, -1);
		EXPECT_EQ(2, *it);
		hamon::advance(it, 3);
		EXPECT_TRUE(it == hamon::end(a));
	}
}

}	// namespace advance_test

}	// namespace hamon_iterator_test
