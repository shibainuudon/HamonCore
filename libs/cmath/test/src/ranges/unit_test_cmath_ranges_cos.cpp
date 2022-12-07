/**
 *	@file	unit_test_cmath_ranges_cos.cpp
 *
 *	@brief	ranges::cos のテスト
 */

#include <hamon/cmath/ranges/cos.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/degrees_to_radians.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_cos_test
{

template <typename T>
struct Radian
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T cos(Radian<T> const& r)
{
	return hamon::cos(r.value);
}

template <typename T>
struct Degree
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T cos(Degree<T> const& d)
{
	return hamon::cos(hamon::degrees_to_radians(d.value));
}

template <typename T>
struct cos_error;

template <>
struct cos_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000001;
};

template <>
struct cos_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <>
struct cos_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <typename T>
struct cos_error<Radian<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = cos_error<T>::value;
};

template <typename T>
void RangesCosTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = cos_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.41614683654, (double)hamon::ranges::cos(T{-2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.07073720166, (double)hamon::ranges::cos(T{-1.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.54030230586, (double)hamon::ranges::cos(T{-1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.87758256189, (double)hamon::ranges::cos(T{-0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::cos(T{-0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::cos(T{ 0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.87758256189, (double)hamon::ranges::cos(T{ 0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.54030230586, (double)hamon::ranges::cos(T{ 1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.07073720166, (double)hamon::ranges::cos(T{ 1.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.41614683654, (double)hamon::ranges::cos(T{ 2.0}), error);
}

template <typename T>
void RangesCosTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = cos_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.00000000000000000, (double)hamon::ranges::cos(Degree<T>{-180}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, (double)hamon::ranges::cos(Degree<T>{ -90}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000000000, (double)hamon::ranges::cos(Degree<T>{ -60}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118654757, (double)hamon::ranges::cos(Degree<T>{ -45}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.86602540378443871, (double)hamon::ranges::cos(Degree<T>{ -30}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000000000, (double)hamon::ranges::cos(Degree<T>{   0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.86602540378443871, (double)hamon::ranges::cos(Degree<T>{  30}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118654757, (double)hamon::ranges::cos(Degree<T>{  45}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000000000, (double)hamon::ranges::cos(Degree<T>{  60}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, (double)hamon::ranges::cos(Degree<T>{  90}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.00000000000000000, (double)hamon::ranges::cos(Degree<T>{ 180}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, (double)hamon::ranges::cos(Degree<T>{ 270}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000000000, (double)hamon::ranges::cos(Degree<T>{ 360}), error);
}

GTEST_TEST(CMathTest, RangesCosTest)
{
	RangesCosTest<float>();
	RangesCosTest<double>();
	RangesCosTest<long double>();

	RangesCosTest<Radian<float>>();
	RangesCosTest<Radian<double>>();
	RangesCosTest<Radian<long double>>();

	RangesCosTest2<float>();
	RangesCosTest2<double>();
	RangesCosTest2<long double>();
}

}	// namespace ranges_cos_test

}	// namespace hamon_cmath_test
