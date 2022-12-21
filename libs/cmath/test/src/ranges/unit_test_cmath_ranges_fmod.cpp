/**
 *	@file	unit_test_cmath_ranges_fmod.cpp
 *
 *	@brief	ranges::fmod のテスト
 */

#include <hamon/cmath/ranges/fmod.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_fmod_test
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
HAMON_CXX11_CONSTEXPR Real<T> fmod(Real<T> const& x, Real<T> const& y)
{
	return Real<T>{ hamon::fmod(x.value, y.value) };
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	fmod(Vector3<T> const& v1, Vector3<T> const& v2)
	{
		return Vector3<T>
		{
			hamon::fmod(v1.x, v2.x),
			hamon::fmod(v1.y, v2.y),
			hamon::fmod(v1.z, v2.z),
		};
	}
};

template <typename T>
void RangesFmodTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 2.5}, hamon::ranges::fmod(T{ 5.5}, T{ 3.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-2.5}, hamon::ranges::fmod(T{-5.5}, T{ 3.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 2.5}, hamon::ranges::fmod(T{ 5.5}, T{-3.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-2.5}, hamon::ranges::fmod(T{-5.5}, T{-3.0}));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.5}, hamon::ranges::fmod(T{ 5.5}, T{ 2.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-0.5}, hamon::ranges::fmod(T{-5.5}, T{ 2.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.5}, hamon::ranges::fmod(T{ 5.5}, T{-2.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-0.5}, hamon::ranges::fmod(T{-5.5}, T{-2.5}));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0}, hamon::ranges::fmod(T{ 7.5}, T{ 2.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-0.0}, hamon::ranges::fmod(T{-7.5}, T{ 2.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0}, hamon::ranges::fmod(T{ 7.5}, T{-2.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-0.0}, hamon::ranges::fmod(T{-7.5}, T{-2.5}));
}

template <typename T>
void RangesFmodTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 5, -5,  5 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 { 3,  3, -3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v3 = hamon::ranges::fmod(v1, v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, v3.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-2, v3.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, v3.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -7,  7, -7 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 {  4, -4, -4 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v3 = hamon::ranges::fmod(v1, v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, v3.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3, v3.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, v3.z);
	}
}

GTEST_TEST(CMathTest, RangesFmodTest)
{
	RangesFmodTest<float>();
	RangesFmodTest<double>();
	RangesFmodTest<long double>();

	RangesFmodTest<Real<float>>();
	RangesFmodTest<Real<double>>();
	RangesFmodTest<Real<long double>>();

	RangesFmodTest2<float>();
	RangesFmodTest2<double>();
	RangesFmodTest2<long double>();
}

}	// namespace ranges_fmod_test

}	// namespace hamon_cmath_test
