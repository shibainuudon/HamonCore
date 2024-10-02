/**
 *	@file	unit_test_algorithm_find.cpp
 *
 *	@brief	find のテスト
 */

#include <hamon/algorithm/find.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace find_test
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
	int const a[] {0,1,2};
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), 0);
		VERIFY(it == hamon::begin(a));
	}
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), 1);
		VERIFY(it == hamon::begin(a) + 1);
	}
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), 2);
		VERIFY(it == hamon::begin(a) + 2);
	}
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), 3);
		VERIFY(it == hamon::end(a));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	hamon::array<float, 8> const a{{3, 4, 4, 5, 5, 5, 3, 6}};
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), 3.0f);
		VERIFY(it == hamon::begin(a));
	}
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), 4.0f);
		VERIFY(it == hamon::begin(a) + 1);
	}
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), 5.0f);
		VERIFY(it == hamon::begin(a) + 3);
	}
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), 6.0f);
		VERIFY(it == hamon::begin(a) + 7);
	}
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), 0.0f);
		VERIFY(it == hamon::end(a));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[] {0,1,2};
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), 0);
		VERIFY(it == hamon::begin(a));
		*it = 10;
	}
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), 2);
		VERIFY(it == hamon::begin(a) + 2);
		*it = 20;
	}
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), 3);
		VERIFY(it == hamon::end(a));
	}
	VERIFY(10 == a[0]);
	VERIFY( 1 == a[1]);
	VERIFY(20 == a[2]);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	Point const a[]
	{
		{1, 2}, {1, 1}, {1, 2}, {2, 1},
	};

	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), {1, 1});
		VERIFY(it == hamon::begin(a) + 1);
	}
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), {1, 2});
		VERIFY(it == hamon::begin(a) + 0);
	}
	{
		auto it = hamon::find(hamon::begin(a), hamon::end(a), {1, 3});
		VERIFY(it == hamon::end(a));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, FindTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());

	{
		const hamon::vector<int> a {7, 8, 9};
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 7);
			EXPECT_TRUE(it == hamon::begin(a));
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 8);
			EXPECT_TRUE(it == hamon::begin(a) + 1);
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 9);
			EXPECT_TRUE(it == hamon::begin(a) + 2);
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 10);
			EXPECT_TRUE(it == hamon::end(a));
		}
	}
	{
		const hamon::list<int> a {0,1,2};
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 0);
			EXPECT_TRUE(it == hamon::begin(a));
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 1);
			EXPECT_TRUE(it == ++hamon::begin(a));
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 2);
			EXPECT_TRUE(it == ++(++hamon::begin(a)));
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), -1);
			EXPECT_TRUE(it == hamon::end(a));
		}
	}
	{
		hamon::list<int> a {0,1,2};
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 1);
			EXPECT_TRUE(it == ++hamon::begin(a));
			*it = 30;
		}
		{
			auto it = hamon::find(hamon::begin(a), hamon::end(a), 3);
			EXPECT_TRUE(it == hamon::end(a));
		}
		{
			auto it = a.begin();
			EXPECT_EQ( 0, *it++);
			EXPECT_EQ(30, *it++);
			EXPECT_EQ( 2, *it++);
		}
	}
}

}	// namespace find_test

}	// namespace hamon_algorithm_test
