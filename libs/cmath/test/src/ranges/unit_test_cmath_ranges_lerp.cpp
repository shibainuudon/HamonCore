/**
 *	@file	unit_test_cmath_ranges_lerp.cpp
 *
 *	@brief	ranges::lerp のテスト
 */

#include <hamon/cmath/ranges/lerp.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_lerp_test
{

template <typename T>
struct Real
{
	T value;

	HAMON_CXX11_CONSTEXPR bool operator==(Real const& rhs) const
	{
		return value == rhs.value;
	}
};

template <typename T>
HAMON_CXX11_CONSTEXPR Real<T> lerp(Real<T> const& x, Real<T> const& y, Real<T> const& z)
{
	return Real<T>{ hamon::lerp(x.value, y.value, z.value) };
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	lerp(Vector3<T> const& v1, Vector3<T> const& v2, Vector3<T> const& v3)
	{
		return Vector3<T>
		{
			hamon::lerp(v1.x, v2.x, v3.x),
			hamon::lerp(v1.y, v2.y, v3.y),
			hamon::lerp(v1.z, v2.z, v3.z),
		};
	}

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	lerp(Vector3<T> const& v1, Vector3<T> const& v2, double s)
	{
		return Vector3<T>
		{
			static_cast<T>(hamon::lerp(v1.x, v2.x, s)),
			static_cast<T>(hamon::lerp(v1.y, v2.y, s)),
			static_cast<T>(hamon::lerp(v1.z, v2.z, s)),
		};
	}
};

template <typename T>
void RangesLerpTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-20.0}, hamon::ranges::lerp(T{ 0.0}, T{10.0f}, T{-2.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-10.0}, hamon::ranges::lerp(T{ 0.0}, T{10.0f}, T{-1.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{  0.0}, hamon::ranges::lerp(T{ 0.0}, T{10.0f}, T{ 0.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{  2.5}, hamon::ranges::lerp(T{ 0.0}, T{10.0f}, T{ 0.25}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{  5.0}, hamon::ranges::lerp(T{ 0.0}, T{10.0f}, T{ 0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{  7.5}, hamon::ranges::lerp(T{ 0.0}, T{10.0f}, T{ 0.75}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 10.0}, hamon::ranges::lerp(T{ 0.0}, T{10.0f}, T{ 1.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 20.0}, hamon::ranges::lerp(T{ 0.0}, T{10.0f}, T{ 2.0}));
}

template <typename T>
void RangesLerpTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 1, 2, 3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 { 5, 6, 7 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v3 { 0.5, 0.75, 1.0 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v4 = hamon::ranges::lerp(v1, v2, v3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v4.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5, v4.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7, v4.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 1, 2, 3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 { 2, 4, 13 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v3 = hamon::ranges::lerp(v1, v2, 0.25);
		HAMON_CXX11_CONSTEXPR Vector3<T> v4 = hamon::ranges::lerp(v1, v2, 0.5);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.25, v3.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5,  v3.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5.5,  v3.z);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.5,  v4.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3.0,  v4.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8.0,  v4.z);
	}
}

GTEST_TEST(CMathTest, RangesLerpTest)
{
	RangesLerpTest<float>();
	RangesLerpTest<double>();
	RangesLerpTest<long double>();

	RangesLerpTest<Real<float>>();
	RangesLerpTest<Real<double>>();
	RangesLerpTest<Real<long double>>();

	RangesLerpTest2<float>();
	RangesLerpTest2<double>();
	RangesLerpTest2<long double>();
}

}	// namespace ranges_lerp_test

}	// namespace hamon_cmath_test
