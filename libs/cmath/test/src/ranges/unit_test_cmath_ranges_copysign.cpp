/**
 *	@file	unit_test_cmath_ranges_copysign.cpp
 *
 *	@brief	ranges::copysign のテスト
 */

#include <hamon/cmath/ranges/copysign.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_copysign_test
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
HAMON_CXX11_CONSTEXPR Real<T> copysign(Real<T> const& x, Real<T> const& y)
{
	return Real<T>{hamon::copysign(x.value, y.value)};
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	copysign(Vector3<T> const& v1, Vector3<T> const& v2)
	{
		return Vector3<T>
		{
			hamon::copysign(v1.x, v2.x),
			hamon::copysign(v1.y, v2.y),
			hamon::copysign(v1.z, v2.z),
		};
	}
};

template <typename T>
void RangesCopysignTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0}, hamon::ranges::copysign(T{ 1.0}, T{+2.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0}, hamon::ranges::copysign(T{ 1.0}, T{-2.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 5.0}, hamon::ranges::copysign(T{-5.0}, T{+2.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-5.0}, hamon::ranges::copysign(T{-5.0}, T{-2.0}));
}

template <typename T>
void RangesCopysignTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 2, 3, -4 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 { 1, -1, 1 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v3 = hamon::ranges::copysign(v1, v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2, v3.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, v3.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, v3.z);
	}
}

GTEST_TEST(CMathTest, RangesCopysignTest)
{
	RangesCopysignTest<float>();
	RangesCopysignTest<double>();
	RangesCopysignTest<long double>();

	RangesCopysignTest<Real<float>>();
	RangesCopysignTest<Real<double>>();
	RangesCopysignTest<Real<long double>>();

	RangesCopysignTest2<float>();
	RangesCopysignTest2<double>();
	RangesCopysignTest2<long double>();
}

}	// namespace ranges_copysign_test

}	// namespace hamon_cmath_test
