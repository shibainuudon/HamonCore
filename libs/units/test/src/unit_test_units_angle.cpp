/**
 *	@file	unit_test_units_angle.cpp
 *
 *	@brief	angle のテスト
 */

#include <hamon/units/radian.hpp>
#include <hamon/units/degree.hpp>
#include <hamon/numbers.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace units_angle_test
{

template <typename T>
class AngleTest : public ::testing::Test {};

using AngleTestTypes = ::testing::Types<float, double, long double>;

TYPED_TEST_SUITE(AngleTest, AngleTestTypes);

template <typename T>
struct angle_accuracy;
template <> struct angle_accuracy<float>       { static HAMON_CONSTEXPR double get() { return 0.0001; } };
template <> struct angle_accuracy<double>      { static HAMON_CONSTEXPR double get() { return 0.000000000000001; } };
template <> struct angle_accuracy<long double> { static HAMON_CONSTEXPR double get() { return 0.000000000000001; } };

TYPED_TEST(AngleTest, AccuracyTest)
{
	using T = TypeParam;
	using radians = hamon::units::radians<T>;
	using degrees = hamon::units::degrees<T>;

	HAMON_CXX11_CONSTEXPR auto p = hamon::numbers::pi_fn<T>();

	HAMON_CXX11_CONSTEXPR double error = angle_accuracy<T>::get();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.0, (double)degrees(radians(p * T(0.00))).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 45.0, (double)degrees(radians(p * T(0.25))).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 90.0, (double)degrees(radians(p * T(0.50))).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(135.0, (double)degrees(radians(p * T(0.75))).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(180.0, (double)degrees(radians(p * T(1.00))).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(225.0, (double)degrees(radians(p * T(1.25))).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(270.0, (double)degrees(radians(p * T(1.50))).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(315.0, (double)degrees(radians(p * T(1.75))).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(360.0, (double)degrees(radians(p * T(2.00))).value(), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)(p * 0.00), (double)radians(degrees(  0.0)).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)(p * 0.25), (double)radians(degrees( 45.0)).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)(p * 0.50), (double)radians(degrees( 90.0)).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)(p * 0.75), (double)radians(degrees(135.0)).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)(p * 1.00), (double)radians(degrees(180.0)).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)(p * 1.25), (double)radians(degrees(225.0)).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)(p * 1.50), (double)radians(degrees(270.0)).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)(p * 1.75), (double)radians(degrees(315.0)).value(), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR((double)(p * 2.00), (double)radians(degrees(360.0)).value(), error);
}

template <typename T>
struct angle_error;
template <> struct angle_error<float>       { static HAMON_CONSTEXPR double get() { return 0.00001; } };
template <> struct angle_error<double>      { static HAMON_CONSTEXPR double get() { return 0.00000000001; } };
template <> struct angle_error<long double> { static HAMON_CONSTEXPR double get() { return 0.00000000001; } };

