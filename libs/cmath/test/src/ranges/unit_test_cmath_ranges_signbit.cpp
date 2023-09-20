/**
 *	@file	unit_test_cmath_ranges_signbit.cpp
 *
 *	@brief	ranges::signbit のテスト
 */

#include <hamon/cmath/ranges/signbit.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_signbit_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR bool signbit(Real<T> const& r)
{
	return hamon::signbit(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<bool>
	signbit(Vector3<T> const& v)
	{
		return Vector3<bool>
		{
			hamon::signbit(v.x),
			hamon::signbit(v.y),
			hamon::signbit(v.z),
		};
	}
};

template <typename T, typename U = T>
void RangesSignbitTest(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = hamon::numeric_limits<U>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = hamon::numeric_limits<U>::infinity();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<U>::min();
	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<U>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<U>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::signbit(T{ inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::signbit(T{-inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::signbit(T{ nan}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::signbit(T{-nan}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::signbit(T{-1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::signbit(T{ 0}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::signbit(T{ 1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::signbit(T{min}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::signbit(T{max}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::signbit(T{lowest}));
}

template <typename T>
void RangesSignbitTest2(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 0, 0.5 };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::signbit(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { nan, max, -inf };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::signbit(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { min, inf, lowest };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::signbit(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v2.z);
	}
}

GTEST_TEST(CMathTest, RangesSignbitTest)
{
	RangesSignbitTest<float>();
	RangesSignbitTest<double>();
	RangesSignbitTest<long double>();

	RangesSignbitTest<Real<float>, float>();
	RangesSignbitTest<Real<double>, double>();
	RangesSignbitTest<Real<long double>, long double>();

	RangesSignbitTest2<float>();
	RangesSignbitTest2<double>();
	RangesSignbitTest2<long double>();
}

}	// namespace ranges_signbit_test

}	// namespace hamon_cmath_test
