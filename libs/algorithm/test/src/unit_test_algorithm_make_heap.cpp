/**
 *	@file	unit_test_algorithm_make_heap.cpp
 *
 *	@brief	make_heap のテスト
 */

#include <hamon/algorithm/make_heap.hpp>
#include <hamon/algorithm/is_heap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace make_heap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool MakeHeapTest1()
{
	{
		int a[] { 3, 1, 4 };
		hamon::make_heap(hamon::begin(a), hamon::end(a));
		VERIFY( hamon::is_heap(hamon::begin(a), hamon::end(a)));
		VERIFY(!hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool MakeHeapTest2()
{
	{
		int a[] { 3, 1, 4 };
		hamon::make_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		VERIFY(!hamon::is_heap(hamon::begin(a), hamon::end(a)));
		VERIFY( hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool MakeHeapTest3()
{
	{
		hamon::array<int, 6> a {{ 3, 1, 4, 1, 5, 9 }};
		hamon::make_heap(hamon::begin(a), hamon::end(a));
		VERIFY( hamon::is_heap(hamon::begin(a), hamon::end(a)));
		VERIFY(!hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool MakeHeapTest4()
{
	{
		hamon::array<int, 6> a {{ 3, 1, 4, 1, 5, 9 }};
		hamon::make_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		VERIFY(!hamon::is_heap(hamon::begin(a), hamon::end(a)));
		VERIFY( hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));
	}
	return true;
}

GTEST_TEST(AlgorithmTest, MakeHeapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MakeHeapTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MakeHeapTest2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MakeHeapTest3());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MakeHeapTest4());

	{
		std::vector<int> a { 5, 4, 1, 1, 3 };
		hamon::make_heap(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE (hamon::is_heap(hamon::begin(a), hamon::end(a)));
		EXPECT_FALSE(hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));
	}
	{
		std::vector<int> a { 5, 4, 1, 1, 3 };
		hamon::make_heap(hamon::begin(a), hamon::end(a), hamon::greater<>());
		EXPECT_FALSE(hamon::is_heap(hamon::begin(a), hamon::end(a)));
		EXPECT_TRUE (hamon::is_heap(hamon::begin(a), hamon::end(a), hamon::greater<>()));
	}
	{
		std::vector<int> a;
		hamon::make_heap(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(a.empty());
	}
}

#undef VERIFY

}	// namespace make_heap_test

}	// namespace hamon_algorithm_test
