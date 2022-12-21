/**
 *	@file	unit_test_cmath_ranges_saturate.cpp
 *
 *	@brief	ranges::saturate のテスト
 */

#include <hamon/cmath/ranges/saturate.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_saturate_test
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
HAMON_CXX11_CONSTEXPR Real<T> saturate(Real<T> const& r)
{
	return Real<T>{ hamon::saturate(r.value) };
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	saturate(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::saturate(v.x),
			hamon::saturate(v.y),
			hamon::saturate(v.z),
		};
	}
};

template <typename T>
void RangesSaturateTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0.0f}, hamon::ranges::saturate(T{-100000}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0.0f}, hamon::ranges::saturate(T{-0.2f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0.0f}, hamon::ranges::saturate(T{-0.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0.0f}, hamon::ranges::saturate(T{ 0.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0.1f}, hamon::ranges::saturate(T{ 0.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0.2f}, hamon::ranges::saturate(T{ 0.2f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0.9f}, hamon::ranges::saturate(T{ 0.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1.0f}, hamon::ranges::saturate(T{ 1.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1.0f}, hamon::ranges::saturate(T{ 1.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1.0f}, hamon::ranges::saturate(T{ 2.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1.0f}, hamon::ranges::saturate(T{ 100000}));
}

template <typename T>
void RangesSaturateTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -0.1f, 0.0f, 0.5f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::saturate(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0f, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0f, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.5f, v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 0.9f, 1.0f, 1.1f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::saturate(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.9f, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0f, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0f, v2.z);
	}
}

GTEST_TEST(CMathTest, RangesSaturateTest)
{
	RangesSaturateTest<float>();
	RangesSaturateTest<double>();
	RangesSaturateTest<long double>();

	RangesSaturateTest<Real<float>>();
	RangesSaturateTest<Real<double>>();
	RangesSaturateTest<Real<long double>>();

	RangesSaturateTest2<float>();
	RangesSaturateTest2<double>();
	RangesSaturateTest2<long double>();
}

}	// namespace ranges_saturate_test

}	// namespace hamon_cmath_test
