/**
 *	@file	unit_test_algorithm_nth_element.cpp
 *
 *	@brief	nth_element のテスト
 */

#include <hamon/algorithm/nth_element.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace nth_element_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename RandomAccessIterator>
HAMON_CXX14_CONSTEXPR bool
NthElementTest(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last)
{
	for (auto i = first; i < nth; ++i)
	{
		for (auto j = nth; j < last; ++j)
		{
			if (*j < *i)
			{
				return false;
			}
		}
	}
	return true;
}

template <typename RandomAccessIterator, typename Compare>
HAMON_CXX14_CONSTEXPR bool
NthElementTest(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last,
	Compare comp)
{
	for (auto i = first; i < nth; ++i)
	{
		for (auto j = nth; j < last; ++j)
		{
			if (comp(*j, *i))
			{
				return false;
			}
		}
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool NthElementTest1()
{
	{
		const int nth = 1;
		int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
		hamon::nth_element(hamon::begin(a), hamon::next(hamon::begin(a), nth), hamon::end(a));
		VERIFY(NthElementTest(hamon::begin(a), hamon::next(hamon::begin(a), nth), hamon::end(a)));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool NthElementTest2()
{
	{
		const int nth = 3;
		int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
		hamon::nth_element(hamon::begin(a), hamon::next(hamon::begin(a), nth), hamon::end(a), hamon::greater<>());
		VERIFY(NthElementTest(hamon::begin(a), hamon::next(hamon::begin(a), nth), hamon::end(a), hamon::greater<>()));
	}
	return true;
}

inline HAMON_CXX17_CONSTEXPR bool NthElementTest3()
{
	{
		const int nth = 5;
		std::array<int, 10> a {{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 }};
		hamon::nth_element(hamon::begin(a), hamon::next(hamon::begin(a), nth), hamon::end(a));
		VERIFY(NthElementTest(hamon::begin(a), hamon::next(hamon::begin(a), nth), hamon::end(a)));
	}
	return true;
}

inline HAMON_CXX17_CONSTEXPR bool NthElementTest4()
{
	{
		const int nth = 7;
		std::array<int, 10> a {{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 }};
		hamon::nth_element(hamon::begin(a), hamon::next(hamon::begin(a), nth), hamon::end(a), hamon::greater<>());
		VERIFY(NthElementTest(hamon::begin(a), hamon::next(hamon::begin(a), nth), hamon::end(a), hamon::greater<>()));
	}
	return true;
}

GTEST_TEST(AlgorithmTest, NthElementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NthElementTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NthElementTest2());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(NthElementTest3());
	HAMON_CXX17_CONSTEXPR_EXPECT_TRUE(NthElementTest4());

	{
		const int nth = 6;
		std::vector<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
		hamon::nth_element(hamon::begin(a), hamon::next(hamon::begin(a), nth), hamon::end(a));
		EXPECT_TRUE(NthElementTest(hamon::begin(a), hamon::next(hamon::begin(a), nth), hamon::end(a)));
	}
	{
		const int nth = 8;
		std::vector<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
		hamon::nth_element(hamon::begin(a), hamon::next(hamon::begin(a), nth), hamon::end(a), hamon::greater<>());
		EXPECT_TRUE(NthElementTest(hamon::begin(a), hamon::next(hamon::begin(a), nth), hamon::end(a), hamon::greater<>()));
	}
}

#undef VERIFY

}	// namespace nth_element_test

}	// namespace hamon_algorithm_test
