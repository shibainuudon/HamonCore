/**
 *	@file	unit_test_cmath_tanh.cpp
 *
 *	@brief	tanh のテスト
 */

#include <hamon/cmath/tanh.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
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
static_assert(hamon::is_same<double,      decltype(hamon::tanh(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::tanh(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::tanh(0.0l))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::tanhf(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::tanhl(0.0l))>::value, "");

template <typename T>
void TanhTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = hamon::is_same<T, float>::value ? 1e-6 : 1e-11;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.99505475368673045133188018525548847509781385470028, (double)hamon::tanh(T(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.98661429815143028888127603923734963921251198218541, (double)hamon::tanh(T(-2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.96402758007581688394641372410092315025502997624094, (double)hamon::tanh(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.90514825364486643824230369645649559722764113515878, (double)hamon::tanh(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.76159415595576488811945828260479359041276859725794, (double)hamon::tanh(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.46211715726000975850231848364367254873028928033011, (double)hamon::tanh(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000000000000000000000000000000000000, (double)hamon::tanh(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.46211715726000975850231848364367254873028928033011, (double)hamon::tanh(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.76159415595576488811945828260479359041276859725794, (double)hamon::tanh(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.90514825364486643824230369645649559722764113515878, (double)hamon::tanh(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.96402758007581688394641372410092315025502997624094, (double)hamon::tanh(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.98661429815143028888127603923734963921251198218541, (double)hamon::tanh(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99505475368673045133188018525548847509781385470028, (double)hamon::tanh(T( 3.0)), error);

	// if the argument is ±0, ±0 is returned.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::tanh(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::tanh(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::tanh(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::tanh(T(-0.0))));

	// if the argument is ±∞, ±1 is returned.
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+1.0, hamon::tanh(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-1.0, hamon::tanh(-inf));

	// if the argument is NaN, NaN is returned.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tanh(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::tanh(-nan)));
}

template <typename T>
void TanhTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.99505475368673045133188018525548847509781385470028, (double)hamon::tanh(T(-3)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.96402758007581688394641372410092315025502997624094, (double)hamon::tanh(T(-2)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.76159415595576488811945828260479359041276859725794, (double)hamon::tanh(T(-1)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000000000000000000000000000000000000, (double)hamon::tanh(T( 0)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.76159415595576488811945828260479359041276859725794, (double)hamon::tanh(T( 1)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.96402758007581688394641372410092315025502997624094, (double)hamon::tanh(T( 2)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99505475368673045133188018525548847509781385470028, (double)hamon::tanh(T( 3)), 1e-11);
}

template <typename T>
void TanhTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000000000000000000000000000000000000, (double)hamon::tanh(T( 0)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.76159415595576488811945828260479359041276859725794, (double)hamon::tanh(T( 1)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.96402758007581688394641372410092315025502997624094, (double)hamon::tanh(T( 2)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99505475368673045133188018525548847509781385470028, (double)hamon::tanh(T( 3)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99932929973906704379224334434172496200533985289441, (double)hamon::tanh(T( 4)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99990920426259513121099044753447302108981261599055, (double)hamon::tanh(T( 5)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99998771165079557056434885235523206531471806464383, (double)hamon::tanh(T( 6)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99999833694394467173571641595066711288205699209227, (double)hamon::tanh(T( 7)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99999977492967588981001883295636839335406188812688, (double)hamon::tanh(T( 8)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99999996954004097447930211118358239752536037274914, (double)hamon::tanh(T( 9)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99999999587769276361959283713827574105081461849502, (double)hamon::tanh(T(10)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99999999999999999150329148941682204543855819119099, (double)hamon::tanh(T(20)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99999999999999999999999998248697847460695932302253, (double)hamon::tanh(T(30)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99999999999999999999999999999999996390297224309170, (double)hamon::tanh(T(40)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99999999999999999999999999999999999999999992559848, (double)hamon::tanh(T(50)), 1e-11);
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
