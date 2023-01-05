/**
 *	@file	unit_test_cmath_ranges_sign.cpp
 *
 *	@brief	ranges::sign のテスト
 */

#include <hamon/cmath/ranges/sign.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_sign_test
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
HAMON_CXX11_CONSTEXPR Real<T> sign(Real<T> const& r)
{
	return Real<T>{ hamon::ranges::sign(r.value) };
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	sign(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::ranges::sign(v.x),
			hamon::ranges::sign(v.y),
			hamon::ranges::sign(v.z),
		};
	}
};

template <typename T>
void RangesSignTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0}, hamon::ranges::sign(T{ 0.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0}, hamon::ranges::sign(T{-0.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1}, hamon::ranges::sign(T{ 1.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1}, hamon::ranges::sign(T{-1.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1}, hamon::ranges::sign(T{ 2.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1}, hamon::ranges::sign(T{-2.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1}, hamon::ranges::sign(T{ 3.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1}, hamon::ranges::sign(T{-3.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1}, hamon::ranges::sign(T{ 0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1}, hamon::ranges::sign(T{-0.5}));
}

template <typename T>
void RangesSignTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 0, 0.5 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::sign(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1), v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 0, 2, -3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::sign(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1), v2.z);
	}
}

GTEST_TEST(CMathTest, RangesSignTest)
{
	RangesSignTest<float>();
	RangesSignTest<double>();
	RangesSignTest<long double>();

	RangesSignTest<Real<float>>();
	RangesSignTest<Real<double>>();
	RangesSignTest<Real<long double>>();

	RangesSignTest2<float>();
	RangesSignTest2<double>();
	RangesSignTest2<long double>();
}

}	// namespace ranges_sign_test

}	// namespace hamon_cmath_test
