/**
 *	@file	unit_test_cmath_ranges_round_half_even.cpp
 *
 *	@brief	ranges::round_half_even のテスト
 */

#include <hamon/cmath/ranges/round_half_even.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_round_half_even_test
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
HAMON_CXX11_CONSTEXPR Real<T> round_half_even(Real<T> const& r)
{
	return Real<T>{ hamon::round_half_even(r.value) };
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	round_half_even(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::round_half_even(v.x),
			hamon::round_half_even(v.y),
			hamon::round_half_even(v.z),
		};
	}
};

template <typename T>
void RangesRoundHalfEvenTest(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-2.0},  hamon::ranges::round_half_even(T{-1.50001f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-2.0},  hamon::ranges::round_half_even(T{-1.50000f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0},  hamon::ranges::round_half_even(T{-1.49999f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{-1.0},  hamon::ranges::round_half_even(T{-0.50001f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0},  hamon::ranges::round_half_even(T{-0.50000f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0},  hamon::ranges::round_half_even(T{-0.49999f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0},  hamon::ranges::round_half_even(T{-0.00001f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0},  hamon::ranges::round_half_even(T{ 0.00000f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0},  hamon::ranges::round_half_even(T{ 0.00001f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0},  hamon::ranges::round_half_even(T{ 0.49999f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 0.0},  hamon::ranges::round_half_even(T{ 0.50000f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0},  hamon::ranges::round_half_even(T{ 0.50001f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 1.0},  hamon::ranges::round_half_even(T{ 1.49999f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 2.0},  hamon::ranges::round_half_even(T{ 1.50000f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T{ 2.0},  hamon::ranges::round_half_even(T{ 1.50001f}));
}

template <typename T>
void RangesRoundHalfEvenTest2(void)
{
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 2.4f, 2.5f, 2.6f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::round_half_even(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -3.4f, -3.5f, -3.6f };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::round_half_even(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-3, v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4, v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-4, v2.z);
	}
}

GTEST_TEST(CMathTest, RangesRoundHalfEvenTest)
{
	RangesRoundHalfEvenTest<float>();
	RangesRoundHalfEvenTest<double>();
	RangesRoundHalfEvenTest<long double>();

	RangesRoundHalfEvenTest<Real<float>>();
	RangesRoundHalfEvenTest<Real<double>>();
	RangesRoundHalfEvenTest<Real<long double>>();

	RangesRoundHalfEvenTest2<float>();
	RangesRoundHalfEvenTest2<double>();
	RangesRoundHalfEvenTest2<long double>();
}

}	// namespace ranges_round_half_even_test

}	// namespace hamon_cmath_test
