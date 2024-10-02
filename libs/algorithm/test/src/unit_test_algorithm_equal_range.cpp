/**
 *	@file	unit_test_algorithm_equal_range.cpp
 *
 *	@brief	equal_range のテスト
 */

#include <hamon/algorithm/equal_range.hpp>
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

namespace equal_range_test
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
		return y < x;
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
	int const a[] { 1,2,2,3,3,3,4,4,5,5,5 };
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 1);
		VERIFY(ret.first  == hamon::next(hamon::begin(a), 0));
		VERIFY(ret.second == hamon::next(hamon::begin(a), 1));
	}
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 3, pred1);
		VERIFY(ret.first  == hamon::next(hamon::begin(a), 3));
		VERIFY(ret.second == hamon::next(hamon::begin(a), 6));
	}
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 5);
		VERIFY(ret.first  == hamon::next(hamon::begin(a), 8));
		VERIFY(ret.second == hamon::next(hamon::begin(a), 11));
	}
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 0);
		VERIFY(ret.first  == hamon::next(hamon::begin(a), 0));
		VERIFY(ret.second == hamon::next(hamon::begin(a), 0));
	}
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 10);
		VERIFY(ret.first  == hamon::end(a));
		VERIFY(ret.second == hamon::end(a));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	hamon::array<int, 9> const a {{ 5,5,4,2,2,2,1,0,0 }};
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 2, pred2());
		VERIFY(ret.first  == hamon::next(hamon::begin(a), 3));
		VERIFY(ret.second == hamon::next(hamon::begin(a), 6));
	}
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), -1, pred2());
		VERIFY(ret.first  == hamon::end(a));
		VERIFY(ret.second == hamon::end(a));
	}
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 6, pred2());
		VERIFY(ret.first  == hamon::begin(a));
		VERIFY(ret.second == hamon::begin(a));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	S const a[] { {1},{2},{2},{3},{3},{3}, };
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), {1});
		VERIFY(ret.first  == hamon::next(hamon::begin(a), 0));
		VERIFY(ret.second == hamon::next(hamon::begin(a), 1));
	}
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), {2});
		VERIFY(ret.first  == hamon::next(hamon::begin(a), 1));
		VERIFY(ret.second == hamon::next(hamon::begin(a), 3));
	}
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), {3});
		VERIFY(ret.first  == hamon::next(hamon::begin(a), 3));
		VERIFY(ret.second == hamon::next(hamon::begin(a), 6));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	S const a[] { {3},{2},{2},{2},{1},{1}, };
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), {1}, pred2{});
		VERIFY(ret.first  == hamon::next(hamon::begin(a), 4));
		VERIFY(ret.second == hamon::next(hamon::begin(a), 6));
	}
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), {2}, pred2{});
		VERIFY(ret.first  == hamon::next(hamon::begin(a), 1));
		VERIFY(ret.second == hamon::next(hamon::begin(a), 4));
	}
	{
		auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), {3}, pred2{});
		VERIFY(ret.first  == hamon::next(hamon::begin(a), 0));
		VERIFY(ret.second == hamon::next(hamon::begin(a), 1));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, EqualRangeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());

	{
		// ソートされていなくても区分化されていれば良い
		const hamon::vector<int> a { 2,1,2,3,3,4,7,5,5 };
		{
			auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 3);
			EXPECT_TRUE(ret.first  == hamon::next(hamon::begin(a), 3));
			EXPECT_TRUE(ret.second == hamon::next(hamon::begin(a), 5));
		}
	}
	{
		const hamon::list<int> a { 8, 6, 6, 7, 5, 5, 5, 3, 4, 2, 2 };
		{
			auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 5, [] (int x, int y) { return x > y; });
			EXPECT_TRUE(ret.first  == hamon::next(hamon::begin(a), 4));
			EXPECT_TRUE(ret.second == hamon::next(hamon::begin(a), 7));
		}
	}
	{
		const hamon::vector<int> a;
		{
			auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 0);
			EXPECT_TRUE(ret.first  == hamon::begin(a));
			EXPECT_TRUE(ret.second == hamon::end(a));
		}
	}
	{
		const hamon::list<int> a;
		{
			auto ret = hamon::equal_range(hamon::begin(a), hamon::end(a), 0, pred1);
			EXPECT_TRUE(ret.first  == hamon::begin(a));
			EXPECT_TRUE(ret.second == hamon::end(a));
		}
	}
}

}	// namespace equal_range_test

}	// namespace hamon_algorithm_test
