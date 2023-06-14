/**
 *	@file	unit_test_cmath_exp.cpp
 *
 *	@brief	exp のテスト
 */

#include <hamon/cmath/exp.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace exp_test
{

static_assert(hamon::is_same<float,       decltype(hamon::exp(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::expf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::exp(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::exp(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::exp(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::expl(0.0l))>::value, "");

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 0.00001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 0.000000000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 0.000000000001;
}

template <typename T>
void ExpTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0000000000000000, (double)hamon::exp(T(+0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0000000000000000, (double)hamon::exp(T(-0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.2840254166877414, (double)hamon::exp(T( 0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.6487212707001282, (double)hamon::exp(T( 0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.1170000166126748, (double)hamon::exp(T( 0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.7182818284590451, (double)hamon::exp(T( 1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.4816890703380645, (double)hamon::exp(T( 1.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(7.3890560989306504, (double)hamon::exp(T( 2.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(12.182493960703473, (double)hamon::exp(T( 2.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(20.085536923187668, (double)hamon::exp(T( 3.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(33.115451958692312, (double)hamon::exp(T( 3.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(7.7880078307140488e-01, (double)hamon::exp(T(-0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(6.0653065971263342e-01, (double)hamon::exp(T(-0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.7236655274101469e-01, (double)hamon::exp(T(-0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.6787944117144233e-01, (double)hamon::exp(T(-1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.2313016014842982e-01, (double)hamon::exp(T(-1.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.3533528323661270e-01, (double)hamon::exp(T(-2.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(8.2084998623898800e-02, (double)hamon::exp(T(-2.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.9787068367863944e-02, (double)hamon::exp(T(-3.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.0197383422318501e-02, (double)hamon::exp(T(-3.50)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::exp(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::exp(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::exp(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::exp(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::exp(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::exp(-nan)));
}

template <typename T>
void ExpTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.5399929762484847e-05, hamon::exp(T(-10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.2340980408667953e-04, hamon::exp(T(-9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.3546262790251191e-04, hamon::exp(T(-8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(9.1188196555451614e-04, hamon::exp(T(-7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.4787521766663585e-03, hamon::exp(T(-6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(6.7379469990854661e-03, hamon::exp(T(-5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.8315638888734179e-02, hamon::exp(T(-4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.9787068367863944e-02, hamon::exp(T(-3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.3533528323661270e-01, hamon::exp(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.6787944117144233e-01, hamon::exp(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0000000000000000, hamon::exp(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.7182818284590451, hamon::exp(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(7.3890560989306504, hamon::exp(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(20.085536923187668, hamon::exp(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(54.598150033144243, hamon::exp(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(148.41315910257663, hamon::exp(T( 5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(403.42879349273511, hamon::exp(T( 6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1096.6331584284587, hamon::exp(T( 7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2980.9579870417278, hamon::exp(T( 8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(8103.0839275753851, hamon::exp(T( 9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(22026.465794806718, hamon::exp(T(10)), error);
}

template <typename T>
void ExpTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0000000000000000, hamon::exp(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.7182818284590451, hamon::exp(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(7.3890560989306504, hamon::exp(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(20.085536923187668, hamon::exp(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(54.598150033144243, hamon::exp(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(148.41315910257663, hamon::exp(T( 5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(403.42879349273511, hamon::exp(T( 6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1096.6331584284587, hamon::exp(T( 7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2980.9579870417278, hamon::exp(T( 8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(8103.0839275753851, hamon::exp(T( 9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(22026.465794806718, hamon::exp(T(10)), error);
}

GTEST_TEST(CMathTest, ExpTest)
{
	ExpTestFloat<float>();
	ExpTestFloat<double>();
	ExpTestFloat<long double>();

	ExpTestSignedInt<int>();
//	ExpTestSignedInt<signed char>();
	ExpTestSignedInt<short>();
//	ExpTestSignedInt<long>();
	ExpTestSignedInt<long long>();

	ExpTestUnsignedInt<unsigned int>();
	ExpTestUnsignedInt<unsigned char>();
//	ExpTestUnsignedInt<unsigned short>();
	ExpTestUnsignedInt<unsigned long>();
//	ExpTestUnsignedInt<unsigned long long>();
}

}	// namespace exp_test

}	// namespace hamon_cmath_test
