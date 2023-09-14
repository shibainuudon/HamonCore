/**
 *	@file	unit_test_algorithm_partition.cpp
 *
 *	@brief	partition のテスト
 */

#include <hamon/algorithm/partition.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <forward_list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace partition_test
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

inline HAMON_CXX14_CONSTEXPR bool PartitionTest1()
{
	{
		int a[] {1,2,3,4,5};
		auto ret = hamon::partition(hamon::begin(a), hamon::end(a), pred1);
		VERIFY(ret == hamon::next(hamon::begin(a), 2));
		VERIFY( pred1(a[0]));
		VERIFY( pred1(a[1]));
		VERIFY(!pred1(a[2]));
		VERIFY(!pred1(a[3]));
		VERIFY(!pred1(a[4]));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartitionTest2()
{
	{
		int a[] {1,3,5,7};
		auto ret = hamon::partition(hamon::begin(a), hamon::end(a), pred1);
		VERIFY(ret == hamon::next(hamon::begin(a), 0));
		VERIFY(!pred1(a[0]));
		VERIFY(!pred1(a[1]));
		VERIFY(!pred1(a[2]));
		VERIFY(!pred1(a[3]));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartitionTest3()
{
	{
		int a[] {2,4,6};
		auto ret = hamon::partition(hamon::begin(a), hamon::end(a), pred1);
		VERIFY(ret == hamon::end(a));
		VERIFY(pred1(a[0]));
		VERIFY(pred1(a[1]));
		VERIFY(pred1(a[2]));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool PartitionTest4()
{
	{
		hamon::array<int, 5> a {{1,2,3,4,5}};
		auto ret = hamon::partition(hamon::begin(a), hamon::end(a), pred2());
		VERIFY(ret == hamon::next(hamon::begin(a), 3));
		VERIFY( pred2()(a[0]));
		VERIFY( pred2()(a[1]));
		VERIFY( pred2()(a[2]));
		VERIFY(!pred2()(a[3]));
		VERIFY(!pred2()(a[4]));
	}
	return true;
}

GTEST_TEST(AlgorithmTest, PartitionTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartitionTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartitionTest2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartitionTest3());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(PartitionTest4());

	{
		hamon::vector<int> a {1,2,3,4,5};
		auto ret = hamon::partition(hamon::begin(a), hamon::end(a), [](int x) { return (x % 2) == 1; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
		EXPECT_TRUE ((a[0] % 2) == 1);
		EXPECT_TRUE ((a[1] % 2) == 1);
		EXPECT_TRUE ((a[2] % 2) == 1);
		EXPECT_TRUE ((a[3] % 2) == 0);
		EXPECT_TRUE ((a[4] % 2) == 0);
	}
	{
		hamon::list<int> a {1,2,3,4,5};
		auto ret = hamon::partition(hamon::begin(a), hamon::end(a), [](int x) { return x < 3; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
		auto it = a.begin();
		EXPECT_TRUE (*it++ < 3);
		EXPECT_TRUE (*it++ < 3);
		EXPECT_FALSE(*it++ < 3);
		EXPECT_FALSE(*it++ < 3);
		EXPECT_FALSE(*it++ < 3);
		EXPECT_TRUE(it == a.end());
	}
	{
		std::forward_list<int> a {1,2,3,4,5};
		auto ret = hamon::partition(hamon::begin(a), hamon::end(a), pred1);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
		auto it = a.begin();
		EXPECT_TRUE (pred1(*it++));
		EXPECT_TRUE (pred1(*it++));
		EXPECT_FALSE(pred1(*it++));
		EXPECT_FALSE(pred1(*it++));
		EXPECT_FALSE(pred1(*it++));
		EXPECT_TRUE(it == a.end());
	}
	{
		std::forward_list<int> a {1,2,3,4,5};
		auto ret = hamon::partition(hamon::begin(a), hamon::end(a), pred2());
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 3));
		auto it = a.begin();
		EXPECT_TRUE (pred2()(*it++));
		EXPECT_TRUE (pred2()(*it++));
		EXPECT_TRUE (pred2()(*it++));
		EXPECT_FALSE(pred2()(*it++));
		EXPECT_FALSE(pred2()(*it++));
		EXPECT_TRUE(it == a.end());
	}
	{
		std::forward_list<int> a {1,2,3,4,5};
		auto ret = hamon::partition(hamon::begin(a), hamon::end(a), [](int x) { return x < 2; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 1));
		auto it = a.begin();
		EXPECT_TRUE (*it++ < 2);
		EXPECT_FALSE(*it++ < 2);
		EXPECT_FALSE(*it++ < 2);
		EXPECT_FALSE(*it++ < 2);
		EXPECT_FALSE(*it++ < 2);
		EXPECT_TRUE(it == a.end());
	}
	{
		hamon::vector<int> a;
		auto ret = hamon::partition(hamon::begin(a), hamon::end(a), pred1);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
	{
		hamon::list<int> a;
		auto ret = hamon::partition(hamon::begin(a), hamon::end(a), pred2());
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
}

#undef VERIFY

}	// namespace partition_test

}	// namespace hamon_algorithm_test
