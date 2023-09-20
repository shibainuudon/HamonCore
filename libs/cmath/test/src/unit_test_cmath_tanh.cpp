/**
 *	@file	unit_test_cmath_tanh.cpp
 *
 *	@brief	tanh のテスト
 */

#include <hamon/cmath/tanh.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace tanh_test
{

static_assert(hamon::is_same<float,       decltype(hamon::tanh(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::tanhf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::tanh(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::tanh(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::tanh(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::tanhl(0.0l))>::value, "");

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
	return 1e-11;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 1e-11;
}

template <typename T>
void TanhTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.99505475368, (double)hamon::tanh(T(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.98661429815, (double)hamon::tanh(T(-2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.96402758007, (double)hamon::tanh(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.90514825364, (double)hamon::tanh(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.76159415595, (double)hamon::tanh(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.46211715726, (double)hamon::tanh(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::tanh(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.46211715726, (double)hamon::tanh(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.76159415595, (double)hamon::tanh(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.90514825364, (double)hamon::tanh(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.96402758007, (double)hamon::tanh(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.98661429815, (double)hamon::tanh(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99505475368, (double)hamon::tanh(T( 3.0)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::tanh(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::tanh(T(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+1.0, hamon::tanh(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0, hamon::tanh(-inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tanh(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tanh(-nan)));
}

template <typename T>
void TanhTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.99505475368, (double)hamon::tanh(T(-3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.96402758007, (double)hamon::tanh(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.76159415595, (double)hamon::tanh(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::tanh(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.76159415595, (double)hamon::tanh(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.96402758007, (double)hamon::tanh(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99505475368, (double)hamon::tanh(T( 3)), error);
}

template <typename T>
void TanhTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000, (double)hamon::tanh(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.76159415595, (double)hamon::tanh(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.96402758007, (double)hamon::tanh(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99505475368, (double)hamon::tanh(T( 3)), error);
}

GTEST_TEST(CMathTest, TanhTest)
{
	TanhTestFloat<float>();
	TanhTestFloat<double>();
	TanhTestFloat<long double>();

	TanhTestSignedInt<int>();
//	TanhTestSignedInt<signed char>();
	TanhTestSignedInt<short>();
//	TanhTestSignedInt<long>();
	TanhTestSignedInt<long long>();

//	TanhTestUnsignedInt<unsigned int>();
	TanhTestUnsignedInt<unsigned char>();
//	TanhTestUnsignedInt<unsigned short>();
	TanhTestUnsignedInt<unsigned long>();
//	TanhTestUnsignedInt<unsigned long long>();
}

}	// namespace tanh_test

}	// namespace hamon_cmath_test
