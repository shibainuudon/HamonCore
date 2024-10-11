/**
 *	@file	unit_test_forward_list_erase.cpp
 *
 *	@brief	erase のテスト
 *
 *	template<class T, class Allocator, class U = T>
 *	typename forward_list<T, Allocator>::size_type
 *	erase(forward_list<T, Allocator>& c, const U& value);
 */

#include <hamon/forward_list/erase.hpp>
#include <hamon/forward_list/forward_list.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace erase_test
{

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

FORWARD_LIST_TEST_CONSTEXPR bool test1()
{
	{
		hamon::forward_list<int> v = {3,1,4,5,2};
		auto r = hamon::erase(v, 1);
		VERIFY(r == 1);
		const int v2[] = {3,4,5,2,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		hamon::forward_list<int> v = {9,1,9,9,2,3,9,9,9,4,5,9,9,9,9,};
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

FORWARD_LIST_TEST_CONSTEXPR bool test2()
{
	hamon::forward_list<Point> v
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

#undef VERIFY

GTEST_TEST(ForwardListTest, EraseTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace erase_test

}	// namespace hamon_forward_list_test
