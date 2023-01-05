/**
 *	@file	unit_test_cmath_ranges_isnan.cpp
 *
 *	@brief	ranges::isnan のテスト
 */

#include <hamon/cmath/ranges/isnan.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_isnan_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR bool isnan(Real<T> const& r)
{
	return hamon::isnan(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<bool>
	isnan(Vector3<T> const& v)
	{
		return Vector3<bool>
		{
			hamon::isnan(v.x),
			hamon::isnan(v.y),
			hamon::isnan(v.z),
		};
	}
};

template <typename T, typename U = T>
void RangesIsNanTest(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = std::numeric_limits<U>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = std::numeric_limits<U>::infinity();
	HAMON_CXX11_CONSTEXPR auto min    = std::numeric_limits<U>::min();
	HAMON_CXX11_CONSTEXPR auto max    = std::numeric_limits<U>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = std::numeric_limits<U>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isnan(T{ inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isnan(T{-inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::isnan(T{ nan}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::isnan(T{-nan}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isnan(T{-1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isnan(T{ 0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isnan(T{ 1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isnan(T{min}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isnan(T{max}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isnan(T{lowest}));
}

template <typename T>
void RangesIsNanTest2(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 0, 0.5 };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::isnan(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { nan, max, -inf };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::isnan(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { min, inf, lowest };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::isnan(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
}

GTEST_TEST(CMathTest, RangesIsNanTest)
{
	RangesIsNanTest<float>();
	RangesIsNanTest<double>();
	RangesIsNanTest<long double>();

	RangesIsNanTest<Real<float>, float>();
	RangesIsNanTest<Real<double>, double>();
	RangesIsNanTest<Real<long double>, long double>();

	RangesIsNanTest2<float>();
	RangesIsNanTest2<double>();
	RangesIsNanTest2<long double>();
}

}	// namespace ranges_isnan_test

}	// namespace hamon_cmath_test
