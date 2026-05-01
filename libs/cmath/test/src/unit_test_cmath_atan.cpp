/**
 *	@file	unit_test_cmath_atan.cpp
 *
 *	@brief	atan のテスト
 */

#include <hamon/cmath/atan.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/numbers.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace atan_test
{

static_assert(hamon::is_same<float,       decltype(hamon::atan(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atan(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atan(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atan(0.0l))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::atanf(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atanl(0.0l))>::value, "");

template <typename T>
void AtanTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = hamon::is_same<T, float>::value ? 1e-6 : 1e-12;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.550798992821746086170568494738154954149351501001,   (double)hamon::atan(T(-50.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.1902899496825317329277337748293183376011789860295,  (double)hamon::atan(T( -2.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.78539816339744830961566084581987572104929234984378, (double)hamon::atan(T( -1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.64350110879328438680280922871732263804151059111531, (double)hamon::atan(T( -0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.46364760900080611621425623146121440202853705428612, (double)hamon::atan(T( -0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.24497866312686415417208248121127581091414409838118, (double)hamon::atan(T( -0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000000000000000000000000000000000000, (double)hamon::atan(T(  0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.24497866312686415417208248121127581091414409838118, (double)hamon::atan(T(  0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.46364760900080611621425623146121440202853705428612, (double)hamon::atan(T(  0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.64350110879328438680280922871732263804151059111531, (double)hamon::atan(T(  0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.78539816339744830961566084581987572104929234984378, (double)hamon::atan(T(  1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1902899496825317329277337748293183376011789860295,  (double)hamon::atan(T(  2.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.550798992821746086170568494738154954149351501001,   (double)hamon::atan(T( 50.00)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::atan(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::atan(T(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( hamon::numbers::pi_fn<double>() / 2, (double)hamon::atan(+inf), 0.000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-hamon::numbers::pi_fn<double>() / 2, (double)hamon::atan(-inf), 0.000001);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan(-nan)));
}

template <typename T>
void AtanTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-15;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000000000000000000000000000000000000, hamon::atan(T(   0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.7853981633974483096156608458198757210492923498437, hamon::atan(T(   1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.7853981633974483096156608458198757210492923498437, hamon::atan(T(  -1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1071487177940905030170654601785370400700476454014, hamon::atan(T(   2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.1071487177940905030170654601785370400700476454014, hamon::atan(T(  -2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.2490457723982544258299170772810901230778294041299, hamon::atan(T(   3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.2490457723982544258299170772810901230778294041299, hamon::atan(T(  -3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4711276743037345918528755717617308518553063771832, hamon::atan(T(  10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.4711276743037345918528755717617308518553063771832, hamon::atan(T( -10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5607966601082313810249815754304718935372153471432, hamon::atan(T( 100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5607966601082313810249815754304718935372153471432, hamon::atan(T(-100)), error);
}

template <typename T>
void AtanTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-15;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0000000000000000000000000000000000000000000000000, hamon::atan(T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.7853981633974483096156608458198757210492923498437, hamon::atan(T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.1071487177940905030170654601785370400700476454014, hamon::atan(T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.2490457723982544258299170772810901230778294041299, hamon::atan(T(  3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.4711276743037345918528755717617308518553063771832, hamon::atan(T( 10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5607966601082313810249815754304718935372153471432, hamon::atan(T(100)), error);
}

GTEST_TEST(CMathTest, AtanTest)
{
	AtanTestFloat<float>();
	AtanTestFloat<double>();
	AtanTestFloat<long double>();

	AtanTestSignedInt<int>();
//	AtanTestSignedInt<signed char>();
	AtanTestSignedInt<short>();
//	AtanTestSignedInt<long>();
	AtanTestSignedInt<long long>();

	AtanTestUnsignedInt<unsigned int>();
	AtanTestUnsignedInt<unsigned char>();
//	AtanTestUnsignedInt<unsigned short>();
	AtanTestUnsignedInt<unsigned long>();
//	AtanTestUnsignedInt<unsigned long long>();
}

}	// namespace atan_test

}	// namespace hamon_cmath_test
