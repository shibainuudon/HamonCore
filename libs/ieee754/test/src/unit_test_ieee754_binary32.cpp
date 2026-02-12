/**
 *	@file	unit_test_ieee754_binary32.cpp
 *
 *	@brief	binary32 のテスト
 */

#include <hamon/ieee754/binary32.hpp>
#include <hamon/limits.hpp>
#include <hamon/cmath/isnan.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "constexpr_test.hpp"

namespace hamon_ieee754_test
{

namespace binary32_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX20_CONSTEXPR bool make_floating_point_test(float f)
{
	using hamon::ieee754::binary32;
	binary32 b1(f);
	binary32 b2(b1.sign(), b1.exponent(), b1.fraction());
	return b1.to_uint() == b2.to_uint();
}

inline HAMON_CXX20_CONSTEXPR bool test()
{
	using T = float;
	using hamon::ieee754::binary32;
	using uint_type = typename binary32::uint_type;

	static_assert(binary32::sign_bits == 1, "");

	static_assert(binary32::exponent_bits == 8, "");
	static_assert(binary32::exponent_component_min == 0, "");
	static_assert(binary32::exponent_component_max == 255, "");
	static_assert(binary32::exponent_min == -126, "");
	static_assert(binary32::exponent_max == 127, "");
	static_assert(binary32::exponent_bias == 127, "");

	static_assert(binary32::fraction_bits == 23, "");
	static_assert(binary32::fraction_bias == 0x800000, "");

	// +0.0
	{
		binary32 f{0.0f};
		VERIFY(f.to_uint()              == 0x00000000);
		VERIFY(f.to_float()             == 0.0f);
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
		binary32 f{uint_type{0x00000000U}};
		VERIFY(f.to_uint()              == 0x00000000);
		VERIFY(f.to_float()             == 0.0f);
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
		binary32 f{-0.0f};
		VERIFY(f.to_uint()              == 0x80000000);
		VERIFY(f.to_float()             == -0.0f);
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
		binary32 f{1, 0, 0};
		VERIFY(f.to_uint()              == 0x80000000);
		VERIFY(f.to_float()             == -0.0f);
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
		binary32 f{1.0f};
		VERIFY(f.to_uint()              == 0x3f800000);
		VERIFY(f.to_float()             == 1.0f);
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0x7f);
		VERIFY(f.fraction_component()   == 0x00000000);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0x00800000);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 0);
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
		binary32 f{uint_type{0x3f800000U}};
		VERIFY(f.to_uint()              == 0x3f800000);
		VERIFY(f.to_float()             == 1.0f);
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0x7f);
		VERIFY(f.fraction_component()   == 0x00000000);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0x00800000);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 0);
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
		binary32 f{0.25f};
		VERIFY(f.to_uint()              == 0x3e800000);
		VERIFY(f.to_float()             == 0.25f);
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0x7d);
		VERIFY(f.fraction_component()   == 0x00000000);
		VERIFY(f.unbiased_exponent()    == -2);
		VERIFY(f.unbiased_fraction()    == 0x00800000);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == -2);
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
		binary32 f{0, -2, 1};
		VERIFY(f.to_uint()              == 0x3e800000);
		VERIFY(f.to_float()             == 0.25f);
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0x7d);
		VERIFY(f.fraction_component()   == 0x00000000);
		VERIFY(f.unbiased_exponent()    == -2);
		VERIFY(f.unbiased_fraction()    == 0x00800000);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == -2);
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
		binary32 f{-1.5f};
		VERIFY(f.to_uint()              == 0xbfc00000);
		VERIFY(f.to_float()             == -1.5f);
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 0x7f);
		VERIFY(f.fraction_component()   == 0x00400000);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0x00c00000);
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
		binary32 f{uint_type{0xbfc00000U}};
		VERIFY(f.to_uint()              == 0xbfc00000);
		VERIFY(f.to_float()             == -1.5f);
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 0x7f);
		VERIFY(f.fraction_component()   == 0x00400000);
		VERIFY(f.unbiased_exponent()    == 0);
		VERIFY(f.unbiased_fraction()    == 0x00c00000);
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
		binary32 f{123.0f};
		VERIFY(f.to_uint()              == 0x42f60000);
		VERIFY(f.to_float()             == 123.0f);
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0x85);
		VERIFY(f.fraction_component()   == 0x00760000);
		VERIFY(f.unbiased_exponent()    == 6);
		VERIFY(f.unbiased_fraction()    == 0x00f60000);
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
		binary32 f{0, 0, 123};
		VERIFY(f.to_uint()              == 0x42f60000);
		VERIFY(f.to_float()             == 123.0f);
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0x85);
		VERIFY(f.fraction_component()   == 0x00760000);
		VERIFY(f.unbiased_exponent()    == 6);
		VERIFY(f.unbiased_fraction()    == 0x00f60000);
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
		binary32 f{hamon::numeric_limits<T>::min()};
		VERIFY(f.to_uint()              == 0x00800000);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::min());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 1);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == -126);
		VERIFY(f.unbiased_fraction()    == 0x00800000);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == -126);
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
		binary32 f{uint_type{0x00800000U}};
		VERIFY(f.to_uint()              == 0x00800000);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::min());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 1);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == -126);
		VERIFY(f.unbiased_fraction()    == 0x00800000);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == -126);
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
		binary32 f{-hamon::numeric_limits<T>::min()};
		VERIFY(f.to_uint()              == 0x80800000);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::min());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 1);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == -126);
		VERIFY(f.unbiased_fraction()    == 0x00800000);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == -126);
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
		binary32 f{1, -126, 1};
		VERIFY(f.to_uint()              == 0x80800000);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::min());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 1);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == -126);
		VERIFY(f.unbiased_fraction()    == 0x00800000);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == -126);
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
		binary32 f{hamon::numeric_limits<T>::denorm_min()};
		VERIFY(f.to_uint()              == 0x00000001);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::denorm_min());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 1);
		VERIFY(f.unbiased_exponent()    == -126);
		VERIFY(f.unbiased_fraction()    == 0x00000001);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == -149);
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
		binary32 f{uint_type{0x00000001U}};
		VERIFY(f.to_uint()              == 0x00000001);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::denorm_min());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 1);
		VERIFY(f.unbiased_exponent()    == -126);
		VERIFY(f.unbiased_fraction()    == 0x00000001);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == -149);
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
		binary32 f{-hamon::numeric_limits<T>::denorm_min()};
		VERIFY(f.to_uint()              == 0x80000001);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::denorm_min());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 1);
		VERIFY(f.unbiased_exponent()    == -126);
		VERIFY(f.unbiased_fraction()    == 0x00000001);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == -149);
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
		binary32 f{1, -149, 1};
		VERIFY(f.to_uint()              == 0x80000001);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::denorm_min());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 0);
		VERIFY(f.fraction_component()   == 1);
		VERIFY(f.unbiased_exponent()    == -126);
		VERIFY(f.unbiased_fraction()    == 0x00000001);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == -149);
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
		binary32 f{hamon::numeric_limits<T>::infinity()};
		VERIFY(f.to_uint()              == 0x7f800000);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::infinity());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 255);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 255);
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
	{
		binary32 f{uint_type{0x7f800000U}};
		VERIFY(f.to_uint()              == 0x7f800000);
		VERIFY(f.to_float()             == hamon::numeric_limits<T>::infinity());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 255);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 255);
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
		binary32 f{-hamon::numeric_limits<T>::infinity()};
		VERIFY(f.to_uint()              == 0xff800000);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::infinity());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 255);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 255);
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
	{
		binary32 f{1, 255, 0};
		VERIFY(f.to_uint()              == 0xff800000);
		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::infinity());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 255);
		VERIFY(f.fraction_component()   == 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    == 0);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 255);
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
		binary32 f{hamon::numeric_limits<T>::quiet_NaN()};
