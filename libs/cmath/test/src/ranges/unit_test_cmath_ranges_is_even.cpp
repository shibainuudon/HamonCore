/**
 *	@file	unit_test_cmath_ranges_is_even.cpp
 *
 *	@brief	ranges::is_even のテスト
 */

#include <hamon/cmath/ranges/is_even.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_is_even_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR bool is_even(Real<T> const& r)
{
	return hamon::is_even(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<bool>
	is_even(Vector3<T> const& v)
	{
		return Vector3<bool>
		{
			hamon::is_even(v.x),
			hamon::is_even(v.y),
			hamon::is_even(v.z),
		};
	}
};

template <typename T, typename U = T>
void RangesIsEvenTest(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<U>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<U>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-4.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::is_even(T{-4.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-3.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-3.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-3.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-2.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-2.2f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-2.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::is_even(T{-2.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-1.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-1.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-1.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-0.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-0.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::is_even(T{-0.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::is_even(T{ 0.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ 0.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ 0.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ 1.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ 1.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ 1.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::is_even(T{ 2.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ 2.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ 2.2f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ 2.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ 3.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ 3.1f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ 3.9f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::ranges::is_even(T{ 4.0f}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ 4.1f}));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ nan}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-nan}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{ inf}));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::ranges::is_even(T{-inf}));
}

template <typename T>
void RangesIsEvenTest2(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 0.0f, 0.1f, 0.2f };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::is_even(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 0, 0.5 };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::is_even(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { nan, inf, -inf };
		HAMON_CXX11_CONSTEXPR Vector3<bool> v2 = hamon::ranges::is_even(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.x);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.y);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(v2.z);
	}
}

GTEST_TEST(CMathTest, RangesIsEvenTest)
{
	RangesIsEvenTest<float>();
	RangesIsEvenTest<double>();
	RangesIsEvenTest<long double>();

	RangesIsEvenTest<Real<float>, float>();
	RangesIsEvenTest<Real<double>, double>();
	RangesIsEvenTest<Real<long double>, long double>();

	RangesIsEvenTest2<float>();
	RangesIsEvenTest2<double>();
	RangesIsEvenTest2<long double>();
}

}	// namespace ranges_is_even_test

}	// namespace hamon_cmath_test
