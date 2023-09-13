/**
 *	@file	unit_test_algorithm_copy_if.cpp
 *
 *	@brief	copy_if のテスト
 */

#include <hamon/algorithm/copy_if.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace copy_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CONSTEXPR bool pred1(int x)
{
	return x > 1;
}

inline HAMON_CONSTEXPR bool pred2(int x)
{
	return (x % 2) == 0;
}

inline HAMON_CXX14_CONSTEXPR bool CopyIfArrayTest()
{
	const int a1[] { 1, 2, 3 };
	int a2[3]{};

	auto it = hamon::copy_if(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), pred1);

	VERIFY(2 == a2[0]);
	VERIFY(3 == a2[1]);
	VERIFY(0 == a2[2]);
	VERIFY(it == hamon::begin(a2) + 2);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool CopyIfStdArrayTest()
{
	const hamon::array<int, 4> a1 {{ 4, 5, 6, 7 }};
	int a2[5] {{}};

	auto it = hamon::copy_if(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), pred2);

	VERIFY(4 == a2[0]);
	VERIFY(6 == a2[1]);
	VERIFY(0 == a2[2]);
	VERIFY(0 == a2[3]);
	VERIFY(0 == a2[4]);
	VERIFY(it == hamon::begin(a2) + 2);

	return true;
}

GTEST_TEST(AlgorithmTest, CopyIfTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyIfArrayTest());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyIfStdArrayTest());

	{
		const hamon::vector<int> v { 5, 6, 7, 8, 9 };
		std::list<int> l;

		hamon::copy_if(hamon::begin(v), hamon::end(v), std::back_inserter(l), [](int x) { return (x % 2) == 1; });

		auto it = l.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(7, *it++);
		EXPECT_EQ(9, *it++);
		EXPECT_TRUE(it == l.end());
	}
}

#undef VERIFY

}	// namespace copy_if_test

}	// namespace hamon_algorithm_test
