/**
 *	@file	unit_test_cmath_ranges_isfinite.cpp
 *
 *	@brief	ranges::isfinite のテスト
 */

#include <hamon/cmath/ranges/isfinite.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_isfinite_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR bool isfinite(Real<T> const& r)
{
	return hamon::isfinite(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<bool>
	isfinite(Vector3<T> const& v)
	{
		return Vector3<bool>
		{
			hamon::isfinite(v.x),
			hamon::isfinite(v.y),
			hamon::isfinite(v.z),
		};
	}
};

template <typename T, typename U = T>
void RangesIsFiniteTest(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = hamon::numeric_limits<U>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = hamon::numeric_limits<U>::infinity();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<U>::min();
	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<U>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<U>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isfinite(T{ inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isfinite(T{-inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isfinite(T{ nan}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isfinite(T{-nan}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::isfinite(T{-1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::isfinite(T{ 0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::isfinite(T{ 1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::isfinite(T{min}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::isfinite(T{max}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::isfinite(T{lowest}));
}

template <typename T>
void RangesIsFiniteTest2(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 0, 0.5 };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::isfinite(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { nan, max, -inf };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::isfinite(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { min, inf, lowest };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::isfinite(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v2.z);
	}
}

GTEST_TEST(CMathTest, RangesIsFiniteTest)
{
	RangesIsFiniteTest<float>();
	RangesIsFiniteTest<double>();
	RangesIsFiniteTest<long double>();

	RangesIsFiniteTest<Real<float>, float>();
	RangesIsFiniteTest<Real<double>, double>();
	RangesIsFiniteTest<Real<long double>, long double>();

	RangesIsFiniteTest2<float>();
	RangesIsFiniteTest2<double>();
	RangesIsFiniteTest2<long double>();
}

}	// namespace ranges_isfinite_test

}	// namespace hamon_cmath_test
