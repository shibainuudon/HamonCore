/**
 *	@file	unit_test_ieee754_binary64.cpp
 *
 *	@brief	binary64 のテスト
 */

#include <hamon/ieee754/binary64.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ieee754_test
{

namespace binary64_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test()
{
	using T = double;
	using hamon::ieee754::binary64;
	using uint_type = typename binary64::uint_type;

	static_assert(binary64::sign_bits     ==  1, "");
	static_assert(binary64::exponent_bits == 11, "");
	static_assert(binary64::fraction_bits == 52, "");

	static_assert(binary64::exponent_min == -1022, "");
	static_assert(binary64::exponent_max ==  1023, "");

	// +0.0
	{
		binary64 f{0.0};
		VERIFY(f.to_uint()              == 0x0000000000000000ULL);
		VERIFY(f.to_float()             == 0.0);
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.is_zero()              == true);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);

		f.set_sign(1);
		VERIFY(f.to_float()             == -0.0);
		VERIFY(f.sign()                 == 1);
	}
	{
		binary64 f{uint_type{0x0000000000000000ULL}};
		VERIFY(f.to_uint()              == 0x0000000000000000ULL);
		VERIFY(f.to_float()             == 0.0);
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.is_zero()              == true);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	{
		binary64 f{0, 0, 0};
		VERIFY(f.to_uint()              == 0x0000000000000000ULL);
		VERIFY(f.to_float()             == 0.0);
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 0);
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
		VERIFY(f.to_uint()              == 0x8000000000000000ULL);
		VERIFY(f.to_float()             == -0.0);
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.is_zero()              == true);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);

		f.set_sign(0);
		VERIFY(f.to_float()             == 0.0);
		VERIFY(f.sign()                 == 0);
	}
	{
		binary64 f{uint_type{0x8000000000000000ULL}};
		VERIFY(f.to_uint()              == 0x8000000000000000ULL);
		VERIFY(f.to_float()             == -0.0);
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.is_zero()              == true);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	{
		binary64 f{1, 0, 0};
		VERIFY(f.to_uint()              == 0x8000000000000000ULL);
		VERIFY(f.to_float()             == -0.0);
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.is_zero()              == true);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	// normal
	{
		binary64 f{-1.5};
		VERIFY(f.to_uint()              == 0xbff8000000000000ULL);
		VERIFY(f.to_float()             == -1.5);
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 0x3ff);
		VERIFY(f.fraction_component()   == 0x0008000000000000ULL);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0x0018000000000000ULL);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == -1);
		VERIFY(f.fraction()             == 3);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == true);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);

		f.set_sign(0);
		VERIFY(f.to_float()             == 1.5);
	}
	{
		binary64 f{uint_type{0xbff8000000000000ULL}};
		VERIFY(f.to_uint()              == 0xbff8000000000000ULL);
		VERIFY(f.to_float()             == -1.5);
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 0x3ff);
		VERIFY(f.fraction_component()   == 0x0008000000000000ULL);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0x0018000000000000ULL);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == -1);
		VERIFY(f.fraction()             == 3);
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
		VERIFY(f.to_uint()              == 0x405ec00000000000ULL);
		VERIFY(f.to_float()             == 123.0);
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0x405);
		VERIFY(f.fraction_component()   == 0x000ec00000000000ULL);
		VERIFY(f.unbiased_exponent()    == 6);
		VERIFY(f.unbiased_fraction()    == 0x001ec00000000000ULL);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 123);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == true);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);

		f.set_sign(1);
		VERIFY(f.to_float()             == -123.0);
	}
	{
		binary64 f{0, 0, 123};
		VERIFY(f.to_uint()              == 0x405ec00000000000ULL);
		VERIFY(f.to_float()             == 123.0);
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0x405);
		VERIFY(f.fraction_component()   == 0x000ec00000000000ULL);
		VERIFY(f.unbiased_exponent()    == 6);
		VERIFY(f.unbiased_fraction()    == 0x001ec00000000000ULL);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 0);
		VERIFY(f.fraction()             == 123);
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
		binary64 f{hamon::numeric_limits<T>::min()};
		VERIFY(f.to_uint()              == 0x0010000000000000ULL);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::min());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 1);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == -1022);
		VERIFY(f.unbiased_fraction()    == 0x0010000000000000ULL);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == -1022);
		VERIFY(f.fraction()             == 1);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == true);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);

		f.set_sign(1);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::min());
	}
	{
		binary64 f{uint_type{0x0010000000000000ULL}};
		VERIFY(f.to_uint()              == 0x0010000000000000ULL);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::min());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 1);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == -1022);
		VERIFY(f.unbiased_fraction()    == 0x0010000000000000ULL);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == -1022);
		VERIFY(f.fraction()             == 1);
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
		binary64 f{-hamon::numeric_limits<T>::min()};
		VERIFY(f.to_uint()              == 0x8010000000000000ULL);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::min());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 1);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == -1022);
		VERIFY(f.unbiased_fraction()    == 0x0010000000000000ULL);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == -1022);
		VERIFY(f.fraction()             == 1);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == true);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);

		f.set_sign(0);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::min());
	}
	{
		binary64 f{1, -1022, 1};
		VERIFY(f.to_uint()              == 0x8010000000000000ULL);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::min());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 1);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == -1022);
		VERIFY(f.unbiased_fraction()    == 0x0010000000000000ULL);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == -1022);
		VERIFY(f.fraction()             == 1);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == true);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	// subnormal
	{
		binary64 f{hamon::numeric_limits<T>::denorm_min()};
		VERIFY(f.to_uint()              == 0x0000000000000001ULL);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::denorm_min());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 1);
		VERIFY(f.unbiased_exponent()    == -1022);
		VERIFY(f.unbiased_fraction()    == 0x0000000000000001ULL);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == -1074);
		VERIFY(f.fraction()             == 1);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == true);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);

		f.set_sign(1);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::denorm_min());
	}
	{
		binary64 f{uint_type{0x0000000000000001ULL}};
		VERIFY(f.to_uint()              == 0x0000000000000001ULL);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::denorm_min());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 1);
		VERIFY(f.unbiased_exponent()    == -1022);
		VERIFY(f.unbiased_fraction()    == 0x0000000000000001ULL);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == -1074);
		VERIFY(f.fraction()             == 1);
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
		binary64 f{-hamon::numeric_limits<T>::denorm_min()};
		VERIFY(f.to_uint()              == 0x8000000000000001ULL);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::denorm_min());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 1);
		VERIFY(f.unbiased_exponent()    == -1022);
		VERIFY(f.unbiased_fraction()    == 0x0000000000000001ULL);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == -1074);
		VERIFY(f.fraction()             == 1);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == true);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);

		f.set_sign(0);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::denorm_min());
	}
	{
		binary64 f{1, -1074, 1};
		VERIFY(f.to_uint()              == 0x8000000000000001ULL);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::denorm_min());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 1);
		VERIFY(f.unbiased_exponent()    == -1022);
		VERIFY(f.unbiased_fraction()    == 0x0000000000000001ULL);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == -1074);
		VERIFY(f.fraction()             == 1);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == true);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == true);
		VERIFY(f.is_infinity()          == false);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);
	}
	// +inf
	{
		binary64 f{hamon::numeric_limits<T>::infinity()};
		VERIFY(f.to_uint()              == 0x7ff0000000000000ULL);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::infinity());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 2047);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == false);
		VERIFY(f.is_infinity()          == true);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);

		f.set_sign(1);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::infinity());
	}
	{
		binary64 f{uint_type{0x7ff0000000000000ULL}};
		VERIFY(f.to_uint()              == 0x7ff0000000000000ULL);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::infinity());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 2047);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             == 0);
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
		binary64 f{-hamon::numeric_limits<T>::infinity()};
		VERIFY(f.to_uint()              == 0xfff0000000000000ULL);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::infinity());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 2047);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             == 0);
		VERIFY(f.is_zero()              == false);
		VERIFY(f.is_subnormal()         == false);
		VERIFY(f.is_normal()            == false);
		VERIFY(f.is_finite()            == false);
		VERIFY(f.is_infinity()          == true);
		VERIFY(f.is_nan()               == false);
		VERIFY(f.is_signaling_nan()     == false);
		VERIFY(f.is_quiet_nan()         == false);

		f.set_sign(0);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::infinity());
	}
	{
		binary64 f{1, 2047, 0};
		VERIFY(f.to_uint()              == 0xfff0000000000000ULL);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::infinity());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 2047);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             == 0);
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
		binary64 f{hamon::numeric_limits<T>::quiet_NaN()};
