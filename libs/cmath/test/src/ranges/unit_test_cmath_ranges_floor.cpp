/**
 *	@file	unit_test_cmath_ranges_floor.cpp
 *
 *	@brief	ranges::floor のテスト
 */

#include <hamon/cmath/ranges/floor.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_floor_test
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
HAMON_CXX11_CONSTEXPR Real<T> floor(Real<T> const& r)
{
	return Real<T>{hamon::floor(r.value)};
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	floor(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::floor(v.x),
			hamon::floor(v.y),
			hamon::floor(v.z),
		};
	}
};

template <typename T>
void RangesFloorTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-2.0f}, hamon::ranges::floor(T{-1.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0f}, hamon::ranges::floor(T{-1.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0f}, hamon::ranges::floor(T{-0.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0f}, hamon::ranges::floor(T{-0.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0f}, hamon::ranges::floor(T{ 0.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0f}, hamon::ranges::floor(T{ 0.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0f}, hamon::ranges::floor(T{ 0.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0f}, hamon::ranges::floor(T{ 1.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0f}, hamon::ranges::floor(T{ 1.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{10.0f}, hamon::ranges::floor(T{10.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{11.0f}, hamon::ranges::floor(T{11.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{11.0f}, hamon::ranges::floor(T{11.1f}));
}

template <typename T>
void RangesFloorTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 2.9f, 3.0f, 3.1f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::floor(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{2.0}, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{3.0}, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{3.0}, v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -2.9f, -3.0f, -3.1f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::floor(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-3.0}, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-3.0}, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-4.0}, v2.z);
	}
}

GTEST_TEST(CMathTest, RangesFloorTest)
{
	RangesFloorTest<float>();
	RangesFloorTest<double>();
	RangesFloorTest<long double>();

	RangesFloorTest<Real<float>>();
	RangesFloorTest<Real<double>>();
	RangesFloorTest<Real<long double>>();

	RangesFloorTest2<float>();
	RangesFloorTest2<double>();
	RangesFloorTest2<long double>();
}

}	// namespace ranges_floor_test

}	// namespace hamon_cmath_test
