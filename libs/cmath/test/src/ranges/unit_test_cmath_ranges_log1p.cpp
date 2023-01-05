/**
 *	@file	unit_test_cmath_ranges_log1p.cpp
 *
 *	@brief	ranges::log1p のテスト
 */

#include <hamon/cmath/ranges/log1p.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_log1p_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T log1p(Real<T> const& r)
{
	return hamon::log1p(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	log1p(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::log1p(v.x),
			hamon::log1p(v.y),
			hamon::log1p(v.z),
		};
	}
};

template <typename T>
struct log1p_error;

template <>
struct log1p_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000001;
};

template <>
struct log1p_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000000000001;
};

template <>
struct log1p_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000000000001;
};

template <typename T>
struct log1p_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = log1p_error<T>::value;
};

template <typename T>
void RangesLog1pTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = log1p_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.69314718055994530, (double)hamon::ranges::log1p(T{-0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.40546510810816438, (double)hamon::ranges::log1p(T{ 0.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.69314718055994530, (double)hamon::ranges::log1p(T{ 1.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.91629073187415506, (double)hamon::ranges::log1p(T{ 1.5}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.09861228866810969, (double)hamon::ranges::log1p(T{ 2.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.60943791243410037, (double)hamon::ranges::log1p(T{ 4.0}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.19722457733621938, (double)hamon::ranges::log1p(T{ 8.0}), error);
}

template <typename T>
void RangesLog1pTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = log1p_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 1, 2, 3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::log1p(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.69314718055994530, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.09861228866810969, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.3862943611198901,  (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesLog1pTest)
{
	RangesLog1pTest<float>();
	RangesLog1pTest<double>();
	RangesLog1pTest<long double>();

	RangesLog1pTest<Real<float>>();
	RangesLog1pTest<Real<double>>();
	RangesLog1pTest<Real<long double>>();

	RangesLog1pTest2<float>();
	RangesLog1pTest2<double>();
	RangesLog1pTest2<long double>();
}

}	// namespace ranges_log1p_test

}	// namespace hamon_cmath_test