//		VERIFY(f.to_uint()              == 0x7ff8000000000000ULL);
//		VERIFY(f.to_float()             == hamon::numeric_limits<T>::quiet_NaN());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 2047);
		VERIFY(f.fraction_component()   != 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             != 0);
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
		binary64 f{hamon::numeric_limits<T>::signaling_NaN()};
//		VERIFY(f.to_uint()              == 0x7ff0000000000001ULL);
//		VERIFY(f.to_float()             == hamon::numeric_limits<T>::signaling_NaN());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 2047);
		VERIFY(f.fraction_component()   != 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             != 0);
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
		binary64 f{-hamon::numeric_limits<T>::quiet_NaN()};
//		VERIFY(f.to_uint()              == 0xfff8000000000000ULL);
//		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::quiet_NaN());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 2047);
		VERIFY(f.fraction_component()   != 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             != 0);
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
		binary64 f{-hamon::numeric_limits<T>::signaling_NaN()};
//		VERIFY(f.to_uint()              == 0xfff0000000000001ULL);
//		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::signaling_NaN());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 2047);
		VERIFY(f.fraction_component()   != 0);
		VERIFY(f.unbiased_exponent()    == 2047);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 2047);
		VERIFY(f.fraction()             != 0);
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
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace binary64_test

}	// namespace hamon_ieee754_test
