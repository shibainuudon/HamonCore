/**
 *	@file	unit_test_cmath_ranges_rsqrt.cpp
 *
 *	@brief	ranges::rsqrt のテスト
 */

#include <hamon/cmath/ranges/rsqrt.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_rsqrt_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T rsqrt(Real<T> const& r)
{
	return hamon::rsqrt(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	rsqrt(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::rsqrt(v.x),
			hamon::rsqrt(v.y),
			hamon::rsqrt(v.z),
		};
	}
};

template <typename T>
struct rsqrt_error;

template <>
struct rsqrt_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.0000001;
};

template <>
struct rsqrt_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <>
struct rsqrt_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <typename T>
struct rsqrt_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = rsqrt_error<T>::value;
};

template <typename T>
void RangesRsqrtTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = rsqrt_error<T>::value;
	
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0,           (double)hamon::ranges::rsqrt(T{  0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0,           (double)hamon::ranges::rsqrt(T{  1.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.66666666666, (double)hamon::ranges::rsqrt(T{  2.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::ranges::rsqrt(T{  2.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.57735026918, (double)hamon::ranges::rsqrt(T{  3.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.1,           (double)hamon::ranges::rsqrt(T{100.00}), error);
}

template <typename T>
void RangesRsqrtTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = rsqrt_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 1, 2, 3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::rsqrt(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000000000, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.70710678118, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.57735026918, (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesRsqrtTest)
{
	RangesRsqrtTest<float>();
	RangesRsqrtTest<double>();
	RangesRsqrtTest<long double>();

	RangesRsqrtTest<Real<float>>();
	RangesRsqrtTest<Real<double>>();
	RangesRsqrtTest<Real<long double>>();

	RangesRsqrtTest2<float>();
	RangesRsqrtTest2<double>();
	RangesRsqrtTest2<long double>();
}

}	// namespace ranges_rsqrt_test

}	// namespace hamon_cmath_test
