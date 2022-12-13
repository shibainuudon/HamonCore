/**
 *	@file	unit_test_cmath_ranges_asin.cpp
 *
 *	@brief	ranges::asin のテスト
 */

#include <hamon/cmath/ranges/asin.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_asin_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T asin(Real<T> const& r)
{
	return hamon::asin(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	asin(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::asin(v.x),
			hamon::asin(v.y),
			hamon::asin(v.z),
		};
	}
};

template <typename T>
struct asin_error;

template <>
struct asin_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000001;
};

template <>
struct asin_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <>
struct asin_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <typename T>
struct asin_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = asin_error<T>::value;
};

template <typename T>
void RangesAsinTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = asin_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5707963267949, (double)hamon::ranges::asin(T{-1.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.8480620789814, (double)hamon::ranges::asin(T{-0.75}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.5235987755983, (double)hamon::ranges::asin(T{-0.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.2526802551420, (double)hamon::ranges::asin(T{-0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)hamon::ranges::asin(T{ 0.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.2526802551420, (double)hamon::ranges::asin(T{ 0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.5235987755983, (double)hamon::ranges::asin(T{ 0.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.8480620789814, (double)hamon::ranges::asin(T{ 0.75}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5707963267949, (double)hamon::ranges::asin(T{ 1.00}), error);
}

template <typename T>
void RangesAsinTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = asin_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 0, 0.5 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::asin(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5707963267949, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.5235987755983, (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesAsinTest)
{
	RangesAsinTest<float>();
	RangesAsinTest<double>();
	RangesAsinTest<long double>();

	RangesAsinTest<Real<float>>();
	RangesAsinTest<Real<double>>();
	RangesAsinTest<Real<long double>>();

	RangesAsinTest2<float>();
	RangesAsinTest2<double>();
	RangesAsinTest2<long double>();
}

}	// namespace ranges_asin_test

}	// namespace hamon_cmath_test
