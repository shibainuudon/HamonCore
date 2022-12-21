/**
 *	@file	unit_test_cmath_ranges_trunc.cpp
 *
 *	@brief	ranges::trunc のテスト
 */

#include <hamon/cmath/ranges/trunc.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_trunc_test
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
HAMON_CXX11_CONSTEXPR Real<T> trunc(Real<T> const& r)
{
	return Real<T>{ hamon::trunc(r.value) };
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	trunc(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::trunc(v.x),
			hamon::trunc(v.y),
			hamon::trunc(v.z),
		};
	}
};

template <typename T>
void RangesTruncTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0}, hamon::ranges::trunc(T{ 0.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0}, hamon::ranges::trunc(T{ 0.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0}, hamon::ranges::trunc(T{ 0.5f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0}, hamon::ranges::trunc(T{ 0.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0}, hamon::ranges::trunc(T{ 1.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0}, hamon::ranges::trunc(T{ 1.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0}, hamon::ranges::trunc(T{ 1.5f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0}, hamon::ranges::trunc(T{ 1.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 2.0}, hamon::ranges::trunc(T{ 2.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 2.0}, hamon::ranges::trunc(T{ 2.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 2.0}, hamon::ranges::trunc(T{ 2.5f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 2.0}, hamon::ranges::trunc(T{ 2.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 3.0}, hamon::ranges::trunc(T{ 3.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0}, hamon::ranges::trunc(T{-0.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0}, hamon::ranges::trunc(T{-0.5f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0}, hamon::ranges::trunc(T{-0.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0}, hamon::ranges::trunc(T{-1.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0}, hamon::ranges::trunc(T{-1.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0}, hamon::ranges::trunc(T{-1.5f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0}, hamon::ranges::trunc(T{-1.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-2.0}, hamon::ranges::trunc(T{-2.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-2.0}, hamon::ranges::trunc(T{-2.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-2.0}, hamon::ranges::trunc(T{-2.5f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-2.0}, hamon::ranges::trunc(T{-2.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-3.0}, hamon::ranges::trunc(T{-3.0f}));
}

template <typename T>
void RangesTruncTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -0.9f, -1.0f, -1.1f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::trunc(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0, v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 0.9f, 1.0f, 1.1f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::trunc(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0, v2.z);
	}
}

GTEST_TEST(CMathTest, RangesTruncTest)
{
	RangesTruncTest<float>();
	RangesTruncTest<double>();
	RangesTruncTest<long double>();

	RangesTruncTest<Real<float>>();
	RangesTruncTest<Real<double>>();
	RangesTruncTest<Real<long double>>();

	RangesTruncTest2<float>();
	RangesTruncTest2<double>();
	RangesTruncTest2<long double>();
}

}	// namespace ranges_trunc_test

}	// namespace hamon_cmath_test
