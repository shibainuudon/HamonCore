/**
 *	@file	unit_test_numeric_iota.cpp
 *
 *	@brief	iota のテスト
 */

#include <hamon/numeric/iota.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_numeric_test
{

namespace iota_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		int a[5]{};
		hamon::iota(hamon::begin(a), hamon::end(a), 0);
		VERIFY(0 == a[0]);
		VERIFY(1 == a[1]);
		VERIFY(2 == a[2]);
		VERIFY(3 == a[3]);
		VERIFY(4 == a[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		hamon::array<int, 4> a{};
		hamon::iota(hamon::begin(a), hamon::end(a), -2);
		VERIFY(-2 == a[0]);
		VERIFY(-1 == a[1]);
		VERIFY( 0 == a[2]);
		VERIFY( 1 == a[3]);
	}
	return true;
}

GTEST_TEST(NumericTest, IotaTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());

	{
		hamon::vector<int> a(6);
		hamon::iota(hamon::begin(a), hamon::end(a), -1);
		EXPECT_EQ(-1, a[0]);
		EXPECT_EQ( 0, a[1]);
		EXPECT_EQ( 1, a[2]);
		EXPECT_EQ( 2, a[3]);
		EXPECT_EQ( 3, a[4]);
		EXPECT_EQ( 4, a[5]);
	}
	{
		hamon::list<int> a(3);
		hamon::iota(hamon::begin(a), hamon::end(a), 1);
		auto it = a.begin();
		EXPECT_EQ( 1, *it++);
		EXPECT_EQ( 2, *it++);
		EXPECT_EQ( 3, *it++);
		EXPECT_TRUE(it == a.end());
	}
}

#undef VERIFY

}	// namespace iota_test

}	// namespace hamon_numeric_test
