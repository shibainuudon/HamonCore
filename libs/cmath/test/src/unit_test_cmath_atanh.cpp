/**
 *	@file	unit_test_cmath_atanh.cpp
 *
 *	@brief	atanh のテスト
 */

#include <hamon/cmath/atanh.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace atanh_test
{

static_assert(hamon::is_same<float,       decltype(hamon::atanh(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::atanhf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atanh(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atanh(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atanh(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atanhl(0.0l))>::value, "");

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 1e-6;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 1e-12;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 1e-12;
}

template <typename T>
void AtanhTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)hamon::atanh(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.1003353477310, (double)hamon::atanh(T( 0.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.2027325540540, (double)hamon::atanh(T( 0.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.3095196042031, (double)hamon::atanh(T( 0.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.5493061443340, (double)hamon::atanh(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4722194895832, (double)hamon::atanh(T( 0.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.6466524123622, (double)hamon::atanh(T( 0.99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.1003353477310, (double)hamon::atanh(T(-0.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.2027325540540, (double)hamon::atanh(T(-0.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.3095196042031, (double)hamon::atanh(T(-0.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.5493061443340, (double)hamon::atanh(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.4722194895832, (double)hamon::atanh(T(-0.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.6466524123622, (double)hamon::atanh(T(-0.99)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::atanh(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::atanh(T(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::atanh(T(+1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::atanh(T(-1.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atanh(T(+1.0) + eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atanh(T(-1.0) - eps)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atanh(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atanh(-nan)));
}

template <typename T>
void AtanhTestSignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::atanh(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::atanh(T(+1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::atanh(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atanh(T(+2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atanh(T(-2))));
}

template <typename T>
void AtanhTestUnsignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::atanh(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::atanh(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atanh(T(2))));
}

GTEST_TEST(CMathTest, AtanhTest)
{
	AtanhTestFloat<float>();
	AtanhTestFloat<double>();
	AtanhTestFloat<long double>();

	AtanhTestSignedInt<int>();
//	AtanhTestSignedInt<signed char>();
	AtanhTestSignedInt<short>();
//	AtanhTestSignedInt<long>();
	AtanhTestSignedInt<long long>();

	AtanhTestUnsignedInt<unsigned int>();
	AtanhTestUnsignedInt<unsigned char>();
//	AtanhTestUnsignedInt<unsigned short>();
	AtanhTestUnsignedInt<unsigned long>();
//	AtanhTestUnsignedInt<unsigned long long>();
}

}	// namespace atanh_test

}	// namespace hamon_cmath_test
