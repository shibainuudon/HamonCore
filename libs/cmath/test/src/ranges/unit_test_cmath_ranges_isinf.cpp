/**
 *	@file	unit_test_cmath_ranges_isinf.cpp
 *
 *	@brief	ranges::isinf のテスト
 */

#include <hamon/cmath/ranges/isinf.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_isinf_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR bool isinf(Real<T> const& r)
{
	return hamon::isinf(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<bool>
	isinf(Vector3<T> const& v)
	{
		return Vector3<bool>
		{
			hamon::isinf(v.x),
			hamon::isinf(v.y),
			hamon::isinf(v.z),
		};
	}
};

template <typename T, typename U = T>
void RangesIsInfTest(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = std::numeric_limits<U>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = std::numeric_limits<U>::infinity();
	HAMON_CXX11_CONSTEXPR auto min    = std::numeric_limits<U>::min();
	HAMON_CXX11_CONSTEXPR auto max    = std::numeric_limits<U>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = std::numeric_limits<U>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::isinf(T{ inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::isinf(T{-inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isinf(T{ nan}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isinf(T{-nan}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isinf(T{-1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isinf(T{ 0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isinf(T{ 1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isinf(T{min}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isinf(T{max}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::isinf(T{lowest}));
}

template <typename T>
void RangesIsInfTest2(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 0, 0.5 };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::isinf(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { nan, max, -inf };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::isinf(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { min, inf, lowest };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::isinf(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
}

GTEST_TEST(CMathTest, RangesIsInfTest)
{
	RangesIsInfTest<float>();
	RangesIsInfTest<double>();
	RangesIsInfTest<long double>();

	RangesIsInfTest<Real<float>, float>();
	RangesIsInfTest<Real<double>, double>();
	RangesIsInfTest<Real<long double>, long double>();

	RangesIsInfTest2<float>();
	RangesIsInfTest2<double>();
	RangesIsInfTest2<long double>();
}

}	// namespace ranges_isinf_test

}	// namespace hamon_cmath_test
