/**
 *	@file	unit_test_cmath_ranges_pow.cpp
 *
 *	@brief	ranges::pow のテスト
 */

#include <hamon/cmath/ranges/pow.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_pow_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T pow(Real<T> const& x, Real<T> const& y)
{
	return hamon::pow(x.value, y.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	pow(Vector3<T> const& v1, Vector3<T> const& v2)
	{
		return Vector3<T>
		{
			hamon::pow(v1.x, v2.x),
			hamon::pow(v1.y, v2.y),
			hamon::pow(v1.z, v2.z),
		};
	}
};

template <typename T>
struct pow_error;

template <>
struct pow_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.0001;
};

template <>
struct pow_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <>
struct pow_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <typename T>
struct pow_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = pow_error<T>::value;
};

template <typename T>
void RangesPowTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = pow_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(8.0,               (double)hamon::ranges::pow(T{2.0}, T{ 3.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.0,               (double)hamon::ranges::pow(T{2.0}, T{ 2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0,               (double)hamon::ranges::pow(T{2.0}, T{ 1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.414213562373095, (double)hamon::ranges::pow(T{2.0}, T{ 0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0,               (double)hamon::ranges::pow(T{2.0}, T{ 0.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.707106781186547, (double)hamon::ranges::pow(T{2.0}, T{-0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5,               (double)hamon::ranges::pow(T{2.0}, T{-1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.25,              (double)hamon::ranges::pow(T{2.0}, T{-2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.125,             (double)hamon::ranges::pow(T{2.0}, T{-3.0}), error);
}

template <typename T>
void RangesPowTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = pow_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 2.5, 3.0, -2.0 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 { 3.0, -0.5, 1.0 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v3 = hamon::ranges::pow(v1, v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(15.625, (double)v3.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5773502691896259, (double)v3.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.0, (double)v3.z, error);
	}
}

GTEST_TEST(CMathTest, RangesPowTest)
{
	RangesPowTest<float>();
	RangesPowTest<double>();
	RangesPowTest<long double>();

	RangesPowTest<Real<float>>();
	RangesPowTest<Real<double>>();
	RangesPowTest<Real<long double>>();

	RangesPowTest2<float>();
	RangesPowTest2<double>();
	RangesPowTest2<long double>();
}

}	// namespace ranges_pow_test

}	// namespace hamon_cmath_test
