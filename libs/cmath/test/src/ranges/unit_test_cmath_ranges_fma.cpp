/**
 *	@file	unit_test_cmath_ranges_fma.cpp
 *
 *	@brief	ranges::fma のテスト
 */

#include <hamon/cmath/ranges/fma.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_fma_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T fma(Real<T> const& x, Real<T> const& y, Real<T> const& z)
{
	return hamon::fma(x.value, y.value, z.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	fma(Vector3<T> const& v1, Vector3<T> const& v2, Vector3<T> const& v3)
	{
		return Vector3<T>
		{
			hamon::fma(v1.x, v2.x, v3.x),
			hamon::fma(v1.y, v2.y, v3.y),
			hamon::fma(v1.z, v2.z, v3.z),
		};
	}
};

template <typename T>
void RangesFmaTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, hamon::ranges::fma(T{ 0.0}, T{ 0.0}, T{ 0.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::ranges::fma(T{ 0.0}, T{ 0.0}, T{ 0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::ranges::fma(T{ 0.0}, T{ 0.0}, T{-0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::ranges::fma(T{ 0.0}, T{ 2.5}, T{ 0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::ranges::fma(T{ 0.0}, T{ 2.5}, T{-0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.5, hamon::ranges::fma(T{ 0.0}, T{-2.5}, T{ 0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-0.5, hamon::ranges::fma(T{ 0.0}, T{-2.5}, T{-0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3.0, hamon::ranges::fma(T{ 1.0}, T{ 2.5}, T{ 0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2.0, hamon::ranges::fma(T{ 1.0}, T{ 2.5}, T{-0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2.0, hamon::ranges::fma(T{ 1.0}, T{-2.5}, T{ 0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3.0, hamon::ranges::fma(T{ 1.0}, T{-2.5}, T{-0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-6.0, hamon::ranges::fma(T{-3.0}, T{ 2.5}, T{ 1.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-9.0, hamon::ranges::fma(T{-3.0}, T{ 2.5}, T{-1.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 9.0, hamon::ranges::fma(T{-3.0}, T{-2.5}, T{ 1.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6.0, hamon::ranges::fma(T{-3.0}, T{-2.5}, T{-1.5}));
}

template <typename T>
void RangesFmaTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 1, 2, 3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 { 4, 5, 6 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v3 { 7, 8, 9 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v4 = hamon::ranges::fma(v1, v2, v3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, v4.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(18, v4.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(27, v4.z);
	}
}

GTEST_TEST(CMathTest, RangesFmaTest)
{
	RangesFmaTest<float>();
	RangesFmaTest<double>();
	RangesFmaTest<long double>();

	RangesFmaTest<Real<float>>();
	RangesFmaTest<Real<double>>();
	RangesFmaTest<Real<long double>>();

	RangesFmaTest2<float>();
	RangesFmaTest2<double>();
	RangesFmaTest2<long double>();
}

}	// namespace ranges_fma_test

}	// namespace hamon_cmath_test
