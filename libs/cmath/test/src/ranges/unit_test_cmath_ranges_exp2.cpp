/**
 *	@file	unit_test_cmath_ranges_exp2.cpp
 *
 *	@brief	ranges::exp2 のテスト
 */

#include <hamon/cmath/ranges/exp2.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_exp2_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T exp2(Real<T> const& r)
{
	return hamon::exp2(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	exp2(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::exp2(v.x),
			hamon::exp2(v.y),
			hamon::exp2(v.z),
		};
	}
};

template <typename T>
struct exp2_error;

template <>
struct exp2_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00001;
};

template <>
struct exp2_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <>
struct exp2_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <typename T>
struct exp2_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = exp2_error<T>::value;
};

template <typename T>
void RangesExp2Test(void)
{
	HAMON_CXX11_CONSTEXPR double error = exp2_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::exp2(T{+0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::exp2(T{-0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.09050773266, (double)hamon::ranges::exp2(T{ 0.125}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.18920711500, (double)hamon::ranges::exp2(T{ 0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.41421356237, (double)hamon::ranges::exp2(T{ 0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.68179283051, (double)hamon::ranges::exp2(T{ 0.75}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.00000000000, (double)hamon::ranges::exp2(T{ 1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.37841423000, (double)hamon::ranges::exp2(T{ 1.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.82842712474, (double)hamon::ranges::exp2(T{ 1.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 4.00000000000, (double)hamon::ranges::exp2(T{ 2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5.65685424949, (double)hamon::ranges::exp2(T{ 2.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 8.00000000000, (double)hamon::ranges::exp2(T{ 3.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(11.31370849898, (double)hamon::ranges::exp2(T{ 3.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(16.00000000000, (double)hamon::ranges::exp2(T{ 4.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(22.62741699796, (double)hamon::ranges::exp2(T{ 4.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(32.00000000000, (double)hamon::ranges::exp2(T{ 5.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.91700404320, (double)hamon::ranges::exp2(T{-0.125}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.84089641525, (double)hamon::ranges::exp2(T{-0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::ranges::exp2(T{-0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.59460355750, (double)hamon::ranges::exp2(T{-0.75}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000, (double)hamon::ranges::exp2(T{-1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.25000000000, (double)hamon::ranges::exp2(T{-2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.17677669529, (double)hamon::ranges::exp2(T{-2.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.12500000000, (double)hamon::ranges::exp2(T{-3.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.08838834764, (double)hamon::ranges::exp2(T{-3.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.06250000000, (double)hamon::ranges::exp2(T{-4.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.04419417382, (double)hamon::ranges::exp2(T{-4.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.03125000000, (double)hamon::ranges::exp2(T{-5.0}), error);
}

template <typename T>
void RangesExp2Test2(void)
{
	HAMON_CXX11_CONSTEXPR double error = exp2_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 0, 1 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::exp2(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.50000000000, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000000000, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.00000000000, (double)v2.z, error);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 1.5, 2, 2.5 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::exp2(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.82842712474, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.00000000000, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(5.65685424949, (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesExp2Test)
{
	RangesExp2Test<float>();
	RangesExp2Test<double>();
	RangesExp2Test<long double>();

	RangesExp2Test<Real<float>>();
	RangesExp2Test<Real<double>>();
	RangesExp2Test<Real<long double>>();

	RangesExp2Test2<float>();
	RangesExp2Test2<double>();
	RangesExp2Test2<long double>();
}

}	// namespace ranges_exp2_test

}	// namespace hamon_cmath_test