//		VERIFY(f.to_uint()              == 0x7fc00000);
//		VERIFY(f.to_float()             == hamon::numeric_limits<T>::quiet_NaN());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 255);
		VERIFY(f.fraction_component()   != 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 255);
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
		binary32 f{hamon::numeric_limits<T>::signaling_NaN()};
//		VERIFY(f.to_uint()              == 0x7fc00001);
//		VERIFY(f.to_float()             == hamon::numeric_limits<T>::signaling_NaN());
		VERIFY(f.sign_component()       == 0);
		VERIFY(f.exponent_component()   == 255);
		VERIFY(f.fraction_component()   != 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.sign()                 == 0);
		VERIFY(f.exponent()             == 255);
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
		binary32 f{-hamon::numeric_limits<T>::quiet_NaN()};
//		VERIFY(f.to_uint()              == 0xffc00000);
//		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::quiet_NaN());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 255);
		VERIFY(f.fraction_component()   != 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 255);
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
		binary32 f{-hamon::numeric_limits<T>::signaling_NaN()};
//		VERIFY(f.to_uint()              == 0xffc00001);
//		VERIFY(f.to_float()             == -hamon::numeric_limits<T>::signaling_NaN());
		VERIFY(f.sign_component()       == 1);
		VERIFY(f.exponent_component()   == 255);
		VERIFY(f.fraction_component()   != 0);
		VERIFY(f.unbiased_exponent()    == 255);
		VERIFY(f.unbiased_fraction()    != 0);
		VERIFY(f.sign()                 == 1);
		VERIFY(f.exponent()             == 255);
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

GTEST_TEST(IEEE754Test, Binary32Test)
{
	using T = float;

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(+0.0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-0.0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(+0.5f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-0.5f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(+0.0001f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-0.0001f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(+1.5f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-1.5f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(+1.125f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-1.125f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(+123.456f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-123.456f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(+1.0f / 3.0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-1.0f / 3.0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(hamon::numeric_limits<T>::min()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(hamon::numeric_limits<T>::min() * 2));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(hamon::numeric_limits<T>::min() * 3));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(hamon::numeric_limits<T>::min() * 4));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(hamon::numeric_limits<T>::max()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(hamon::numeric_limits<T>::lowest()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test( hamon::numeric_limits<T>::denorm_min()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-hamon::numeric_limits<T>::denorm_min()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test( hamon::numeric_limits<T>::denorm_min() * 2));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-hamon::numeric_limits<T>::denorm_min() * 2));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test( hamon::numeric_limits<T>::denorm_min() * 3));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-hamon::numeric_limits<T>::denorm_min() * 3));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test( hamon::numeric_limits<T>::denorm_min() * 4));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-hamon::numeric_limits<T>::denorm_min() * 4));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test( hamon::numeric_limits<T>::infinity()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-hamon::numeric_limits<T>::infinity()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test( hamon::numeric_limits<T>::quiet_NaN()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(make_floating_point_test(-hamon::numeric_limits<T>::quiet_NaN()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace binary32_test

}	// namespace hamon_ieee754_test
