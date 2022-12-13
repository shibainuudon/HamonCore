/**
 *	@file	unit_test_cmath_ranges_ceil.cpp
 *
 *	@brief	ranges::ceil のテスト
 */

#include <hamon/cmath/ranges/ceil.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_ceil_test
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
HAMON_CXX11_CONSTEXPR Real<T> ceil(Real<T> const& r)
{
	return Real<T>{hamon::ceil(r.value)};
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	ceil(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::ceil(v.x),
			hamon::ceil(v.y),
			hamon::ceil(v.z),
		};
	}
};

template <typename T>
void RangesCeilTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0f}, hamon::ranges::ceil(T{-1.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0f}, hamon::ranges::ceil(T{-1.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0f}, hamon::ranges::ceil(T{-0.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0f}, hamon::ranges::ceil(T{-0.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0f}, hamon::ranges::ceil(T{ 0.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0f}, hamon::ranges::ceil(T{ 0.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0f}, hamon::ranges::ceil(T{ 0.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0f}, hamon::ranges::ceil(T{ 1.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 2.0f}, hamon::ranges::ceil(T{ 1.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{11.0f}, hamon::ranges::ceil(T{10.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{11.0f}, hamon::ranges::ceil(T{11.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{12.0f}, hamon::ranges::ceil(T{11.1f}));
}

template <typename T>
void RangesCeilTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 2.9f, 3.0f, 3.1f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::ceil(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{3.0}, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{3.0}, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{4.0}, v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -2.9f, -3.0f, -3.1f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::ceil(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-2.0}, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-3.0}, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-3.0}, v2.z);
	}
}

GTEST_TEST(CMathTest, RangesCeilTest)
{
	RangesCeilTest<float>();
	RangesCeilTest<double>();
	RangesCeilTest<long double>();

	RangesCeilTest<Real<float>>();
	RangesCeilTest<Real<double>>();
	RangesCeilTest<Real<long double>>();

	RangesCeilTest2<float>();
	RangesCeilTest2<double>();
	RangesCeilTest2<long double>();
}

}	// namespace ranges_ceil_test

}	// namespace hamon_cmath_test
