/**
 *	@file	unit_test_cmath_ranges_log10.cpp
 *
 *	@brief	ranges::log10 のテスト
 */

#include <hamon/cmath/ranges/log10.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_log10_test
{

template <typename T>
struct Real
{
	T value;

	template <typename U>
	HAMON_CXX11_CONSTEXPR Real(U v) : value(static_cast<T>(v)) {}
};

template <typename T>
HAMON_CXX11_CONSTEXPR T log10(Real<T> const& r)
{
	return hamon::log10(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	log10(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::log10(v.x),
			hamon::log10(v.y),
			hamon::log10(v.z),
		};
	}
};

template <typename T>
struct log10_error;

template <>
struct log10_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000001;
};

template <>
struct log10_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000000000001;
};

template <>
struct log10_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000000000001;
};

template <typename T>
struct log10_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = log10_error<T>::value;
};

template <typename T>
void RangesLog10Test(void)
{
	HAMON_CXX11_CONSTEXPR double error = log10_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-3.0,                  (double)hamon::ranges::log10(T(   0.001)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.0,                  (double)hamon::ranges::log10(T(   0.01)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0,                  (double)hamon::ranges::log10(T(   0.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.301029995663981195, (double)hamon::ranges::log10(T(   0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0,                  (double)hamon::ranges::log10(T(   1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.301029995663981195, (double)hamon::ranges::log10(T(   2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.477121254719662437, (double)hamon::ranges::log10(T(   3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.954242509439324875, (double)hamon::ranges::log10(T(   9.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0,                  (double)hamon::ranges::log10(T(  10.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0,                  (double)hamon::ranges::log10(T( 100.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0,                  (double)hamon::ranges::log10(T(1000.0)), error);
}

template <typename T>
void RangesLog10Test2(void)
{
	HAMON_CXX11_CONSTEXPR double error = log10_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { T(0.1), 2, 10 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::log10(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0,                  (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.301029995663981195, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0,                  (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesLog10Test)
{
	RangesLog10Test<float>();
	RangesLog10Test<double>();
	RangesLog10Test<long double>();

	RangesLog10Test<Real<float>>();
	RangesLog10Test<Real<double>>();
	RangesLog10Test<Real<long double>>();

	RangesLog10Test2<float>();
	RangesLog10Test2<double>();
	RangesLog10Test2<long double>();
}

}	// namespace ranges_log10_test

}	// namespace hamon_cmath_test
