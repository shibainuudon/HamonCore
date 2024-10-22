/**
 *	@file	unit_test_list_erasure.cpp
 *
 *	@brief	erase, erase_if のテスト
 *
 *	template<class T, class Allocator, class U = T>
 *	typename list<T, Allocator>::size_type
 *	erase(list<T, Allocator>& c, const U& value);
 *
 *	template<class T, class Allocator, class Predicate>
 *	typename list<T, Allocator>::size_type
 *	erase_if(list<T, Allocator>& c, Predicate pred);
 */

#include <hamon/list/erase.hpp>
#include <hamon/list/erase_if.hpp>
#include <hamon/list/list.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace erasure_test
{

#if !defined(HAMON_USE_STD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

LIST_TEST_CONSTEXPR bool test1()
{
	{
		hamon::list<int> v = {3,1,4,5,2};
		auto r = hamon::erase(v, 1);
		VERIFY(r == 1);
		const int v2[] = {3,4,5,2};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		hamon::list<int> v = {9,1,9,9,2,3,9,9,9,4,5,9,9,9,9};
		auto r = hamon::erase(v, 9);
		VERIFY(r == 10);
		const int v2[] = {1,2,3,4,5};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

struct Point
{
	int x;
	int y;
};

HAMON_CXX11_CONSTEXPR bool
operator==(Point const& lhs, Point const& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

HAMON_CXX11_CONSTEXPR bool
operator!=(Point const& lhs, Point const& rhs)
{
	return !(lhs == rhs);
}

LIST_TEST_CONSTEXPR bool test2()
{
	hamon::list<Point> v
	{
		Point{1,2},
		Point{2,3},
		Point{1,3},
		Point{1,2},
		Point{3,2},
	};
	auto r = hamon::erase(v, {1,2});
	VERIFY(r == 2);
	Point const v2[]
	{
		Point{2,3},
		Point{1,3},
		Point{3,2},
	};
	VERIFY(hamon::ranges::equal(v, v2));
	return true;
}

LIST_TEST_CONSTEXPR bool test3()
{
	{
		hamon::list<int> v = {3,1,4,5,2};
		auto r = hamon::erase_if(v, [](int x) { return x % 2 == 0; });
		VERIFY(r == 2);
		const int v2[] = {3,1,5};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		hamon::list<int> v = {3,1,4,1,5,9,2,6,5,3,5};
		auto r = hamon::erase_if(v, [](int x) { return x >= 5; });
		VERIFY(r == 5);
		const int v2[] = {3,1,4,1,2,3};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, ErasureTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test3());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace erasure_test

}	// namespace hamon_list_test
