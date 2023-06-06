/**
 *	@file	unit_test_complex.cpp
 *
 *	@brief	complex のテスト
 */

#include <hamon/complex.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

static_assert(hamon::is_same<typename hamon::complex<float>::value_type, float>::value, "");
static_assert(hamon::is_same<typename hamon::complex<double>::value_type, double>::value, "");
static_assert(hamon::is_same<typename hamon::complex<long double>::value_type, long double>::value, "");

// [complex.numbers.general]/2
static_assert(hamon::is_trivially_copyable<hamon::complex<float>>::value, "");
static_assert(hamon::is_trivially_copyable<hamon::complex<double>>::value, "");
static_assert(hamon::is_trivially_copyable<hamon::complex<long double>>::value, "");

GTEST_TEST(ComplexTest, GeneralTest)
{
	// [complex.numbers.general]/4
	{
		hamon::complex<float> z{1, 2};
		auto r = reinterpret_cast<float(&)[2]>(z);
		EXPECT_EQ(1, r[0]);
		EXPECT_EQ(2, r[1]);
	}
	{
		hamon::complex<double> const z{3, 4};
		auto r = reinterpret_cast<double const(&)[2]>(z);
		EXPECT_EQ(3, r[0]);
		EXPECT_EQ(4, r[1]);
	}

	{
		hamon::complex<float> a[3] =
		{
			{1, 2}, {3, 4}, {5, 6},
		};
		auto p = reinterpret_cast<float const*>(a);
		EXPECT_EQ(1, p[0]);
		EXPECT_EQ(2, p[1]);
		EXPECT_EQ(3, p[2]);
		EXPECT_EQ(4, p[3]);
		EXPECT_EQ(5, p[4]);
		EXPECT_EQ(6, p[5]);
	}
	{
		hamon::complex<double> a[2] =
		{
			{7, 8}, {9,10},
		};
		auto p = reinterpret_cast<double*>(a);
		EXPECT_EQ( 7, p[0]);
		EXPECT_EQ( 8, p[1]);
		EXPECT_EQ( 9, p[2]);
		EXPECT_EQ(10, p[3]);
	}
}
