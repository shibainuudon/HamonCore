/**
 *	@file	unit_test_cmath_cos.cpp
 *
 *	@brief	cos のテスト
 */

#include <hamon/cmath/cos.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/numbers.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace cos_test
{

static_assert(hamon::is_same<float,       decltype(hamon::cos(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::cosf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::cos(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::cos(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::cos(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::cosl(0.0l))>::value, "");

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 0.000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 0.00000000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 0.00000000001;
}

template <typename T>
void CosTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.93645668729, (double)hamon::cos(T(-3.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.98999249660, (double)hamon::cos(T(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.80114361554, (double)hamon::cos(T(-2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.41614683654, (double)hamon::cos(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.07073720166, (double)hamon::cos(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.54030230586, (double)hamon::cos(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.87758256189, (double)hamon::cos(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::cos(T(-0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::cos(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.87758256189, (double)hamon::cos(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.54030230586, (double)hamon::cos(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.07073720166, (double)hamon::cos(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.41614683654, (double)hamon::cos(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.80114361554, (double)hamon::cos(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.98999249660, (double)hamon::cos(T( 3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.93645668729, (double)hamon::cos(T( 3.5)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0, (double)hamon::cos( hamon::numbers::pi_fn<T>()), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0, (double)hamon::cos(-hamon::numbers::pi_fn<T>()), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0, hamon::cos(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1.0, hamon::cos(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::cos( nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::cos(-nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::cos( inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::cos(-inf)));
}

template <typename T>
void CosTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, hamon::cos(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.54030230586, hamon::cos(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.54030230586, hamon::cos(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.41614683654, hamon::cos(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.41614683654, hamon::cos(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.98999249660, hamon::cos(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.98999249660, hamon::cos(T(-3)), error);
}

template <typename T>
void CosTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, hamon::cos(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.54030230586, hamon::cos(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.41614683654, hamon::cos(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.98999249660, hamon::cos(T( 3)), error);
}

GTEST_TEST(CMathTest, CosTest)
{
	CosTestFloat<float>();
	CosTestFloat<double>();
	CosTestFloat<long double>();

	CosTestSignedInt<int>();
	CosTestSignedInt<signed char>();
//	CosTestSignedInt<short>();
	CosTestSignedInt<long>();
//	CosTestSignedInt<long long>();

	CosTestUnsignedInt<unsigned int>();
//	CosTestUnsignedInt<unsigned char>();
	CosTestUnsignedInt<unsigned short>();
//	CosTestUnsignedInt<unsigned long>();
	CosTestUnsignedInt<unsigned long long>();
}

}	// namespace cos_test

}	// namespace hamon_cmath_test
