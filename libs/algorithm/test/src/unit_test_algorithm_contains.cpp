/**
 *	@file	unit_test_algorithm_contains.cpp
 *
 *	@brief	contains のテスト
 */

#include <hamon/algorithm/contains.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace contains_test
{

struct Point
{
	int x;
	int y;
};

inline HAMON_CXX11_CONSTEXPR bool
operator==(Point const& lhs, Point const& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		int x[] = { 1,2,3,4,5 };
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 0));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 1));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 2));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 3));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 4));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 5));
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 6));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		hamon::array<int, 5> x = { 3,1,4,1,5 };
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 0));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 1));
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 2));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 3));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 4));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 5));
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 6));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	Point const a[]
	{
		{1, 2}, {1, 1}, {1, 2}, {2, 1},
	};

	VERIFY( hamon::contains(hamon::begin(a), hamon::end(a), {1, 1}));
	VERIFY( hamon::contains(hamon::begin(a), hamon::end(a), {1, 2}));
	VERIFY(!hamon::contains(hamon::begin(a), hamon::end(a), {1, 3}));
	VERIFY( hamon::contains(hamon::begin(a), hamon::end(a), {2, 1}));
	VERIFY(!hamon::contains(hamon::begin(a), hamon::end(a), {2, 2}));
	VERIFY(!hamon::contains(hamon::begin(a), hamon::end(a), {2, 3}));

	return true;
}

inline bool testVector()
{
	{
		hamon::vector<int> x;
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 0));
	}
	{
		hamon::vector<int> x{0, 2, 4};
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 0));
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 1));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 2));
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 3));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 4));
	}
	return true;
}

inline bool testList()
{
	{
		hamon::list<int> x;
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 0));
	}
	{
		hamon::list<int> x{1, 3, 5};
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 0));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 1));
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 2));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 3));
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 4));
	}
	return true;
}

inline bool testForwardList()
{
	{
		hamon::forward_list<int> x;
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 0));
	}
	{
		hamon::forward_list<int> x{4,1,4,1,4};
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 0));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 1));
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 2));
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 3));
		VERIFY( hamon::contains(hamon::begin(x), hamon::end(x), 4));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, ContainsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	EXPECT_TRUE(testVector());
	EXPECT_TRUE(testList());
	EXPECT_TRUE(testForwardList());
}

}	// namespace contains_test

}	// namespace hamon_algorithm_test
