/**
 *	@file	unit_test_cmath_ranges_smoothstep.cpp
 *
 *	@brief	ranges::smoothstep のテスト
 */

#include <hamon/cmath/ranges/smoothstep.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_smoothstep_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T smoothstep(Real<T> const& x, Real<T> const& y, Real<T> const& z)
{
	return hamon::smoothstep(x.value, y.value, z.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	smoothstep(Vector3<T> const& v1, Vector3<T> const& v2, Vector3<T> const& v3)
	{
		return Vector3<T>
		{
			hamon::smoothstep(v1.x, v2.x, v3.x),
			hamon::smoothstep(v1.y, v2.y, v3.y),
			hamon::smoothstep(v1.z, v2.z, v3.z),
		};
	}
};

template <typename T>
struct smoothstep_error;

template <>
struct smoothstep_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.0000001;
};

template <>
struct smoothstep_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <>
struct smoothstep_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <typename T>
struct smoothstep_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = smoothstep_error<T>::value;
};

template <typename T>
void RangesSmoothstepTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = smoothstep_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00000, (double)hamon::ranges::smoothstep(T{ 0.0}, T{10.0}, T{ 0.00f}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00725, (double)hamon::ranges::smoothstep(T{ 0.0}, T{10.0}, T{ 0.50f}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.02800, (double)hamon::ranges::smoothstep(T{ 0.0}, T{10.0}, T{ 1.00f}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.50000, (double)hamon::ranges::smoothstep(T{ 0.0}, T{10.0}, T{ 5.00f}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.97200, (double)hamon::ranges::smoothstep(T{ 0.0}, T{10.0}, T{ 9.00f}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.99275, (double)hamon::ranges::smoothstep(T{ 0.0}, T{10.0}, T{ 9.50f}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000, (double)hamon::ranges::smoothstep(T{ 0.0}, T{10.0}, T{10.00f}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.00000, (double)hamon::ranges::smoothstep(T{ 0.0}, T{10.0}, T{10.10f}), error);
}

template <typename T>
void RangesSmoothstepTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = smoothstep_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 {  0,  0,  0 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 { 10, 10, 10 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v3 { 0.5, 5.0, 9.0 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v4 = hamon::ranges::smoothstep(v1, v2, v3);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00725, (double)v4.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.50000, (double)v4.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.97200, (double)v4.z, error);
	}
}

GTEST_TEST(CMathTest, RangesSmoothstepTest)
{
	RangesSmoothstepTest<float>();
	RangesSmoothstepTest<double>();
	RangesSmoothstepTest<long double>();

	RangesSmoothstepTest<Real<float>>();
	RangesSmoothstepTest<Real<double>>();
	RangesSmoothstepTest<Real<long double>>();

	RangesSmoothstepTest2<float>();
	RangesSmoothstepTest2<double>();
	RangesSmoothstepTest2<long double>();
}

}	// namespace ranges_smoothstep_test

}	// namespace hamon_cmath_test
