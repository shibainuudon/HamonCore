/**
 *	@file	unit_test_cmath_ranges_cbrt.cpp
 *
 *	@brief	ranges::cbrt のテスト
 */

#include <hamon/cmath/ranges/cbrt.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_cbrt_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T cbrt(Real<T> const& r)
{
	return hamon::cbrt(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	cbrt(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::cbrt(v.x),
			hamon::cbrt(v.y),
			hamon::cbrt(v.z),
		};
	}
};

template <typename T>
struct cbrt_error;

template <>
struct cbrt_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00001;
};

template <>
struct cbrt_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.0000000000001;
};

template <>
struct cbrt_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.0000000000001;
};

template <typename T>
struct cbrt_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = cbrt_error<T>::value;
};

template <typename T>
void RangesCbrtTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = cbrt_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)hamon::ranges::cbrt(T{   0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.5, (double)hamon::ranges::cbrt(T{   0.125}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0, (double)hamon::ranges::cbrt(T{   1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5, (double)hamon::ranges::cbrt(T{   3.375}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0, (double)hamon::ranges::cbrt(T{   8.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0, (double)hamon::ranges::cbrt(T{  27.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 4.0, (double)hamon::ranges::cbrt(T{  64.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5.0, (double)hamon::ranges::cbrt(T{ 125.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.0, (double)hamon::ranges::cbrt(T{ 216.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 7.0, (double)hamon::ranges::cbrt(T{ 343.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 8.0, (double)hamon::ranges::cbrt(T{ 512.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 9.0, (double)hamon::ranges::cbrt(T{ 729.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.5, (double)hamon::ranges::cbrt(T{  -0.125}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0, (double)hamon::ranges::cbrt(T{  -1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5, (double)hamon::ranges::cbrt(T{  -3.375}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.0, (double)hamon::ranges::cbrt(T{  -8.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-3.0, (double)hamon::ranges::cbrt(T{ -27.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-4.0, (double)hamon::ranges::cbrt(T{ -64.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-5.0, (double)hamon::ranges::cbrt(T{-125.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-6.0, (double)hamon::ranges::cbrt(T{-216.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-7.0, (double)hamon::ranges::cbrt(T{-343.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-8.0, (double)hamon::ranges::cbrt(T{-512.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-9.0, (double)hamon::ranges::cbrt(T{-729.0}), error);
}

template <typename T>
void RangesCbrtTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = cbrt_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 1, -2, 3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::cbrt(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0000000000000000000000000000000, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.2599210498948731647672106072782, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4422495703074083823216383107801, (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesCbrtTest)
{
	RangesCbrtTest<float>();
	RangesCbrtTest<double>();
	RangesCbrtTest<long double>();

	RangesCbrtTest<Real<float>>();
	RangesCbrtTest<Real<double>>();
	RangesCbrtTest<Real<long double>>();

	RangesCbrtTest2<float>();
	RangesCbrtTest2<double>();
	RangesCbrtTest2<long double>();
}

}	// namespace ranges_cbrt_test

}	// namespace hamon_cmath_test
