/**
 *	@file	unit_test_cmath_ranges_iszero.cpp
 *
 *	@brief	ranges::iszero のテスト
 */

#include <hamon/cmath/ranges/iszero.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_iszero_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR bool iszero(Real<T> const& r)
{
	return hamon::iszero(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<bool>
	iszero(Vector3<T> const& v)
	{
		return Vector3<bool>
		{
			hamon::iszero(v.x),
			hamon::iszero(v.y),
			hamon::iszero(v.z),
		};
	}
};

template <typename T, typename U = T>
void RangesIsZeroTest(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = hamon::numeric_limits<U>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = hamon::numeric_limits<U>::infinity();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<U>::min();
	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<U>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<U>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::iszero(T{ inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::iszero(T{-inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::iszero(T{ nan}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::iszero(T{-nan}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::iszero(T{-1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::iszero(T{ 0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::iszero(T{ 1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::iszero(T{min}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::iszero(T{max}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::iszero(T{lowest}));
}

template <typename T>
void RangesIsZeroTest2(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 0, 0.5 };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::iszero(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { nan, max, -inf };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::iszero(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { min, inf, lowest };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::iszero(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
}

GTEST_TEST(CMathTest, RangesIsZeroTest)
{
	RangesIsZeroTest<float>();
	RangesIsZeroTest<double>();
	RangesIsZeroTest<long double>();

	RangesIsZeroTest<Real<float>, float>();
	RangesIsZeroTest<Real<double>, double>();
	RangesIsZeroTest<Real<long double>, long double>();

	RangesIsZeroTest2<float>();
	RangesIsZeroTest2<double>();
	RangesIsZeroTest2<long double>();
}

}	// namespace ranges_iszero_test

}	// namespace hamon_cmath_test
