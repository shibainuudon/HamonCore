/**
 *	@file	unit_test_cmath_ranges_round_down.cpp
 *
 *	@brief	ranges::round_down のテスト
 */

#include <hamon/cmath/ranges/round_down.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_round_down_test
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
HAMON_CXX11_CONSTEXPR Real<T> round_down(Real<T> const& x, Real<T> const& y)
{
	return Real<T>{ hamon::round_down(x.value, y.value) };
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	round_down(Vector3<T> const& v1, Vector3<T> const& v2)
	{
		return Vector3<T>
		{
			hamon::round_down(v1.x, v2.x),
			hamon::round_down(v1.y, v2.y),
			hamon::round_down(v1.z, v2.z),
		};
	}
};

template <typename T>
void RangesRoundDownTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-7.0}, hamon::ranges::round_down(T{-3.6f}, T{3.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-3.5}, hamon::ranges::round_down(T{-3.5f}, T{3.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-3.5}, hamon::ranges::round_down(T{-3.4f}, T{3.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-3.5}, hamon::ranges::round_down(T{-0.1f}, T{3.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0}, hamon::ranges::round_down(T{ 0.0f}, T{3.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0}, hamon::ranges::round_down(T{ 0.1f}, T{3.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0}, hamon::ranges::round_down(T{ 3.4f}, T{3.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 3.5}, hamon::ranges::round_down(T{ 3.5f}, T{3.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 3.5}, hamon::ranges::round_down(T{ 3.6f}, T{3.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 3.5}, hamon::ranges::round_down(T{ 6.9f}, T{3.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 7.0}, hamon::ranges::round_down(T{ 7.0f}, T{3.5}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 7.0}, hamon::ranges::round_down(T{ 7.1f}, T{3.5}));
}

template <typename T>
void RangesRoundDownTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 13, 13, 13 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 {  1,  2,  5 };
		HAMON_CXX11_CONSTEXPR auto v3 = hamon::ranges::round_down(v1, v2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{13}, v3.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{12}, v3.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{10}, v3.z);
	}
}

GTEST_TEST(CMathTest, RangesRoundDownTest)
{
	RangesRoundDownTest<float>();
	RangesRoundDownTest<double>();
	RangesRoundDownTest<long double>();

	RangesRoundDownTest<Real<float>>();
	RangesRoundDownTest<Real<double>>();
	RangesRoundDownTest<Real<long double>>();

	RangesRoundDownTest2<float>();
	RangesRoundDownTest2<double>();
	RangesRoundDownTest2<long double>();
}

}	// namespace ranges_round_down_test

}	// namespace hamon_cmath_test
