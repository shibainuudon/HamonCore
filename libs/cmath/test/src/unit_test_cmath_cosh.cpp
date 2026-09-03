/**
 *	@file	unit_test_cmath_cosh.cpp
 *
 *	@brief	cosh のテスト
 */

#include <hamon/cmath/cosh.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace cosh_test
{

static_assert(hamon::is_same<float,       decltype(hamon::cosh(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::cosh(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::cosh(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::cosh(0.0l))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::coshf(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::coshl(0.0l))>::value, "");

template <typename T>
void CoshTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = hamon::is_same<T, float>::value ? 1e-6 : 1e-11;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.067661995777765841953936035115889836809803715371, (double)hamon::cosh(T(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.132289479663686116619852312817562995510285955539, (double)hamon::cosh(T(-2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.762195691083631459562213477773746108293973558230, (double)hamon::cosh(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.352409615243247325767667965441644170173960748865, (double)hamon::cosh(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.543080634815243778477905620757061682601529112365, (double)hamon::cosh(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.127625965206380785226225161402672012547847118098, (double)hamon::cosh(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.000000000000000000000000000000000000000000000000, (double)hamon::cosh(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.127625965206380785226225161402672012547847118098, (double)hamon::cosh(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.543080634815243778477905620757061682601529112365, (double)hamon::cosh(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.352409615243247325767667965441644170173960748865, (double)hamon::cosh(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.762195691083631459562213477773746108293973558230, (double)hamon::cosh(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.132289479663686116619852312817562995510285955539, (double)hamon::cosh(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.067661995777765841953936035115889836809803715371, (double)hamon::cosh(T( 3.0)), error);

	// if the argument is ±0, 1 is returned.
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0, hamon::cosh(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0, hamon::cosh(T(-0.0)));

	// If the argument is ±∞, +∞ is returned.
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::cosh(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::cosh(-inf));

	// if the argument is NaN, NaN is returned.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::cosh(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::cosh(-nan)));
}

template <typename T>
void CoshTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.067661995777765841953936035115889836809803715371, (double)hamon::cosh(T(-3)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.762195691083631459562213477773746108293973558230, (double)hamon::cosh(T(-2)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.543080634815243778477905620757061682601529112365, (double)hamon::cosh(T(-1)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.000000000000000000000000000000000000000000000000, (double)hamon::cosh(T( 0)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.543080634815243778477905620757061682601529112365, (double)hamon::cosh(T( 1)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.762195691083631459562213477773746108293973558230, (double)hamon::cosh(T( 2)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.067661995777765841953936035115889836809803715371, (double)hamon::cosh(T( 3)), 1e-11);
}

template <typename T>
void CoshTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.000000000000000000000000000000000000000000000000, (double)hamon::cosh(T( 0)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.543080634815243778477905620757061682601529112365, (double)hamon::cosh(T( 1)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.762195691083631459562213477773746108293973558230, (double)hamon::cosh(T( 2)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.067661995777765841953936035115889836809803715371, (double)hamon::cosh(T( 3)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(27.308232836016486629201989612067059822501324553084, (double)hamon::cosh(T( 4)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(74.209948524787844444106108044487714023868258589453, (double)hamon::cosh(T( 5)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(201.71563612245589448340511285540954813689570191836, (double)hamon::cosh(T( 6)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(548.31703515521207688996412071210292086242280427907, (double)hamon::cosh(T( 7)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1490.4791612521780886277154604210072273084936250165, (double)hamon::cosh(T( 8)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4051.5420254925940471947730935347253475226510799922, (double)hamon::cosh(T( 9)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(11013.232920103323139721376090437879963452061428237, (double)hamon::cosh(T(10)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(242582597.70489514001513022649004919332528968455033, (double)hamon::cosh(T(20)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(5343237290762.2310734952343721588156692131205273157, (double)hamon::cosh(T(30)), 1e-3);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(117692633418509992.70394995537451740437861293627307, (double)hamon::cosh(T(40)), 1e+8);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2592352764293536232043.7266614667426924137346467294, (double)hamon::cosh(T(50)), 1e+16);
}

GTEST_TEST(CMathTest, CoshTest)
{
	CoshTestFloat<float>();
	CoshTestFloat<double>();
	CoshTestFloat<long double>();

	CoshTestSignedInt<int>();
//	CoshTestSignedInt<signed char>();
	CoshTestSignedInt<short>();
//	CoshTestSignedInt<long>();
	CoshTestSignedInt<long long>();

	CoshTestUnsignedInt<unsigned int>();
	CoshTestUnsignedInt<unsigned char>();
//	CoshTestUnsignedInt<unsigned short>();
	CoshTestUnsignedInt<unsigned long>();
//	CoshTestUnsignedInt<unsigned long long>();
}

}	// namespace cosh_test

}	// namespace hamon_cmath_test
