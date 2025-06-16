/**
 *	@file	unit_test_algorithm_stable_sort.cpp
 *
 *	@brief	stable_sort のテスト
 */

#include <hamon/algorithm/stable_sort.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace stable_sort_test
{

struct Foo
{
	int key;
	float value;
};

HAMON_CXX14_CONSTEXPR bool
operator<(const Foo& lhs, const Foo& rhs)
{
	return lhs.key < rhs.key;
}

HAMON_CXX14_CONSTEXPR bool
operator>(const Foo& lhs, const Foo& rhs)
{
	return lhs.key > rhs.key;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		Foo a[]
		{
			{ 1, 0.5f },
			{ 2, 1.5f },
			{ 1, 2.5f },
		};

		hamon::stable_sort(hamon::begin(a), hamon::end(a));

		VERIFY(0.5 == a[0].value);
		VERIFY(2.5 == a[1].value);
		VERIFY(1.5 == a[2].value);
	}
	{
		Foo a[]
		{
			{ 1, 0.5f },
			{ 2, 1.5f },
			{ 1, 2.5f },
		};

		hamon::stable_sort(hamon::begin(a), hamon::end(a), hamon::greater<>());

		VERIFY(1.5 == a[0].value);
		VERIFY(0.5 == a[1].value);
		VERIFY(2.5 == a[2].value);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test2()
{
	{
		hamon::array<Foo, 5> a
		{{
			{ 3, 0.5f },
			{ 1, 1.5f },
			{ 4, 2.5f },
			{ 1, 3.5f },
			{ 5, 4.5f },
		}};

		hamon::stable_sort(hamon::begin(a), hamon::end(a));

		VERIFY(1.5 == a[0].value);
		VERIFY(3.5 == a[1].value);
		VERIFY(0.5 == a[2].value);
		VERIFY(2.5 == a[3].value);
		VERIFY(4.5 == a[4].value);
	}
	{
		hamon::array<Foo, 5> a
		{{
			{ 3, 0.5f },
			{ 1, 1.5f },
			{ 4, 2.5f },
			{ 1, 3.5f },
			{ 5, 4.5f },
		}};

		hamon::stable_sort(hamon::begin(a), hamon::end(a), hamon::greater<>());

		VERIFY(4.5 == a[0].value);
		VERIFY(2.5 == a[1].value);
		VERIFY(0.5 == a[2].value);
		VERIFY(1.5 == a[3].value);
		VERIFY(3.5 == a[4].value);
	}
	return true;
}

inline bool test3()
{
	{
		hamon::vector<Foo> a
		{
			{ 3, 0.5f },
			{ 1, 1.5f },
			{ 4, 2.5f },
			{ 1, 3.5f },
			{ 5, 4.5f },
			{ 9, 5.5f },
			{ 2, 6.5f },
			{ 6, 7.5f },
			{ 5, 8.5f },
			{ 3, 9.5f },
		};

		hamon::stable_sort(hamon::begin(a), hamon::end(a));

		VERIFY(1.5 == a[0].value);
		VERIFY(3.5 == a[1].value);
		VERIFY(6.5 == a[2].value);
		VERIFY(0.5 == a[3].value);
		VERIFY(9.5 == a[4].value);
		VERIFY(2.5 == a[5].value);
		VERIFY(4.5 == a[6].value);
		VERIFY(8.5 == a[7].value);
		VERIFY(7.5 == a[8].value);
		VERIFY(5.5 == a[9].value);
	}
	{
		hamon::vector<Foo> a
		{
			{ 3, 0.5f },
			{ 1, 1.5f },
			{ 4, 2.5f },
			{ 1, 3.5f },
			{ 5, 4.5f },
			{ 9, 5.5f },
			{ 2, 6.5f },
			{ 6, 7.5f },
			{ 5, 8.5f },
			{ 3, 9.5f },
		};

		hamon::stable_sort(hamon::begin(a), hamon::end(a), hamon::greater<>());

		VERIFY(5.5 == a[0].value);
		VERIFY(7.5 == a[1].value);
		VERIFY(4.5 == a[2].value);
		VERIFY(8.5 == a[3].value);
		VERIFY(2.5 == a[4].value);
		VERIFY(0.5 == a[5].value);
		VERIFY(9.5 == a[6].value);
		VERIFY(6.5 == a[7].value);
		VERIFY(1.5 == a[8].value);
		VERIFY(3.5 == a[9].value);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, StableSortTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2());
	EXPECT_TRUE(test3());
}

}	// namespace stable_sort_test

}	// namespace hamon_algorithm_test
