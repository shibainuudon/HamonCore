/**
 *	@file	unit_test_cmath_ranges_log.cpp
 *
 *	@brief	ranges::log のテスト
 */

#include <hamon/cmath/ranges/log.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_log_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T log(Real<T> const& r)
{
	return hamon::log(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	log(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::log(v.x),
			hamon::log(v.y),
			hamon::log(v.z),
		};
	}
};

template <typename T>
struct log_error;

template <>
struct log_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000001;
};

template <>
struct log_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000000000001;
};

template <>
struct log_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000000000001;
};

template <typename T>
struct log_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = log_error<T>::value;
};

template <typename T>
void RangesLogTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = log_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.38629436111989, (double)hamon::ranges::log(T{0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.69314718055995, (double)hamon::ranges::log(T{0.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.28768207245178, (double)hamon::ranges::log(T{0.75}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000, (double)hamon::ranges::log(T{1.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.22314355131421, (double)hamon::ranges::log(T{1.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.40546510810816, (double)hamon::ranges::log(T{1.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.69314718055994, (double)hamon::ranges::log(T{2.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.09861228866810, (double)hamon::ranges::log(T{3.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.38629436111989, (double)hamon::ranges::log(T{4.00}), error);
}

template <typename T>
void RangesLogTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = log_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 1, 2, 3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::log(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00000000000000, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.69314718055994, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.09861228866810, (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesLogTest)
{
	RangesLogTest<float>();
	RangesLogTest<double>();
	RangesLogTest<long double>();

	RangesLogTest<Real<float>>();
	RangesLogTest<Real<double>>();
	RangesLogTest<Real<long double>>();

	RangesLogTest2<float>();
	RangesLogTest2<double>();
	RangesLogTest2<long double>();
}

}	// namespace ranges_log_test

}	// namespace hamon_cmath_test
