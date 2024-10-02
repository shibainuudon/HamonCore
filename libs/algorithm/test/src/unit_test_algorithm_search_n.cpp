/**
 *	@file	unit_test_algorithm_search_n.cpp
 *
 *	@brief	search_n のテスト
 */

#include <hamon/algorithm/search_n.hpp>
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

namespace search_n_test
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
	const int a[] = { 1,2,3,2,1,3,3,2,3,3,1 };
	{
		auto it = hamon::search_n(hamon::begin(a), hamon::end(a), 0, 3);
		VERIFY(it == hamon::begin(a));
	}
	{
		auto it = hamon::search_n(hamon::begin(a), hamon::end(a), 1, 3);
		VERIFY(it == hamon::next(hamon::begin(a), 2));
	}
	{
		auto it = hamon::search_n(hamon::begin(a), hamon::end(a), 2, 3);
		VERIFY(it == hamon::next(hamon::begin(a), 5));
	}
	{
		auto it = hamon::search_n(hamon::begin(a), hamon::end(a), 3, 3);
		VERIFY(it == hamon::end(a));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	const hamon::array<int, 11> a = {{ 1,2,3,2,1,3,3,2,3,3,1 }};
	{
		auto it = hamon::search_n(hamon::begin(a), hamon::end(a), 0, 3);
		VERIFY(it == hamon::begin(a));
	}
	{
		auto it = hamon::search_n(hamon::begin(a), hamon::end(a), 1, 3);
		VERIFY(it == hamon::next(hamon::begin(a), 2));
	}
	{
		auto it = hamon::search_n(hamon::begin(a), hamon::end(a), 2, 3);
		VERIFY(it == hamon::next(hamon::begin(a), 5));
	}
	{
		auto it = hamon::search_n(hamon::begin(a), hamon::end(a), 3, 3);
		VERIFY(it == hamon::end(a));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	Point const a[]
	{
		{1, 2}, {2, 1}, {2, 1}, {1, 1},
	};

	{
		auto it = hamon::search_n(hamon::begin(a), hamon::end(a), 0, {1,3});
		VERIFY(it == hamon::begin(a));
	}
	{
		auto it = hamon::search_n(hamon::begin(a), hamon::end(a), 1, {1,3});
		VERIFY(it == hamon::end(a));
	}
	{
		auto it = hamon::search_n(hamon::begin(a), hamon::end(a), 2, {2,1});
		VERIFY(it == hamon::next(hamon::begin(a), 1));
	}
	{
		auto it = hamon::search_n(hamon::begin(a), hamon::end(a), 3, {2,1});
		VERIFY(it == hamon::end(a));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, SearchNTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());

	{
		const hamon::vector<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 1, 2);
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 1));
	}
	{
		const hamon::list<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 2, 2);
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 3));
	}
	{
		const hamon::vector<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 3, 2);
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 6));
	}
	{
		const hamon::list<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 3, 2, [](int x, int y) { return x <= y; });
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 3));
	}
	{
		const hamon::vector<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 3, 2, [](int x, int y) { return x >= y; });
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 1));
	}
	{
		const hamon::list<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 0, 5);
		EXPECT_TRUE(it == hamon::next(hamon::begin(a), 0));
	}
	{
		const hamon::vector<int> a;
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 2, 3);
		EXPECT_TRUE(it == hamon::end(a));
	}
	{
		const hamon::list<int> a;
		auto const it = hamon::search_n(hamon::begin(a), hamon::end(a), 2, 3);
		EXPECT_TRUE(it == hamon::begin(a));
	}
}

}	// namespace search_n_test

}	// namespace hamon_algorithm_test
