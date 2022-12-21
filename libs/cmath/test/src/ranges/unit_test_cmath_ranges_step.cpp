/**
 *	@file	unit_test_cmath_ranges_step.cpp
 *
 *	@brief	ranges::step のテスト
 */

#include <hamon/cmath/ranges/step.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_step_test
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
HAMON_CXX11_CONSTEXPR Real<T> step(Real<T> const& x, Real<T> const& y)
{
	return Real<T>{ hamon::step(x.value, y.value) };
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	step(Vector3<T> const& v1, Vector3<T> const& v2)
	{
		return Vector3<T>
		{
			hamon::step(v1.x, v2.x),
			hamon::step(v1.y, v2.y),
			hamon::step(v1.z, v2.z),
		};
	}
};

template <typename T>
void RangesStepTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1}, hamon::ranges::step(T{0.0}, T{ 0.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0}, hamon::ranges::step(T{0.0}, T{-1.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1}, hamon::ranges::step(T{0.0}, T{ 1.0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0}, hamon::ranges::step(T{0.0}, T{-0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1}, hamon::ranges::step(T{0.0}, T{ 0.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0}, hamon::ranges::step(T{0.0}, T{-0.00001f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1}, hamon::ranges::step(T{0.0}, T{ 0.00001f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{0}, hamon::ranges::step(T{0.0}, T{-9999999}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{1}, hamon::ranges::step(T{0.0}, T{ 9999999}));
}

template <typename T>
void RangesStepTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 0, 1, 2 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 { -1, 1, 3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v3 = hamon::ranges::step(v1, v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0, v3.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v3.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, v3.z);
	}
}

GTEST_TEST(CMathTest, RangesStepTest)
{
	RangesStepTest<float>();
	RangesStepTest<double>();
	RangesStepTest<long double>();

	RangesStepTest<Real<float>>();
	RangesStepTest<Real<double>>();
	RangesStepTest<Real<long double>>();

	RangesStepTest2<float>();
	RangesStepTest2<double>();
	RangesStepTest2<long double>();
}

}	// namespace ranges_step_test

}	// namespace hamon_cmath_test
