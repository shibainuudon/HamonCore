/**
 *	@file	unit_test_cmath_ranges_sqrt.cpp
 *
 *	@brief	ranges::sqrt のテスト
 */

#include <hamon/cmath/ranges/sqrt.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_sqrt_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T sqrt(Real<T> const& r)
{
	return hamon::sqrt(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	sqrt(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::sqrt(v.x),
			hamon::sqrt(v.y),
			hamon::sqrt(v.z),
		};
	}
};

template <typename T>
struct sqrt_error;

template <>
struct sqrt_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.0000001;
};

template <>
struct sqrt_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <>
struct sqrt_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <typename T>
struct sqrt_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = sqrt_error<T>::value;
};

template <typename T>
void RangesSqrtTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = sqrt_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(   0.00000000000, (double)hamon::ranges::sqrt(T{      0.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(   0.50000000000, (double)hamon::ranges::sqrt(T{      0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(   1.00000000000, (double)hamon::ranges::sqrt(T{      1.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(   1.50000000000, (double)hamon::ranges::sqrt(T{      2.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(   1.41421356237, (double)hamon::ranges::sqrt(T{      2.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(   1.73205080757, (double)hamon::ranges::sqrt(T{      3.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  10.00000000000, (double)hamon::ranges::sqrt(T{    100.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1000.00000000000, (double)hamon::ranges::sqrt(T{1000000.00}), error);
}

template <typename T>
void RangesSqrtTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = sqrt_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 1, 2, 3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::sqrt(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000000000, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.41421356237, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.73205080757, (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesSqrtTest)
{
	RangesSqrtTest<float>();
	RangesSqrtTest<double>();
	RangesSqrtTest<long double>();

	RangesSqrtTest<Real<float>>();
	RangesSqrtTest<Real<double>>();
	RangesSqrtTest<Real<long double>>();

	RangesSqrtTest2<float>();
	RangesSqrtTest2<double>();
	RangesSqrtTest2<long double>();
}

}	// namespace ranges_sqrt_test

}	// namespace hamon_cmath_test
