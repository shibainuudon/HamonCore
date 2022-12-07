/**
 *	@file	unit_test_cmath_ranges_tan.cpp
 *
 *	@brief	ranges::tan のテスト
 */

#include <hamon/cmath/ranges/tan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/degrees_to_radians.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_tan_test
{

template <typename T>
struct Radian
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T tan(Radian<T> const& r)
{
	return hamon::tan(r.value);
}

template <typename T>
struct Degree
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T tan(Degree<T> const& d)
{
	return hamon::tan(hamon::degrees_to_radians(d.value));
}

template <typename T>
struct tan_error;

template <>
struct tan_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.0001;
};

template <>
struct tan_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.0000000001;
};

template <>
struct tan_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.0000000001;
};

template <typename T>
struct tan_error<Radian<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = tan_error<T>::value;
};

template <typename T>
void RangesTanTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = tan_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.1850398632615189, (double)hamon::ranges::tan(T{-2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-14.101419947171719, (double)hamon::ranges::tan(T{-1.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5574077246549023, (double)hamon::ranges::tan(T{-1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.54630248984379048,(double)hamon::ranges::tan(T{-0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000, (double)hamon::ranges::tan(T{ 0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.54630248984379048,(double)hamon::ranges::tan(T{ 0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5574077246549023, (double)hamon::ranges::tan(T{ 1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(14.101419947171719,  (double)hamon::ranges::tan(T{ 1.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.1850398632615189, (double)hamon::ranges::tan(T{ 2.0}), error);
}

template <typename T>
void RangesTanTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = tan_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000, (double)hamon::ranges::tan(Degree<T>{-180}), error);
//	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000, (double)hamon::ranges::tan(Degree<T>{ -90}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.7320508075688772, (double)hamon::ranges::tan(Degree<T>{ -60}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0000000000000000, (double)hamon::ranges::tan(Degree<T>{ -45}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.57735026918962573,(double)hamon::ranges::tan(Degree<T>{ -30}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000, (double)hamon::ranges::tan(Degree<T>{   0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.57735026918962573,(double)hamon::ranges::tan(Degree<T>{  30}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0000000000000000, (double)hamon::ranges::tan(Degree<T>{  45}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.7320508075688772, (double)hamon::ranges::tan(Degree<T>{  60}), error);
//	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000, (double)hamon::ranges::tan(Degree<T>{  90}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000, (double)hamon::ranges::tan(Degree<T>{ 180}), error);
}

GTEST_TEST(CMathTest, RangesTanTest)
{
	RangesTanTest<float>();
	RangesTanTest<double>();
	RangesTanTest<long double>();

	RangesTanTest<Radian<float>>();
	RangesTanTest<Radian<double>>();
	RangesTanTest<Radian<long double>>();

	RangesTanTest2<float>();
	RangesTanTest2<double>();
	RangesTanTest2<long double>();
}

}	// namespace ranges_tan_test

}	// namespace hamon_cmath_test
