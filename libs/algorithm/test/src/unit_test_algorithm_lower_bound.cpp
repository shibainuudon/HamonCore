/**
 *	@file	unit_test_algorithm_lower_bound.cpp
 *
 *	@brief	lower_bound のテスト
 */

#include <hamon/algorithm/lower_bound.hpp>
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

namespace lower_bound_test
{

HAMON_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

struct pred2
{
	template <typename T>
	HAMON_CONSTEXPR bool operator()(T x, T y) const
	{
		return x < y;
	}
};

struct S
{
	int x;
};

inline HAMON_CXX11_CONSTEXPR bool
operator<(S const& lhs, S const& rhs)
{
	return lhs.x < rhs.x;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		int const a[] { 1,2,3,4,5 };
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 3);
		VERIFY(ret == hamon::next(hamon::begin(a), 2));
	}
	{
		int const a[] { 1,1,2,2,2,3,3 };
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 2);
		VERIFY(ret == hamon::next(hamon::begin(a), 2));
	}
	{
		int const a[] { 1,1,2,2,2,3,3 };
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 3);
		VERIFY(ret == hamon::next(hamon::begin(a), 5));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		int const a[] { 1,3,5,6,7,9 };
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 7, pred1);
		VERIFY(ret == hamon::next(hamon::begin(a), 4));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	{
		hamon::array<int, 5> const a {{ 3,1,4,6,5 }};
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 4);
		VERIFY(ret == hamon::next(hamon::begin(a), 2));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	{
		hamon::array<int, 3> const a {{ 10,20,30 }};
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 10, pred2());
		VERIFY(ret == hamon::next(hamon::begin(a), 0));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test05()
{
	{
		S const a[] { {1},{2},{3},{4},{5} };
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), {3});
		VERIFY(ret == hamon::next(hamon::begin(a), 2));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test06()
{
	{
		S const a[] { {1},{2},{3},{4},{5} };
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), {3}, pred2{});
		VERIFY(ret == hamon::next(hamon::begin(a), 2));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, LowerBoundTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test06());

	{
		const hamon::vector<int> a { 1,3,5,8,13,17,25 };
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 10);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 4));
	}
	{
		const hamon::vector<int> a { 1,3,5,8,13,17,25 };
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 1, [](int x, int y) { return x < y; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
	{
		const hamon::list<int> a { 5,1,25,13,17 };
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 10);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 2));
	}
	{
		const hamon::vector<int> a;
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 0);
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
	{
		const hamon::list<int> a;
		auto ret = hamon::lower_bound(hamon::begin(a), hamon::end(a), 0, [](int x, int y) { return x < y; });
		EXPECT_TRUE(ret == hamon::next(hamon::begin(a), 0));
	}
}

}	// namespace lower_bound_test

}	// namespace hamon_algorithm_test
