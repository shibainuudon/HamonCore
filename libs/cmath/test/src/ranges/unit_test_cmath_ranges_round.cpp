/**
 *	@file	unit_test_cmath_ranges_round.cpp
 *
 *	@brief	ranges::round のテスト
 */

#include <hamon/cmath/ranges/round.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_round_test
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
HAMON_CXX11_CONSTEXPR Real<T> round(Real<T> const& r)
{
	return Real<T>{ hamon::round(r.value) };
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	round(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::round(v.x),
			hamon::round(v.y),
			hamon::round(v.z),
		};
	}
};

template <typename T>
void RangesRoundTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-2.0},  hamon::ranges::round(T{-1.50001f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-2.0},  hamon::ranges::round(T{-1.50000f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0},  hamon::ranges::round(T{-1.49999f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0},  hamon::ranges::round(T{-0.50001f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0},  hamon::ranges::round(T{-0.50000f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0},  hamon::ranges::round(T{-0.49999f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0},  hamon::ranges::round(T{-0.00001f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0},  hamon::ranges::round(T{ 0.00000f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0},  hamon::ranges::round(T{ 0.00001f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0},  hamon::ranges::round(T{ 0.49999f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0},  hamon::ranges::round(T{ 0.50000f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0},  hamon::ranges::round(T{ 0.50001f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0},  hamon::ranges::round(T{ 1.49999f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 2.0},  hamon::ranges::round(T{ 1.50000f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 2.0},  hamon::ranges::round(T{ 1.50001f}));
}

template <typename T>
void RangesRoundTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 2.4f, 2.5f, 2.6f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::round(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -3.4f, -3.5f, -3.6f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::round(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4, v2.z);
	}
}

GTEST_TEST(CMathTest, RangesRoundTest)
{
	RangesRoundTest<float>();
	RangesRoundTest<double>();
	RangesRoundTest<long double>();

	RangesRoundTest<Real<float>>();
	RangesRoundTest<Real<double>>();
	RangesRoundTest<Real<long double>>();

	RangesRoundTest2<float>();
	RangesRoundTest2<double>();
	RangesRoundTest2<long double>();
}

}	// namespace ranges_round_test

}	// namespace hamon_cmath_test
