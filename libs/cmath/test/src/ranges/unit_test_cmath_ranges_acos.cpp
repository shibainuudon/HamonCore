/**
 *	@file	unit_test_cmath_ranges_acos.cpp
 *
 *	@brief	ranges::acos のテスト
 */

#include <hamon/cmath/ranges/acos.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ranges_acos_test
{

template <typename T>
struct Real
{
	T value;
};

template <typename T>
HAMON_CXX11_CONSTEXPR T acos(Real<T> const& r)
{
	return hamon::acos(r.value);
}

template <typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	friend HAMON_CXX11_CONSTEXPR Vector3<T>
	acos(Vector3<T> const& v)
	{
		return Vector3<T>
		{
			hamon::acos(v.x),
			hamon::acos(v.y),
			hamon::acos(v.z),
		};
	}
};

template <typename T>
struct acos_error;

template <>
struct acos_error<float>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.000001;
};

template <>
struct acos_error<double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <>
struct acos_error<long double>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = 0.00000000001;
};

template <typename T>
struct acos_error<Real<T>>
{
	HAMON_CXX11_STATIC_CONSTEXPR double value = acos_error<T>::value;
};

template <typename T>
void RangesAcosTest(void)
{
	HAMON_CXX11_CONSTEXPR double error = acos_error<T>::value;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.141592653590, (double)hamon::ranges::acos(T{-1.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.418858405776, (double)hamon::ranges::acos(T{-0.75}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.094395102393, (double)hamon::ranges::acos(T{-0.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.823476581937, (double)hamon::ranges::acos(T{-0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.570796326795, (double)hamon::ranges::acos(T{ 0.00}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.318116071653, (double)hamon::ranges::acos(T{ 0.25}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.047197551197, (double)hamon::ranges::acos(T{ 0.50}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.722734247813, (double)hamon::ranges::acos(T{ 0.75}), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.000000000000, (double)hamon::ranges::acos(T{ 1.00}), error);
}

template <typename T>
void RangesAcosTest2(void)
{
	HAMON_CXX11_CONSTEXPR double error = acos_error<T>::value;

	{
		HAMON_CXX11_CONSTEXPR Vector3<T> v1 { -1, 0, 0.5 };
		HAMON_CXX11_CONSTEXPR Vector3<T> v2 = hamon::ranges::acos(v1);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.141592653590, (double)v2.x, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.570796326795, (double)v2.y, error);
		HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.047197551197, (double)v2.z, error);
	}
}

GTEST_TEST(CMathTest, RangesAcosTest)
{
	RangesAcosTest<float>();
	RangesAcosTest<double>();
	RangesAcosTest<long double>();

	RangesAcosTest<Real<float>>();
	RangesAcosTest<Real<double>>();
	RangesAcosTest<Real<long double>>();

	RangesAcosTest2<float>();
	RangesAcosTest2<double>();
	RangesAcosTest2<long double>();
}

}	// namespace ranges_acos_test

}	// namespace hamon_cmath_test
