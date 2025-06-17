/**
 *	@file	unit_test_algorithm_stable_partition.cpp
 *
 *	@brief	stable_partition のテスト
 */

#include <hamon/algorithm/stable_partition.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace stable_partition_test
{

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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		int a[] {1,2,3,4,5};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), pred1);
		VERIFY(ret == hamon::next(hamon::begin(a), 2));
		VERIFY(2 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(1 == a[2]);
		VERIFY(3 == a[3]);
		VERIFY(5 == a[4]);
	}
	{
		int a[] {1,3,5,7};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), pred1);
		VERIFY(ret == hamon::next(hamon::begin(a), 0));
		VERIFY(1 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(5 == a[2]);
		VERIFY(7 == a[3]);
	}
	{
		int a[] {2,4,6};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), pred1);
		VERIFY(ret == hamon::end(a));
		VERIFY(2 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(6 == a[2]);
	}
	return true;
}

struct Foo
{
	int key;
	float value;
};

HAMON_CONSTEXPR bool is_even(Foo const& x)
{
	return (x.key % 2) == 0;
}

inline HAMON_CXX14_CONSTEXPR bool test2()
{
	{
		hamon::array<int, 5> a {{1,2,3,4,5}};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), pred2());
		VERIFY(ret == hamon::next(hamon::begin(a), 3));
		VERIFY(3 == a[0]);
		VERIFY(4 == a[1]);
		VERIFY(5 == a[2]);
		VERIFY(1 == a[3]);
		VERIFY(2 == a[4]);
	}
	{
		hamon::array<Foo, 8> a
		{{
			{ 3, 0.5f },
			{ 1, 1.5f },
			{ 4, 2.5f },
			{ 1, 3.5f },
			{ 5, 4.5f },
			{ 9, 5.5f },
			{ 2, 6.5f },
			{ 6, 7.5f },
		}};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), is_even);
		VERIFY(ret == hamon::next(hamon::begin(a), 3));
		VERIFY(4 == a[0].key);
		VERIFY(2 == a[1].key);
		VERIFY(6 == a[2].key);
		VERIFY(3 == a[3].key);
		VERIFY(1 == a[4].key);
		VERIFY(1 == a[5].key);
		VERIFY(5 == a[6].key);
		VERIFY(9 == a[7].key);
		VERIFY(2.5f == a[0].value);
		VERIFY(6.5f == a[1].value);
		VERIFY(7.5f == a[2].value);
		VERIFY(0.5f == a[3].value);
		VERIFY(1.5f == a[4].value);
		VERIFY(3.5f == a[5].value);
		VERIFY(4.5f == a[6].value);
		VERIFY(5.5f == a[7].value);
	}
	return true;
}

inline bool test3()
{
	{
		hamon::vector<int> a {1,2,3,4,5};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), [](int x) { return (x % 2) == 1; });
		VERIFY(ret == hamon::next(hamon::begin(a), 3));
		VERIFY(1 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(5 == a[2]);
		VERIFY(2 == a[3]);
		VERIFY(4 == a[4]);
	}
	{
		hamon::vector<int> a;
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), pred1);
		VERIFY(ret == hamon::next(hamon::begin(a), 0));
	}
	return true;
}

inline bool test4()
{
	{
		hamon::list<int> a {1,2,3,4,5};
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), [](int x) { return x < 3; });
		VERIFY(ret == hamon::next(hamon::begin(a), 2));
		auto it = a.begin();
		VERIFY(1 == *it++);
		VERIFY(2 == *it++);
		VERIFY(3 == *it++);
		VERIFY(4 == *it++);
		VERIFY(5 == *it++);
		VERIFY(it == a.end());
	}
	{
		hamon::list<int> a;
		auto ret = hamon::stable_partition(hamon::begin(a), hamon::end(a), pred2());
		VERIFY(ret == hamon::next(hamon::begin(a), 0));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, StablePartitionTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2());
	EXPECT_TRUE(test3());
	EXPECT_TRUE(test4());
}

}	// namespace stable_partition_test

}	// namespace hamon_algorithm_test
