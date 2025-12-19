/**
 *	@file	unit_test_ieee754_binary64.cpp
 *
 *	@brief	binary64 のテスト
 */

#include <hamon/ieee754/binary64.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "constexpr_test.hpp"

namespace hamon_ieee754_test
{

namespace binary64_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline bool normalized_test(double f)
{
	hamon::ieee754::binary64 b(f);
	auto f2 = double(b.normalized_fraction()) *
		std::pow(2.0f, double(b.normalized_exponent())) *
		std::pow(-1.0f, double(b.sign()));
	return f == f2;
}

HAMON_CXX20_CONSTEXPR bool test()
{
	using hamon::ieee754::binary64;

	// +0.0
	{
		binary64 f{0.0};
		VERIFY(f.uint()                 == 0x0000000000000000ULL);
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
		binary64 f{-0.0};
		VERIFY(f.uint()                 == 0x8000000000000000ULL);
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
		binary64 f{hamon::numeric_limits<double>::denorm_min()};
		VERIFY(f.uint()                 == 0x0000000000000001ULL);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 1);
		VERIFY(f.unbiased_exponent()    == -1022);
		VERIFY(f.unbiased_fraction()    == 1);
		VERIFY(f.normalized_exponent()  == -1074);
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
		binary64 f{-hamon::numeric_limits<double>::denorm_min()};
		VERIFY(f.uint()                 == 0x8000000000000001ULL);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 1);
		VERIFY(f.unbiased_exponent()    == -1022);
		VERIFY(f.unbiased_fraction()    == 1);
		VERIFY(f.normalized_exponent()  == -1074);
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
		binary64 f{hamon::numeric_limits<double>::min()};
		VERIFY(f.uint()                 == 0x0010000000000000ULL);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 1);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.unbiased_exponent()    == -1022);
		VERIFY(f.unbiased_fraction()    == 0x0010000000000000ULL);
		VERIFY(f.normalized_exponent()  == -1022);
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
		binary64 f{-hamon::numeric_limits<double>::min()};
		VERIFY(f.uint()                 == 0x8010000000000000ULL);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 1);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.unbiased_exponent()    == -1022);
		VERIFY(f.unbiased_fraction()    == 0x0010000000000000ULL);
		VERIFY(f.normalized_exponent()  == -1022);
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
		binary64 f{-1.5};
		VERIFY(f.uint()                 == 0xbff8000000000000ULL);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 0x3ff);
		VERIFY(f.fraction()             == 0x0008000000000000ULL);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0x0018000000000000ULL);
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
		binary64 f{123.0};
		VERIFY(f.uint()                 == 0x405ec00000000000ULL);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 0x405);
		VERIFY(f.fraction()             == 0x000ec00000000000ULL);
		VERIFY(f.unbiased_exponent()    == 6);
		VERIFY(f.unbiased_fraction()    == 0x001ec00000000000ULL);
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
		binary64 f{hamon::numeric_limits<double>::infinity()};
		VERIFY(f.uint()                 == 0x7ff0000000000000ULL);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.normalized_exponent()  == 2047);
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
		binary64 f{-hamon::numeric_limits<double>::infinity()};
		VERIFY(f.uint()                 == 0xfff0000000000000ULL);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.normalized_exponent()  == 2047);
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
		binary64 f{hamon::numeric_limits<double>::quiet_NaN()};
//		VERIFY(f.uint()                 == 0x7ff8000000000000ULL);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             != 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.normalized_exponent()  == 2047);
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
		binary64 f{hamon::numeric_limits<double>::signaling_NaN()};
//		VERIFY(f.uint()                 == 0x7ff0000000000001ULL);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             != 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.normalized_exponent()  == 2047);
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
		binary64 f{-hamon::numeric_limits<double>::quiet_NaN()};
//		VERIFY(f.uint()                 == 0xfff8000000000000ULL);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             != 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.normalized_exponent()  == 2047);
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
		binary64 f{-hamon::numeric_limits<double>::signaling_NaN()};
//		VERIFY(f.uint()                 == 0xfff0000000000001ULL);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             != 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.normalized_exponent()  == 2047);
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

GTEST_TEST(IEEE754Test, Binary64Test)
{
	EXPECT_TRUE(normalized_test(+0.0));
	EXPECT_TRUE(normalized_test(-0.0));
	EXPECT_TRUE(normalized_test(+0.5));
	EXPECT_TRUE(normalized_test(-0.5));
	EXPECT_TRUE(normalized_test(+1.5));
	EXPECT_TRUE(normalized_test(-1.5));
	EXPECT_TRUE(normalized_test(+1.125));
	EXPECT_TRUE(normalized_test(-1.125));
	EXPECT_TRUE(normalized_test(+123.456));
	EXPECT_TRUE(normalized_test(-123.456));
	EXPECT_TRUE(normalized_test(+1.0 / 3.0));
	EXPECT_TRUE(normalized_test(-1.0 / 3.0));
	EXPECT_TRUE(normalized_test(hamon::numeric_limits<double>::min()));
	EXPECT_TRUE(normalized_test(hamon::numeric_limits<double>::max()));
	EXPECT_TRUE(normalized_test(hamon::numeric_limits<double>::lowest()));
	EXPECT_TRUE(normalized_test(hamon::numeric_limits<double>::denorm_min()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace binary64_test

}	// namespace hamon_ieee754_test