TYPED_TEST(AngleTest, SinTest)
{
	using T = TypeParam;
	using radians = hamon::units::radians<T>;
	using degrees = hamon::units::degrees<T>;

	HAMON_CXX11_CONSTEXPR auto p = hamon::numbers::pi_fn<T>();

	HAMON_CXX11_CONSTEXPR double error = angle_error<T>::get();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::sin(radians(p * T(0.000))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::ranges::sin(radians(p * T(0.250))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::sin(radians(p * T(0.500))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::ranges::sin(radians(p * T(0.750))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::sin(radians(p * T(1.000))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.70710678118, (double)hamon::ranges::sin(radians(p * T(1.250))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.00000000000, (double)hamon::ranges::sin(radians(p * T(1.500))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.70710678118, (double)hamon::ranges::sin(radians(p * T(1.750))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::sin(radians(p * T(2.000))), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::sin(degrees(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000, (double)hamon::ranges::sin(degrees( 30)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::ranges::sin(degrees( 45)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.86602540378, (double)hamon::ranges::sin(degrees( 60)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::sin(degrees( 90)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.86602540378, (double)hamon::ranges::sin(degrees(120)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::ranges::sin(degrees(135)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000, (double)hamon::ranges::sin(degrees(150)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::sin(degrees(180)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.50000000000, (double)hamon::ranges::sin(degrees(210)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.70710678118, (double)hamon::ranges::sin(degrees(225)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.86602540378, (double)hamon::ranges::sin(degrees(240)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.00000000000, (double)hamon::ranges::sin(degrees(270)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.86602540378, (double)hamon::ranges::sin(degrees(300)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.70710678118, (double)hamon::ranges::sin(degrees(315)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.50000000000, (double)hamon::ranges::sin(degrees(330)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::sin(degrees(360)), error);
}

TYPED_TEST(AngleTest, CosTest)
{
	using T = TypeParam;
	using radians = hamon::units::radians<T>;
	using degrees = hamon::units::degrees<T>;

	HAMON_CXX11_CONSTEXPR auto p = hamon::numbers::pi_fn<T>();

	HAMON_CXX11_CONSTEXPR double error = angle_error<T>::get();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::cos(radians(p * T(0.000))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::ranges::cos(radians(p * T(0.250))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::cos(radians(p * T(0.500))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.70710678118, (double)hamon::ranges::cos(radians(p * T(0.750))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.00000000000, (double)hamon::ranges::cos(radians(p * T(1.000))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.70710678118, (double)hamon::ranges::cos(radians(p * T(1.250))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::cos(radians(p * T(1.500))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::ranges::cos(radians(p * T(1.750))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::cos(radians(p * T(2.000))), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::cos(degrees(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.86602540378, (double)hamon::ranges::cos(degrees( 30)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::ranges::cos(degrees( 45)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000, (double)hamon::ranges::cos(degrees( 60)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::cos(degrees( 90)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.50000000000, (double)hamon::ranges::cos(degrees(120)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.70710678118, (double)hamon::ranges::cos(degrees(135)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.86602540378, (double)hamon::ranges::cos(degrees(150)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.00000000000, (double)hamon::ranges::cos(degrees(180)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.86602540378, (double)hamon::ranges::cos(degrees(210)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.70710678118, (double)hamon::ranges::cos(degrees(225)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.50000000000, (double)hamon::ranges::cos(degrees(240)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::cos(degrees(270)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000, (double)hamon::ranges::cos(degrees(300)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::ranges::cos(degrees(315)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.86602540378, (double)hamon::ranges::cos(degrees(330)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::cos(degrees(360)), error);
}

TYPED_TEST(AngleTest, TanTest)
{
	using T = TypeParam;
	using radians = hamon::units::radians<T>;
	using degrees = hamon::units::degrees<T>;

	HAMON_CXX11_CONSTEXPR auto p = hamon::numbers::pi_fn<T>();

	HAMON_CXX11_CONSTEXPR double error = angle_error<T>::get();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::tan(radians(p * T(0.000))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::tan(radians(p * T(0.250))), error);
//	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.6331239e+16, (double)hamon::ranges::tan(radians(p * T(0.500))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.00000000000, (double)hamon::ranges::tan(radians(p * T(0.750))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::tan(radians(p * T(1.000))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::tan(radians(p * T(1.250))), error);
//	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5.4437465e+15, (double)hamon::ranges::tan(radians(p * T(1.500))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.00000000000, (double)hamon::ranges::tan(radians(p * T(1.750))), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::tan(radians(p * T(2.000))), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::tan(degrees(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.57735026919, (double)hamon::ranges::tan(degrees( 30)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::tan(degrees( 45)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.73205080757, (double)hamon::ranges::tan(degrees( 60)), error);
//	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.6331239e+16, (double)hamon::ranges::tan(degrees( 90)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.73205080757, (double)hamon::ranges::tan(degrees(120)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.00000000000, (double)hamon::ranges::tan(degrees(135)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.57735026919, (double)hamon::ranges::tan(degrees(150)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::tan(degrees(180)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.57735026919, (double)hamon::ranges::tan(degrees(210)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::ranges::tan(degrees(225)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.73205080757, (double)hamon::ranges::tan(degrees(240)), error);
//	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 5.4437465e+15, (double)hamon::ranges::tan(degrees(270)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.73205080757, (double)hamon::ranges::tan(degrees(300)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.00000000000, (double)hamon::ranges::tan(degrees(315)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.57735026919, (double)hamon::ranges::tan(degrees(330)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::ranges::tan(degrees(360)), error);
}

}	// namespace units_angle_test
