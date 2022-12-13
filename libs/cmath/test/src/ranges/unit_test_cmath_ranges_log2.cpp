/**
 *	@file	unit_test_cmath_ranges_log2.cpp
 *
 *	@brief	ranges::log2 のテスト
 */

#include <hamon/cmath/ranges/log2.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_log2_test
{

template <typename T>
struct Real
{
	T value;

	template <typename U>
	HAMON_CXX11_CONSTEXPR Real(U v) : value(static_cast<T>(v)) {}
};

template <typename T>
HAMON_CXX11_CONSTEXPR T log2(Real<T> const& r)
{
	return hamon::log2(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	log2(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::log2(v.x),
			hamon::log2(v.y),
			hamon::log2(v.z),
		};
	}
};

template <typename T>
struct log2_error;

template <>
struct log2_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000001;
};

template <>
struct log2_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <>
struct log2_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <typename T>
struct log2_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = log2_error<T>::value;
};

template <typename T>
void RangesLog2Test(void)
{
	HAMON_CXX11_CONSTEXPR double error = log2_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-3.0000000000000000, (double)hamon::ranges::log2(T(0.125)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.0000000000000000, (double)hamon::ranges::log2(T(0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0000000000000000, (double)hamon::ranges::log2(T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000, (double)hamon::ranges::log2(T(1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0000000000000000, (double)hamon::ranges::log2(T(2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5849625007211561, (double)hamon::ranges::log2(T(3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0000000000000000, (double)hamon::ranges::log2(T(4.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.3219280948873622, (double)hamon::ranges::log2(T(5.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0000000000000000, (double)hamon::ranges::log2(T(8.0)), error);
}

template <typename T>
void RangesLog2Test2(void)
{
	HAMON_CXX11_CONSTEXPR double error = log2_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 1, 2, 4 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::log2(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0, (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesLog2Test)
{
	RangesLog2Test<float>();
	RangesLog2Test<double>();
	RangesLog2Test<long double>();

	RangesLog2Test<Real<float>>();
	RangesLog2Test<Real<double>>();
	RangesLog2Test<Real<long double>>();

	RangesLog2Test2<float>();
	RangesLog2Test2<double>();
	RangesLog2Test2<long double>();
}

}	// namespace ranges_log2_test

}	// namespace hamon_cmath_test
