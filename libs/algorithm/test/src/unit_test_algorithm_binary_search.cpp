/**
 *	@file	unit_test_algorithm_binary_search.cpp
 *
 *	@brief	binary_search のテスト
 */

#include <hamon/algorithm/binary_search.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace binary_search_test
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
	{
		int const a[] { 1,2,3,4,5 };
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 1)));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 4)));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 5)));
		VERIFY(!(hamon::binary_search(hamon::begin(a), hamon::end(a), 0)));
		VERIFY(!(hamon::binary_search(hamon::begin(a), hamon::end(a), 6)));
	}
	{
		int const a[] { 1,1,2,3,3,3,4,4,5 };
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 1, pred1)));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 2, pred1)));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 3, pred1)));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 4, pred1)));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 5, pred1)));
		VERIFY(!(hamon::binary_search(hamon::begin(a), hamon::end(a), 0, pred1)));
		VERIFY(!(hamon::binary_search(hamon::begin(a), hamon::end(a), 6, pred1)));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		hamon::array<int,5> const a {{ 3,1,4,6,5 }};
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 4)));
		VERIFY(!(hamon::binary_search(hamon::begin(a), hamon::end(a), 0)));
		VERIFY(!(hamon::binary_search(hamon::begin(a), hamon::end(a), 6)));
	}
	{
		hamon::array<int,5> const a {{ 5,4,3,2,1 }};
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 1, pred2())));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 2, pred2())));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 3, pred2())));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 4, pred2())));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), 5, pred2())));
		VERIFY(!(hamon::binary_search(hamon::begin(a), hamon::end(a), 0, pred2())));
		VERIFY(!(hamon::binary_search(hamon::begin(a), hamon::end(a), 6, pred2())));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	{
		S const a[] { {1},{1},{2},{3},{3},{3}, };
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), {1})));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), {2})));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), {3})));
		VERIFY(!(hamon::binary_search(hamon::begin(a), hamon::end(a), {0})));
		VERIFY(!(hamon::binary_search(hamon::begin(a), hamon::end(a), {4})));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	{
		S const a[] { {3},{2},{2},{2},{1},{1}, };
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), {1}, pred2{})));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), {2}, pred2{})));
		VERIFY( (hamon::binary_search(hamon::begin(a), hamon::end(a), {3}, pred2{})));
		VERIFY(!(hamon::binary_search(hamon::begin(a), hamon::end(a), {0}, pred2{})));
		VERIFY(!(hamon::binary_search(hamon::begin(a), hamon::end(a), {4}, pred2{})));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, BinarySearchTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());

	{
		const hamon::vector<int> a { 1,2,3,4,5 };
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 1, [](int x, int y) { return x < y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 2, [](int x, int y) { return x < y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 3, [](int x, int y) { return x < y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 4, [](int x, int y) { return x < y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 5, [](int x, int y) { return x < y; }));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 0, [](int x, int y) { return x < y; }));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 6, [](int x, int y) { return x < y; }));
	}
	{
		const hamon::list<int> a { 5,3,3,2,0 };
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 0, [](int x, int y) { return x > y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 2, [](int x, int y) { return x > y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 3, [](int x, int y) { return x > y; }));
		EXPECT_TRUE (hamon::binary_search(hamon::begin(a), hamon::end(a), 5, [](int x, int y) { return x > y; }));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 1, [](int x, int y) { return x > y; }));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 4, [](int x, int y) { return x > y; }));
	}
	{
		const hamon::vector<int> a;
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 0));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 1));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 2));
	}
	{
		const hamon::list<int> a;
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 0, [](int x, int y) { return x < y; }));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 1, [](int x, int y) { return x < y; }));
		EXPECT_FALSE(hamon::binary_search(hamon::begin(a), hamon::end(a), 2, [](int x, int y) { return x < y; }));
	}
}

}	// namespace binary_search_test

}	// namespace hamon_algorithm_test
