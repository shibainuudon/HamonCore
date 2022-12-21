/**
 *	@file	unit_test_cmath_ranges_frac.cpp
 *
 *	@brief	ranges::frac のテスト
 */

#include <hamon/cmath/ranges/frac.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_frac_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T frac(Real<T> const& r)
{
	return hamon::frac(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	frac(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::frac(v.x),
			hamon::frac(v.y),
			hamon::frac(v.z),
		};
	}
};

template <typename T>
struct frac_error;

template <>
struct frac_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.0000001;
};

template <>
struct frac_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.0000001;
};

template <>
struct frac_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.0000001;
};

template <typename T>
struct frac_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = frac_error<T>::value;
};

template <typename T>
void RangesFracTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = frac_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.8,    (double)hamon::ranges::frac(T{-1.2f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.9,    (double)hamon::ranges::frac(T{-1.1f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,    (double)hamon::ranges::frac(T{-1.0f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.1,    (double)hamon::ranges::frac(T{-0.9f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.2,    (double)hamon::ranges::frac(T{-0.8f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5,    (double)hamon::ranges::frac(T{-0.5f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.8,    (double)hamon::ranges::frac(T{-0.2f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.9,    (double)hamon::ranges::frac(T{-0.1f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,    (double)hamon::ranges::frac(T{ 0.0f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.1,    (double)hamon::ranges::frac(T{ 0.1f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.123,  (double)hamon::ranges::frac(T{ 0.123f}),  error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.2,    (double)hamon::ranges::frac(T{ 0.2f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5,    (double)hamon::ranges::frac(T{ 0.5f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.8,    (double)hamon::ranges::frac(T{ 0.8f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.9,    (double)hamon::ranges::frac(T{ 0.9f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.99,   (double)hamon::ranges::frac(T{ 0.99f}),   error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.999,  (double)hamon::ranges::frac(T{ 0.999f}),  error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,    (double)hamon::ranges::frac(T{ 1.0f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.1,    (double)hamon::ranges::frac(T{ 1.1f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.2,    (double)hamon::ranges::frac(T{ 1.2f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.2525, (double)hamon::ranges::frac(T{ 1.2525f}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.8,    (double)hamon::ranges::frac(T{ 1.8f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.9,    (double)hamon::ranges::frac(T{ 1.9f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,    (double)hamon::ranges::frac(T{ 2.0f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.1,    (double)hamon::ranges::frac(T{ 2.1f}),    error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.2,    (double)hamon::ranges::frac(T{ 2.2f}),    error);
}

template <typename T>
void RangesFracTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = frac_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 1.0f, 1.1f, 1.2f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::frac(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.1, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.2, (double)v2.z, error);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 6.25f, 5.4f, 4.5f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::frac(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.25, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.4, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.5, (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesFracTest)
{
	RangesFracTest<float>();
	RangesFracTest<double>();
	RangesFracTest<long double>();

	RangesFracTest<Real<float>>();
	RangesFracTest<Real<double>>();
	RangesFracTest<Real<long double>>();

	RangesFracTest2<float>();
	RangesFracTest2<double>();
	RangesFracTest2<long double>();
}

}	// namespace ranges_frac_test

}	// namespace hamon_cmath_test
