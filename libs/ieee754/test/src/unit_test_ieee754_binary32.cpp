/**
 *	@file	unit_test_ieee754_binary32.cpp
 *
 *	@brief	binary32 のテスト
 */

#include <hamon/ieee754/binary32.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "constexpr_test.hpp"

namespace hamon_ieee754_test
{

namespace binary32_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline bool normalized_test(float f)
{
	hamon::ieee754::binary32 b(f);
	auto f2 = float(b.normalized_fraction()) *
		std::pow(2.0f, float(b.normalized_exponent())) *
		std::pow(-1.0f, float(b.sign()));
	return f == f2;
}

inline HAMON_CXX20_CONSTEXPR bool test()
{
	using hamon::ieee754::binary32;

	// +0.0
	{
		binary32 f{0.0f};
		VERIFY(f.uint()                 == 0x00000000);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.normalized_exponent()  == 0);
		VERIFY(f.normalized_fraction()  == 0);
		VERIFY(f.is_zero()              == true);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	// -0.0
	{
		binary32 f{-0.0f};
		VERIFY(f.uint()                 == 0x80000000);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.normalized_exponent()  == 0);
		VERIFY(f.normalized_fraction()  == 0);
		VERIFY(f.is_zero()              == true);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	// subnormal
	{
		binary32 f{hamon::numeric_limits<float>::denorm_min()};
		VERIFY(f.uint()                 == 0x00000001);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 1);
		VERIFY(f.unbiased_exponent()    == -126);
		VERIFY(f.unbiased_fraction()    == 1);
		VERIFY(f.normalized_exponent()  == -149);
		VERIFY(f.normalized_fraction()  == 1);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == true);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	{
		binary32 f{-hamon::numeric_limits<float>::denorm_min()};
		VERIFY(f.uint()                 == 0x80000001);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 1);
		VERIFY(f.unbiased_exponent()    == -126);
		VERIFY(f.unbiased_fraction()    == 1);
		VERIFY(f.normalized_exponent()  == -149);
		VERIFY(f.normalized_fraction()  == 1);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == true);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	// normal
	{
		binary32 f{hamon::numeric_limits<float>::min()};
		VERIFY(f.uint()                 == 0x00800000);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 1);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.unbiased_exponent()    == -126);
		VERIFY(f.unbiased_fraction()    == 0x00800000);
		VERIFY(f.normalized_exponent()  == -126);
		VERIFY(f.normalized_fraction()  == 1);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == true);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	{
		binary32 f{-hamon::numeric_limits<float>::min()};
		VERIFY(f.uint()                 == 0x80800000);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 1);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.unbiased_exponent()    == -126);
		VERIFY(f.unbiased_fraction()    == 0x00800000);
		VERIFY(f.normalized_exponent()  == -126);
		VERIFY(f.normalized_fraction()  == 1);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == true);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	{
		binary32 f{-1.5f};
		VERIFY(f.uint()                 == 0xbfc00000);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 0x7f);
		VERIFY(f.fraction()             == 0x00400000);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0x00c00000);
		VERIFY(f.normalized_exponent()  == -1);
		VERIFY(f.normalized_fraction()  == 3);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == true);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	{
		binary32 f{123.0f};
		VERIFY(f.uint()                 == 0x42f60000);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 0x85);
		VERIFY(f.fraction()             == 0x00760000);
		VERIFY(f.unbiased_exponent()    == 6);
		VERIFY(f.unbiased_fraction()    == 0x00f60000);
		VERIFY(f.normalized_exponent()  == 0);
		VERIFY(f.normalized_fraction()  == 123);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == true);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	// +inf
	{
		binary32 f{hamon::numeric_limits<float>::infinity()};
		VERIFY(f.uint()                 == 0x7f800000);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 255);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.normalized_exponent()  == 255);
		VERIFY(f.normalized_fraction()  == 0);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == false);
		VERIFY(f.is_infinity()          == true);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	// -inf
	{
		binary32 f{-hamon::numeric_limits<float>::infinity()};
		VERIFY(f.uint()                 == 0xff800000);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 255);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.normalized_exponent()  == 255);
		VERIFY(f.normalized_fraction()  == 0);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == false);
		VERIFY(f.is_infinity()          == true);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	// +nan
	{
		binary32 f{hamon::numeric_limits<float>::quiet_NaN()};
//		VERIFY(f.uint()                 == 0x7fc00000);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 255);
		VERIFY(f.fraction()             != 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.normalized_exponent()  == 255);
		VERIFY(f.normalized_fraction()  != 0);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == false);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == true);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == true);
	}
	{
		binary32 f{hamon::numeric_limits<float>::signaling_NaN()};
//		VERIFY(f.uint()                 == 0x7fc00001);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 255);
		VERIFY(f.fraction()             != 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.normalized_exponent()  == 255);
		VERIFY(f.normalized_fraction()  != 0);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == false);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == true);
		VERIFY(f.is_signaling_nan()     == true);
		VERIFY(f.is_quiet_nan()         == false);
	}
	// -nan
	{
		binary32 f{-hamon::numeric_limits<float>::quiet_NaN()};
//		VERIFY(f.uint()                 == 0xffc00000);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 255);
		VERIFY(f.fraction()             != 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.normalized_exponent()  == 255);
		VERIFY(f.normalized_fraction()  != 0);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == false);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == true);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == true);
	}
	{
		binary32 f{-hamon::numeric_limits<float>::signaling_NaN()};
//		VERIFY(f.uint()                 == 0xffc00001);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 255);
		VERIFY(f.fraction()             != 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.normalized_exponent()  == 255);
		VERIFY(f.normalized_fraction()  != 0);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == false);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == true);
		VERIFY(f.is_signaling_nan()     == true);
		VERIFY(f.is_quiet_nan()         == false);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(IEEE754Test, Binary32Test)
{
	EXPECT_TRUE(normalized_test(+0.0f));
	EXPECT_TRUE(normalized_test(-0.0f));
	EXPECT_TRUE(normalized_test(+0.5f));
	EXPECT_TRUE(normalized_test(-0.5f));
	EXPECT_TRUE(normalized_test(+1.5f));
	EXPECT_TRUE(normalized_test(-1.5f));
	EXPECT_TRUE(normalized_test(+1.125f));
	EXPECT_TRUE(normalized_test(-1.125f));
	EXPECT_TRUE(normalized_test(+123.456f));
	EXPECT_TRUE(normalized_test(-123.456f));
	EXPECT_TRUE(normalized_test(+1.0f / 3.0f));
	EXPECT_TRUE(normalized_test(-1.0f / 3.0f));
	EXPECT_TRUE(normalized_test(hamon::numeric_limits<float>::min()));
	EXPECT_TRUE(normalized_test(hamon::numeric_limits<float>::max()));
	EXPECT_TRUE(normalized_test(hamon::numeric_limits<float>::lowest()));
	EXPECT_TRUE(normalized_test(hamon::numeric_limits<float>::denorm_min()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace binary32_test

}	// namespace hamon_ieee754_test
