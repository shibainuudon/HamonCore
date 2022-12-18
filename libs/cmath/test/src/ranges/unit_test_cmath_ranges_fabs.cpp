/**
 *	@file	unit_test_cmath_ranges_fabs.cpp
 *
 *	@brief	ranges::fabs のテスト
 */

#include <hamon/cmath/ranges/fabs.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_fabs_test
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
HAMON_CXX11_CONSTEXPR Real<T> fabs(Real<T> const& r)
{
	return Real<T>{hamon::fabs(r.value)};
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	fabs(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::fabs(v.x),
			hamon::fabs(v.y),
			hamon::fabs(v.z),
		};
	}
};

template <typename T>
void RangesFabsTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1.0}, hamon::ranges::fabs(T{ 1.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1.0}, hamon::ranges::fabs(T{-1.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{3.5}, hamon::ranges::fabs(T{ 3.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{3.5}, hamon::ranges::fabs(T{-3.5}));
}

template <typename T>
void RangesFabsTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 2, -3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::fabs(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v2.z);
	}
}

GTEST_TEST(CMathTest, RangesFabsTest)
{
	RangesFabsTest<float>();
	RangesFabsTest<double>();
	RangesFabsTest<long double>();

	RangesFabsTest<Real<float>>();
	RangesFabsTest<Real<double>>();
	RangesFabsTest<Real<long double>>();

	RangesFabsTest2<float>();
	RangesFabsTest2<double>();
	RangesFabsTest2<long double>();
}

}	// namespace ranges_fabs_test

}	// namespace hamon_cmath_test
