/**
 *	@file	unit_test_cmath_ranges_atan2.cpp
 *
 *	@brief	ranges::atan2 のテスト
 */

#include <hamon/cmath/ranges/atan2.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/numbers/pi.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_atan2_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T atan2(Real<T> const& x, Real<T> const& y)
{
	return hamon::atan2(x.value, y.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	atan2(Vector3<T> const& v1, Vector3<T> const& v2)
	{
		return Vector3<T>
		{
			hamon::atan2(v1.x, v2.x),
			hamon::atan2(v1.y, v2.y),
			hamon::atan2(v1.z, v2.z),
		};
	}
};

template <typename T>
struct atan2_error;

template <>
struct atan2_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000001;
};

template <>
struct atan2_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000000000001;
};

template <>
struct atan2_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000000000001;
};

template <typename T>
struct atan2_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = atan2_error<T>::value;
};

template <typename T>
void RangesAtan2Test(void)
{
	HAMON_CXX11_CONSTEXPR auto pi = hamon::numbers::pi_fn<double>();
	HAMON_CXX11_CONSTEXPR double error = atan2_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.00, (double)hamon::ranges::atan2(T{ 0.0}, T{ 1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.00, (double)hamon::ranges::atan2(T{ 0.0}, T{ 2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.00, (double)hamon::ranges::atan2(T{ 0.0}, T{ 0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.25, (double)hamon::ranges::atan2(T{ 1.0}, T{ 1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.25, (double)hamon::ranges::atan2(T{ 2.0}, T{ 2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.25, (double)hamon::ranges::atan2(T{ 0.5}, T{ 0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.50, (double)hamon::ranges::atan2(T{ 1.0}, T{ 0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.50, (double)hamon::ranges::atan2(T{ 2.0}, T{ 0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.50, (double)hamon::ranges::atan2(T{ 0.5}, T{ 0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.75, (double)hamon::ranges::atan2(T{ 1.0}, T{-1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.75, (double)hamon::ranges::atan2(T{ 2.0}, T{-2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  0.75, (double)hamon::ranges::atan2(T{ 0.5}, T{-0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  1.00, (double)hamon::ranges::atan2(T{ 0.0}, T{-1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  1.00, (double)hamon::ranges::atan2(T{ 0.0}, T{-2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi *  1.00, (double)hamon::ranges::atan2(T{ 0.0}, T{-0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.75, (double)hamon::ranges::atan2(T{-1.0}, T{-1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.75, (double)hamon::ranges::atan2(T{-2.0}, T{-2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.75, (double)hamon::ranges::atan2(T{-0.5}, T{-0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.50, (double)hamon::ranges::atan2(T{-1.0}, T{ 0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.50, (double)hamon::ranges::atan2(T{-2.0}, T{ 0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.50, (double)hamon::ranges::atan2(T{-0.5}, T{ 0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.25, (double)hamon::ranges::atan2(T{-1.0}, T{ 1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.25, (double)hamon::ranges::atan2(T{-2.0}, T{ 2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * -0.25, (double)hamon::ranges::atan2(T{-0.5}, T{ 0.5}), error);
}

template <typename T>
void RangesAtan2Test2(void)
{
	HAMON_CXX11_CONSTEXPR auto pi = hamon::numbers::pi_fn<double>();
	HAMON_CXX11_CONSTEXPR double error = atan2_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 0, 1, 1};
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 { 1, 1, 0 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v3 = hamon::ranges::atan2(v1, v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * 0.00, (double)v3.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * 0.25, (double)v3.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(pi * 0.50, (double)v3.z, error);
	}
}

GTEST_TEST(CMathTest, RangesAtan2Test)
{
	RangesAtan2Test<float>();
	RangesAtan2Test<double>();
	RangesAtan2Test<long double>();

	RangesAtan2Test<Real<float>>();
	RangesAtan2Test<Real<double>>();
	RangesAtan2Test<Real<long double>>();

	RangesAtan2Test2<float>();
	RangesAtan2Test2<double>();
	RangesAtan2Test2<long double>();
}

}	// namespace ranges_atan2_test

}	// namespace hamon_cmath_test
