/**
 *	@file	unit_test_algorithm_contains.cpp
 *
 *	@brief	contains のテスト
 */

#include <hamon/algorithm/contains.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include <forward_list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace contains_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool testRawArray()
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

inline HAMON_CXX14_CONSTEXPR bool testArray()
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
		std::list<int> x;
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 0));
	}
	{
		std::list<int> x{1, 3, 5};
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
		std::forward_list<int> x;
		VERIFY(!hamon::contains(hamon::begin(x), hamon::end(x), 0));
	}
	{
		std::forward_list<int> x{4,1,4,1,4};
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
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(testRawArray());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(testArray());
	EXPECT_TRUE(testVector());
	EXPECT_TRUE(testList());
	EXPECT_TRUE(testForwardList());
}

}	// namespace contains_test

}	// namespace hamon_algorithm_test
