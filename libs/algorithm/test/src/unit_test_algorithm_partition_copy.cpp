/**
 *	@file	unit_test_algorithm_partition_copy.cpp
 *
 *	@brief	partition_copy のテスト
 */

#include <hamon/algorithm/partition_copy.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace partition_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CONSTEXPR bool pred1(int x)
{
	return (x % 2) == 0;
}

struct pred2
{
	HAMON_CONSTEXPR bool operator()(int x) const
	{
		return x > 2;
	}
};

inline HAMON_CXX14_CONSTEXPR bool PartitionCopyTest1()
{
	{
		const int a[] {1,2,3,4,5};
		int b[5] {};
		int c[5] {};
		auto ret = hamon::partition_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::begin(c), pred1);
		VERIFY(ret.first  == hamon::next(hamon::begin(b), 2));
		VERIFY(ret.second == hamon::next(hamon::begin(c), 3));

		VERIFY(2 == b[0]);
		VERIFY(4 == b[1]);
		VERIFY(0 == b[2]);
		VERIFY(0 == b[3]);
		VERIFY(0 == b[4]);

		VERIFY(1 == c[0]);
		VERIFY(3 == c[1]);
		VERIFY(5 == c[2]);
		VERIFY(0 == c[3]);
		VERIFY(0 == c[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartitionCopyTest2()
{
	{
		const hamon::array<int, 5> a {{1,2,3,4,5}};
		hamon::array<int, 5> b {};
		hamon::array<int, 5> c {};
		auto ret = hamon::partition_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::begin(c), pred2());
		VERIFY(ret.first  == hamon::next(hamon::begin(b), 3));
		VERIFY(ret.second == hamon::next(hamon::begin(c), 2));

		VERIFY(3 == b[0]);
		VERIFY(4 == b[1]);
		VERIFY(5 == b[2]);
		VERIFY(0 == b[3]);
		VERIFY(0 == b[4]);

		VERIFY(1 == c[0]);
		VERIFY(2 == c[1]);
		VERIFY(0 == c[2]);
		VERIFY(0 == c[3]);
		VERIFY(0 == c[4]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, PartitionCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartitionCopyTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartitionCopyTest2());

	{
		const hamon::array<int, 5> a {{1,2,3,4,5}};
		hamon::vector<int> b(5);
		hamon::list<int> c(5);
		auto ret = hamon::partition_copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::begin(c), pred2());
		EXPECT_TRUE(ret.first  == hamon::next(hamon::begin(b), 3));
		EXPECT_TRUE(ret.second == hamon::next(hamon::begin(c), 2));

		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(4, b[1]);
		EXPECT_EQ(5, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
		auto it = c.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_EQ(0, *it++);
		EXPECT_TRUE(it == c.end());
	}
	{
		const hamon::list<int> a {1,2,3,4,5};
		hamon::vector<int> b;
		hamon::array<int, 5> c{{}};
		auto ret = hamon::partition_copy(
			hamon::begin(a),
			hamon::end(a),
			std::back_inserter(b),
			hamon::begin(c),
			[](int x) { return (x % 2) == 1; });
		//EXPECT_TRUE(ret.first  == hamon::next(hamon::begin(b), 3));
		EXPECT_TRUE(ret.second == hamon::next(hamon::begin(c), 2));

		EXPECT_EQ(3u, b.size());
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(5, b[2]);
		EXPECT_EQ(2, c[0]);
		EXPECT_EQ(4, c[1]);
		EXPECT_EQ(0, c[2]);
		EXPECT_EQ(0, c[3]);
		EXPECT_EQ(0, c[4]);
	}
	{
		const hamon::vector<int> a;
		hamon::vector<int> b;
		hamon::list<int> c;
		auto ret = hamon::partition_copy(
			hamon::begin(a),
			hamon::end(a),
			std::back_inserter(b),
			std::back_inserter(c),
			[](int x) { return (x % 2) == 1; });
		(void)ret;
		//EXPECT_TRUE(ret.first  == hamon::next(hamon::begin(b), 3));
		//EXPECT_TRUE(ret.second == hamon::next(hamon::begin(c), 2));

		EXPECT_TRUE(b.empty());
		EXPECT_TRUE(c.empty());
	}
}

#undef VERIFY

}	// namespace partition_copy_test

}	// namespace hamon_algorithm_test
