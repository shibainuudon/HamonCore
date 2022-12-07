/**
 *	@file	unit_test_cmath_ranges_sin.cpp
 *
 *	@brief	ranges::sin のテスト
 */

#include <hamon/cmath/ranges/sin.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/degrees_to_radians.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_sin_test
{

template <typename T>
struct Radian
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T sin(Radian<T> const& r)
{
	return hamon::sin(r.value);
}

template <typename T>
struct Degree
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T sin(Degree<T> const& d)
{
	return hamon::sin(hamon::degrees_to_radians(d.value));
}

template <typename T>
struct sin_error;

template <>
struct sin_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000001;
};

template <>
struct sin_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <>
struct sin_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <typename T>
struct sin_error<Radian<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = sin_error<T>::value;
};

template <typename T>
void RangesSinTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = sin_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.90929742682568171, (double)hamon::ranges::sin(T{-2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.99749498660405445, (double)hamon::ranges::sin(T{-1.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.84147098480789650, (double)hamon::ranges::sin(T{-1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.47942553860420301, (double)hamon::ranges::sin(T{-0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, (double)hamon::ranges::sin(T{-0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, (double)hamon::ranges::sin(T{ 0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.47942553860420301, (double)hamon::ranges::sin(T{ 0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.84147098480789650, (double)hamon::ranges::sin(T{ 1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99749498660405445, (double)hamon::ranges::sin(T{ 1.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.90929742682568171, (double)hamon::ranges::sin(T{ 2.0}), error);
}

template <typename T>
void RangesSinTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = sin_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, (double)hamon::ranges::sin(Degree<T>{-180}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.00000000000000000, (double)hamon::ranges::sin(Degree<T>{ -90}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.86602540378443860, (double)hamon::ranges::sin(Degree<T>{ -60}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.70710678118654757, (double)hamon::ranges::sin(Degree<T>{ -45}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.50000000000000000, (double)hamon::ranges::sin(Degree<T>{ -30}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, (double)hamon::ranges::sin(Degree<T>{   0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000000000, (double)hamon::ranges::sin(Degree<T>{  30}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118654757, (double)hamon::ranges::sin(Degree<T>{  45}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.86602540378443860, (double)hamon::ranges::sin(Degree<T>{  60}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000000000, (double)hamon::ranges::sin(Degree<T>{  90}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, (double)hamon::ranges::sin(Degree<T>{ 180}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.00000000000000000, (double)hamon::ranges::sin(Degree<T>{ 270}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, (double)hamon::ranges::sin(Degree<T>{ 360}), error);
}

GTEST_TEST(CMathTest, RangesSinTest)
{
	RangesSinTest<float>();
	RangesSinTest<double>();
	RangesSinTest<long double>();

	RangesSinTest<Radian<float>>();
	RangesSinTest<Radian<double>>();
	RangesSinTest<Radian<long double>>();

	RangesSinTest2<float>();
	RangesSinTest2<double>();
	RangesSinTest2<long double>();
}

}	// namespace ranges_sin_test

}	// namespace hamon_cmath_test
