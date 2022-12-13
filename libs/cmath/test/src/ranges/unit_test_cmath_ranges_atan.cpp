/**
 *	@file	unit_test_cmath_ranges_atan.cpp
 *
 *	@brief	ranges::atan のテスト
 */

#include <hamon/cmath/ranges/atan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_atan_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T atan(Real<T> const& r)
{
	return hamon::atan(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	atan(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::atan(v.x),
			hamon::atan(v.y),
			hamon::atan(v.z),
		};
	}
};

template <typename T>
struct atan_error;

template <>
struct atan_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000001;
};

template <>
struct atan_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <>
struct atan_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <typename T>
struct atan_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = atan_error<T>::value;
};

template <typename T>
void RangesAtanTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = atan_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5507989928217, (double)hamon::ranges::atan(T{-50.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.1902899496825, (double)hamon::ranges::atan(T{ -2.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.7853981633974, (double)hamon::ranges::atan(T{ -1.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.6435011087932, (double)hamon::ranges::atan(T{ -0.75}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.4636476090008, (double)hamon::ranges::atan(T{ -0.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.2449786631268, (double)hamon::ranges::atan(T{ -0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)hamon::ranges::atan(T{  0.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.2449786631268, (double)hamon::ranges::atan(T{  0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.4636476090008, (double)hamon::ranges::atan(T{  0.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.6435011087932, (double)hamon::ranges::atan(T{  0.75}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.7853981633974, (double)hamon::ranges::atan(T{  1.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1902899496825, (double)hamon::ranges::atan(T{  2.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5507989928217, (double)hamon::ranges::atan(T{ 50.00}), error);
}

template <typename T>
void RangesAtanTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = atan_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 0, 0.5 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::atan(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.7853981633974, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.4636476090008, (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesAtanTest)
{
	RangesAtanTest<float>();
	RangesAtanTest<double>();
	RangesAtanTest<long double>();

	RangesAtanTest<Real<float>>();
	RangesAtanTest<Real<double>>();
	RangesAtanTest<Real<long double>>();

	RangesAtanTest2<float>();
	RangesAtanTest2<double>();
	RangesAtanTest2<long double>();
}

}	// namespace ranges_atan_test

}	// namespace hamon_cmath_test
