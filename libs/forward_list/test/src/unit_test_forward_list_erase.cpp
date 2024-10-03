/**
 *	@file	unit_test_forward_list_erase.cpp
 *
 *	@brief	erase のテスト
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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline /*HAMON_CXX14_CONSTEXPR*/ bool test1()
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

inline HAMON_CXX11_CONSTEXPR bool
operator==(Point const& lhs, Point const& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline HAMON_CXX11_CONSTEXPR bool
operator!=(Point const& lhs, Point const& rhs)
{
	return !(lhs == rhs);
}

inline /*HAMON_CXX14_CONSTEXPR*/ bool test2()
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
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test1());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test2());
}

}	// namespace erase_test

}	// namespace hamon_forward_list_test
