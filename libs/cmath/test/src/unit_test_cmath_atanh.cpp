/**
 *	@file	unit_test_cmath_atanh.cpp
 *
 *	@brief	atanh のテスト
 */

#include <hamon/cmath/atanh.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>	// HAMON_CXX11_CONSTEXPR_EXPECT_NEAR
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace atanh_test
{

static_assert(hamon::is_same<float,       decltype(hamon::atanh(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atanh(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atanh(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atanh(0.0l))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::atanhf(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atanhl(0.0l))>::value, "");

template <typename T>
void AtanhTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR double error = hamon::is_same<T, float>::value ? 1e-6 : 1e-12;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000000000000000000000000000000000000, (double)hamon::atanh(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.1003353477310755806357265520600389452633628691459, (double)hamon::atanh(T( 0.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.2027325540540821909890065577321745682859952117312, (double)hamon::atanh(T( 0.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.3095196042031117154740673490610694375840916075891, (double)hamon::atanh(T( 0.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.5493061443340548456976226184612628523237452789113, (double)hamon::atanh(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4722194895832202300045137159439267686186896306496, (double)hamon::atanh(T( 0.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.6466524123622461977050606459342686009455526402847, (double)hamon::atanh(T( 0.99)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.1003353477310755806357265520600389452633628691459, (double)hamon::atanh(T(-0.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.2027325540540821909890065577321745682859952117312, (double)hamon::atanh(T(-0.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.3095196042031117154740673490610694375840916075891, (double)hamon::atanh(T(-0.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.5493061443340548456976226184612628523237452789113, (double)hamon::atanh(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.4722194895832202300045137159439267686186896306496, (double)hamon::atanh(T(-0.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.6466524123622461977050606459342686009455526402847, (double)hamon::atanh(T(-0.99)), error);

	// if the argument is ±0, it is returned unmodified.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::atanh(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::atanh(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::atanh(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::atanh(T(-0.0))));

	// if the argument is ±1, ±∞ is returned and FE_DIVBYZERO is raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::atanh(T(+1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::atanh(T(-1.0)));

	// if |num|>1, NaN is returned and FE_INVALID is raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atanh(T(+1.0) + eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atanh(T(-1.0) - eps)));

	// if the argument is NaN, NaN is returned.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atanh(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atanh(-nan)));
}

template <typename T>
void AtanhTestSignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<R>::infinity();

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
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<R>::infinity();

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
