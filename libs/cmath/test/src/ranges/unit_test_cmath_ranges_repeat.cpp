/**
 *	@file	unit_test_cmath_ranges_repeat.cpp
 *
 *	@brief	ranges::repeat のテスト
 */

#include <hamon/cmath/ranges/repeat.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_repeat_test
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
HAMON_CXX11_CONSTEXPR Real<T> repeat(Real<T> const& x, Real<T> const& y, Real<T> const& z)
{
	return Real<T>{ hamon::repeat(x.value, y.value, z.value) };
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	repeat(Vector3<T> const& v1, Vector3<T> const& v2, Vector3<T> const& v3)
	{
		return Vector3<T>
		{
			hamon::repeat(v1.x, v2.x, v3.x),
			hamon::repeat(v1.y, v2.y, v3.y),
			hamon::repeat(v1.z, v2.z, v3.z),
		};
	}
};

template <typename T>
void RangesRepeatTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0}, hamon::ranges::repeat(T{ 0}, T{0}, T{3}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1}, hamon::ranges::repeat(T{ 1}, T{0}, T{3}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{2}, hamon::ranges::repeat(T{ 2}, T{0}, T{3}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0}, hamon::ranges::repeat(T{ 3}, T{0}, T{3}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1}, hamon::ranges::repeat(T{ 4}, T{0}, T{3}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{2}, hamon::ranges::repeat(T{ 5}, T{0}, T{3}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0}, hamon::ranges::repeat(T{ 6}, T{0}, T{3}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1}, hamon::ranges::repeat(T{ 7}, T{0}, T{3}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{2}, hamon::ranges::repeat(T{ 8}, T{0}, T{3}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0}, hamon::ranges::repeat(T{ 9}, T{0}, T{3}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1}, hamon::ranges::repeat(T{10}, T{0}, T{3}));
}

template <typename T>
void RangesRepeatTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 {  9, 10, 11 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 { 10, 10, 10 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v3 { 20, 20, 20 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v4 = hamon::ranges::repeat(v1, v2, v3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19, v4.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, v4.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11, v4.z);
	}
}

GTEST_TEST(CMathTest, RangesRepeatTest)
{
	RangesRepeatTest<float>();
	RangesRepeatTest<double>();
	RangesRepeatTest<long double>();

	RangesRepeatTest<Real<float>>();
	RangesRepeatTest<Real<double>>();
	RangesRepeatTest<Real<long double>>();

	RangesRepeatTest2<float>();
	RangesRepeatTest2<double>();
	RangesRepeatTest2<long double>();
}

}	// namespace ranges_repeat_test

}	// namespace hamon_cmath_test
