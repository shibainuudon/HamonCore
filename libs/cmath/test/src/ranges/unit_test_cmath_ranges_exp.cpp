/**
 *	@file	unit_test_cmath_ranges_exp.cpp
 *
 *	@brief	ranges::exp のテスト
 */

#include <hamon/cmath/ranges/exp.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_exp_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T exp(Real<T> const& r)
{
	return hamon::exp(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	exp(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::exp(v.x),
			hamon::exp(v.y),
			hamon::exp(v.z),
		};
	}
};

template <typename T>
struct exp_error;

template <>
struct exp_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00001;
};

template <>
struct exp_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000000000001;
};

template <>
struct exp_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000000000001;
};

template <typename T>
struct exp_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = exp_error<T>::value;
};

template <typename T>
void RangesExpTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = exp_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0000000000000000, (double)hamon::ranges::exp(T{+0.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0000000000000000, (double)hamon::ranges::exp(T{-0.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.2840254166877414, (double)hamon::ranges::exp(T{ 0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.6487212707001282, (double)hamon::ranges::exp(T{ 0.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.1170000166126748, (double)hamon::ranges::exp(T{ 0.75}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.7182818284590451, (double)hamon::ranges::exp(T{ 1.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.4816890703380645, (double)hamon::ranges::exp(T{ 1.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(7.3890560989306504, (double)hamon::ranges::exp(T{ 2.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(12.182493960703473, (double)hamon::ranges::exp(T{ 2.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(20.085536923187668, (double)hamon::ranges::exp(T{ 3.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(33.115451958692312, (double)hamon::ranges::exp(T{ 3.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(7.7880078307140488e-01, (double)hamon::ranges::exp(T{-0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(6.0653065971263342e-01, (double)hamon::ranges::exp(T{-0.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.7236655274101469e-01, (double)hamon::ranges::exp(T{-0.75}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.6787944117144233e-01, (double)hamon::ranges::exp(T{-1.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.2313016014842982e-01, (double)hamon::ranges::exp(T{-1.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.3533528323661270e-01, (double)hamon::ranges::exp(T{-2.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(8.2084998623898800e-02, (double)hamon::ranges::exp(T{-2.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.9787068367863944e-02, (double)hamon::ranges::exp(T{-3.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.0197383422318501e-02, (double)hamon::ranges::exp(T{-3.50}), error);
}

template <typename T>
void RangesExpTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = exp_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 0, 1 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::exp(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.3678794411714423, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0000000000000000, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.7182818284590451, (double)v2.z, error);
	}
	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { 2, 2.5, 3 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::exp(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(7.3890560989306504, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(12.182493960703473, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(20.085536923187668, (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesExpTest)
{
	RangesExpTest<float>();
	RangesExpTest<double>();
	RangesExpTest<long double>();

	RangesExpTest<Real<float>>();
	RangesExpTest<Real<double>>();
	RangesExpTest<Real<long double>>();

	RangesExpTest2<float>();
	RangesExpTest2<double>();
	RangesExpTest2<long double>();
}

}	// namespace ranges_exp_test

}	// namespace hamon_cmath_test
