/**
 *	@file	unit_test_cmath_acosh.cpp
 *
 *	@brief	acosh のテスト
 */

#include <hamon/cmath/acosh.hpp>
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

namespace acosh_test
{

static_assert(hamon::is_same<float,       decltype(hamon::acosh(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::acosh(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::acosh(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::acosh(0.0l))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::acoshf(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::acoshl(0.0l))>::value, "");

template <typename T>
void AcoshTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR double error = hamon::is_same<T, float>::value ? 1e-6 : 1e-12;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0000000000000000000000000000000000000000000000000, (double)hamon::acosh(T(1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.9624236501192068949955178268487368462703686687713, (double)hamon::acosh(T(1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.3169578969248167086250463473079684440269819714675, (double)hamon::acosh(T(2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5667992369724110786640568625804834938620823510927, (double)hamon::acosh(T(2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.7627471740390860504652186499595846180563206565233, (double)hamon::acosh(T(3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.9248473002384137899910356536974736925407373375426, (double)hamon::acosh(T(3.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0634370688955605467272811726201318714565914498834, (double)hamon::acosh(T(4.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.1846437916051087266762781330721277714640033555892, (double)hamon::acosh(T(4.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.2924316695611776878007873113480154316218682400157, (double)hamon::acosh(T(5.0)), error);

	// if the argument is less than 1, FE_INVALID is raised an NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acosh(T(+1.0) - eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acosh(T( 0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acosh(T(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acosh(-inf)));

	// if the argument is 1, +0 is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::acosh(T(+1.0)));

	// if the argument is +∞, +∞ is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::acosh(+inf));

	// if the argument is NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acosh(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acosh(-nan)));
}

template <typename T>
void AcoshTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-12;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0000000000000000000000000000000000000000000000000, (double)hamon::acosh(T(1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.3169578969248167086250463473079684440269819714675, (double)hamon::acosh(T(2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.7627471740390860504652186499595846180563206565233, (double)hamon::acosh(T(3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0634370688955605467272811726201318714565914498834, (double)hamon::acosh(T(4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.2924316695611776878007873113480154316218682400157, (double)hamon::acosh(T(5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acosh(T( 0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acosh(T(-1))));
}

template <typename T>
void AcoshTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-12;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0000000000000000000000000000000000000000000000000, (double)hamon::acosh(T(1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.3169578969248167086250463473079684440269819714675, (double)hamon::acosh(T(2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.7627471740390860504652186499595846180563206565233, (double)hamon::acosh(T(3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0634370688955605467272811726201318714565914498834, (double)hamon::acosh(T(4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.2924316695611776878007873113480154316218682400157, (double)hamon::acosh(T(5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acosh(T( 0))));
}

GTEST_TEST(CMathTest, AcoshTest)
{
	AcoshTestFloat<float>();
	AcoshTestFloat<double>();
	AcoshTestFloat<long double>();

	AcoshTestSignedInt<int>();
//	AcoshTestSignedInt<signed char>();
	AcoshTestSignedInt<short>();
//	AcoshTestSignedInt<long>();
	AcoshTestSignedInt<long long>();

	AcoshTestUnsignedInt<unsigned int>();
	AcoshTestUnsignedInt<unsigned char>();
//	AcoshTestUnsignedInt<unsigned short>();
	AcoshTestUnsignedInt<unsigned long>();
//	AcoshTestUnsignedInt<unsigned long long>();
}

}	// namespace acosh_test

}	// namespace hamon_cmath_test
