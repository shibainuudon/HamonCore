/**
 *	@file	unit_test_charconv_from_chars_floating_point.cpp
 *
 *	@brief	from_chars のテスト
 *
 *	from_chars_result from_chars(const char* first, const char* last, floating-point-type& value, chars_format fmt = chars_format::general);
 */

#include <hamon/charconv/from_chars.hpp>
#include <hamon/charconv/chars_format.hpp>
#include <hamon/string_view.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/ieee754.hpp>
#include <hamon/iomanip/setw.hpp>
#include <hamon/ios.hpp>
#include <hamon/ostream/endl.hpp>
#include <hamon/cstring.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

//#define RANDOM_TEST
#if defined(RANDOM_TEST)
#include <random>
#endif

//#define PERFORMANCE_TEST
#if defined(PERFORMANCE_TEST)
#include <random>
#include <chrono>
#include <vector>
#include <string>
#endif

namespace hamon_charconv_test
{

namespace from_chars_floating_point_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
test(hamon::string_view sv, hamon::chars_format fmt, hamon::size_t expected_idx, hamon::errc expected_ec, T expected_value)
{
	T const unmodified_value{1234};
	T dest = unmodified_value;
	auto ret = hamon::from_chars(sv.data(), sv.data() + sv.size(), dest, fmt);
	VERIFY(ret.ptr == sv.data() + expected_idx);
	VERIFY(ret.ec == expected_ec);

	if (ret)
	{
		hamon::ieee754::binary<T> const bits1(dest);
		hamon::ieee754::binary<T> const bits2(expected_value);
		if (bits2.is_nan())
		{
			VERIFY(bits1.is_nan());
#if !(defined(HAMON_USE_STD_CHARCONV) && defined(HAMON_STDLIB_LIBSTDCPP3))
			// libstdc++ で chars_format::hex のときテストが通らない
			VERIFY(bits1.sign() == bits2.sign());
#endif
		}
		else
		{
#if 1
			VERIFY(bits1.to_uint() == bits2.to_uint());
#else
			if (bits1.to_uint() != bits2.to_uint())
			{
				std::cout << hamon::hex;
				std::cout << "hamon: " << bits1.to_uint() << ", ";
				std::cout << "expected: " << bits2.to_uint() << ", ";
				std::cout << hamon::dec;
	
				std::cout << "\"" << sv << "\": ";
				if (bits1.to_uint() == bits2.to_uint())
				{
					std::cout << "ok ";
				}
				else if (bits1.to_uint() > bits2.to_uint())
				{
					std::cout << "ng(+" << (bits1.to_uint() - bits2.to_uint()) << ") ";
				}
				else if (bits1.to_uint() < bits2.to_uint())
				{
					std::cout << "ng(-" << (bits2.to_uint() - bits1.to_uint()) << ") ";
				}
				std::cout << hamon::endl;
			}
#endif
		}
	}
	else if (ret.ec == hamon::errc::result_out_of_range)
	{
#if !(defined(HAMON_USE_STD_CHARCONV) && defined(HAMON_STDLIB_DINKUMWARE))
		// Microsoft-STL だと result_out_of_range のときもvalueが書き込まれる
		VERIFY(dest == unmodified_value);
#endif
	}
	else
	{
		VERIFY(dest == unmodified_value);
	}

	return true;
}

#undef VERIFY

template <typename T, hamon::chars_format fmt>
inline void inf_test()
{
	constexpr T infinity = hamon::numeric_limits<T>::infinity();

	using hamon::errc;

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("I",          fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("II",         fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("IN",         fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("INT",        fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("INF",        fmt, 3, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("INFI",       fmt, 3, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("INFIN",      fmt, 3, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("INFINI",     fmt, 3, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("INFINIT",    fmt, 3, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("INFINITX",   fmt, 3, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("INFINITY",   fmt, 8, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("INFINITYX",  fmt, 8, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("INFINITYXX", fmt, 8, errc{}, infinity));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-I",          fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-II",         fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-IN",         fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-INT",        fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-INF",        fmt, 4, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-INFI",       fmt, 4, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-INFIN",      fmt, 4, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-INFINI",     fmt, 4, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-INFINIT",    fmt, 4, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-INFINITX",   fmt, 4, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-INFINITY",   fmt, 9, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-INFINITYX",  fmt, 9, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-INFINITYXX", fmt, 9, errc{}, -infinity));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("i",          fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("ii",         fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("in",         fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("int",        fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("inf",        fmt, 3, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("infi",       fmt, 3, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("infin",      fmt, 3, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("infini",     fmt, 3, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("infinit",    fmt, 3, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("infinitx",   fmt, 3, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("infinity",   fmt, 8, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("infinityx",  fmt, 8, errc{}, infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("infinityxx", fmt, 8, errc{}, infinity));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-i",          fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-ii",         fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-in",         fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-int",        fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-inf",        fmt, 4, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-infi",       fmt, 4, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-infin",      fmt, 4, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-infini",     fmt, 4, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-infinit",    fmt, 4, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-infinitx",   fmt, 4, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-infinity",   fmt, 9, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-infinityx",  fmt, 9, errc{}, -infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-infinityxx", fmt, 9, errc{}, -infinity));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("InF",         fmt, 3, errc{},  infinity));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-iNfInItY",   fmt, 9, errc{}, -infinity));
}

template <typename T, hamon::chars_format fmt>
inline void nan_test()
{
	constexpr T nan = hamon::numeric_limits<T>::quiet_NaN();

	using hamon::errc;

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("N",          fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("NA",         fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("NAM",        fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("NAN",        fmt, 3, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("NAN(",       fmt, 3, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("NAN(!)",     fmt, 3, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("NAN(1",      fmt, 3, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("NAN(1_",     fmt, 3, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("NAN(1_A",    fmt, 3, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("NAN(1_A)",   fmt, 8, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("NAN(1_A)X",  fmt, 8, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("NAN(1_A)XX", fmt, 8, errc{}, nan));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-N",          fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-NA",         fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-NAM",        fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-NAN",        fmt, 4, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-NAN(",       fmt, 4, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-NAN(!)",     fmt, 4, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-NAN(1",      fmt, 4, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-NAN(1_",     fmt, 4, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-NAN(1_A",    fmt, 4, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-NAN(1_A)",   fmt, 9, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-NAN(1_A)X",  fmt, 9, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-NAN(1_A)XX", fmt, 9, errc{}, -nan));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("n",          fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("na",         fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("nam",        fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("nan",        fmt, 3, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("nan(",       fmt, 3, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("nan(!)",     fmt, 3, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("nan(1",      fmt, 3, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("nan(1_",     fmt, 3, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("nan(1_a",    fmt, 3, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("nan(1_a)",   fmt, 8, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("nan(1_a)x",  fmt, 8, errc{}, nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("nan(1_a)xx", fmt, 8, errc{}, nan));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-n",          fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-na",         fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-nam",        fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-nan",        fmt, 4, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-nan(",       fmt, 4, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-nan(!)",     fmt, 4, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-nan(1",      fmt, 4, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-nan(1_",     fmt, 4, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-nan(1_a",    fmt, 4, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-nan(1_a)",   fmt, 9, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-nan(1_a)x",  fmt, 9, errc{}, -nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-nan(1_a)xx", fmt, 9, errc{}, -nan));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("NaN",        fmt, 3, errc{},  nan));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-nAn",       fmt, 4, errc{}, -nan));
}

template <typename T, hamon::chars_format fmt>
inline void invalid_argument_test()
{
	using hamon::errc;

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("",      fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-",     fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(".",     fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-.",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("+0.25", fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("+1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("p5",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-p5",   fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-+1",   fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("--1",   fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("- 1",   fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("`1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("~1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("!1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("@1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("#1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("$1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("%1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("^1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("&1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("*1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("(1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(")1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("_1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("=1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("[1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("]1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("{1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("}1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("\\1",   fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("|1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(";1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(":1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("'1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("\"1",   fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(",1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("/1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("<1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(">1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("?1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(" 1",    fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("\t1",   fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("\v1",   fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("\r1",   fmt, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("\n1",   fmt, 0, errc::invalid_argument, T{0}));
}

template <typename T>
inline void fixed_test()
{
	using hamon::chars_format;
	using hamon::errc;

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("a123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("b123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("c123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("d123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("e123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("f123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("g123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("h123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("i123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("j123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("k123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("l123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("m123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("n123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("o123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("p123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("q123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("r123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("s123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("t123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("u123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("v123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("w123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("x123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("y123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("z123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("A123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("B123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("C123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("D123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("E123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("F123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("G123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("H123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("I123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("J123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("K123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("L123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("M123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("N123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("O123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("P123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("Q123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("R123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("S123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("T123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("U123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("V123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("W123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("X123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("Y123", chars_format::fixed, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("Z123", chars_format::fixed, 0, errc::invalid_argument, T{0}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0",       chars_format::fixed, 1, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0",      chars_format::fixed, 2, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0",     chars_format::fixed, 3, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.0",    chars_format::fixed, 4, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.",      chars_format::fixed, 2, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.",     chars_format::fixed, 3, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.000",   chars_format::fixed, 5, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.000",  chars_format::fixed, 6, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("000.000", chars_format::fixed, 7, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-00.000", chars_format::fixed, 7, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0e0",     chars_format::fixed, 1, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0e0",    chars_format::fixed, 2, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("00E00",   chars_format::fixed, 2, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-00E00",  chars_format::fixed, 3, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0p0",     chars_format::fixed, 1, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0p0",    chars_format::fixed, 2, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0p0",   chars_format::fixed, 3, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.0p0",  chars_format::fixed, 4, errc{}, T(-0.0)));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1729",      chars_format::fixed, 4, errc{}, T(1729)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1729e3",    chars_format::fixed, 4, errc{}, T(1729)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10",        chars_format::fixed, 2, errc{}, T(10)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("11.",       chars_format::fixed, 3, errc{}, T(11)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12.13",     chars_format::fixed, 5, errc{}, T(12.13)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123",       chars_format::fixed, 3, errc{}, T( 123)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-123",      chars_format::fixed, 4, errc{}, T(-123)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.25",      chars_format::fixed, 4, errc{}, T( 0.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.25",     chars_format::fixed, 5, errc{}, T(-0.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("001x",      chars_format::fixed, 3, errc{}, T( 1.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(".5",        chars_format::fixed, 2, errc{}, T( 0.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-.5",       chars_format::fixed, 3, errc{}, T(-0.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25.78",   chars_format::fixed, 4, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e10",    chars_format::fixed, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5E10",    chars_format::fixed, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e+10",   chars_format::fixed, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e-10",   chars_format::fixed, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e",      chars_format::fixed, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e+",     chars_format::fixed, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e-",     chars_format::fixed, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e +1",   chars_format::fixed, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e+ 1",   chars_format::fixed, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e -1",   chars_format::fixed, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e- 1",   chars_format::fixed, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e0e12", chars_format::fixed, 4, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e++12", chars_format::fixed, 4, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e+-12", chars_format::fixed, 4, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e-+12", chars_format::fixed, 4, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e--12", chars_format::fixed, 4, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e0x12", chars_format::fixed, 4, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("20040229",  chars_format::fixed, 8, errc{}, T(20040229)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456",   chars_format::fixed, 7, errc{}, T(1.23456e2)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456e3", chars_format::fixed, 7, errc{}, T(1.23456e2)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("5.0000000000000000000001", chars_format::fixed, 24, errc{}, T(5.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-5.0000000000000000000001", chars_format::fixed, 25, errc{}, T(-5.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.111111111111111111111111111111111111111111", chars_format::fixed, 44, errc{}, T(0.111111111111111111111111111111111111111111)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("111111111111.111111111111111111111111111111111111111111", chars_format::fixed, 55, errc{}, T(111111111111.111111111111111111111111111111111111111111)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		chars_format::fixed, 801, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"-1"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
		chars_format::fixed, 802, errc::result_out_of_range, T{}));
}

template <typename T>
inline void scientific_test()
{
	using hamon::chars_format;
	using hamon::errc;

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("a1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("b1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("c1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("d1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("e1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("f1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("g1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("h1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("i1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("j1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("k1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("l1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("m1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("n1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("o1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("p1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("q1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("r1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("s1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("t1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("u1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("v1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("w1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("x1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("y1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("z1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("A1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("B1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("C1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("D1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("E1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("F1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("G1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("H1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("I1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("J1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("K1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("L1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("M1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("N1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("O1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("P1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("Q1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("R1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("S1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("T1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("U1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("V1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("W1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("X1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("Y1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("Z1e0", chars_format::scientific, 0, errc::invalid_argument, T{0}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.23",      chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.23e",     chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e+",     chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e-",     chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e +1",   chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e+ 1",   chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e -1",   chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e- 1",   chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e++12", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e+-12", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e-+12", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e--12", chars_format::scientific, 0, errc::invalid_argument, T{0}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0",       chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0",      chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0",     chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.0",    chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.",      chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.",     chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.000",   chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.000",  chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("000.000", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-00.000", chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0e0",     chars_format::scientific, 3, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0e0",    chars_format::scientific, 4, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("00E00",   chars_format::scientific, 5, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-00E00",  chars_format::scientific, 6, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0p0",     chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0p0",    chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0p0",   chars_format::scientific, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.0p0",  chars_format::scientific, 0, errc::invalid_argument, T{0}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1729",       chars_format::scientific,  0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1729e3",     chars_format::scientific,  6, errc{}, T{1729000}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10",         chars_format::scientific,  0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("11.",        chars_format::scientific,  0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12.13",      chars_format::scientific,  0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.25e0",     chars_format::scientific,  6, errc{}, T( 0.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.25e0",    chars_format::scientific,  7, errc{}, T(-0.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("001e0x",     chars_format::scientific,  5, errc{}, T(1.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e0.78",  chars_format::scientific,  6, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e10",     chars_format::scientific,  6, errc{}, T(1.5e10)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5E10",     chars_format::scientific,  6, errc{}, T(1.5e10)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e+10",    chars_format::scientific,  7, errc{}, T(1.5e10)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e-10",    chars_format::scientific,  7, errc{}, T(1.5e-10)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.001e5",    chars_format::scientific,  7, errc{}, T(1.0e2)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.001e-5",   chars_format::scientific,  8, errc{}, T(1.0e-8)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e0x12",  chars_format::scientific,  6, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("20040229e0", chars_format::scientific, 10, errc{}, T(20040229)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456e-4", chars_format::scientific, 10, errc{}, T(1.23456e-2)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456e-3", chars_format::scientific, 10, errc{}, T(1.23456e-1)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456e-2", chars_format::scientific, 10, errc{}, T(1.23456e0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456e-1", chars_format::scientific, 10, errc{}, T(1.23456e1)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456e0",  chars_format::scientific,  9, errc{}, T(1.23456e2)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456e1",  chars_format::scientific,  9, errc{}, T(1.23456e3)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456e2",  chars_format::scientific,  9, errc{}, T(1.23456e4)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456e3",  chars_format::scientific,  9, errc{}, T(1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12.3456e4",  chars_format::scientific,  9, errc{}, T(1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.23456e5",  chars_format::scientific,  9, errc{}, T(1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.123456e6", chars_format::scientific, 10, errc{}, T(1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0123456e7", chars_format::scientific, 11, errc{}, T(1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.00123456e8", chars_format::scientific, 12, errc{}, T(1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-00123.456000e+003",  chars_format::scientific, 18, errc{}, T(-1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0012.3456000e+004",  chars_format::scientific, 18, errc{}, T(-1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-001.23456000e+005",  chars_format::scientific, 18, errc{}, T(-1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-000.123456000e+006", chars_format::scientific, 19, errc{}, T(-1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-000.0123456000e+007", chars_format::scientific, 20, errc{}, T(-1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-000.00123456000e+008", chars_format::scientific, 21, errc{}, T(-1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.111111111111111111111111111111111111111111e0", chars_format::scientific, 46, errc{}, T(0.111111111111111111111111111111111111111111)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("111111111111.111111111111111111111111111111111111111111e0", chars_format::scientific, 57, errc{}, T(111111111111.111111111111111111111111111111111111111111)));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e9999999999999999999999999999999999999999",   chars_format::scientific, 42, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-1e9999999999999999999999999999999999999999",  chars_format::scientific, 43, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-9999999999999999999999999999999999999999",  chars_format::scientific, 43, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-1e-9999999999999999999999999999999999999999", chars_format::scientific, 44, errc::result_out_of_range, T{}));
}

template <typename T>
inline void general_test()
{
	using hamon::chars_format;
	using hamon::errc;

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("a1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("b1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("c1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("d1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("e1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("f1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("g1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("h1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("i1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("j1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("k1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("l1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("m1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("n1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("o1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("p1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("q1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("r1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("s1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("t1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("u1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("v1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("w1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("x1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("y1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("z1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("A1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("B1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("C1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("D1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("E1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("F1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("G1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("H1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("I1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("J1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("K1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("L1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("M1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("N1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("O1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("P1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("Q1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("R1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("S1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("T1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("U1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("V1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("W1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("X1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("Y1", chars_format::general, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("Z1", chars_format::general, 0, errc::invalid_argument, T{0}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0",       chars_format::general, 1, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0",      chars_format::general, 2, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0",     chars_format::general, 3, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.0",    chars_format::general, 4, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.",      chars_format::general, 2, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.",     chars_format::general, 3, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.000",   chars_format::general, 5, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.000",  chars_format::general, 6, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("000.000", chars_format::general, 7, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-00.000", chars_format::general, 7, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0e0",     chars_format::general, 3, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0e0",    chars_format::general, 4, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("00e00",   chars_format::general, 5, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-00e00",  chars_format::general, 6, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0p0",     chars_format::general, 1, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0p0",    chars_format::general, 2, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0p0",   chars_format::general, 3, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.0p0",  chars_format::general, 4, errc{}, T(-0.0)));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.25",      chars_format::general, 4, errc{}, T( 0.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.25",     chars_format::general, 5, errc{}, T(-0.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("001x",      chars_format::general, 3, errc{}, T( 1.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(".5e0",      chars_format::general, 4, errc{}, T( 0.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-.5e0",     chars_format::general, 5, errc{}, T(-0.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(".5",        chars_format::general, 2, errc{}, T( 0.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-.5",       chars_format::general, 3, errc{}, T(-0.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25.78",   chars_format::general, 4, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e10",    chars_format::general, 6, errc{}, T(1.5e10)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5E10",    chars_format::general, 6, errc{}, T(1.5e10)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e+10",   chars_format::general, 7, errc{}, T(1.5e10)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e-10",   chars_format::general, 7, errc{}, T(1.5e-10)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e",      chars_format::general, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e+",     chars_format::general, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e-",     chars_format::general, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e +1",   chars_format::general, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e+ 1",   chars_format::general, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e -1",   chars_format::general, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e- 1",   chars_format::general, 3, errc{}, T(1.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e++12", chars_format::general, 4, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e+-12", chars_format::general, 4, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e-+12", chars_format::general, 4, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e--12", chars_format::general, 4, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e0x12", chars_format::general, 6, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25e0e12", chars_format::general, 6, errc{}, T(1.25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("20040229",  chars_format::general, 8, errc{}, T(20040229)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456",   chars_format::general, 7, errc{}, T(1.23456e2)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456e3", chars_format::general, 9, errc{}, T(1.23456e5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.111111111111111111111111111111111111111111", chars_format::general, 44, errc{}, T(0.111111111111111111111111111111111111111111)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("111111111111.111111111111111111111111111111111111111111", chars_format::general, 55, errc{}, T(111111111111.111111111111111111111111111111111111111111)));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1729",      chars_format::general, 4, errc{}, T(1729)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1729e3",    chars_format::general, 6, errc{}, T(1729000)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10",        chars_format::general, 2, errc{}, T(10)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("11.",       chars_format::general, 3, errc{}, T(11)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12.13",     chars_format::general, 5, errc{}, T(12.13)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(".14",       chars_format::general, 3, errc{}, T(0.14)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("20e5",      chars_format::general, 4, errc{}, T(2000000)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("21.e5",     chars_format::general, 5, errc{}, T(2100000)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("22.23e5",   chars_format::general, 7, errc{}, T(2223000)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(".24e5",     chars_format::general, 5, errc{}, T(24000)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("33e+5",     chars_format::general, 5, errc{}, T(3300000)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("33e-5",     chars_format::general, 5, errc{}, T(0.00033)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4E7",       chars_format::general, 3, errc{}, T{40000000}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-00123abc", chars_format::general, 6, errc{}, T{-123}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(".0045000",  chars_format::general, 8, errc{}, T(0.0045)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("000",       chars_format::general, 3, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0e9999",    chars_format::general, 6, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0e-9999",   chars_format::general, 7, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-000",      chars_format::general, 4, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0e9999",   chars_format::general, 7, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0e-9999",  chars_format::general, 8, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"e-100", chars_format::general, 106, errc{}, T(1.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"
		"e100", chars_format::general, 106, errc{}, T(1.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"3"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"e-200", chars_format::general, 206, errc{}, T(3.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000003"
		"e200", chars_format::general, 206, errc{}, T(3.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e9999",   chars_format::general, 6, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-1e9999",  chars_format::general, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-9999",  chars_format::general, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-1e-9999", chars_format::general, 8, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e9999999999999999999999999999999999999999",   chars_format::general, 42, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-1e9999999999999999999999999999999999999999",  chars_format::general, 43, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-9999999999999999999999999999999999999999",  chars_format::general, 43, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-1e-9999999999999999999999999999999999999999", chars_format::general, 44, errc::result_out_of_range, T{}));
}

template <typename T>
inline void hex_test()
{
	using hamon::chars_format;
	using hamon::errc;

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("a1", chars_format::hex, 2, errc{}, T{0xa1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("b1", chars_format::hex, 2, errc{}, T{0xb1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("c1", chars_format::hex, 2, errc{}, T{0xc1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("d1", chars_format::hex, 2, errc{}, T{0xd1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("e1", chars_format::hex, 2, errc{}, T{0xe1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("f1", chars_format::hex, 2, errc{}, T{0xf1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("g1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("h1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("i1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("j1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("k1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("l1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("m1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("n1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("o1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("p1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("q1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("r1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("s1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("t1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("u1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("v1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("w1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("x1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("y1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("z1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("A1", chars_format::hex, 2, errc{}, T{0xa1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("B1", chars_format::hex, 2, errc{}, T{0xb1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("C1", chars_format::hex, 2, errc{}, T{0xc1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("D1", chars_format::hex, 2, errc{}, T{0xd1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("E1", chars_format::hex, 2, errc{}, T{0xe1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("F1", chars_format::hex, 2, errc{}, T{0xf1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("G1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("H1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("I1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("J1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("K1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("L1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("M1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("N1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("O1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("P1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("Q1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("R1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("S1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("T1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("U1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("V1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("W1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("X1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("Y1", chars_format::hex, 0, errc::invalid_argument, T{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("Z1", chars_format::hex, 0, errc::invalid_argument, T{0}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0",       chars_format::hex, 1, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0",      chars_format::hex, 2, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0",     chars_format::hex, 3, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.0",    chars_format::hex, 4, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.",      chars_format::hex, 2, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.",     chars_format::hex, 3, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.000",   chars_format::hex, 5, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.000",  chars_format::hex, 6, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("000.000", chars_format::hex, 7, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-00.000", chars_format::hex, 7, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0e0",     chars_format::hex, 3, errc{}, T( 0xe0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0e0",    chars_format::hex, 4, errc{}, T(-0xe0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("00e00",   chars_format::hex, 5, errc{}, T( 0xe00)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-00e00",  chars_format::hex, 6, errc{}, T(-0xe00)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0p0",     chars_format::hex, 3, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0p0",    chars_format::hex, 4, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0p0",   chars_format::hex, 5, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.0p0",  chars_format::hex, 6, errc{}, T(-0.0)));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.25",      chars_format::hex, 4, errc{}, T( 0.14453125)));	// 0x0.25p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0.25",     chars_format::hex, 5, errc{}, T(-0.14453125)));	// -0x0.25p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("001x",      chars_format::hex, 3, errc{}, T(1.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(".5p0",      chars_format::hex, 4, errc{}, T( 0.3125)));		// 0x0.5p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-.5p0",     chars_format::hex, 5, errc{}, T(-0.3125)));		// -0x0.5p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(".5",        chars_format::hex, 2, errc{}, T( 0.3125)));		// 0x0.5p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-.5",       chars_format::hex, 3, errc{}, T(-0.3125)));		// -0x0.5p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25.78",   chars_format::hex, 4, errc{}, T(1.14453125)));	// 0x1.25p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5e",      chars_format::hex, 4, errc{}, T(1.3671875)));		// 0x1.5ep0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5p10",    chars_format::hex, 6, errc{}, T(1344.0)));		// 0x1.5p10
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5P10",    chars_format::hex, 6, errc{}, T(1344.0)));		// 0x1.5p10
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5p+10",   chars_format::hex, 7, errc{}, T(1344.0)));		// 0x1.5p10
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5p-10",   chars_format::hex, 7, errc{}, T(0.00128173828125)));	// 0x1.5p-10
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("001.5000p+0010", chars_format::hex, 14, errc{}, T(1344.0)));		// 0x1.5p10
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0P-7",    chars_format::hex, 6, errc{}, T(0.0078125)));		// 0x1.0p-7
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.1P-3",    chars_format::hex, 6, errc{}, T(0.0078125)));		// 0x0.1p-3
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.01P1",    chars_format::hex, 6, errc{}, T(0.0078125)));		// 0x0.01p1
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.001P5",   chars_format::hex, 7, errc{}, T(0.0078125)));		// 0x0.001p5
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.001P-5",  chars_format::hex, 8, errc{}, T(7.62939453125e-06)));	// 0x0.001p-5
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5p",      chars_format::hex, 3, errc{}, T(1.3125)));		// 0x1.5p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5p+",     chars_format::hex, 3, errc{}, T(1.3125)));		// 0x1.5p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5p-",     chars_format::hex, 3, errc{}, T(1.3125)));		// 0x1.5p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5p +1",   chars_format::hex, 3, errc{}, T(1.3125)));		// 0x1.5p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5p+ 1",   chars_format::hex, 3, errc{}, T(1.3125)));		// 0x1.5p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5p -1",   chars_format::hex, 3, errc{}, T(1.3125)));		// 0x1.5p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.5p- 1",   chars_format::hex, 3, errc{}, T(1.3125)));		// 0x1.5p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25p++12", chars_format::hex, 4, errc{}, T(1.14453125)));	// 0x1.25p0
#if !(defined(HAMON_USE_STD_CHARCONV) && defined(HAMON_STDLIB_LIBSTDCPP3))
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25p+-12", chars_format::hex, 4, errc{}, T(1.14453125)));	// 0x1.25p0
#endif
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25p-+12", chars_format::hex, 4, errc{}, T(1.14453125)));	// 0x1.25p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25p--12", chars_format::hex, 4, errc{}, T(1.14453125)));	// 0x1.25p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25p0x12", chars_format::hex, 6, errc{}, T(1.14453125)));	// 0x1.25p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.25p0p12", chars_format::hex, 6, errc{}, T(1.14453125)));	// 0x1.25p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("131CA25",   chars_format::hex, 7, errc{}, T(0x131CA25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("131ca25",   chars_format::hex, 7, errc{}, T(0x131CA25)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ap0",     chars_format::hex, 5, errc{}, T(1.625)));			// 0x1.ap0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.AP0",     chars_format::hex, 5, errc{}, T(1.625)));			// 0x1.ap0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456",   chars_format::hex, 7, errc{}, T(291.27099609375)));	// 0x123.456p0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p3", chars_format::hex, 9, errc{}, T(2330.16796875)));	// 0x123.456p3
#if defined(HAMON_HAS_CXX17_HEX_FLOAT)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p-9", chars_format::hex, 10, errc{}, T(0x123.456p-9)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p-8", chars_format::hex, 10, errc{}, T(0x123.456p-8)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p-7", chars_format::hex, 10, errc{}, T(0x123.456p-7)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p-6", chars_format::hex, 10, errc{}, T(0x123.456p-6)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p-5", chars_format::hex, 10, errc{}, T(0x123.456p-5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p-4", chars_format::hex, 10, errc{}, T(0x123.456p-4)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p-3", chars_format::hex, 10, errc{}, T(0x123.456p-3)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p-2", chars_format::hex, 10, errc{}, T(0x123.456p-2)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p-1", chars_format::hex, 10, errc{}, T(0x123.456p-1)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p-0", chars_format::hex, 10, errc{}, T(0x123.456p-0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p+1", chars_format::hex, 10, errc{}, T(0x123.456p+1)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p+2", chars_format::hex, 10, errc{}, T(0x123.456p+2)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456p+3", chars_format::hex, 10, errc{}, T(0x123.456p+3)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.111111111111111111111111111111111111111111", chars_format::hex, 44, errc{}, T(0x0.111111111111111111111111111111111111111111p0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("111111111111.111111111111111111111111111111111111111111", chars_format::hex, 55, errc{}, T(0x111111111111.111111111111111111111111111111111111111111p0)));
#endif

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10",       chars_format::hex, 2, errc{}, T(0x10)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("11.",      chars_format::hex, 3, errc{}, T(0x11)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12.00",    chars_format::hex, 5, errc{}, T(0x12)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0x123",    chars_format::hex, 1, errc{}, T(0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("a0",       chars_format::hex, 2, errc{}, T(160)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("a1.",      chars_format::hex, 3, errc{}, T(161)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("a2.a3",    chars_format::hex, 5, errc{}, T(162.63671875)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(".a4",      chars_format::hex, 3, errc{}, T(0.640625)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("a0p5",     chars_format::hex, 4, errc{}, T(5120)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("a1.p5",    chars_format::hex, 5, errc{}, T(5152)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("a2.a3p5",  chars_format::hex, 7, errc{}, T(5204.375)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(".a4p5",    chars_format::hex, 5, errc{}, T(20.5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("a0p+5",    chars_format::hex, 5, errc{}, T(5120)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("a0p-5",    chars_format::hex, 5, errc{}, T(5)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("ABCDEFP3", chars_format::hex, 8, errc{}, T(90075000)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-00cdrom", chars_format::hex, 5, errc{}, T(-205)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(".00ef000", chars_format::hex, 8, errc{}, T(0.0036468505859375)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("000",      chars_format::hex, 3, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0p9999",   chars_format::hex, 6, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0p-9999",  chars_format::hex, 7, errc{}, T( 0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-000",     chars_format::hex, 4, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0p9999",  chars_format::hex, 7, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-0p-9999", chars_format::hex, 8, errc{}, T(-0.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"p0", chars_format::hex, 104, errc{}, T(2.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"p-400", chars_format::hex, 106, errc{}, T(1.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"
		"p400", chars_format::hex, 106, errc{}, T(1.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"5"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"p-800", chars_format::hex, 206, errc{}, T(5.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000003"
		"p1200", chars_format::hex, 307, errc{}, T(3.0)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"123"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"p-1600", chars_format::hex, 409, errc{}, T(0x123)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"123"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"p-3200", chars_format::hex, 809, errc{}, T(0x123)));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1p9999",   chars_format::hex, 6, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-1p9999",  chars_format::hex, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1p-9999",  chars_format::hex, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-1p-9999", chars_format::hex, 8, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1p9999999999999999999999999999999999999999",   chars_format::hex, 42, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-1p9999999999999999999999999999999999999999",  chars_format::hex, 43, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1p-9999999999999999999999999999999999999999",  chars_format::hex, 43, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-1p-9999999999999999999999999999999999999999", chars_format::hex, 44, errc::result_out_of_range, T{}));
}

inline void float_test()
{
	using T = float;

	using hamon::chars_format;
	using hamon::errc;

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.40282347e+38",  chars_format::scientific, 14, errc{}, hamon::numeric_limits<T>::max()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.17549435e-38",  chars_format::scientific, 14, errc{}, hamon::numeric_limits<T>::min()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-3.40282347e+38", chars_format::scientific, 15, errc{}, hamon::numeric_limits<T>::lowest()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.401e-45",       chars_format::scientific,  9, errc{}, hamon::numeric_limits<T>::denorm_min()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.01e40", chars_format::scientific, 7, errc{}, 1e38f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.01e41", chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.1e39",  chars_format::scientific, 6, errc{}, 1e38f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.1e40",  chars_format::scientific, 6, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e38",    chars_format::scientific, 4, errc{}, 1e38f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e39",    chars_format::scientific, 4, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10e37",   chars_format::scientific, 5, errc{}, 1e38f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10e38",   chars_format::scientific, 5, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("100e36",  chars_format::scientific, 6, errc{}, 1e38f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("100e37",  chars_format::scientific, 6, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.01e-43", chars_format::scientific, 8, errc{}, 1e-45f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.01e-44", chars_format::scientific, 8, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.1e-44",  chars_format::scientific, 7, errc{}, 1e-45f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.1e-45",  chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-45",    chars_format::scientific, 5, errc{}, 1e-45f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-46",    chars_format::scientific, 5, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10e-46",   chars_format::scientific, 6, errc{}, 1e-45f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10e-47",   chars_format::scientific, 6, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("100e-47",  chars_format::scientific, 7, errc{}, 1e-45f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("100e-48",  chars_format::scientific, 7, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.09e39", chars_format::scientific, 7, errc{}, 9e37f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.09e40", chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.9e38",  chars_format::scientific, 6, errc{}, 9e37f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.9e39",  chars_format::scientific, 6, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9e37",    chars_format::scientific, 4, errc{}, 9e37f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9e38",    chars_format::scientific, 4, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("90e36",   chars_format::scientific, 5, errc{}, 9e37f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("90e37",   chars_format::scientific, 5, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("900e35",  chars_format::scientific, 6, errc{}, 9e37f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("900e36",  chars_format::scientific, 6, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.09e-44", chars_format::scientific, 8, errc{}, 9e-46f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.09e-45", chars_format::scientific, 8, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.9e-45",  chars_format::scientific, 7, errc{}, 9e-46f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.9e-46",  chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9e-46",    chars_format::scientific, 5, errc{}, 9e-46f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9e-47",    chars_format::scientific, 5, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("90e-47",   chars_format::scientific, 6, errc{}, 9e-46f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("90e-48",   chars_format::scientific, 6, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("900e-48",  chars_format::scientific, 7, errc{}, 9e-46f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("900e-49",  chars_format::scientific, 7, errc::result_out_of_range, T{}));

	// 6 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123456",     chars_format::general, 6, errc{}, 123456.0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12345.6",    chars_format::general, 7, errc{}, 12345.6f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456",    chars_format::general, 7, errc{}, 123.456f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.23456",    chars_format::general, 7, errc{}, 1.23456f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.123456",   chars_format::general, 8, errc{}, 0.123456f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.00123456", chars_format::general, 10, errc{}, 0.00123456f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999999",     chars_format::general, 6, errc{}, 999999.0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("99999.9",    chars_format::general, 7, errc{}, 99999.9f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999.999",    chars_format::general, 7, errc{}, 999.999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.99999",    chars_format::general, 7, errc{}, 9.99999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.999999",   chars_format::general, 8, errc{}, 0.999999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.00999999", chars_format::general, 10, errc{}, 0.00999999f));

	// 7 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1234567",     chars_format::general, 7, errc{}, 1234567.0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12345.67",    chars_format::general, 8, errc{}, 12345.67f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.4567",    chars_format::general, 8, errc{}, 123.4567f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.234567",    chars_format::general, 8, errc{}, 1.234567f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.1234567",   chars_format::general, 9, errc{}, 0.1234567f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.001234567", chars_format::general, 11, errc{}, 0.001234567f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9999999",     chars_format::general, 7, errc{}, 9999999.0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("99999.99",    chars_format::general, 8, errc{}, 99999.99f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999.9999",    chars_format::general, 8, errc{}, 999.9999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.999999",    chars_format::general, 8, errc{}, 9.999999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.9999999",   chars_format::general, 9, errc{}, 0.9999999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.009999999", chars_format::general, 11, errc{}, 0.009999999f));

	// 8 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12345678",     chars_format::general, 8, errc{}, 12345678.0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12345.678",    chars_format::general, 9, errc{}, 12345.678f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.45678",    chars_format::general, 9, errc{}, 123.45678f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.2345678",    chars_format::general, 9, errc{}, 1.2345678f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.12345678",   chars_format::general, 10, errc{}, 0.12345678f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0012345678", chars_format::general, 12, errc{}, 0.0012345678f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("99999999",     chars_format::general, 8, errc{}, 99999999.0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("99999.999",    chars_format::general, 9, errc{}, 99999.999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999.99999",    chars_format::general, 9, errc{}, 999.99999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.9999999",    chars_format::general, 9, errc{}, 9.9999999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.99999999",   chars_format::general, 10, errc{}, 0.99999999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0099999999", chars_format::general, 12, errc{}, 0.0099999999f));

	// 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123456789",     chars_format::general, 9, errc{}, 123456789.0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12345.6789",    chars_format::general, 10, errc{}, 12345.6789f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123.456789",    chars_format::general, 10, errc{}, 123.456789f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.23456789",    chars_format::general, 10, errc{}, 1.23456789f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.123456789",   chars_format::general, 11, errc{}, 0.123456789f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.00123456789", chars_format::general, 13, errc{}, 0.00123456789f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999999999",     chars_format::general, 9, errc{}, 999999999.0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("99999.9999",    chars_format::general, 10, errc{}, 99999.9999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999.999999",    chars_format::general, 10, errc{}, 999.999999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.99999999",    chars_format::general, 10, errc{}, 9.99999999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.999999999",   chars_format::general, 11, errc{}, 0.999999999f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.00999999999", chars_format::general, 13, errc{}, 0.00999999999f));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("100000000000000000000000000000000000000", chars_format::fixed, 39, errc{}, 1e38f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1000000000000000000000000000000000000000", chars_format::fixed, 40, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.000000000000000000000000000000000000000000001", chars_format::fixed, 47, errc{}, 1e-45f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0000000000000000000000000000000000000000000001", chars_format::fixed, 48, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("340282356779733661637539395458142568447", chars_format::fixed, 39, errc{}, hamon::numeric_limits<T>::max()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("340282356779733661637539395458142568448", chars_format::fixed, 39, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.00000000000000000000000000000000000000000000070064923216240853546186479164495806564013097093826", chars_format::fixed, 97, errc{}, hamon::numeric_limits<float>::denorm_min()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.00000000000000000000000000000000000000000000070064923216240853546186479164495806564013097093825", chars_format::fixed, 97, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.a0000400", chars_format::hex, 10, errc{}, 1.62500024f));	// 0x1.a00004p0f // exact
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.a0000401", chars_format::hex, 10, errc{}, 1.62500024f));	// 0x1.a00004p0f // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.a0000500", chars_format::hex, 10, errc{}, 1.62500024f));	// 0x1.a00004p0f // midpoint, round down to even
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.a0000501", chars_format::hex, 10, errc{}, 1.62500036f));	// 0x1.a00006p0f // above midpoint, round up
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.a0000600", chars_format::hex, 10, errc{}, 1.62500036f));	// 0x1.a00006p0f // exact
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.a0000601", chars_format::hex, 10, errc{}, 1.62500036f));	// 0x1.a00006p0f // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.a0000700", chars_format::hex, 10, errc{}, 1.62500048f));	// 0x1.a00008p0f // midpoint, round up to even
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.a0000701", chars_format::hex, 10, errc{}, 1.62500048f));	// 0x1.a00008p0f // above midpoint, round up

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000040", chars_format::hex, 9, errc{}, 1.00000024f));	// 0x1.000004p0f // exact
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000041", chars_format::hex, 9, errc{}, 1.00000024f));	// 0x1.000004p0f // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000050", chars_format::hex, 9, errc{}, 1.00000024f));	// 0x1.000004p0f // midpoint, round down to even
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000051", chars_format::hex, 9, errc{}, 1.00000036f));	// 0x1.000006p0f // above midpoint, round up
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000060", chars_format::hex, 9, errc{}, 1.00000036f));	// 0x1.000006p0f // exact
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000061", chars_format::hex, 9, errc{}, 1.00000036f));	// 0x1.000006p0f // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000070", chars_format::hex, 9, errc{}, 1.00000048f));	// 0x1.000008p0f // midpoint, round up to even
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000071", chars_format::hex, 9, errc{}, 1.00000048f));	// 0x1.000008p0f // above midpoint, round up

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000002384185791015625000000", chars_format::general, 30, errc{}, 1.00000024f));	// 0x1.000004p0f // exact
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000002421438694000244140625", chars_format::general, 30, errc{}, 1.00000024f));	// 0x1.000004p0f // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000002980232238769531249999", chars_format::general, 30, errc{}, 1.00000024f));	// 0x1.000004p0f // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000002980232238769531250000", chars_format::general, 30, errc{}, 1.00000024f));	// 0x1.000004p0f // midpoint, round down to even
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000002980232238769531250001", chars_format::general, 30, errc{}, 1.00000036f));	// 0x1.000006p0f // above midpoint, round up
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000003017485141754150390625", chars_format::general, 30, errc{}, 1.00000036f));	// 0x1.000006p0f // above midpoint, round up
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000003576278686523437500000", chars_format::general, 30, errc{}, 1.00000036f));	// 0x1.000006p0f // exact
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000003613531589508056640625", chars_format::general, 30, errc{}, 1.00000036f));	// 0x1.000006p0f // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000004172325134277343749999", chars_format::general, 30, errc{}, 1.00000036f));	// 0x1.000006p0f // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000004172325134277343750000", chars_format::general, 30, errc{}, 1.00000048f));	// 0x1.000008p0f // midpoint, round up to even
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000004172325134277343750001", chars_format::general, 30, errc{}, 1.00000048f));	// 0x1.000008p0f // above midpoint, round up
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000004209578037261962890625", chars_format::general, 30, errc{}, 1.00000048f));	// 0x1.000008p0f // above midpoint, round up

	// VSO-838635 "<charconv>: from_chars() mishandles certain subnormals"
	// This bug didn't actually affect float, but we should have similar test cases.
	// These values change on half-ulp boundaries:
	// 1 * 2^-150 ~= 7.01e-46 (half-ulp between zero and min subnormal)
	// 2 * 2^-150 ~= 1.40e-45 (min subnormal)
	// 3 * 2^-150 ~= 2.10e-45 (half-ulp between min subnormal and next subnormal)
	// 4 * 2^-150 ~= 2.80e-45 (next subnormal)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"6."
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666e-46",
		chars_format::scientific, 1006, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"7."
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777e-46",
		chars_format::scientific, 1006, errc{}, 1.401e-45f));	// 0x0.000002p-126f
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"8."
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888e-46",
		chars_format::scientific, 1006, errc{}, 1.401e-45f));	// 0x0.000002p-126f
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"9."
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999e-46",
		chars_format::scientific, 1006, errc{}, 1.401e-45f));	// 0x0.000002p-126f
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111e-45",
		chars_format::scientific, 1006, errc{}, 1.401e-45f));	// 0x0.000002p-126f
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222e-45",
		chars_format::scientific, 1006, errc{}, 2.803e-45f));	// 0x0.000004p-126f

	// VSO-733765 "<charconv>: [Feedback] double std::from_chars behavior on exponent out of range"
	// LWG-3081 "Floating point from_chars API does not distinguish between overflow and underflow"
	// These test cases exercise every overflow/underflow codepath.
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e+1000",       chars_format::scientific,  7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-1000",       chars_format::scientific,  7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffffp+127", chars_format::hex,        13, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e+2000",       chars_format::scientific,  7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-2000",       chars_format::scientific,  7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e+9999",       chars_format::scientific,  7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-9999",       chars_format::scientific,  7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10e+5199",      chars_format::scientific,  8, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.001e-5199",   chars_format::scientific, 11, errc::result_out_of_range, T{}));

#if defined(HAMON_HAS_CXX17_HEX_FLOAT)
	// GH-931 "<charconv>: hex from_chars(\"0.fffffffffffff8p-1022\") is incorrect"
	// Test cases for values close to std::numeric_limits<float>::min() and std::numeric_limits<float>::max()
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffp-129", chars_format::hex, 12, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.00000p-129", chars_format::hex, 12, errc{}, 0x1.000000p-126f));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffep-126", chars_format::hex, 13, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffffp-126", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.000000p-126", chars_format::hex, 13, errc{}, 0x1.000000p-126f));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffcp-127", chars_format::hex, 13, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffdp-127", chars_format::hex, 13, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffep-127", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffffp-127", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.000000p-127", chars_format::hex, 13, errc{}, 0x1.000000p-126f));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffff8p-128", chars_format::hex, 13, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffff9p-128", chars_format::hex, 13, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffbp-128", chars_format::hex, 13, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffcp-128", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffdp-128", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffep-128", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffp-128", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.000000p-128", chars_format::hex, 13, errc{}, 0x1.000000p-126f));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffff0p-129", chars_format::hex, 13, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffff1p-129", chars_format::hex, 13, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffff7p-129", chars_format::hex, 13, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffff8p-129", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffff9p-129", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffbp-129", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffcp-129", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffdp-129", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffp-129", chars_format::hex, 13, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.000000p-129", chars_format::hex, 13, errc{}, 0x1.000000p-126f));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffe0p-126", chars_format::hex, 14, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffe1p-126", chars_format::hex, 14, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffefp-126", chars_format::hex, 14, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffff0p-126", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffff1p-126", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffff7p-126", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffff8p-126", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffff9p-126", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffp-126", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000000p-126", chars_format::hex, 14, errc{}, 0x1.000000p-126f));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffc0p-127", chars_format::hex, 14, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffc1p-127", chars_format::hex, 14, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffdfp-127", chars_format::hex, 14, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffe0p-127", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffe1p-127", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffefp-127", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffff0p-127", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffff1p-127", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffp-127", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.0000000p-127", chars_format::hex, 14, errc{}, 0x1.000000p-126f));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffff80p-128", chars_format::hex, 14, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffff81p-128", chars_format::hex, 14, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffbfp-128", chars_format::hex, 14, errc{}, 0x0.fffffep-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffc0p-128", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffc1p-128", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffdfp-128", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffe0p-128", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffe1p-128", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffffp-128", chars_format::hex, 14, errc{}, 0x1.000000p-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.0000000p-128", chars_format::hex, 14, errc{}, 0x1.000000p-126f));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffffp+128", chars_format::hex, 13, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.000000p+128", chars_format::hex, 13, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffep+127", chars_format::hex, 13, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffffp+127", chars_format::hex, 13, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.000000p+127", chars_format::hex, 13, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffcp+126", chars_format::hex, 13, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffdp+126", chars_format::hex, 13, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffep+126", chars_format::hex, 13, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffp+126", chars_format::hex, 13, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.000000p+126", chars_format::hex, 13, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffff8p+125", chars_format::hex, 13, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffff9p+125", chars_format::hex, 13, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffbp+125", chars_format::hex, 13, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffcp+125", chars_format::hex, 13, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffdp+125", chars_format::hex, 13, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffp+125", chars_format::hex, 13, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.000000p+125", chars_format::hex, 13, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffff0p+128", chars_format::hex, 14, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffff1p+128", chars_format::hex, 14, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffff7p+128", chars_format::hex, 14, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffff8p+128", chars_format::hex, 14, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffff9p+128", chars_format::hex, 14, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffp+128", chars_format::hex, 14, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000000p+128", chars_format::hex, 14, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffe0p+127", chars_format::hex, 14, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffe1p+127", chars_format::hex, 14, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffefp+127", chars_format::hex, 14, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffff0p+127", chars_format::hex, 14, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffff1p+127", chars_format::hex, 14, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffp+127", chars_format::hex, 14, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.0000000p+127", chars_format::hex, 14, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffc0p+126", chars_format::hex, 14, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffc1p+126", chars_format::hex, 14, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffdfp+126", chars_format::hex, 14, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffe0p+126", chars_format::hex, 14, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffe1p+126", chars_format::hex, 14, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffffp+126", chars_format::hex, 14, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.0000000p+126", chars_format::hex, 14, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffff80p+125", chars_format::hex, 14, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffff81p+125", chars_format::hex, 14, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffbfp+125", chars_format::hex, 14, errc{}, 0x1.fffffep+127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffc0p+125", chars_format::hex, 14, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffc1p+125", chars_format::hex, 14, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffffp+125", chars_format::hex, 14, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.0000000p+125", chars_format::hex, 14, errc::result_out_of_range, T{}));

	// GH-2363 "<charconv>: from_chars() incorrectly tiebreaks floats"

	// Exhaustive testing found all affected tiebreaker values, which were in a narrow range of exponents.
	// Let's test the smallest, the largest, and 20 randomly selected values in between.
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("32768.009765625", chars_format::general, 15, errc{}, 0x1.000004p+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("32950.728515625", chars_format::general, 15, errc{}, 0x1.016d74p+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("39829.423828125", chars_format::general, 15, errc{}, 0x1.372ad8p+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("41765.416015625", chars_format::general, 15, errc{}, 0x1.464ad4p+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("42367.791015625", chars_format::general, 15, errc{}, 0x1.4aff94p+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("49636.244140625", chars_format::general, 15, errc{}, 0x1.83c87cp+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("49935.205078125", chars_format::general, 15, errc{}, 0x1.861e68p+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("52048.283203125", chars_format::general, 15, errc{}, 0x1.96a090p+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("59961.361328125", chars_format::general, 15, errc{}, 0x1.d472b8p+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("60637.314453125", chars_format::general, 15, errc{}, 0x1.d9baa0p+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("63103.197265625", chars_format::general, 15, errc{}, 0x1.ecfe64p+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("65095.119140625", chars_format::general, 15, errc{}, 0x1.fc8e3cp+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("65161.673828125", chars_format::general, 15, errc{}, 0x1.fd1358p+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("68314.64453125",  chars_format::general, 14, errc{}, 0x1.0adaa4p+16f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("73265.36328125",  chars_format::general, 14, errc{}, 0x1.1e315cp+16f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("75937.95703125",  chars_format::general, 14, errc{}, 0x1.28a1f4p+16f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("78508.66015625",  chars_format::general, 14, errc{}, 0x1.32aca8p+16f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("78948.70703125",  chars_format::general, 14, errc{}, 0x1.3464b4p+16f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("108477.36328125", chars_format::general, 15, errc{}, 0x1.a7bd5cp+16f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("112734.55078125", chars_format::general, 15, errc{}, 0x1.b85e8cp+16f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("122206.28515625", chars_format::general, 15, errc{}, 0x1.dd5e48p+16f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("131071.98828125", chars_format::general, 15, errc{}, 0x1.fffffcp+16f));

	// Let's also test unaffected tiebreaker values, randomly selected for each exponent.
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"7923236592830528266962495740723380649230754633916493372624425609233151344967804"
		"874386274605058133602142333984375e-39",
		chars_format::general, 118, errc{}, 0x0.799f74p-127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"7."
		"9763481546894792284140799767319269123329871825641034117366124028155574716969500"
		"315144614432938396930694580078125e-39",
		chars_format::general, 118, errc{}, 0x1.5b6b40p-127f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"9052005576163193690090080545739076218779912192716113693014974768909805362404608"
		"075621581519953906536102294921875e-38",
		chars_format::general, 118, errc{}, 0x1.9eea7cp-126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"4."
		"2265309874582292803629410309475053960841952808552612374871283027795302103535313"
		"16513908677734434604644775390625e-38",
		chars_format::general, 117, errc{}, 0x1.cc3a7cp-125f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"5."
		"0521038757674987704720499293483845499537646835188976896441474466307747920312820"
		"6108885933645069599151611328125e-38",
		chars_format::general, 116, errc{}, 0x1.13100cp-124f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"8145958078865600010341721150591273787373501139097227567208027653410367524555724"
		"1169080953113734722137451171875e-37",
		chars_format::general, 116, errc{}, 0x1.edfae0p-123f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"3."
		"1382891861663586697238059780935979911377608740250859087647163317316527375577805"
		"969442124478518962860107421875e-37",
		chars_format::general, 115, errc{}, 0x1.ab296cp-122f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"6."
		"9797876086336315967200058909332747298975660039248050725410743583146735979916286"
		"39647387899458408355712890625e-37",
		chars_format::general, 114, errc{}, 0x1.db050cp-121f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"2552261707310301131735683507814953029319672167192828266905128652272324862870789"
		"27489346824586391448974609375e-36",
		chars_format::general, 114, errc{}, 0x1.ab21a0p-120f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"3."
		"0025392157931951816712390941704640072310061660787724992609610478577070180605801"
		"3971778564155101776123046875e-36",
		chars_format::general, 113, errc{}, 0x1.fedb08p-119f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"3."
		"0913831527272194861570692538875246399375580080555006409365282411989828137421909"
		"559634514153003692626953125e-36",
		chars_format::general, 112, errc{}, 0x1.06fc5cp-118f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"7."
		"9075926131660942698878670560324347031415391499103386907449834237679442416890651"
		"65701322257518768310546875e-36",
		chars_format::general, 111, errc{}, 0x1.505a10p-117f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"1800516335751559288984023755321342596236508175851387819513764855863802161195508"
		"23350436985492706298828125e-35",
		chars_format::general, 111, errc{}, 0x1.cfa54cp-116f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"3."
		"2390776970430309122944828427039938718649816467607669767768809130498164350342449"
		"3246711790561676025390625e-35",
		chars_format::general, 110, errc{}, 0x1.587014p-115f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("5.2255932688598390793241011093237458992089588485788678365369526977735059602991896099410951137542724609375e-35", chars_format::general, 109, errc{}, 0x1.15d718p-114f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.4313467229831937522513906733248592628671955253540919930841626879491901291885369573719799518585205078125e-34", chars_format::general, 109, errc{}, 0x1.7c8468p-113f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.027112274456549045009474867635856246621392661089931372514201350643059384992739069275557994842529296875e-34", chars_format::general, 108, errc{}, 0x1.925f4cp-112f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.52910950487264879701434086363339665372666073168583801862173594809934940030871075578033924102783203125e-34", chars_format::general, 107, errc{}, 0x1.f46528p-111f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.14408500401507174876899455686135431757543544372026740870503143387981737078007427044212818145751953125e-33", chars_format::general, 107, errc{}, 0x1.7c2ffcp-110f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.9698051791961815762996994737792056679747397605386597391609153351321737090984242968261241912841796875e-33", chars_format::general, 106, errc{}, 0x1.474a40p-109f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("5.268514803520621083584672887951853477662515936333867229489184846880078794129076413810253143310546875e-33", chars_format::general, 105, errc{}, 0x1.b5b0ecp-108f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.50393900249692617077193139238627039193050960649333913751908575751059515823726542294025421142578125e-33", chars_format::general, 104, errc{}, 0x1.37b390p-107f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.15778658072693470652383973052161677135134628896443638739095771672538148777675814926624298095703125e-32", chars_format::general, 104, errc{}, 0x1.c0279cp-106f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.7244807257832482176334571757971227665613016308952893588905819211021253067883662879467010498046875e-32", chars_format::general, 103, errc{}, 0x1.1aed20p-105f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.299774955947486471988674091977596908356736543597116976221650386236206031753681600093841552734375e-32", chars_format::general, 102, errc{}, 0x1.7b06a8p-104f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.671437709648194711041387021312558712669432301572066952403960993223108744132332503795623779296875e-31", chars_format::general, 102, errc{}, 0x1.b1ee18p-103f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.59994065518403809358388114510645093428958941661859592155148224179583849036134779453277587890625e-31", chars_format::general, 101, errc{}, 0x1.517dd8p-102f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.8318942144363800695431588797193225258328589630883579709996755724432659917511045932769775390625e-31", chars_format::general, 100, errc{}, 0x1.399b9cp-101f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.4984982401937787548278964816524034785339731991004566698244548916818530415184795856475830078125e-30", chars_format::general, 100, errc{}, 0x1.e64a5cp-100f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.840810520824309549915000327081469707228919041030741447773078078853359329514205455780029296875e-30", chars_format::general, 99, errc{}, 0x1.ccf2a8p-99f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("6.24434504563584252360873555936105890961500091202091879127866747012376436032354831695556640625e-30", chars_format::general, 98, errc{}, 0x1.fa99f8p-98f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.14357405563248806830394721780106763644256610240970174763308619958479539491236209869384765625e-29", chars_format::general, 98, errc{}, 0x1.cfe384p-97f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.0501938784329999627247695294069037358553918019474747447272733325007720850408077239990234375e-29", chars_format::general, 97, errc{}, 0x1.9fd428p-96f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.918065382537752045370514999791991168758113433623173349484858363211969844996929168701171875e-29", chars_format::general, 96, errc{}, 0x1.27ed50p-95f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.99006253095320733224329531803019808826400019788858963831756909712566994130611419677734375e-29", chars_format::general, 95, errc{}, 0x1.c7d9b0p-94f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.37981487436018183129367585316693438412586256137069840033149148439406417310237884521484375e-28", chars_format::general, 95, errc{}, 0x1.5dd31cp-93f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.1892832933425246734052751375699547957011568640774135108273412697599269449710845947265625e-28", chars_format::general, 94, errc{}, 0x1.944a28p-92f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.208214947125685004407385115883586561941223061662775695168647871469147503376007080078125e-28", chars_format::general, 93, errc{}, 0x1.0aba30p-91f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.53021925521481334308520547568831890378451203275911307599699284764938056468963623046875e-28", chars_format::general, 92, errc{}, 0x1.2e0654p-90f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.20641961613457467701456314930996842119172184938646896767977523268200457096099853515625e-27", chars_format::general, 92, errc{}, 0x1.fc13d4p-89f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("6.3545259254129926268702973984743504130327470570682724115840755985118448734283447265625e-27", chars_format::general, 91, errc{}, 0x1.f77518p-88f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("6.558057624156852395650497230653342756577658077821180171440573758445680141448974609375e-27", chars_format::general, 90, errc{}, 0x1.03ca9cp-87f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.685447931509345893369802034392883334937914170670314462086025741882622241973876953125e-26", chars_format::general, 90, errc{}, 0x1.4dd65cp-86f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.92104252793916778850995974691044876903598705164544213630506419576704502105712890625e-26", chars_format::general, 89, errc{}, 0x1.84523cp-85f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.2676408587794702077274095979725639958611387025921857230059686116874217987060546875e-26", chars_format::general, 88, errc{}, 0x1.67e04cp-84f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.4607320741942756095091207439691928681086731389715538398377248086035251617431640625e-25", chars_format::general, 88, errc{}, 0x1.69a8e4p-83f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.217546818907087816811047188015620590059197303478555340916500426828861236572265625e-25", chars_format::general, 87, errc{}, 0x1.8e5020p-82f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("5.81345842551030848951581432599921978585967574648663003245019353926181793212890625e-25", chars_format::general, 86, errc{}, 0x1.67d5ecp-81f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.43561773817828810465400997910748526263484403653336585193756036460399627685546875e-24", chars_format::general, 86, errc{}, 0x1.bc4d5cp-80f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.5009625084618796563722303923603734938409248744761725902208127081394195556640625e-24", chars_format::general, 85, errc{}, 0x1.830154p-79f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("6.438555504592931467616905908606949357313176118822184434975497424602508544921875e-24", chars_format::general, 84, errc{}, 0x1.f228bcp-78f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.45391553342758431936910945007871841412605551369097156566567718982696533203125e-24", chars_format::general, 83, errc{}, 0x1.205c00p-77f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.82608874999407002016879928138061808286229936726385858491994440555572509765625e-23", chars_format::general, 83, errc{}, 0x1.613788p-76f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.0330971320549669261149152074471678670886110040783023578114807605743408203125e-23", chars_format::general, 82, errc{}, 0x1.2557d8p-75f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.047615800390950046412361683906950236833122147572794347070157527923583984375e-23", chars_format::general, 81, errc{}, 0x1.b58410p-74f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.629918590838835760835440489828636854985344228907706565223634243011474609375e-22", chars_format::general, 81, errc{}, 0x1.8a1714p-73f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.94048252657369943370189521798427866039471467729526921175420284271240234375e-22", chars_format::general, 80, errc{}, 0x1.dc6008p-72f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.5786579984697799420054304420112968598832736688564182259142398834228515625e-22", chars_format::general, 79, errc{}, 0x1.14c34cp-71f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.946302141897925829519555652514541110864598749685683287680149078369140625e-22", chars_format::general, 78, errc{}, 0x1.0e62a8p-70f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.785950090342239162572248012514526671612458130766754038631916046142578125e-21", chars_format::general, 78, errc{}, 0x1.0de298p-69f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.99766551986752957756650266409916005816427286845282651484012603759765625e-21", chars_format::general, 77, errc{}, 0x1.799ce8p-68f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.9155832354254179919041673591482977112576691069989465177059173583984375e-21", chars_format::general, 76, errc{}, 0x1.7699a4p-67f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.4567686668860434866995250016534491077635493638808839023113250732421875e-20", chars_format::general, 76, errc{}, 0x1.d0120cp-66f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.521465064266366565038455919457727194554763627820648252964019775390625e-20", chars_format::general, 75, errc{}, 0x1.4c97ccp-65f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.043311371320997812921560553116318015298702448490075767040252685546875e-19", chars_format::general, 75, errc{}, 0x1.ecb09cp-64f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.11466519938330895530585545015467285878685288480482995510101318359375e-19", chars_format::general, 74, errc{}, 0x1.f34facp-63f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.7626650824614047437024762048085602117453163373284041881561279296875e-19", chars_format::general, 73, errc{}, 0x1.bc3794p-62f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("5.249785768098752555444624391667307605757741839624941349029541015625e-19", chars_format::general, 72, errc{}, 0x1.35e484p-61f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.128701335814771964497524141257667196214242721907794475555419921875e-18", chars_format::general, 72, errc{}, 0x1.4d2244p-60f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.23260849556985473582620786714425520358417998068034648895263671875e-18", chars_format::general, 71, errc{}, 0x1.dd0c80p-59f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.0576668728638010490692746012886260587038123048841953277587890625e-18", chars_format::general, 70, errc{}, 0x1.2b6728p-58f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.186700258225558131971837105833600389814819209277629852294921875e-18", chars_format::general, 69, errc{}, 0x1.092478p-57f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.138252536308654690329865422082633585887379013001918792724609375e-17", chars_format::general, 69, errc{}, 0x1.8a7020p-56f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.36587053893605176488161567771584259389783255755901336669921875e-17", chars_format::general, 68, errc{}, 0x1.367260p-55f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00199381992365684217356769369899893717956729233264923095703125e-16", chars_format::general, 68, errc{}, 0x1.ce168cp-54f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.9106309771233949130857243670078560171532444655895233154296875e-16", chars_format::general, 67, errc{}, 0x1.b88fc0p-53f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.252045275092124797418347004196448324364610016345977783203125e-16", chars_format::general, 66, errc{}, 0x1.03a4a4p-52f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("6.25785373862855725905773862649539296398870646953582763671875e-16", chars_format::general, 65, errc{}, 0x1.68bda0p-51f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.32820065379350552882409264299212736659683287143707275390625e-15", chars_format::general, 65, errc{}, 0x1.7ed3e8p-50f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.3481136115450535299664647226336455787532031536102294921875e-15", chars_format::general, 64, errc{}, 0x1.e28398p-49f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.091466655560993710694095426561034400947391986846923828125e-15", chars_format::general, 63, errc{}, 0x1.26d23cp-48f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.408177409382050000730135508320017834194004535675048828125e-14", chars_format::general, 63, errc{}, 0x1.fb5970p-47f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.79331010158792060471544260735754505731165409088134765625e-14", chars_format::general, 62, errc{}, 0x1.f732b0p-46f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.3619857454079450642669968374320887960493564605712890625e-14", chars_format::general, 61, errc{}, 0x1.2ed21cp-45f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.967467678253245033648255457592313177883625030517578125e-14", chars_format::general, 60, errc{}, 0x1.93dbdcp-44f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.533036460906085640676366210755077190697193145751953125e-13", chars_format::general, 60, errc{}, 0x1.593588p-43f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.58161398617069715033522925295983441174030303955078125e-13", chars_format::general, 59, errc{}, 0x1.22a9f4p-42f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("6.5738964293883539458107634345651604235172271728515625e-13", chars_format::general, 58, errc{}, 0x1.7213d4p-41f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.7410922421683128202829493602621369063854217529296875e-12", chars_format::general, 58, errc{}, 0x1.ea12ecp-40f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.744738355868470147669313519145362079143524169921875e-12", chars_format::general, 57, errc{}, 0x1.8249a0p-39f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("6.56692126892177707730979818734340369701385498046875e-12", chars_format::general, 56, errc{}, 0x1.ce1b24p-38f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.44632227201679786077193057280965149402618408203125e-11", chars_format::general, 56, errc{}, 0x1.fce120p-37f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.3307480077894293657436719513498246669769287109375e-11", chars_format::general, 55, errc{}, 0x1.9a0790p-36f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.202403529329767906119741383008658885955810546875e-11", chars_format::general, 54, errc{}, 0x1.71a5b8p-35f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("6.17056440666008398920894251205027103424072265625e-11", chars_format::general, 53, errc{}, 0x1.0f6260p-34f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.51108479895523117875200114212930202484130859375e-10", chars_format::general, 53, errc{}, 0x1.4c4a84p-33f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.4807842158878230520713259465992450714111328125e-10", chars_format::general, 52, errc{}, 0x1.ecaadcp-32f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.568819820364836914450279437005519866943359375e-10", chars_format::general, 51, errc{}, 0x1.d7136cp-31f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.827674067644835531609714962542057037353515625e-09", chars_format::general, 51, errc{}, 0x1.f66320p-30f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.55838325472035421626060269773006439208984375e-09", chars_format::general, 50, errc{}, 0x1.e90f7cp-29f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("6.8140402209593275983934290707111358642578125e-09", chars_format::general, 49, errc{}, 0x1.d441dcp-28f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0499675351383075394551269710063934326171875e-08", chars_format::general, 49, errc{}, 0x1.68c420p-27f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.164483614564005620195530354976654052734375e-08", chars_format::general, 48, errc{}, 0x1.73db00p-26f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.37830687868745371815748512744903564453125e-08", chars_format::general, 47, errc{}, 0x1.2231c0p-25f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.2113939587079585180617868900299072265625e-08", chars_format::general, 46, errc{}, 0x1.8ba058p-24f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.3198621335041025304235517978668212890625e-07", chars_format::general, 46, errc{}, 0x1.f22fc4p-23f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.606612407087595784105360507965087890625e-07", chars_format::general, 45, errc{}, 0x1.eea198p-22f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.89136976209192653186619281768798828125e-07", chars_format::general, 44, errc{}, 0x1.a7aa28p-21f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.61564861400620429776608943939208984375e-06", chars_format::general, 44, errc{}, 0x1.b1b288p-20f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.5691997481990256346762180328369140625e-06", chars_format::general, 43, errc{}, 0x1.df0cc4p-19f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("6.589127906408975832164287567138671875e-06", chars_format::general, 42, errc{}, 0x1.ba305cp-18f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.23689594856114126741886138916015625e-06", chars_format::general, 41, errc{}, 0x1.35f054p-17f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.76851235664798878133296966552734375e-05", chars_format::general, 41, errc{}, 0x1.28b508p-16f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.5296461394173093140125274658203125e-05", chars_format::general, 40, errc{}, 0x1.7bf968p-15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.173325113602913916110992431640625e-05", chars_format::general, 39, errc{}, 0x1.56d068p-14f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0001931115912157110869884490966796875", chars_format::general, 39, errc{}, 0x1.94fc00p-13f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.000384750441298820078372955322265625", chars_format::general, 38, errc{}, 0x1.9370a8p-12f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.00082240489427931606769561767578125", chars_format::general, 37, errc{}, 0x1.af2d50p-11f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0012993388227187097072601318359375", chars_format::general, 36, errc{}, 0x1.549d28p-10f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.002476190333254635334014892578125", chars_format::general, 35, errc{}, 0x1.448f28p-9f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.00660236063413321971893310546875", chars_format::general, 34, errc{}, 0x1.b0b13cp-8f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0111609757877886295318603515625", chars_format::general, 33, errc{}, 0x1.6db90cp-7f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.028554522432386875152587890625", chars_format::general, 32, errc{}, 0x1.d3d658p-6f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.03125220723450183868408203125", chars_format::general, 31, errc{}, 0x1.0004a0p-5f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0642316825687885284423828125", chars_format::general, 30, errc{}, 0x1.0717ccp-4f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.179558120667934417724609375", chars_format::general, 29, errc{}, 0x1.6fbc2cp-3f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.33023141324520111083984375", chars_format::general, 28, errc{}, 0x1.522830p-2f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.7265469729900360107421875", chars_format::general, 27, errc{}, 0x1.73fdf8p-1f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.073021352291107177734375", chars_format::general, 26, errc{}, 0x1.12b188p+0f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.05038106441497802734375", chars_format::general, 25, errc{}, 0x1.8672e4p+1f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("5.8614952564239501953125", chars_format::general, 24, errc{}, 0x1.7722bcp+2f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("13.501944065093994140625", chars_format::general, 24, errc{}, 0x1.b00fecp+3f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("17.92080020904541015625", chars_format::general, 23, errc{}, 0x1.1ebb98p+4f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("36.8445644378662109375", chars_format::general, 22, errc{}, 0x1.26c1acp+5f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("82.332279205322265625", chars_format::general, 21, errc{}, 0x1.495440p+6f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("226.95777130126953125", chars_format::general, 21, errc{}, 0x1.c5ea60p+7f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("434.9633941650390625", chars_format::general, 20, errc{}, 0x1.b2f6a0p+8f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("833.712188720703125", chars_format::general, 19, errc{}, 0x1.a0db28p+9f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1322.31732177734375", chars_format::general, 19, errc{}, 0x1.4a9450p+10f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2362.0552978515625", chars_format::general, 18, errc{}, 0x1.2741c4p+11f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("5408.731689453125", chars_format::general, 17, errc{}, 0x1.520bb4p+12f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("14641.10107421875", chars_format::general, 17, errc{}, 0x1.c988d0p+13f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("25027.6005859375", chars_format::general, 16, errc{}, 0x1.870e68p+14f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("54428.662109375", chars_format::general, 15, errc{}, 0x1.a93954p+15f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("72497.15234375", chars_format::general, 14, errc{}, 0x1.1b3128p+16f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("235931.7109375", chars_format::general, 14, errc{}, 0x1.cccddcp+17f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("307448.546875", chars_format::general, 13, errc{}, 0x1.2c3e24p+18f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("754206.65625", chars_format::general, 12, errc{}, 0x1.7043d4p+19f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2016023.0625", chars_format::general, 12, errc{}, 0x1.ec3170p+20f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3692696.375", chars_format::general, 11, errc{}, 0x1.c2c4c4p+21f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("5815279.75", chars_format::general, 10, errc{}, 0x1.62efc0p+22f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9008092.5", chars_format::general, 9, errc{}, 0x1.12e7b8p+23f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("24241463", chars_format::general, 8, errc{}, 0x1.71e538p+24f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("47982950", chars_format::general, 8, errc{}, 0x1.6e14b4p+25f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("79131332", chars_format::general, 8, errc{}, 0x1.2ddcb0p+26f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("264700808", chars_format::general, 9, errc{}, 0x1.f8e070p+27f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("517046992", chars_format::general, 9, errc{}, 0x1.ed182cp+28f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1048496800", chars_format::general, 10, errc{}, 0x1.f3f654p+29f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1705101376", chars_format::general, 10, errc{}, 0x1.968720p+30f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3130702976", chars_format::general, 10, errc{}, 0x1.753578p+31f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4417548032", chars_format::general, 10, errc{}, 0x1.074e70p+32f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10297078272", chars_format::general, 11, errc{}, 0x1.32e078p+33f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("24396919808", chars_format::general, 11, errc{}, 0x1.6b8adcp+34f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("55037933568", chars_format::general, 11, errc{}, 0x1.9a1088p+35f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("75542540288", chars_format::general, 11, errc{}, 0x1.196afcp+36f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("190329544704", chars_format::general, 12, errc{}, 0x1.628434p+37f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("287595773952", chars_format::general, 12, errc{}, 0x1.0bd82cp+38f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("652336922624", chars_format::general, 12, errc{}, 0x1.2fc4a0p+39f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1446220857344", chars_format::general, 13, errc{}, 0x1.50b97cp+40f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3049650257920", chars_format::general, 13, errc{}, 0x1.6306a8p+41f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("5804429934592", chars_format::general, 13, errc{}, 0x1.51dcc0p+42f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("11915443568640", chars_format::general, 14, errc{}, 0x1.5ac8f8p+43f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("23060968112128", chars_format::general, 14, errc{}, 0x1.4f94ccp+44f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("43325560193024", chars_format::general, 14, errc{}, 0x1.3b3c24p+45f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("114586283933696", chars_format::general, 15, errc{}, 0x1.a0dcccp+46f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("165860253630464", chars_format::general, 15, errc{}, 0x1.2db2b4p+47f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("542710977003520", chars_format::general, 15, errc{}, 0x1.ed97c0p+48f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("965357284098048", chars_format::general, 15, errc{}, 0x1.b6fe60p+49f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2126963569328128", chars_format::general, 16, errc{}, 0x1.e39d94p+50f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4012942697693184", chars_format::general, 16, errc{}, 0x1.c83800p+51f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("6463381124939776", chars_format::general, 16, errc{}, 0x1.6f6694p+52f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("17146205767204864", chars_format::general, 17, errc{}, 0x1.e75310p+53f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("21552825569902592", chars_format::general, 17, errc{}, 0x1.3248b8p+54f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("50492608341868544", chars_format::general, 17, errc{}, 0x1.66c584p+55f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("72139932855959552", chars_format::general, 17, errc{}, 0x1.004ae4p+56f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("149368027568144384", chars_format::general, 18, errc{}, 0x1.0954b8p+57f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("396127084272943104", chars_format::general, 18, errc{}, 0x1.5fd4e0p+58f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1027503202523676672", chars_format::general, 19, errc{}, 0x1.c84d98p+59f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1889396589282197504", chars_format::general, 19, errc{}, 0x1.a387c4p+60f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4358042567233765376", chars_format::general, 19, errc{}, 0x1.e3d704p+61f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("6661772452537827328", chars_format::general, 19, errc{}, 0x1.71cd7cp+62f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("15659299028611366912", chars_format::general, 20, errc{}, 0x1.b2a204p+63f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("34719363332678090752", chars_format::general, 20, errc{}, 0x1.e1d3f4p+64f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("56007321318863142912", chars_format::general, 20, errc{}, 0x1.84a0fcp+65f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("109582346995225329664", chars_format::general, 21, errc{}, 0x1.7c30acp+66f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("205592815038392958976", chars_format::general, 21, errc{}, 0x1.64a58cp+67f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("476054177287663255552", chars_format::general, 21, errc{}, 0x1.9ce944p+68f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1051627984347285422080", chars_format::general, 22, errc{}, 0x1.c81228p+69f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1971178902422676307968", chars_format::general, 22, errc{}, 0x1.ab6e68p+70f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4615826656072290009088", chars_format::general, 22, errc{}, 0x1.f472ecp+71f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("5655963530048479166464", chars_format::general, 22, errc{}, 0x1.329c44p+72f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("11976266551929262309376", chars_format::general, 23, errc{}, 0x1.449e0cp+73f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("36646036739993324486656", chars_format::general, 23, errc{}, 0x1.f0a57cp+74f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("73466416828761415614464", chars_format::general, 23, errc{}, 0x1.f1d3ecp+75f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("117009017214230505455616", chars_format::general, 24, errc{}, 0x1.8c7124p+76f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("261226819807596014206976", chars_format::general, 24, errc{}, 0x1.ba8914p+77f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("468228210431424156663808", chars_format::general, 24, errc{}, 0x1.8c9ad0p+78f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("743456640415721750265856", chars_format::general, 24, errc{}, 0x1.3addbcp+79f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1376733616667749789990912", chars_format::general, 25, errc{}, 0x1.2388e0p+80f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3534605563891024308207616", chars_format::general, 25, errc{}, 0x1.763dacp+81f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4963493386259515769356288", chars_format::general, 25, errc{}, 0x1.06c3e0p+82f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("17187232093698040119951360", chars_format::general, 26, errc{}, 0x1.c6f138p+83f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("36669956267341413919752192", chars_format::general, 26, errc{}, 0x1.e552a4p+84f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("42141169478804802988146688", chars_format::general, 26, errc{}, 0x1.16ddecp+85f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("137259072870922187668717568", chars_format::general, 27, errc{}, 0x1.c626f4p+86f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("186185505916516565814083584", chars_format::general, 27, errc{}, 0x1.3404a0p+87f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("431827819461650810014793728", chars_format::general, 27, errc{}, 0x1.653318p+88f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1211174145675821042276237312", chars_format::general, 28, errc{}, 0x1.f4ee0cp+89f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1345637370063013570745991168", chars_format::general, 28, errc{}, 0x1.164574p+90f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4758899447850887737451216896", chars_format::general, 28, errc{}, 0x1.ec0f04p+91f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("5566877020882094785904508928", chars_format::general, 28, errc{}, 0x1.1fcd00p+92f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("17694039586751044919626825728", chars_format::general, 29, errc{}, 0x1.c96154p+93f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("38593678210471799446053060608", chars_format::general, 29, errc{}, 0x1.f2cfc4p+94f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("45160087484195316006301728768", chars_format::general, 29, errc{}, 0x1.23d718p+95f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("129112233891849681667027369984", chars_format::general, 30, errc{}, 0x1.a12f24p+96f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("216656630175808433440891600896", chars_format::general, 30, errc{}, 0x1.5e0714p+97f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("421994276797224408704817823744", chars_format::general, 30, errc{}, 0x1.54e260p+98f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("874649254673651316624210264064", chars_format::general, 30, errc{}, 0x1.61449cp+99f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2166125251618050241024537657344", chars_format::general, 31, errc{}, 0x1.b5720cp+100f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3935861558640302891443247120384", chars_format::general, 31, errc{}, 0x1.8d6ba4p+101f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7350508048337774175132848226304", chars_format::general, 31, errc{}, 0x1.731b18p+102f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("17765603154846586025383087308800", chars_format::general, 32, errc{}, 0x1.c07784p+103f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("39676973205045980650327714562048", chars_format::general, 32, errc{}, 0x1.f4cb38p+104f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("76773363684136016947294228185088", chars_format::general, 32, errc{}, 0x1.e48210p+105f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("161017366677536368674469150982144", chars_format::general, 33, errc{}, 0x1.fc14ccp+106f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("269022059539305734989663994642432", chars_format::general, 33, errc{}, 0x1.a87124p+107f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("396772452133553939418920234516480", chars_format::general, 33, errc{}, 0x1.38ff90p+108f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("699126211644530005899810908930048", chars_format::general, 33, errc{}, 0x1.13c1b4p+109f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1733807367140220814406037893283840", chars_format::general, 34, errc{}, 0x1.55eee8p+110f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3660103578413974514481484236062720", chars_format::general, 34, errc{}, 0x1.68ea00p+111f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8478997023821539945225867390615552", chars_format::general, 34, errc{}, 0x1.a20bfcp+112f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("13967954142855725924178258573656064", chars_format::general, 35, errc{}, 0x1.585630p+113f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("32311637611412935510718602954145792", chars_format::general, 35, errc{}, 0x1.8e458cp+114f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("57660169510975349749437807131099136", chars_format::general, 35, errc{}, 0x1.635bb4p+115f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("83588925144890861008382505730965504", chars_format::general, 35, errc{}, 0x1.019408p+116f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("280981044275986616573540753022648320", chars_format::general, 36, errc{}, 0x1.b0eb7cp+117f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("540580110894867345113842255044542464", chars_format::general, 36, errc{}, 0x1.a072a0p+118f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("750565105750951431544116449153908736", chars_format::general, 36, errc{}, 0x1.211b70p+119f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2519671464696457305794640027949465600", chars_format::general, 37, errc{}, 0x1.e54564p+120f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4192806175473153074327132029524639744", chars_format::general, 37, errc{}, 0x1.93c0a8p+121f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10368829531117867053281330031553937408", chars_format::general, 38, errc{}, 0x1.f33db0p+122f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("20997008966187027788044272068598956032", chars_format::general, 38, errc{}, 0x1.f97c10p+123f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("27164209632110478318892728203406737408", chars_format::general, 38, errc{}, 0x1.46fa30p+124f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("61783690480066413003444625390581055488", chars_format::general, 38, errc{}, 0x1.73d8d8p+125f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("138779583669858850032422956217074188288", chars_format::general, 39, errc{}, 0x1.a19fe8p+126f));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("330107300636279331787628201852738207744", chars_format::general, 39, errc{}, 0x1.f0b0b4p+127f));
#endif

	{
		const char* s = "7.411412e-39U";
		const auto len = hamon::strlen(s) - 1;
		const char* last = s + len;

		EXPECT_TRUE(test(hamon::string_view(s, last), chars_format::general, len, errc{}, 7.411412e-39F));
	}

#if defined(HAMON_HAS_CXX17_HEX_FLOAT)
    // See LWG-2403. This number (exactly 0x1.fffffd00000004 in infinite precision) behaves differently
    // when parsed as double and converted to float, versus being parsed as float directly.
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1.999999821186065729339276231257827021181583404541015625", chars_format::general, 56, errc{}, 0x1.fffffep0f));
#endif
}

inline void double_test()
{
	using T = double;

	using hamon::chars_format;
	using hamon::errc;

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.7976931348623157e+308", chars_format::scientific, 23, errc{}, hamon::numeric_limits<T>::max()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.2250738585072014e-308", chars_format::scientific, 23, errc{}, hamon::numeric_limits<T>::min()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("-1.7976931348623157e+308", chars_format::scientific, 24, errc{}, hamon::numeric_limits<T>::lowest()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.940656458412e-324", chars_format::scientific, 19, errc{}, hamon::numeric_limits<T>::denorm_min()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.01e310", chars_format::scientific, 8, errc{}, 1e308));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.01e311", chars_format::scientific, 8, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.1e309",  chars_format::scientific, 7, errc{}, 1e308));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.1e310",  chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e308",    chars_format::scientific, 5, errc{}, 1e308));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e309",    chars_format::scientific, 5, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10e307",   chars_format::scientific, 6, errc{}, 1e308));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10e308",   chars_format::scientific, 6, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("100e306",  chars_format::scientific, 7, errc{}, 1e308));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("100e307",  chars_format::scientific, 7, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.01e-321", chars_format::scientific, 9, errc{}, 1e-323));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.01e-322", chars_format::scientific, 9, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.1e-322",  chars_format::scientific, 8, errc{}, 1e-323));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.1e-323",  chars_format::scientific, 8, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-323",    chars_format::scientific, 6, errc{}, 1e-323));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-324",    chars_format::scientific, 6, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10e-324",   chars_format::scientific, 7, errc{}, 1e-323));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10e-325",   chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("100e-325",  chars_format::scientific, 8, errc{}, 1e-323));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("100e-326",  chars_format::scientific, 8, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.09e309", chars_format::scientific, 8, errc{}, 9e307));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.09e310", chars_format::scientific, 8, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.9e308",  chars_format::scientific, 7, errc{}, 9e307));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.9e309",  chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9e307",    chars_format::scientific, 5, errc{}, 9e307));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9e308",    chars_format::scientific, 5, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("90e306",   chars_format::scientific, 6, errc{}, 9e307));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("90e307",   chars_format::scientific, 6, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("900e305",  chars_format::scientific, 7, errc{}, 9e307));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("900e306",  chars_format::scientific, 7, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.09e-322", chars_format::scientific, 9, errc{}, 9e-324));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.09e-323", chars_format::scientific, 9, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.9e-323",  chars_format::scientific, 8, errc{}, 9e-324));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.9e-324",  chars_format::scientific, 8, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9e-324",    chars_format::scientific, 6, errc{}, 9e-324));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9e-325",    chars_format::scientific, 6, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("90e-325",   chars_format::scientific, 7, errc{}, 9e-324));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("90e-326",   chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("900e-326",  chars_format::scientific, 8, errc{}, 9e-324));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("900e-327",  chars_format::scientific, 8, errc::result_out_of_range, T{}));

	// 16 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1234567891234567",     chars_format::general, 16, errc{}, 1234567891234567.0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123456789123456.7",    chars_format::general, 17, errc{}, 123456789123456.7));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123456789.1234567",    chars_format::general, 17, errc{}, 123456789.1234567));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.234567891234567",    chars_format::general, 17, errc{}, 1.234567891234567));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.1234567891234567",   chars_format::general, 18, errc{}, 0.1234567891234567));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.001234567891234567", chars_format::general, 20, errc{}, 0.001234567891234567));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9999999999999999",     chars_format::general, 16, errc{}, 9999999999999999.0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999999999999999.9",    chars_format::general, 17, errc{}, 999999999999999.9));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999999999.9999999",    chars_format::general, 17, errc{}, 999999999.9999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.999999999999999",    chars_format::general, 17, errc{}, 9.999999999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.9999999999999999",   chars_format::general, 18, errc{}, 0.9999999999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.009999999999999999", chars_format::general, 20, errc{}, 0.009999999999999999));

	// 17 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12345678912345678",     chars_format::general, 17, errc{}, 12345678912345678.0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1234567891234567.8",    chars_format::general, 18, errc{}, 1234567891234567.8));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123456789.12345678",    chars_format::general, 18, errc{}, 123456789.12345678));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.2345678912345678",    chars_format::general, 18, errc{}, 1.2345678912345678));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.12345678912345678",   chars_format::general, 19, errc{}, 0.12345678912345678));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0012345678912345678", chars_format::general, 21, errc{}, 0.0012345678912345678));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("99999999999999999",     chars_format::general, 17, errc{}, 99999999999999999.0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9999999999999999.9",    chars_format::general, 18, errc{}, 9999999999999999.9));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999999999.99999999",    chars_format::general, 18, errc{}, 999999999.99999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.9999999999999999",    chars_format::general, 18, errc{}, 9.9999999999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.99999999999999999",   chars_format::general, 19, errc{}, 0.99999999999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0099999999999999999", chars_format::general, 21, errc{}, 0.0099999999999999999));

	// 18 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123456789123456789",     chars_format::general, 18, errc{}, 123456789123456789.0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12345678912345678.9",    chars_format::general, 19, errc{}, 12345678912345678.9));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123456789.123456789",    chars_format::general, 19, errc{}, 123456789.123456789));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.23456789123456789",    chars_format::general, 19, errc{}, 1.23456789123456789));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.123456789123456789",   chars_format::general, 20, errc{}, 0.123456789123456789));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.00123456789123456789", chars_format::general, 22, errc{}, 0.00123456789123456789));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999999999999999999",     chars_format::general, 18, errc{}, 999999999999999999.0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("99999999999999999.9",    chars_format::general, 19, errc{}, 99999999999999999.9));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999999999.999999999",    chars_format::general, 19, errc{}, 999999999.999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.99999999999999999",    chars_format::general, 19, errc{}, 9.99999999999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.999999999999999999",   chars_format::general, 20, errc{}, 0.999999999999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.00999999999999999999", chars_format::general, 22, errc{}, 0.00999999999999999999));

	// 19 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1234567891234567891",     chars_format::general, 19, errc{}, 1234567891234567891.0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123456789123456789.1",    chars_format::general, 20, errc{}, 123456789123456789.1));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123456789.1234567891",    chars_format::general, 20, errc{}, 123456789.1234567891));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.234567891234567891",    chars_format::general, 20, errc{}, 1.234567891234567891));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.1234567891234567891",   chars_format::general, 21, errc{}, 0.1234567891234567891));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.001234567891234567891", chars_format::general, 23, errc{}, 0.001234567891234567891));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9999999999999999999",     chars_format::general, 19, errc{}, 9999999999999999999.0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999999999999999999.9",    chars_format::general, 20, errc{}, 999999999999999999.9));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999999999.9999999999",    chars_format::general, 20, errc{}, 999999999.9999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.999999999999999999",    chars_format::general, 20, errc{}, 9.999999999999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.9999999999999999999",   chars_format::general, 21, errc{}, 0.9999999999999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.009999999999999999999", chars_format::general, 23, errc{}, 0.009999999999999999999));

	// 20 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("12345678912345678912",     chars_format::general, 20, errc{}, 12345678912345678912.0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1234567891234567891.2",    chars_format::general, 21, errc{}, 1234567891234567891.2));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("123456789.12345678912",    chars_format::general, 21, errc{}, 123456789.12345678912));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.2345678912345678912",    chars_format::general, 21, errc{}, 1.2345678912345678912));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.12345678912345678912",   chars_format::general, 22, errc{}, 0.12345678912345678912));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0012345678912345678912", chars_format::general, 24, errc{}, 0.0012345678912345678912));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("99999999999999999999",     chars_format::general, 20, errc{}, 99999999999999999999.0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9999999999999999999.9",    chars_format::general, 21, errc{}, 9999999999999999999.9));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("999999999.99999999999",    chars_format::general, 21, errc{}, 999999999.99999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("9.9999999999999999999",    chars_format::general, 21, errc{}, 9.9999999999999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.99999999999999999999",   chars_format::general, 22, errc{}, 0.99999999999999999999));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0099999999999999999999", chars_format::general, 24, errc{}, 0.0099999999999999999999));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"100000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		chars_format::fixed, 309, errc{}, 1e308));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		chars_format::fixed, 310, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000001",
		chars_format::fixed, 325, errc{}, 1e-323));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"000000000000000000000001",
		chars_format::fixed, 326, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"179769313"
		"4862315807937289714053034150799341327100378269361737789804449682927647509466490179775872070963302864"
		"1669288791094655554785000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		chars_format::fixed, 309, errc{}, hamon::numeric_limits<T>::max()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"179769313"
		"4862315807937289714053034150799341327100378269361737789804449682927647509466490179775872070963302864"
		"1669288791094655554786000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		chars_format::fixed, 309, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000"
		"24703282292062327208828439643411068618252990130717",
		chars_format::fixed, 375, errc{}, hamon::numeric_limits<T>::denorm_min()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000"
		"24703282292062327208828439643411068618252990130716",
		chars_format::fixed, 375, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.000000000000a000", chars_format::hex, 18, errc{}, 1.0000000000000022));	// 0x1.000000000000ap0 // exact
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.000000000000a001", chars_format::hex, 18, errc{}, 1.0000000000000022));	// 0x1.000000000000ap0 // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.000000000000a800", chars_format::hex, 18, errc{}, 1.0000000000000022));	// 0x1.000000000000ap0 // midpoint, round down to even
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.000000000000a801", chars_format::hex, 18, errc{}, 1.0000000000000024));	// 0x1.000000000000bp0 // above midpoint, round up
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.000000000000b000", chars_format::hex, 18, errc{}, 1.0000000000000024));	// 0x1.000000000000bp0 // exact
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.000000000000b001", chars_format::hex, 18, errc{}, 1.0000000000000024));	// 0x1.000000000000bp0 // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.000000000000b800", chars_format::hex, 18, errc{}, 1.0000000000000027));	// 0x1.000000000000cp0 // midpoint, round up to even
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.000000000000b801", chars_format::hex, 18, errc{}, 1.0000000000000027));	// 0x1.000000000000cp0 // above midpoint, round up

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000020", chars_format::hex, 16, errc{}, 1.0000000000000004));	// 0x1.0000000000002p0 // exact
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000021", chars_format::hex, 16, errc{}, 1.0000000000000004));	// 0x1.0000000000002p0 // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000028", chars_format::hex, 16, errc{}, 1.0000000000000004));	// 0x1.0000000000002p0 // midpoint, round down to even
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000029", chars_format::hex, 16, errc{}, 1.0000000000000007));	// 0x1.0000000000003p0 // above midpoint, round up
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000030", chars_format::hex, 16, errc{}, 1.0000000000000007));	// 0x1.0000000000003p0 // exact
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000031", chars_format::hex, 16, errc{}, 1.0000000000000007));	// 0x1.0000000000003p0 // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000038", chars_format::hex, 16, errc{}, 1.0000000000000009));	// 0x1.0000000000004p0 // midpoint, round up to even
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000039", chars_format::hex, 16, errc{}, 1.0000000000000009));	// 0x1.0000000000004p0 // above midpoint, round up

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000044408920985006261616945266723632812500000", chars_format::general, 58, errc{}, 1.0000000000000004));	// 0x1.0000000000002p0 // exact
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000045796699765787707292474806308746337890625", chars_format::general, 58, errc{}, 1.0000000000000004));	// 0x1.0000000000002p0 // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000055511151231257827021181583404541015624999", chars_format::general, 58, errc{}, 1.0000000000000004));	// 0x1.0000000000002p0 // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000055511151231257827021181583404541015625000", chars_format::general, 58, errc{}, 1.0000000000000004));	// 0x1.0000000000002p0 // midpoint, round down to even
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000055511151231257827021181583404541015625001", chars_format::general, 58, errc{}, 1.0000000000000007));	// 0x1.0000000000003p0 // above midpoint, round up
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000056898930012039272696711122989654541015625", chars_format::general, 58, errc{}, 1.0000000000000007));	// 0x1.0000000000003p0 // above midpoint, round up
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000066613381477509392425417900085449218750000", chars_format::general, 58, errc{}, 1.0000000000000007));	// 0x1.0000000000003p0 // exact
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000068001160258290838100947439670562744140625", chars_format::general, 58, errc{}, 1.0000000000000007));	// 0x1.0000000000003p0 // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000077715611723760957829654216766357421874999", chars_format::general, 58, errc{}, 1.0000000000000007));	// 0x1.0000000000003p0 // below midpoint, round down
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000077715611723760957829654216766357421875000", chars_format::general, 58, errc{}, 1.0000000000000009));	// 0x1.0000000000004p0 // midpoint, round up to even
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000077715611723760957829654216766357421875001", chars_format::general, 58, errc{}, 1.0000000000000009));	// 0x1.0000000000004p0 // above midpoint, round up
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000079103390504542403505183756351470947265625", chars_format::general, 58, errc{}, 1.0000000000000009));	// 0x1.0000000000004p0 // above midpoint, round up

	// https://www.exploringbinary.com/nondeterministic-floating-point-conversions-in-java/
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.0000008p-1022", chars_format::hex, 15, errc{}, 6.631236846766e-316));	// 0x0.0000008p-1022

	// VSO-838635 "<charconv>: from_chars() mishandles certain subnormals"
	// These values change on half-ulp boundaries:
	// 1 * 2^-1075 ~= 2.47e-324 (half-ulp between zero and min subnormal)
	// 2 * 2^-1075 ~= 4.94e-324 (min subnormal)
	// 3 * 2^-1075 ~= 7.41e-324 (half-ulp between min subnormal and next subnormal)
	// 4 * 2^-1075 ~= 9.88e-324 (next subnormal)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111e-324",
		chars_format::scientific, 1007, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"
		"2222222222222222222e-324",
		chars_format::scientific, 1007, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"3."
		"3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333"
		"3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333"
		"3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333"
		"3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333"
		"3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333"
		"3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333"
		"3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333"
		"3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333"
		"3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333"
		"3333333333333333333e-324",
		chars_format::scientific, 1007, errc{}, 4.940656458412e-324));	// 0x0.0000000000001p-1022
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"4."
		"4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444"
		"4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444"
		"4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444"
		"4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444"
		"4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444"
		"4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444"
		"4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444"
		"4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444"
		"4444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444"
		"4444444444444444444e-324",
		chars_format::scientific, 1007, errc{}, 4.940656458412e-324));	// 0x0.0000000000001p-1022
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"5."
		"5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555"
		"5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555"
		"5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555"
		"5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555"
		"5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555"
		"5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555"
		"5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555"
		"5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555"
		"5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555"
		"5555555555555555555e-324",
		chars_format::scientific, 1007, errc{}, 4.940656458412e-324));	// 0x0.0000000000001p-1022
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"6."
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666"
		"6666666666666666666e-324",
		chars_format::scientific, 1007, errc{}, 4.940656458412e-324));	// 0x0.0000000000001p-1022
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"7."
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777"
		"7777777777777777777e-324",
		chars_format::scientific, 1007, errc{}, 9.881312916825e-324));	// 0x0.0000000000002p-1022
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"8."
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888"
		"8888888888888888888e-324",
		chars_format::scientific, 1007, errc{}, 9.881312916825e-324));	// 0x0.0000000000002p-1022
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"9."
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
		"9999999999999999999e-324",
		chars_format::scientific, 1007, errc{}, 9.881312916825e-324));	// 0x0.0000000000002p-1022

	// VSO-852024: Test cases for round-to-nearest, ties-to-even.
	// Consider the values:
	// A: 0x1.0000000000000p+0 == 1.0000000000000000000000000000000000000000000000000000
	// X:    (1 + 2^-53) * 2^0 == 1.00000000000000011102230246251565404236316680908203125
	// B: 0x1.0000000000001p+0 == 1.0000000000000002220446049250313080847263336181640625
	// X is equidistant from A and B. Because they're tied for being nearest, we need to round to even.
	// That means rounding down to A, because A's least significant hexit 0 is even.
	// However, values between X and B aren't tied - they're simply nearer to B, so they need to round up to B.
	// We need to handle tricky cases like the digits of X, followed by a million 0 digits, followed by a 1 digit.
	// Similarly:
	// E:      0x1.ffffffffffffep+0 == 1.999999999999999555910790149937383830547332763671875
	// Y: (1 + 1 - 3 * 2^-53) * 2^0 == 1.99999999999999966693309261245303787291049957275390625
	// F:      0x1.fffffffffffffp+0 == 1.9999999999999997779553950749686919152736663818359375
	// The hexit E is 14 and even, while F is 15 and odd.

	// just below (0 + 2^-53) * 2^-1022: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002470"
		"3282292062327208828439643411068618252990130716238221279284125033775363510437593264991818081799618989828234772"
		"2858865463328355177969898199387398005390939063150356595155702263922908583924491051844359318028499365361525003"
		"1937045767824921936562366986365848075700158576926990370631192827955855133292783433840935197801553124659726357"
		"9574622766465272827220056374006485499977096599470454020828166226237857393450736339007967761930577506740176324"
		"6736009689513405355374585166611342237666786041621596804619144672918403005300575308490487653917113865916462395"
		"2491262365388187963623937328042389101867234849766823508986338858792562830275599565752445550725518931369083625"
		"4779186948667994968324049705821028513185451396213837722826145437693412532098591327667236328124999",
		chars_format::fixed, 1080, errc::result_out_of_range, T{}));

	// (0 + 2^-53) * 2^-1022 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002470"
		"3282292062327208828439643411068618252990130716238221279284125033775363510437593264991818081799618989828234772"
		"2858865463328355177969898199387398005390939063150356595155702263922908583924491051844359318028499365361525003"
		"1937045767824921936562366986365848075700158576926990370631192827955855133292783433840935197801553124659726357"
		"9574622766465272827220056374006485499977096599470454020828166226237857393450736339007967761930577506740176324"
		"6736009689513405355374585166611342237666786041621596804619144672918403005300575308490487653917113865916462395"
		"2491262365388187963623937328042389101867234849766823508986338858792562830275599565752445550725518931369083625"
		"4779186948667994968324049705821028513185451396213837722826145437693412532098591327667236328125",
		chars_format::fixed, 1077, errc::result_out_of_range, T{}));

	// (0 + 2^-53) * 2^-1022 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002470"
		"3282292062327208828439643411068618252990130716238221279284125033775363510437593264991818081799618989828234772"
		"2858865463328355177969898199387398005390939063150356595155702263922908583924491051844359318028499365361525003"
		"1937045767824921936562366986365848075700158576926990370631192827955855133292783433840935197801553124659726357"
		"9574622766465272827220056374006485499977096599470454020828166226237857393450736339007967761930577506740176324"
		"6736009689513405355374585166611342237666786041621596804619144672918403005300575308490487653917113865916462395"
		"2491262365388187963623937328042389101867234849766823508986338858792562830275599565752445550725518931369083625"
		"4779186948667994968324049705821028513185451396213837722826145437693412532098591327667236328125000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000",
		chars_format::fixed, 2077, errc::result_out_of_range, T{}));

	// above (0 + 2^-53) * 2^-1022: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002470"
		"3282292062327208828439643411068618252990130716238221279284125033775363510437593264991818081799618989828234772"
		"2858865463328355177969898199387398005390939063150356595155702263922908583924491051844359318028499365361525003"
		"1937045767824921936562366986365848075700158576926990370631192827955855133292783433840935197801553124659726357"
		"9574622766465272827220056374006485499977096599470454020828166226237857393450736339007967761930577506740176324"
		"6736009689513405355374585166611342237666786041621596804619144672918403005300575308490487653917113865916462395"
		"2491262365388187963623937328042389101867234849766823508986338858792562830275599565752445550725518931369083625"
		"4779186948667994968324049705821028513185451396213837722826145437693412532098591327667236328125000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00001",
		chars_format::fixed, 2078, errc{}, 4.940656458412e-324));	// 0x0.0000000000001p-1022

	// above (0 + 2^-53) * 2^-1022: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002470"
		"3282292062327208828439643411068618252990130716238221279284125033775363510437593264991818081799618989828234772"
		"2858865463328355177969898199387398005390939063150356595155702263922908583924491051844359318028499365361525003"
		"1937045767824921936562366986365848075700158576926990370631192827955855133292783433840935197801553124659726357"
		"9574622766465272827220056374006485499977096599470454020828166226237857393450736339007967761930577506740176324"
		"6736009689513405355374585166611342237666786041621596804619144672918403005300575308490487653917113865916462395"
		"2491262365388187963623937328042389101867234849766823508986338858792562830275599565752445550725518931369083625"
		"47791869486679949683240497058210285131854513962138377228261454376934125320985913276672363281251",
		chars_format::fixed, 1078, errc{}, 4.940656458412e-324));	// 0x0.0000000000001p-1022

	// above (0 + 2^-53) * 2^-1022: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002470"
		"3282292062327208828439643411068618252990130716238221279284125033775363510437593264991818081799618989828234772"
		"2858865463328355177969898199387398005390939063150356595155702263922908583924491051844359318028499365361525003"
		"1937045767824921936562366986365848075700158576926990370631192827955855133292783433840935197801553124659726357"
		"9574622766465272827220056374006485499977096599470454020828166226237857393450736339007967761930577506740176324"
		"6736009689513405355374585166611342237666786041621596804619144672918403005300575308490487653917113865916462395"
		"2491262365388187963623937328042389101867234849766823508986338858792562830275599565752445550725518931369083625"
		"4779186948667994968324049705821028513185451396213837722826145437693412532098591327667236328126",
		chars_format::fixed, 1077, errc{}, 4.940656458412e-324));	// 0x0.0000000000001p-1022

	// just below (0 + 1 - 3 * 2^-53) * 2^-1022: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000022250738585072006419"
		"9176395546258779936602667813027328296362349540005779643539444484102225369938322261431279727704724131030539099"
		"2976863718870946851468024222968583977359185141028540361975476844303195813273469348201130421165308554532083149"
		"3676067608324920106709384047261543474082573017216837765643921010648239116172158852475760231303527077156200284"
		"1775343298712758123539074213191978739083589771549597066404661620550578925994422322342444472859570416955675758"
		"5423752417124134805999073137808018133811049489046686648944255834488901008259721496147104204399198556535697531"
		"0055231935448663898095485089604066035268185282450207861510244351362091237759797852153577038777504570568436147"
		"5530270683064113556748943345076587312006145811358486831521563686919762403704226016998291015624999",
		chars_format::fixed, 1080, errc{}, 2.225073858507200395e-308));	// 0x0.ffffffffffffep-1022

	// (0 + 1 - 3 * 2^-53) * 2^-1022 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000022250738585072006419"
		"9176395546258779936602667813027328296362349540005779643539444484102225369938322261431279727704724131030539099"
		"2976863718870946851468024222968583977359185141028540361975476844303195813273469348201130421165308554532083149"
		"3676067608324920106709384047261543474082573017216837765643921010648239116172158852475760231303527077156200284"
		"1775343298712758123539074213191978739083589771549597066404661620550578925994422322342444472859570416955675758"
		"5423752417124134805999073137808018133811049489046686648944255834488901008259721496147104204399198556535697531"
		"0055231935448663898095485089604066035268185282450207861510244351362091237759797852153577038777504570568436147"
		"5530270683064113556748943345076587312006145811358486831521563686919762403704226016998291015625",
		chars_format::fixed, 1077, errc{}, 2.225073858507200395e-308));	// 0x0.ffffffffffffep-1022

	// (0 + 1 - 3 * 2^-53) * 2^-1022 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000022250738585072006419"
		"9176395546258779936602667813027328296362349540005779643539444484102225369938322261431279727704724131030539099"
		"2976863718870946851468024222968583977359185141028540361975476844303195813273469348201130421165308554532083149"
		"3676067608324920106709384047261543474082573017216837765643921010648239116172158852475760231303527077156200284"
		"1775343298712758123539074213191978739083589771549597066404661620550578925994422322342444472859570416955675758"
		"5423752417124134805999073137808018133811049489046686648944255834488901008259721496147104204399198556535697531"
		"0055231935448663898095485089604066035268185282450207861510244351362091237759797852153577038777504570568436147"
		"5530270683064113556748943345076587312006145811358486831521563686919762403704226016998291015625000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000",
		chars_format::fixed, 2077, errc{}, 2.225073858507200395e-308));	// 0x0.ffffffffffffep-1022

	// above (0 + 1 - 3 * 2^-53) * 2^-1022: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000022250738585072006419"
		"9176395546258779936602667813027328296362349540005779643539444484102225369938322261431279727704724131030539099"
		"2976863718870946851468024222968583977359185141028540361975476844303195813273469348201130421165308554532083149"
		"3676067608324920106709384047261543474082573017216837765643921010648239116172158852475760231303527077156200284"
		"1775343298712758123539074213191978739083589771549597066404661620550578925994422322342444472859570416955675758"
		"5423752417124134805999073137808018133811049489046686648944255834488901008259721496147104204399198556535697531"
		"0055231935448663898095485089604066035268185282450207861510244351362091237759797852153577038777504570568436147"
		"5530270683064113556748943345076587312006145811358486831521563686919762403704226016998291015625000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00001",
		chars_format::fixed, 2078, errc{}, 2.225073858507200889e-308));	// 0x0.fffffffffffffp-1022

	// above (0 + 1 - 3 * 2^-53) * 2^-1022: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000022250738585072006419"
		"9176395546258779936602667813027328296362349540005779643539444484102225369938322261431279727704724131030539099"
		"2976863718870946851468024222968583977359185141028540361975476844303195813273469348201130421165308554532083149"
		"3676067608324920106709384047261543474082573017216837765643921010648239116172158852475760231303527077156200284"
		"1775343298712758123539074213191978739083589771549597066404661620550578925994422322342444472859570416955675758"
		"5423752417124134805999073137808018133811049489046686648944255834488901008259721496147104204399198556535697531"
		"0055231935448663898095485089604066035268185282450207861510244351362091237759797852153577038777504570568436147"
		"55302706830641135567489433450765873120061458113584868315215636869197624037042260169982910156251",
		chars_format::fixed, 1078, errc{}, 2.225073858507200889e-308));	// 0x0.fffffffffffffp-1022

	// above (0 + 1 - 3 * 2^-53) * 2^-1022: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000022250738585072006419"
		"9176395546258779936602667813027328296362349540005779643539444484102225369938322261431279727704724131030539099"
		"2976863718870946851468024222968583977359185141028540361975476844303195813273469348201130421165308554532083149"
		"3676067608324920106709384047261543474082573017216837765643921010648239116172158852475760231303527077156200284"
		"1775343298712758123539074213191978739083589771549597066404661620550578925994422322342444472859570416955675758"
		"5423752417124134805999073137808018133811049489046686648944255834488901008259721496147104204399198556535697531"
		"0055231935448663898095485089604066035268185282450207861510244351362091237759797852153577038777504570568436147"
		"5530270683064113556748943345076587312006145811358486831521563686919762403704226016998291015626",
		chars_format::fixed, 1077, errc{}, 2.225073858507200889e-308));	// 0x0.fffffffffffffp-1022

	// just below (1 + 2^-53) * 2^-1022: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000022250738585072016301"
		"2305563795567615250361241457301801308322872404958664760675944619203679411688695321398552054903200090343478188"
		"4412325572184367563347617020518175998922941393629966742598285899994830148971433555578567693279306015978183162"
		"1424250679624607852958851992724935776883207324924799248168692322471659649343292587839501022509739575795105716"
		"0073834364573849432419299709217920738991976169431413149717326525502008499797367678374315520581880443916381057"
		"2367791175177756227497413804253387084478193655533073867420834526162513029462022730109054820067654020201547112"
		"0020281397001415752591234401773622442737124681517501897455599786532342558862196115163359241679580296044770649"
		"4647018477736093430045142168360701364747951396213837722826145437693412532098591327667236328124999",
		chars_format::fixed, 1080, errc{}, 2.225073858507201383e-308));	// 0x1.0000000000000p-1022

	// (1 + 2^-53) * 2^-1022 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000022250738585072016301"
		"2305563795567615250361241457301801308322872404958664760675944619203679411688695321398552054903200090343478188"
		"4412325572184367563347617020518175998922941393629966742598285899994830148971433555578567693279306015978183162"
		"1424250679624607852958851992724935776883207324924799248168692322471659649343292587839501022509739575795105716"
		"0073834364573849432419299709217920738991976169431413149717326525502008499797367678374315520581880443916381057"
		"2367791175177756227497413804253387084478193655533073867420834526162513029462022730109054820067654020201547112"
		"0020281397001415752591234401773622442737124681517501897455599786532342558862196115163359241679580296044770649"
		"4647018477736093430045142168360701364747951396213837722826145437693412532098591327667236328125",
		chars_format::fixed, 1077, errc{}, 2.225073858507201383e-308));	// 0x1.0000000000000p-1022

	// (1 + 2^-53) * 2^-1022 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000022250738585072016301"
		"2305563795567615250361241457301801308322872404958664760675944619203679411688695321398552054903200090343478188"
		"4412325572184367563347617020518175998922941393629966742598285899994830148971433555578567693279306015978183162"
		"1424250679624607852958851992724935776883207324924799248168692322471659649343292587839501022509739575795105716"
		"0073834364573849432419299709217920738991976169431413149717326525502008499797367678374315520581880443916381057"
		"2367791175177756227497413804253387084478193655533073867420834526162513029462022730109054820067654020201547112"
		"0020281397001415752591234401773622442737124681517501897455599786532342558862196115163359241679580296044770649"
		"4647018477736093430045142168360701364747951396213837722826145437693412532098591327667236328125000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000",
		chars_format::fixed, 2077, errc{}, 2.225073858507201383e-308));	// 0x1.0000000000000p-1022

	// above (1 + 2^-53) * 2^-1022: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000022250738585072016301"
		"2305563795567615250361241457301801308322872404958664760675944619203679411688695321398552054903200090343478188"
		"4412325572184367563347617020518175998922941393629966742598285899994830148971433555578567693279306015978183162"
		"1424250679624607852958851992724935776883207324924799248168692322471659649343292587839501022509739575795105716"
		"0073834364573849432419299709217920738991976169431413149717326525502008499797367678374315520581880443916381057"
		"2367791175177756227497413804253387084478193655533073867420834526162513029462022730109054820067654020201547112"
		"0020281397001415752591234401773622442737124681517501897455599786532342558862196115163359241679580296044770649"
		"4647018477736093430045142168360701364747951396213837722826145437693412532098591327667236328125000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00001",
		chars_format::fixed, 2078, errc{}, 2.225073858507201877e-308));	// 0x1.0000000000001p-1022

	// above (1 + 2^-53) * 2^-1022: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000022250738585072016301"
		"2305563795567615250361241457301801308322872404958664760675944619203679411688695321398552054903200090343478188"
		"4412325572184367563347617020518175998922941393629966742598285899994830148971433555578567693279306015978183162"
		"1424250679624607852958851992724935776883207324924799248168692322471659649343292587839501022509739575795105716"
		"0073834364573849432419299709217920738991976169431413149717326525502008499797367678374315520581880443916381057"
		"2367791175177756227497413804253387084478193655533073867420834526162513029462022730109054820067654020201547112"
		"0020281397001415752591234401773622442737124681517501897455599786532342558862196115163359241679580296044770649"
		"46470184777360934300451421683607013647479513962138377228261454376934125320985913276672363281251",
		chars_format::fixed, 1078, errc{}, 2.225073858507201877e-308));	// 0x1.0000000000001p-1022

	// above (1 + 2^-53) * 2^-1022: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000022250738585072016301"
		"2305563795567615250361241457301801308322872404958664760675944619203679411688695321398552054903200090343478188"
		"4412325572184367563347617020518175998922941393629966742598285899994830148971433555578567693279306015978183162"
		"1424250679624607852958851992724935776883207324924799248168692322471659649343292587839501022509739575795105716"
		"0073834364573849432419299709217920738991976169431413149717326525502008499797367678374315520581880443916381057"
		"2367791175177756227497413804253387084478193655533073867420834526162513029462022730109054820067654020201547112"
		"0020281397001415752591234401773622442737124681517501897455599786532342558862196115163359241679580296044770649"
		"4647018477736093430045142168360701364747951396213837722826145437693412532098591327667236328126",
		chars_format::fixed, 1077, errc{}, 2.225073858507201877e-308));	// 0x1.0000000000001p-1022

	// just below (1 + 1 - 3 * 2^-53) * 2^-1022: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000044501477170144020250"
		"8199667279499186358524265859260511351695091228726223124931264069530541271189424317838013700808305231545782515"
		"4530323827726959236845743044099361970891187471508150509418060480375117378320411851935338796416115205148741308"
		"3163272520124606023105869053620631175265621765214646643181420505164043632222668006474326056011713528291579642"
		"2274554896821334728738317548403413978098469341510556195293821919814730032341053661708792231510873354131880491"
		"1055533902788485678121901775450062980622457102958163711745945687733011032421168917765671370549738710820782247"
		"7584250967061891687062782163335299376138075114200886249979505279101870966346394401564490729731565935244123171"
		"5398102212132212018470035807616260163568645811358486831521563686919762403704226016998291015624999",
		chars_format::fixed, 1080, errc{}, 4.450147717014401778e-308));	// 0x1.ffffffffffffep-1022

	// (1 + 1 - 3 * 2^-53) * 2^-1022 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000044501477170144020250"
		"8199667279499186358524265859260511351695091228726223124931264069530541271189424317838013700808305231545782515"
		"4530323827726959236845743044099361970891187471508150509418060480375117378320411851935338796416115205148741308"
		"3163272520124606023105869053620631175265621765214646643181420505164043632222668006474326056011713528291579642"
		"2274554896821334728738317548403413978098469341510556195293821919814730032341053661708792231510873354131880491"
		"1055533902788485678121901775450062980622457102958163711745945687733011032421168917765671370549738710820782247"
		"7584250967061891687062782163335299376138075114200886249979505279101870966346394401564490729731565935244123171"
		"5398102212132212018470035807616260163568645811358486831521563686919762403704226016998291015625",
		chars_format::fixed, 1077, errc{}, 4.450147717014401778e-308));	// 0x1.ffffffffffffep-1022

	// (1 + 1 - 3 * 2^-53) * 2^-1022 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000044501477170144020250"
		"8199667279499186358524265859260511351695091228726223124931264069530541271189424317838013700808305231545782515"
		"4530323827726959236845743044099361970891187471508150509418060480375117378320411851935338796416115205148741308"
		"3163272520124606023105869053620631175265621765214646643181420505164043632222668006474326056011713528291579642"
		"2274554896821334728738317548403413978098469341510556195293821919814730032341053661708792231510873354131880491"
		"1055533902788485678121901775450062980622457102958163711745945687733011032421168917765671370549738710820782247"
		"7584250967061891687062782163335299376138075114200886249979505279101870966346394401564490729731565935244123171"
		"5398102212132212018470035807616260163568645811358486831521563686919762403704226016998291015625000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000",
		chars_format::fixed, 2077, errc{}, 4.450147717014401778e-308));	// 0x1.ffffffffffffep-1022

	// above (1 + 1 - 3 * 2^-53) * 2^-1022: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000044501477170144020250"
		"8199667279499186358524265859260511351695091228726223124931264069530541271189424317838013700808305231545782515"
		"4530323827726959236845743044099361970891187471508150509418060480375117378320411851935338796416115205148741308"
		"3163272520124606023105869053620631175265621765214646643181420505164043632222668006474326056011713528291579642"
		"2274554896821334728738317548403413978098469341510556195293821919814730032341053661708792231510873354131880491"
		"1055533902788485678121901775450062980622457102958163711745945687733011032421168917765671370549738710820782247"
		"7584250967061891687062782163335299376138075114200886249979505279101870966346394401564490729731565935244123171"
		"5398102212132212018470035807616260163568645811358486831521563686919762403704226016998291015625000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00001",
		chars_format::fixed, 2078, errc{}, 4.450147717014402272e-308));	// 0x1.fffffffffffffp-1022

	// above (1 + 1 - 3 * 2^-53) * 2^-1022: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000044501477170144020250"
		"8199667279499186358524265859260511351695091228726223124931264069530541271189424317838013700808305231545782515"
		"4530323827726959236845743044099361970891187471508150509418060480375117378320411851935338796416115205148741308"
		"3163272520124606023105869053620631175265621765214646643181420505164043632222668006474326056011713528291579642"
		"2274554896821334728738317548403413978098469341510556195293821919814730032341053661708792231510873354131880491"
		"1055533902788485678121901775450062980622457102958163711745945687733011032421168917765671370549738710820782247"
		"7584250967061891687062782163335299376138075114200886249979505279101870966346394401564490729731565935244123171"
		"53981022121322120184700358076162601635686458113584868315215636869197624037042260169982910156251",
		chars_format::fixed, 1078, errc{}, 4.450147717014402272e-308));	// 0x1.fffffffffffffp-1022

	// above (1 + 1 - 3 * 2^-53) * 2^-1022: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000044501477170144020250"
		"8199667279499186358524265859260511351695091228726223124931264069530541271189424317838013700808305231545782515"
		"4530323827726959236845743044099361970891187471508150509418060480375117378320411851935338796416115205148741308"
		"3163272520124606023105869053620631175265621765214646643181420505164043632222668006474326056011713528291579642"
		"2274554896821334728738317548403413978098469341510556195293821919814730032341053661708792231510873354131880491"
		"1055533902788485678121901775450062980622457102958163711745945687733011032421168917765671370549738710820782247"
		"7584250967061891687062782163335299376138075114200886249979505279101870966346394401564490729731565935244123171"
		"5398102212132212018470035807616260163568645811358486831521563686919762403704226016998291015626",
		chars_format::fixed, 1077, errc{}, 4.450147717014402272e-308));	// 0x1.fffffffffffffp-1022

	// just below (1 + 2^-53) * 2^-33: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0.00000000011641532182693482737782207114105741986576081359316958696581423282623291015624999",
		chars_format::fixed, 91, errc{}, 1.164153218269348145e-10));	// 0x1.0000000000000p-33

	// (1 + 2^-53) * 2^-33 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0.00000000011641532182693482737782207114105741986576081359316958696581423282623291015625",
		chars_format::fixed, 88, errc{}, 1.164153218269348145e-10));	// 0x1.0000000000000p-33

	// (1 + 2^-53) * 2^-33 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000001164153218269348273778220711410574198657608135931695869658142328262329101562500000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		chars_format::fixed, 1088, errc{}, 1.164153218269348145e-10));	// 0x1.0000000000000p-33

	// above (1 + 2^-53) * 2^-33: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000001164153218269348273778220711410574198657608135931695869658142328262329101562500000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
		chars_format::fixed, 1089, errc{}, 1.164153218269348403e-10));	// 0x1.0000000000001p-33

	// above (1 + 2^-53) * 2^-33: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0.000000000116415321826934827377822071141057419865760813593169586965814232826232910156251",
		chars_format::fixed, 89, errc{}, 1.164153218269348403e-10));	// 0x1.0000000000001p-33

	// above (1 + 2^-53) * 2^-33: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0.00000000011641532182693482737782207114105741986576081359316958696581423282623291015626",
		chars_format::fixed, 88, errc{}, 1.164153218269348403e-10));	// 0x1.0000000000001p-33

	// just below (1 + 1 - 3 * 2^-53) * 2^-33: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0.00000000023283064365386959013215878657682774040271755922049123910255730152130126953124999",
		chars_format::fixed, 91, errc{}, 2.328306436538695772e-10));	// 0x1.ffffffffffffep-33

	// (1 + 1 - 3 * 2^-53) * 2^-33 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0.00000000023283064365386959013215878657682774040271755922049123910255730152130126953125",
		chars_format::fixed, 88, errc{}, 2.328306436538695772e-10));	// 0x1.ffffffffffffep-33

	// (1 + 1 - 3 * 2^-53) * 2^-33 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000002328306436538695901321587865768277404027175592204912391025573015213012695312500000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		chars_format::fixed, 1088, errc{}, 2.328306436538695772e-10));	// 0x1.ffffffffffffep-33

	// above (1 + 1 - 3 * 2^-53) * 2^-33: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000002328306436538695901321587865768277404027175592204912391025573015213012695312500000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
			chars_format::fixed, 1089, errc{}, 2.328306436538696031e-10));	// 0x1.fffffffffffffp-33

	// above (1 + 1 - 3 * 2^-53) * 2^-33: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0.000000000232830643653869590132158786576827740402717559220491239102557301521301269531251",
		chars_format::fixed, 89, errc{}, 2.328306436538696031e-10));	// 0x1.fffffffffffffp-33

	// above (1 + 1 - 3 * 2^-53) * 2^-33: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0.00000000023283064365386959013215878657682774040271755922049123910255730152130126953126",
		chars_format::fixed, 88, errc{}, 2.328306436538696031e-10));	// 0x1.fffffffffffffp-33

	// just below (1 + 2^-53) * 2^0: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000011102230246251565404236316680908203124999", chars_format::fixed, 58, errc{}, 1.0));

	// (1 + 2^-53) * 2^0 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000011102230246251565404236316680908203125", chars_format::fixed, 55, errc{}, 1.0));

	// (1 + 2^-53) * 2^0 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"0000000000000001110223024625156540423631668090820312500000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"000000000000000000000000000000000000000000000000000000000000000000000000",
		chars_format::fixed, 1055, errc{}, 1.0));

	// above (1 + 2^-53) * 2^0: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"0000000000000001110223024625156540423631668090820312500000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000001",
		chars_format::fixed, 1056, errc{}, 1.000000000000000222));	// 0x1.0000000000001p+0

	// above (1 + 2^-53) * 2^0: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.000000000000000111022302462515654042363166809082031251", chars_format::fixed, 56, errc{}, 1.000000000000000222));	// 0x1.0000000000001p+0

	// above (1 + 2^-53) * 2^0: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000011102230246251565404236316680908203126", chars_format::fixed, 55, errc{}, 1.000000000000000222));	// 0x1.0000000000001p+0

	// just below (1 + 1 - 3 * 2^-53) * 2^0: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.99999999999999966693309261245303787291049957275390624999", chars_format::fixed, 58, errc{}, 1.999999999999999556));	// 0x1.ffffffffffffep+0

	// (1 + 1 - 3 * 2^-53) * 2^0 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.99999999999999966693309261245303787291049957275390625", chars_format::fixed, 55, errc{}, 1.999999999999999556));	// 0x1.ffffffffffffep+0

	// (1 + 1 - 3 * 2^-53) * 2^0 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"9999999999999996669330926124530378729104995727539062500000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"000000000000000000000000000000000000000000000000000000000000000000000000",
		chars_format::fixed, 1055, errc{}, 1.999999999999999556));	// 0x1.ffffffffffffep+0

	// above (1 + 1 - 3 * 2^-53) * 2^0: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"9999999999999996669330926124530378729104995727539062500000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000001",
		chars_format::fixed, 1056, errc{}, 1.999999999999999778));	// 0x1.fffffffffffffp+0

	// above (1 + 1 - 3 * 2^-53) * 2^0: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.999999999999999666933092612453037872910499572753906251", chars_format::fixed, 56, errc{}, 1.999999999999999778));	// 0x1.fffffffffffffp+0

	// above (1 + 1 - 3 * 2^-53) * 2^0: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.99999999999999966693309261245303787291049957275390626", chars_format::fixed, 55, errc{}, 1.999999999999999778));	// 0x1.fffffffffffffp+0

	// just below (1 + 2^-53) * 2^33: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8589934592.00000095367431640624999", chars_format::fixed, 34, errc{}, 8589934592.0));	// 0x1.0000000000000p+33

	// (1 + 2^-53) * 2^33 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8589934592.00000095367431640625", chars_format::fixed, 31, errc{}, 8589934592.0));	// 0x1.0000000000000p+33

	// (1 + 2^-53) * 2^33 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"8589934592."
		"0000009536743164062500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"000000000000000000000000000000000000000",
		chars_format::fixed, 1031, errc{}, 8589934592.0));	// 0x1.0000000000000p+33

	// above (1 + 2^-53) * 2^33: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"8589934592."
		"0000009536743164062500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000001",
		chars_format::fixed, 1032, errc{}, 8589934592.000001907));	// 0x1.0000000000001p+33

	// above (1 + 2^-53) * 2^33: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8589934592.000000953674316406251", chars_format::fixed, 32, errc{}, 8589934592.000001907));	// 0x1.0000000000001p+33

	// above (1 + 2^-53) * 2^33: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8589934592.00000095367431640626", chars_format::fixed, 31, errc{}, 8589934592.000001907));	// 0x1.0000000000001p+33

	// just below (1 + 1 - 3 * 2^-53) * 2^33: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("17179869183.99999713897705078124999", chars_format::fixed, 35, errc{}, 17179869183.99999619));	// 0x1.ffffffffffffep+33

	// (1 + 1 - 3 * 2^-53) * 2^33 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("17179869183.99999713897705078125", chars_format::fixed, 32, errc{}, 17179869183.99999619));	// 0x1.ffffffffffffep+33

	// (1 + 1 - 3 * 2^-53) * 2^33 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17179869183."
		"9999971389770507812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"000000000000000000000000000000000000000",
		chars_format::fixed, 1032, errc{}, 17179869183.99999619));	// 0x1.ffffffffffffep+33

	// above (1 + 1 - 3 * 2^-53) * 2^33: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17179869183."
		"9999971389770507812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000001",
		chars_format::fixed, 1033, errc{}, 17179869183.99999809));	// 0x1.fffffffffffffp+33

	// above (1 + 1 - 3 * 2^-53) * 2^33: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("17179869183.999997138977050781251", chars_format::fixed, 33, errc{}, 17179869183.99999809));	// 0x1.fffffffffffffp+33

	// above (1 + 1 - 3 * 2^-53) * 2^33: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("17179869183.99999713897705078126", chars_format::fixed, 32, errc{}, 17179869183.99999809));	// 0x1.fffffffffffffp+33

	// just below (1 + 2^-53) * 2^77: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("151115727451828663615487.999", chars_format::fixed, 28, errc{}, 1.511157274518286468e+23));	// 0x1.0000000000000p+77

	// (1 + 2^-53) * 2^77 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("151115727451828663615488", chars_format::fixed, 24, errc{}, 1.511157274518286468e+23));	// 0x1.0000000000000p+77

	// (1 + 2^-53) * 2^77 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"151115727451828663615488."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000",
		chars_format::fixed, 1025, errc{}, 1.511157274518286468e+23));	// 0x1.0000000000000p+77

	// above (1 + 2^-53) * 2^77: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"151115727451828663615488."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000001",
		chars_format::fixed, 1026, errc{}, 1.511157274518286804e+23));	// 0x1.0000000000001p+77

	// above (1 + 2^-53) * 2^77: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("151115727451828663615488.1", chars_format::fixed, 26, errc{}, 1.511157274518286804e+23));	// 0x1.0000000000001p+77

	// above (1 + 2^-53) * 2^77: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("151115727451828663615489", chars_format::fixed, 24, errc{}, 1.511157274518286804e+23));	// 0x1.0000000000001p+77

	// just below (1 + 1 - 3 * 2^-53) * 2^77: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("302231454903657243344895.999", chars_format::fixed, 28, errc{}, 3.022314549036572266e+23));	// 0x1.ffffffffffffep+77

	// (1 + 1 - 3 * 2^-53) * 2^77 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("302231454903657243344896", chars_format::fixed, 24, errc{}, 3.022314549036572266e+23));	// 0x1.ffffffffffffep+77

	// (1 + 1 - 3 * 2^-53) * 2^77 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"302231454903657243344896."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000",
		chars_format::fixed, 1025, errc{}, 3.022314549036572266e+23));	// 0x1.ffffffffffffep+77

	// above (1 + 1 - 3 * 2^-53) * 2^77: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"302231454903657243344896."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000001",
		chars_format::fixed, 1026, errc{}, 3.022314549036572601e+23));	// 0x1.fffffffffffffp+77

	// above (1 + 1 - 3 * 2^-53) * 2^77: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("302231454903657243344896.1", chars_format::fixed, 26, errc{}, 3.022314549036572601e+23));	// 0x1.fffffffffffffp+77

	// above (1 + 1 - 3 * 2^-53) * 2^77: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("302231454903657243344897", chars_format::fixed, 24, errc{}, 3.022314549036572601e+23));	// 0x1.fffffffffffffp+77

	// just below (1 + 2^-53) * 2^1023: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"8988465674311580536566680721305029496276241413130815897397134275615404541548669375241369800602409693534988440"
		"3114202125541629105369684531108613657287705365884742938136589844238179474556051429647415148697857438797685859"
		"063890851407391008830874765563025951597582513936655578157348020066364210154316532161708031.999",
		chars_format::fixed, 312, errc{}, 8.988465674311579539e+307));	// 0x1.0000000000000p+1023

	// (1 + 2^-53) * 2^1023 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"8988465674311580536566680721305029496276241413130815897397134275615404541548669375241369800602409693534988440"
		"3114202125541629105369684531108613657287705365884742938136589844238179474556051429647415148697857438797685859"
		"063890851407391008830874765563025951597582513936655578157348020066364210154316532161708032",
		chars_format::fixed, 308, errc{}, 8.988465674311579539e+307));	// 0x1.0000000000000p+1023

	// (1 + 2^-53) * 2^1023 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"8988465674311580536566680721305029496276241413130815897397134275615404541548669375241369800602409693534988440"
		"3114202125541629105369684531108613657287705365884742938136589844238179474556051429647415148697857438797685859"
		"063890851407391008830874765563025951597582513936655578157348020066364210154316532161708032."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000",
		chars_format::fixed, 1309, errc{}, 8.988465674311579539e+307));	// 0x1.0000000000000p+1023

	// above (1 + 2^-53) * 2^1023: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"8988465674311580536566680721305029496276241413130815897397134275615404541548669375241369800602409693534988440"
		"3114202125541629105369684531108613657287705365884742938136589844238179474556051429647415148697857438797685859"
		"063890851407391008830874765563025951597582513936655578157348020066364210154316532161708032."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000001",
		chars_format::fixed, 1310, errc{}, 8.988465674311581534e+307));	// 0x1.0000000000001p+1023

	// above (1 + 2^-53) * 2^1023: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"8988465674311580536566680721305029496276241413130815897397134275615404541548669375241369800602409693534988440"
		"3114202125541629105369684531108613657287705365884742938136589844238179474556051429647415148697857438797685859"
		"063890851407391008830874765563025951597582513936655578157348020066364210154316532161708032.1",
		chars_format::fixed, 310, errc{}, 8.988465674311581534e+307));	// 0x1.0000000000001p+1023

	// above (1 + 2^-53) * 2^1023: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"8988465674311580536566680721305029496276241413130815897397134275615404541548669375241369800602409693534988440"
		"3114202125541629105369684531108613657287705365884742938136589844238179474556051429647415148697857438797685859"
		"063890851407391008830874765563025951597582513936655578157348020066364210154316532161708033",
		chars_format::fixed, 308, errc{}, 8.988465674311581534e+307));	// 0x1.0000000000001p+1023

	// just below (1 + 1 - 3 * 2^-53) * 2^1023: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1797693134862315608353258760581052985162070023416521662616611746258695532672923265745300992879465492467506314"
		"9033587701752208710592698796290627760473556921329019091915239418047621712533496094635638726128664019802903779"
		"9514183602981511756283727771403830521483963923935633133642802139091669457927874464075218943.999",
		chars_format::fixed, 313, errc{}, 1.797693134862315509e+308));	// 0x1.ffffffffffffep+1023

	// (1 + 1 - 3 * 2^-53) * 2^1023 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1797693134862315608353258760581052985162070023416521662616611746258695532672923265745300992879465492467506314"
		"9033587701752208710592698796290627760473556921329019091915239418047621712533496094635638726128664019802903779"
		"9514183602981511756283727771403830521483963923935633133642802139091669457927874464075218944",
		chars_format::fixed, 309, errc{}, 1.797693134862315509e+308));	// 0x1.ffffffffffffep+1023

	// (1 + 1 - 3 * 2^-53) * 2^1023 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1797693134862315608353258760581052985162070023416521662616611746258695532672923265745300992879465492467506314"
		"9033587701752208710592698796290627760473556921329019091915239418047621712533496094635638726128664019802903779"
		"9514183602981511756283727771403830521483963923935633133642802139091669457927874464075218944."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000",
		chars_format::fixed, 1310, errc{}, 1.797693134862315509e+308));	// 0x1.ffffffffffffep+1023

	// above (1 + 1 - 3 * 2^-53) * 2^1023: appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1797693134862315608353258760581052985162070023416521662616611746258695532672923265745300992879465492467506314"
		"9033587701752208710592698796290627760473556921329019091915239418047621712533496094635638726128664019802903779"
		"9514183602981511756283727771403830521483963923935633133642802139091669457927874464075218944."
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000001",
		chars_format::fixed, 1311, errc{}, 1.797693134862315708e+308));	// 0x1.fffffffffffffp+1023

	// above (1 + 1 - 3 * 2^-53) * 2^1023: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1797693134862315608353258760581052985162070023416521662616611746258695532672923265745300992879465492467506314"
		"9033587701752208710592698796290627760473556921329019091915239418047621712533496094635638726128664019802903779"
		"9514183602981511756283727771403830521483963923935633133642802139091669457927874464075218944.1",
		chars_format::fixed, 311, errc{}, 1.797693134862315708e+308));	// 0x1.fffffffffffffp+1023

	// above (1 + 1 - 3 * 2^-53) * 2^1023: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1797693134862315608353258760581052985162070023416521662616611746258695532672923265745300992879465492467506314"
		"9033587701752208710592698796290627760473556921329019091915239418047621712533496094635638726128664019802903779"
		"9514183602981511756283727771403830521483963923935633133642802139091669457927874464075218945",
		chars_format::fixed, 309, errc{}, 1.797693134862315708e+308));	// 0x1.fffffffffffffp+1023

	// VSO-852024 also affected hexfloats.
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.00000000000008p-1022", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"0000000000000800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000001p-1022",
		chars_format::hex, 1023, errc{}, 4.940656458412e-324));	// 0x0.0000000000001p-1022

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffffffffffe8p-1022", chars_format::hex, 22, errc{}, 2.225073858507200395e-308));	// 0x0.ffffffffffffep-1022
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"ffffffffffffe800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000001p-1022",
		chars_format::hex, 1023, errc{}, 2.225073858507200889e-308));	// 0x0.fffffffffffffp-1022

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000008p+0", chars_format::hex, 19, errc{}, 1.0));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"0000000000000800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000001p+0",
			chars_format::hex, 1020, errc{}, 1.000000000000000222));	// 0x1.0000000000001p+0

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffffffffffe8p+0", chars_format::hex, 19, errc{}, 1.999999999999999556));	// 0x1.ffffffffffffep+0
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"ffffffffffffe800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000001p+0",
		chars_format::hex, 1020, errc{}, 1.999999999999999778));	// 0x1.fffffffffffffp+0

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000008p+1023", chars_format::hex, 22, errc{}, 8.988465674311579539e+307));	// 0x1.0000000000000p+1023
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"0000000000000800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000001p+1023",
		chars_format::hex, 1023, errc{}, 8.988465674311581534e+307));	// 0x1.0000000000001p+1023

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffffffffffe8p+1023", chars_format::hex, 22, errc{}, 1.797693134862315509e+308));	// 0x1.ffffffffffffep+1023
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1."
		"ffffffffffffe800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000001p+1023",
		chars_format::hex, 1023, errc{}, 1.797693134862315708e+308));	// 0x1.fffffffffffffp+1023

	// VSO-733765 "<charconv>: [Feedback] double std::from_chars behavior on exponent out of range"
	// LWG-3081 "Floating point from_chars API does not distinguish between overflow and underflow"
	// These test cases exercise every overflow/underflow codepath.
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e+1000",                chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-1000",                chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffff8p+1023", chars_format::hex,       22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e+2000",                chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-2000",                chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e+9999",                chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1e-9999",                chars_format::scientific, 7, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("10e+5199",               chars_format::scientific, 8, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.001e-5199",            chars_format::scientific,11, errc::result_out_of_range, T{}));

#if defined(HAMON_HAS_CXX17_HEX_FLOAT)
	// GH-931 "<charconv>: hex from_chars(\"0.fffffffffffff8p-1022\") is incorrect"
	// Test cases for values close to std::numeric_limits<double>::min() and std::numeric_limits<double>::max()
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffffp-1022", chars_format::hex, 21, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.0000000000000p-1022", chars_format::hex, 21, errc{}, 0x1.0000000000000p-1022));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffffffffffep-1023", chars_format::hex, 21, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffffp-1023", chars_format::hex, 21, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.0000000000000p-1023", chars_format::hex, 21, errc{}, 0x1.0000000000000p-1022));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffcp-1024", chars_format::hex, 21, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffdp-1024", chars_format::hex, 21, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffep-1024", chars_format::hex, 21, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffffffffffp-1024", chars_format::hex, 21, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.0000000000000p-1024", chars_format::hex, 21, errc{}, 0x1.0000000000000p-1022));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffff8p-1025", chars_format::hex, 21, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffff9p-1025", chars_format::hex, 21, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffbp-1025", chars_format::hex, 21, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffcp-1025", chars_format::hex, 21, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffdp-1025", chars_format::hex, 21, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffep-1025", chars_format::hex, 21, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffffffffffp-1025", chars_format::hex, 21, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.0000000000000p-1025", chars_format::hex, 21, errc{}, 0x1.0000000000000p-1022));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffff0p-1022", chars_format::hex, 22, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffff1p-1022", chars_format::hex, 22, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffff7p-1022", chars_format::hex, 22, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffff8p-1022", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffff9p-1022", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffffbp-1022", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffffcp-1022", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffffdp-1022", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffffffffffffp-1022", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000p-1022", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffffffffffe0p-1023", chars_format::hex, 22, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffffffffffe1p-1023", chars_format::hex, 22, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffffffffffefp-1023", chars_format::hex, 22, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffff0p-1023", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffff1p-1023", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffff7p-1023", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffff8p-1023", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffff9p-1023", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffffffffffffp-1023", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.00000000000000p-1023", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffc0p-1024", chars_format::hex, 22, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffc1p-1024", chars_format::hex, 22, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffdfp-1024", chars_format::hex, 22, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffe0p-1024", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffe1p-1024", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffefp-1024", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffffffffff0p-1024", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffffffffff1p-1024", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffffp-1024", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.00000000000000p-1024", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffff80p-1025", chars_format::hex, 22, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffff81p-1025", chars_format::hex, 22, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffbfp-1025", chars_format::hex, 22, errc{}, 0x0.fffffffffffffp-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffc0p-1025", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffc1p-1025", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffdfp-1025", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffe0p-1025", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffe1p-1025", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffffp-1025", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.00000000000000p-1025", chars_format::hex, 22, errc{}, 0x1.0000000000000p-1022));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffffp+1023", chars_format::hex, 21, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.0000000000000p+1023", chars_format::hex, 21, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffep+1022", chars_format::hex, 21, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffffffffffp+1022", chars_format::hex, 21, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.0000000000000p+1022", chars_format::hex, 21, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffcp+1021", chars_format::hex, 21, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffdp+1021", chars_format::hex, 21, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffep+1021", chars_format::hex, 21, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.fffffffffffffp+1021", chars_format::hex, 21, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.0000000000000p+1021", chars_format::hex, 21, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffff8p+1024", chars_format::hex, 22, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffff9p+1024", chars_format::hex, 22, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffffbp+1024", chars_format::hex, 22, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffffcp+1024", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffffdp+1024", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.ffffffffffffffp+1024", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.00000000000000p+1024", chars_format::hex, 22, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffff0p+1023", chars_format::hex, 22, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffff1p+1023", chars_format::hex, 22, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffff7p+1023", chars_format::hex, 22, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffff8p+1023", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.fffffffffffff9p+1023", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.ffffffffffffffp+1023", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("2.00000000000000p+1023", chars_format::hex, 22, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffe0p+1022", chars_format::hex, 22, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffe1p+1022", chars_format::hex, 22, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffefp+1022", chars_format::hex, 22, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffffffffff0p+1022", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.fffffffffffff1p+1022", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("3.ffffffffffffffp+1022", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("4.00000000000000p+1022", chars_format::hex, 22, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffc0p+1021", chars_format::hex, 22, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffc1p+1021", chars_format::hex, 22, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffdfp+1021", chars_format::hex, 22, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffe0p+1021", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffe1p+1021", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("7.ffffffffffffffp+1021", chars_format::hex, 22, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("8.00000000000000p+1021", chars_format::hex, 22, errc::result_out_of_range, T{}));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffff80p+1024", chars_format::hex, 23, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffff81p+1024", chars_format::hex, 23, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffffbfp+1024", chars_format::hex, 23, errc{}, 0x1.fffffffffffffp+1023));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffffc0p+1024", chars_format::hex, 23, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffffc1p+1024", chars_format::hex, 23, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("0.fffffffffffffffp+1024", chars_format::hex, 23, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("1.000000000000000p+1024", chars_format::hex, 23, errc::result_out_of_range, T{}));

	// (0 + 1 - 2 * 2^-53) * 2^-1022 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720088902458687608585988765042311224095946549352480256244000922823569517877588880375915526423097809504"
		"34312085877387158357291821993020294379224223559819827501242041788969571311791082261043971979604000454897391938079"
		"19893608152561311337614984204327175103362739154978273159414382813627511383860409424946494228631669542910508020181"
		"59266421349966065178030950759130587198464239060686371020051087232827846788436319445158661350412234790147923695852"
		"08321597621066375401613736583044193603714778355306682834535634005074073040135602968046375918583163124224521599262"
		"54649430083685186171942241764645513713542013221703137049658321015465406803539741790602258950302350193751977303094"
		"5763173210852507299305089761582519159720757232455434770912461317493580281734466552734375e-308",
		chars_format::scientific, 773, errc{}, 0x0.fffffffffffffp-1022));

	// (0 + 1 - 2 * 2^-53) * 2^-1022 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720088902458687608585988765042311224095946549352480256244000922823569517877588880375915526423097809504"
		"34312085877387158357291821993020294379224223559819827501242041788969571311791082261043971979604000454897391938079"
		"19893608152561311337614984204327175103362739154978273159414382813627511383860409424946494228631669542910508020181"
		"59266421349966065178030950759130587198464239060686371020051087232827846788436319445158661350412234790147923695852"
		"08321597621066375401613736583044193603714778355306682834535634005074073040135602968046375918583163124224521599262"
		"54649430083685186171942241764645513713542013221703137049658321015465406803539741790602258950302350193751977303094"
		"57631732108525072993050897615825191597207572324554347709124613174935802817344665527343750000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000e-308",
		chars_format::scientific, 1773, errc{}, 0x0.fffffffffffffp-1022));

	// above (0 + 1 - 2 * 2^-53) * 2^-1022, appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720088902458687608585988765042311224095946549352480256244000922823569517877588880375915526423097809504"
		"34312085877387158357291821993020294379224223559819827501242041788969571311791082261043971979604000454897391938079"
		"19893608152561311337614984204327175103362739154978273159414382813627511383860409424946494228631669542910508020181"
		"59266421349966065178030950759130587198464239060686371020051087232827846788436319445158661350412234790147923695852"
		"08321597621066375401613736583044193603714778355306682834535634005074073040135602968046375918583163124224521599262"
		"54649430083685186171942241764645513713542013221703137049658321015465406803539741790602258950302350193751977303094"
		"57631732108525072993050897615825191597207572324554347709124613174935802817344665527343750000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"000000000000000000000000000000000000000000000000000000000000000000000001e-308",
		chars_format::scientific, 1774, errc{}, 0x0.fffffffffffffp-1022));

	// above (0 + 1 - 2 * 2^-53) * 2^-1022: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720088902458687608585988765042311224095946549352480256244000922823569517877588880375915526423097809504"
		"34312085877387158357291821993020294379224223559819827501242041788969571311791082261043971979604000454897391938079"
		"19893608152561311337614984204327175103362739154978273159414382813627511383860409424946494228631669542910508020181"
		"59266421349966065178030950759130587198464239060686371020051087232827846788436319445158661350412234790147923695852"
		"08321597621066375401613736583044193603714778355306682834535634005074073040135602968046375918583163124224521599262"
		"54649430083685186171942241764645513713542013221703137049658321015465406803539741790602258950302350193751977303094"
		"57631732108525072993050897615825191597207572324554347709124613174935802817344665527343751e-308",
		chars_format::scientific, 774, errc{}, 0x0.fffffffffffffp-1022));

	// above (0 + 1 - 2 * 2^-53) * 2^-1022: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720088902458687608585988765042311224095946549352480256244000922823569517877588880375915526423097809504"
		"34312085877387158357291821993020294379224223559819827501242041788969571311791082261043971979604000454897391938079"
		"19893608152561311337614984204327175103362739154978273159414382813627511383860409424946494228631669542910508020181"
		"59266421349966065178030950759130587198464239060686371020051087232827846788436319445158661350412234790147923695852"
		"08321597621066375401613736583044193603714778355306682834535634005074073040135602968046375918583163124224521599262"
		"54649430083685186171942241764645513713542013221703137049658321015465406803539741790602258950302350193751977303094"
		"5763173210852507299305089761582519159720757232455434770912461317493580281734466552734376e-308",
		chars_format::scientific, 773, errc{}, 0x0.fffffffffffffp-1022));

	// below (0 + 1 - 2^-53) * 2^-1022: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720113605740979670913197593481954635164564802342610972482222202107694551652952390813508791414915891303"
		"96211068700864386945946455276572074078206217433799881410632673292535522868813721490129811224514518898490572223072"
		"85255133155755015914397476397983411801999323962548289017107081850690630666655994938275772572015763062690663332647"
		"56530000924588831643303777979186961204949739037782970490505108060994073026293712895895000358379996720725430436028"
		"40788957717961509455167482434710307026091446215722898802581825451803257070188608721131280795122334262883686223215"
		"03775666622503982534335974568884423900265498198385487948292206894721689831099698365846814022854243330660339850886"
		"44580400103493397042756718644338377048603786162277173854562306587467901408672332763671874999e-308",
		chars_format::scientific, 777, errc{}, 0x0.fffffffffffffp-1022));

	// (0 + 1 - 2^-53) * 2^-1022 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720113605740979670913197593481954635164564802342610972482222202107694551652952390813508791414915891303"
		"96211068700864386945946455276572074078206217433799881410632673292535522868813721490129811224514518898490572223072"
		"85255133155755015914397476397983411801999323962548289017107081850690630666655994938275772572015763062690663332647"
		"56530000924588831643303777979186961204949739037782970490505108060994073026293712895895000358379996720725430436028"
		"40788957717961509455167482434710307026091446215722898802581825451803257070188608721131280795122334262883686223215"
		"03775666622503982534335974568884423900265498198385487948292206894721689831099698365846814022854243330660339850886"
		"44580400103493397042756718644338377048603786162277173854562306587467901408672332763671875e-308",
		chars_format::scientific, 774, errc{}, 0x1.0000000000000p-1022));

	// (0 + 1 - 2^-53) * 2^-1022 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720113605740979670913197593481954635164564802342610972482222202107694551652952390813508791414915891303"
		"96211068700864386945946455276572074078206217433799881410632673292535522868813721490129811224514518898490572223072"
		"85255133155755015914397476397983411801999323962548289017107081850690630666655994938275772572015763062690663332647"
		"56530000924588831643303777979186961204949739037782970490505108060994073026293712895895000358379996720725430436028"
		"40788957717961509455167482434710307026091446215722898802581825451803257070188608721131280795122334262883686223215"
		"03775666622503982534335974568884423900265498198385487948292206894721689831099698365846814022854243330660339850886"
		"44580400103493397042756718644338377048603786162277173854562306587467901408672332763671875000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"000000000000000000000000000000000000000000000000000000000000000000000000e-308",
		chars_format::scientific, 1774, errc{}, 0x1.0000000000000p-1022));

	// above (0 + 1 - 2^-53) * 2^-1022: append a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720113605740979670913197593481954635164564802342610972482222202107694551652952390813508791414915891303"
		"96211068700864386945946455276572074078206217433799881410632673292535522868813721490129811224514518898490572223072"
		"85255133155755015914397476397983411801999323962548289017107081850690630666655994938275772572015763062690663332647"
		"56530000924588831643303777979186961204949739037782970490505108060994073026293712895895000358379996720725430436028"
		"40788957717961509455167482434710307026091446215722898802581825451803257070188608721131280795122334262883686223215"
		"03775666622503982534335974568884423900265498198385487948292206894721689831099698365846814022854243330660339850886"
		"44580400103493397042756718644338377048603786162277173854562306587467901408672332763671875000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000001e-308",
		chars_format::scientific, 1775, errc{}, 0x1.0000000000000p-1022));

	// above (0 + 1 - 2^-53) * 2^-1022: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720113605740979670913197593481954635164564802342610972482222202107694551652952390813508791414915891303"
		"96211068700864386945946455276572074078206217433799881410632673292535522868813721490129811224514518898490572223072"
		"85255133155755015914397476397983411801999323962548289017107081850690630666655994938275772572015763062690663332647"
		"56530000924588831643303777979186961204949739037782970490505108060994073026293712895895000358379996720725430436028"
		"40788957717961509455167482434710307026091446215722898802581825451803257070188608721131280795122334262883686223215"
		"03775666622503982534335974568884423900265498198385487948292206894721689831099698365846814022854243330660339850886"
		"445804001034933970427567186443383770486037861622771738545623065874679014086723327636718751e-308",
		chars_format::scientific, 775, errc{}, 0x1.0000000000000p-1022));

	// above (0 + 1 - 2^-53) * 2^-1022: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720113605740979670913197593481954635164564802342610972482222202107694551652952390813508791414915891303"
		"96211068700864386945946455276572074078206217433799881410632673292535522868813721490129811224514518898490572223072"
		"85255133155755015914397476397983411801999323962548289017107081850690630666655994938275772572015763062690663332647"
		"56530000924588831643303777979186961204949739037782970490505108060994073026293712895895000358379996720725430436028"
		"40788957717961509455167482434710307026091446215722898802581825451803257070188608721131280795122334262883686223215"
		"03775666622503982534335974568884423900265498198385487948292206894721689831099698365846814022854243330660339850886"
		"44580400103493397042756718644338377048603786162277173854562306587467901408672332763671876e-308",
		chars_format::scientific, 774, errc{}, 0x1.0000000000000p-1022));

	// below (0 + 1 - 0.5 * 2^-53) * 2^-1022: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720125957382125702076802007701776340698873928837676330601332841749757068540634146032305423910824932203"
		"77160560112603001240273771918347963927697214370789908365327989044318498647325041104672730846969778120287162365569"
		"67935895657351868202788722494811530151317616366333296945953431369222190308053787694940411743707809822580740988880"
		"55161790711900214875940191589215148208192489026331270225732118475077186145222409621263169862363877686014183806116"
		"57022637766409076481944355360543363737279780145931006786604921175167849085215111597673733233391919832213268535191"
		"28338784891913380715532840971003878993627240686726663397609149834349831344879676653469091559130189899114521124782"
		"380547341009775590676096291585949697743018930811385869272811532937339507043361663818359374999e-308",
		chars_format::scientific, 778, errc{}, 0x1.0000000000000p-1022));

	// (0 + 1 - 0.5 * 2^-53) * 2^-1022 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720125957382125702076802007701776340698873928837676330601332841749757068540634146032305423910824932203"
		"77160560112603001240273771918347963927697214370789908365327989044318498647325041104672730846969778120287162365569"
		"67935895657351868202788722494811530151317616366333296945953431369222190308053787694940411743707809822580740988880"
		"55161790711900214875940191589215148208192489026331270225732118475077186145222409621263169862363877686014183806116"
		"57022637766409076481944355360543363737279780145931006786604921175167849085215111597673733233391919832213268535191"
		"28338784891913380715532840971003878993627240686726663397609149834349831344879676653469091559130189899114521124782"
		"380547341009775590676096291585949697743018930811385869272811532937339507043361663818359375e-308",
		chars_format::scientific, 775, errc{}, 0x1.0000000000000p-1022));

	// (0 + 1 - 0.5 * 2^-53) * 2^-1022 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720125957382125702076802007701776340698873928837676330601332841749757068540634146032305423910824932203"
		"77160560112603001240273771918347963927697214370789908365327989044318498647325041104672730846969778120287162365569"
		"67935895657351868202788722494811530151317616366333296945953431369222190308053787694940411743707809822580740988880"
		"55161790711900214875940191589215148208192489026331270225732118475077186145222409621263169862363877686014183806116"
		"57022637766409076481944355360543363737279780145931006786604921175167849085215111597673733233391919832213268535191"
		"28338784891913380715532840971003878993627240686726663397609149834349831344879676653469091559130189899114521124782"
		"38054734100977559067609629158594969774301893081138586927281153293733950704336166381835937500000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000e-308",
		chars_format::scientific, 1775, errc{}, 0x1.0000000000000p-1022));

	// above (0 + 1 - 0.5 * 2^-53) * 2^-1022: append a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720125957382125702076802007701776340698873928837676330601332841749757068540634146032305423910824932203"
		"77160560112603001240273771918347963927697214370789908365327989044318498647325041104672730846969778120287162365569"
		"67935895657351868202788722494811530151317616366333296945953431369222190308053787694940411743707809822580740988880"
		"55161790711900214875940191589215148208192489026331270225732118475077186145222409621263169862363877686014183806116"
		"57022637766409076481944355360543363737279780145931006786604921175167849085215111597673733233391919832213268535191"
		"28338784891913380715532840971003878993627240686726663397609149834349831344879676653469091559130189899114521124782"
		"38054734100977559067609629158594969774301893081138586927281153293733950704336166381835937500000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000001e-308",
		chars_format::scientific, 1776, errc{}, 0x1.0000000000000p-1022));

	// above (0 + 1 - 0.5 * 2^-53) * 2^-1022: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720125957382125702076802007701776340698873928837676330601332841749757068540634146032305423910824932203"
		"77160560112603001240273771918347963927697214370789908365327989044318498647325041104672730846969778120287162365569"
		"67935895657351868202788722494811530151317616366333296945953431369222190308053787694940411743707809822580740988880"
		"55161790711900214875940191589215148208192489026331270225732118475077186145222409621263169862363877686014183806116"
		"57022637766409076481944355360543363737279780145931006786604921175167849085215111597673733233391919832213268535191"
		"28338784891913380715532840971003878993627240686726663397609149834349831344879676653469091559130189899114521124782"
		"3805473410097755906760962915859496977430189308113858692728115329373395070433616638183593751e-308",
		chars_format::scientific, 776, errc{}, 0x1.0000000000000p-1022));

	// above (0 + 1 - 0.5 * 2^-53) * 2^-1022: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720125957382125702076802007701776340698873928837676330601332841749757068540634146032305423910824932203"
		"77160560112603001240273771918347963927697214370789908365327989044318498647325041104672730846969778120287162365569"
		"67935895657351868202788722494811530151317616366333296945953431369222190308053787694940411743707809822580740988880"
		"55161790711900214875940191589215148208192489026331270225732118475077186145222409621263169862363877686014183806116"
		"57022637766409076481944355360543363737279780145931006786604921175167849085215111597673733233391919832213268535191"
		"28338784891913380715532840971003878993627240686726663397609149834349831344879676653469091559130189899114521124782"
		"380547341009775590676096291585949697743018930811385869272811532937339507043361663818359376e-308",
		chars_format::scientific, 775, errc{}, 0x1.0000000000000p-1022));

	// below 1 * 2^-1022: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720138309023271733240406421921598046233183055332741688720443481391819585428315901251102056406733973103"
		"58110051524341615534601088560123853777188211307779935320023304796101474425836360719215650469425037342083752508066"
		"50616658158948720491179968591639648500635908770118304874799780887753749949451580451605050915399856582470818645113"
		"53793580499211598108576605199243335211435239014879569960959128889160299264151106346631339366347758651302937176204"
		"73256317814856643508721228286376420448468114076139114770628016898532441100241614474216185671661505401542850847167"
		"52901903161322778896729707373123334086988983175067838846926092773977972858659654941091369095406136467568702398678"
		"315290680984617210924625396728515624999e-308",
		chars_format::scientific, 724, errc{}, 0x1.0000000000000p-1022));

	// 1 * 2^-1022 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"2."
		"22507385850720138309023271733240406421921598046233183055332741688720443481391819585428315901251102056406733973103"
		"58110051524341615534601088560123853777188211307779935320023304796101474425836360719215650469425037342083752508066"
		"50616658158948720491179968591639648500635908770118304874799780887753749949451580451605050915399856582470818645113"
		"53793580499211598108576605199243335211435239014879569960959128889160299264151106346631339366347758651302937176204"
		"73256317814856643508721228286376420448468114076139114770628016898532441100241614474216185671661505401542850847167"
		"52901903161322778896729707373123334086988983175067838846926092773977972858659654941091369095406136467568702398678"
		"315290680984617210924625396728515625e-308",
		chars_format::scientific, 721, errc{}, 0x1.0000000000000p-1022));

	// GH-3161: "<charconv>: from_chars, incorrect conversion of tiny doubles, when specified without a fractional part"
	// slightly above the midpoint between 0x1.4258265642fe8p-1022 and 0x1.4258265642fe9p-1022, without decimal point
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"28017185671564702625986967801367508381305145856029502167789836829722124560807078866183829589255835985468748869481"
		"86583142362517164634520243360501584015713807233124871337198558567758800235976556111488605578858880932554217965863"
		"07051360968462063659891899462054247537745976596872767714180852945844484408053399155613871082139550145579799707241"
		"02739077746853707044081281775302910700845395388393628022004086658191413817026937499382994523889310476633341355125"
		"36970161512201336865537906990405470959087815470627336860267082642705818724890923485099076407427813196992821890396"
		"81414673574614863062987306855746291767811978264371471321046227200851894843139416687953473478884075454592166055730"
		"14774895683738184268219531683594714240155669493243656420489173797250259667634963989257812500000001e-1083",
		chars_format::scientific, 782, errc{}, 0x1.4258265642fe9p-1022));

	// (1 + 1 - 2 * 2^-53) * 2^1023 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623157081452742373170435679807056752584499659891747680315726078002853876058955863276687817154045895351"
		"43824642343213268894641827684675467035375169860499105765512820762454900903893289440758685084551339423045832369032"
		"22948165808559332123348274797826204144723168738177180919299881250404026184124858368",
		chars_format::fixed, 309, errc{}, 0x1.fffffffffffffp+1023));

	// (1 + 1 - 2 * 2^-53) * 2^1023 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623157081452742373170435679807056752584499659891747680315726078002853876058955863276687817154045895351"
		"43824642343213268894641827684675467035375169860499105765512820762454900903893289440758685084551339423045832369032"
		"22948165808559332123348274797826204144723168738177180919299881250404026184124858368."
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		chars_format::fixed, 1310, errc{}, 0x1.fffffffffffffp+1023));

	// above (1 + 1 - 2 * 2^-53) * 2^1023, appended a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623157081452742373170435679807056752584499659891747680315726078002853876058955863276687817154045895351"
		"43824642343213268894641827684675467035375169860499105765512820762454900903893289440758685084551339423045832369032"
		"22948165808559332123348274797826204144723168738177180919299881250404026184124858368."
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
		chars_format::fixed, 1311, errc{}, 0x1.fffffffffffffp+1023));

	// above (1 + 1 - 2 * 2^-53) * 2^1023: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623157081452742373170435679807056752584499659891747680315726078002853876058955863276687817154045895351"
		"43824642343213268894641827684675467035375169860499105765512820762454900903893289440758685084551339423045832369032"
		"22948165808559332123348274797826204144723168738177180919299881250404026184124858368.1",
		chars_format::fixed, 311, errc{}, 0x1.fffffffffffffp+1023));

	// above (1 + 1 - 2 * 2^-53) * 2^1023: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623157081452742373170435679807056752584499659891747680315726078002853876058955863276687817154045895351"
		"43824642343213268894641827684675467035375169860499105765512820762454900903893289440758685084551339423045832369032"
		"22948165808559332123348274797826204144723168738177180919299881250404026184124858369",
		chars_format::fixed, 309, errc{}, 0x1.fffffffffffffp+1023));

	// below (1 + 1 - 2^-53) * 2^1023: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623158079372897140530341507993413271003782693617377898044496829276475094664901797758720709633028641669"
		"28879109465555478519404026306574886715058206819089020007083836762738548458177115317644757302700698555713669596228"
		"42914819860834936475292719074168444365510704342711559699508093042880177904174497791.999",
		chars_format::fixed, 313, errc{}, 0x1.fffffffffffffp+1023));
#endif

	// (1 + 1 - 2^-53) * 2^1023 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623158079372897140530341507993413271003782693617377898044496829276475094664901797758720709633028641669"
		"28879109465555478519404026306574886715058206819089020007083836762738548458177115317644757302700698555713669596228"
		"42914819860834936475292719074168444365510704342711559699508093042880177904174497792",
		chars_format::fixed, 309, errc::result_out_of_range, T{}));

	// (1 + 1 - 2^-53) * 2^1023 exactly, followed by a thousand 0 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623158079372897140530341507993413271003782693617377898044496829276475094664901797758720709633028641669"
		"28879109465555478519404026306574886715058206819089020007083836762738548458177115317644757302700698555713669596228"
		"42914819860834936475292719074168444365510704342711559699508093042880177904174497792."
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		chars_format::fixed, 1310, errc::result_out_of_range, T{}));

	// above (1 + 1 - 2^-53) * 2^1023: append a thousand 0 digits followed by a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623158079372897140530341507993413271003782693617377898044496829276475094664901797758720709633028641669"
		"28879109465555478519404026306574886715058206819089020007083836762738548458177115317644757302700698555713669596228"
		"42914819860834936475292719074168444365510704342711559699508093042880177904174497792."
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
		chars_format::fixed, 1311, errc::result_out_of_range, T{}));

	// above (1 + 1 - 2^-53) * 2^1023: appended a 1 digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623158079372897140530341507993413271003782693617377898044496829276475094664901797758720709633028641669"
		"28879109465555478519404026306574886715058206819089020007083836762738548458177115317644757302700698555713669596228"
		"42914819860834936475292719074168444365510704342711559699508093042880177904174497792.1",
		chars_format::fixed, 311, errc::result_out_of_range, T{}));

	// above (1 + 1 - 2^-53) * 2^1023: incremented last digit
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623158079372897140530341507993413271003782693617377898044496829276475094664901797758720709633028641669"
		"28879109465555478519404026306574886715058206819089020007083836762738548458177115317644757302700698555713669596228"
		"42914819860834936475292719074168444365510704342711559699508093042880177904174497792",
		chars_format::fixed, 309, errc::result_out_of_range, T{}));

	// below 1 * 2^1024: decremented last digit, then appended three 9 digits
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847732240753602112011387987"
		"13933576587897688144166224928474306394741243777678934248654852763022196012460941194530829520850057688381506823424"
		"62881473913110540827237163350510684586298239947245938479716304835356329624224137215.999",
		chars_format::fixed, 313, errc::result_out_of_range, T{}));

	// 1 * 2^1024 exactly
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"17976931348623159077293051907890247336179769789423065727343008115773267580550096313270847732240753602112011387987"
		"13933576587897688144166224928474306394741243777678934248654852763022196012460941194530829520850057688381506823424"
		"62881473913110540827237163350510684586298239947245938479716304835356329624224137216",
		chars_format::fixed, 309, errc::result_out_of_range, T{}));

	{
		const char* s = "4.219902180869891e-2788";
		const auto len = hamon::strlen(s) - 1;
		const char* last = s + len;

		// last + 1 contains a digit. When that value is parsed the exponent is
		// e-2788 which returns std::errc::result_out_of_range and the value 0.
		// the proper exponent is e-278, which can be represented by a double.
		EXPECT_TRUE(test(hamon::string_view(s, last), chars_format::general, len, errc{}, 4.219902180869891e-278));
	}

#if defined(HAMON_HAS_CXX17_HEX_FLOAT)
    // See LWG-2403. This number (exactly 0x1.fffffd00000004 in infinite precision) behaves differently
    // when parsed as double and converted to float, versus being parsed as float directly.
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"1.999999821186065729339276231257827021181583404541015625", chars_format::general, 56, errc{}, 0x1.fffffdp0));
#endif

	// p が -1092 になるケース
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
		"1e-324",
		chars_format::general, 808, errc::result_out_of_range, T{}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
		"0."
		"956035300162774138801060278664817507854743610554714658685623356337924665760046411609746596423686779178146120663411"
		"832400417709397387255524011557739187034880145935040797282505408853164500540263198971379866967126279685193139419378"
		"301052092394154842974987441213148150151422501554604732137774784637373945933030900931061417304182118489439986033606"
		"596274066326401843145981579426222322314143449562050441831771173627477037110781910977573343629493179909523578331891"
		"831074140746495072934093844319764125369570613740971905218065665013749117450859939798450517607431828768951461896671"
		"316615505947959027412206686180517155441774719366414579283545771698485665247419508025260930081409453230176713056142"
		"036335144442544155934546436362082177080233424147895057091901886109680956233765657772851648714481050160876296932242"
		"16536794717923660962094952780249313260743431275034358049093223803071184474755895e-0324",
		chars_format::general, 886, errc::result_out_of_range, T{}));
}

#if defined(RANDOM_TEST)

template <typename RNG>
inline hamon::string_view make_random_number_string(
	char* buf, int integer_part_length, int fraction_part_length, int exponent_part_length, RNG& rng)
{
	std::uniform_int_distribution<> dist(0, 9);

	char* ptr = buf;

	if (integer_part_length == 0)
	{
		*ptr++ = '0';
	}
	else
	{
		for (int i = 0; i < integer_part_length; ++i)
		{
			*ptr++ = char('0' + dist(rng));
		}
	}

	if (fraction_part_length != 0)
	{
		*ptr++ = '.';

		for (int i = 0; i < fraction_part_length; ++i)
		{
			*ptr++ = char('0' + dist(rng));
		}
	}

	if (exponent_part_length != 0)
	{
		*ptr++ = 'e';

		if (dist(rng) % 2 == 0)
		{
			*ptr++ = '-';
		}

		for (int i = 0; i < exponent_part_length; ++i)
		{
			*ptr++ = char('0' + dist(rng));
		}
	}

	*ptr = '\0';

	return {buf, ptr};
}

template <typename T, typename RNG>
inline void random_test_sub(
	char* buf, int count, int integer_part_length, int fraction_part_length, int exponent_part_length, RNG& rng)
{
	for (int i = 0; i < count; ++i)
	{
		auto str = make_random_number_string(buf, integer_part_length, fraction_part_length, exponent_part_length, rng);
		//std::cout << str << hamon::endl;
		T v1{};
		T v2{};
		auto r1 = hamon::from_chars(str.begin(), str.end(), v1);
		auto r2 = std::from_chars(str.begin(), str.end(), v2);
		EXPECT_EQ((int)r1.ec, (int)r2.ec);
		if (r1)
		{
			EXPECT_EQ(v1, v2);
		}
		else
		{
			EXPECT_EQ(v1, T{});
		}
	}
}

template <typename T, int IntegerPartLengthMax, int FractionPartLengthMax, int ExponentPartLengthMax>
inline void random_test()
{
	std::random_device seed_gen;
	std::default_random_engine rng(seed_gen());

	constexpr hamon::size_t buf_size =
		IntegerPartLengthMax
		+ 1 // '.'
		+ FractionPartLengthMax
		+ 1 // 'e'
		+ 1 // '-'
		+ ExponentPartLengthMax
		+ 1; // '\0';
	char buf[buf_size]{};

	for (int i = 0; i <= IntegerPartLengthMax; ++i)
	{
		for (int j = 0; j <= FractionPartLengthMax; ++j)
		{
			for (int k = 0; k <= ExponentPartLengthMax; ++k)
			{
				random_test_sub<T>(buf, 10, i, j, k, rng);
			}
		}

		std::cout <<
			"\rrandom_test<" << (hamon::is_same<T, float>::value ? "float" : "double") << ">" <<
			"("  << i << "/" << IntegerPartLengthMax << ")";
	}
	std::cout << hamon::endl;
}
#endif

#if defined(PERFORMANCE_TEST)

template <typename RNG>
inline std::string make_random_number_string(int integer_part_length, int fraction_part_length, RNG& rng)
{
	std::uniform_int_distribution<> dist(0, 9);

	std::string result;
	result.reserve(integer_part_length + 1 + fraction_part_length);

	if (integer_part_length == 0)
	{
		result += '0';
	}
	else
	{
		for (int i = 0; i < integer_part_length; ++i)
		{
			result += char('0' + dist(rng));
		}
	}

	if (fraction_part_length != 0)
	{
		result += '.';

		for (int i = 0; i < fraction_part_length; ++i)
		{
			result += char('0' + dist(rng));
		}
	}

	return result;
}

template <typename T, typename RNG>
inline void performance_test_sub(int integer_part_length, int fraction_part_length, int loop_count, RNG& rng)
{
	std::vector<std::string> str_tbl;
	for (int i = 0; i < 100; ++i)
	{
		str_tbl.push_back(make_random_number_string(integer_part_length, fraction_part_length, rng));
	}

	{
		auto t0 = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < loop_count; ++i)
		{
			for (auto const& s : str_tbl)
			{
				T val{};
				hamon::from_chars(s.data(), s.data() + s.size(), val);
			}
		}

		auto t1 = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
		std::cout <<
			"from_chars<" << (hamon::is_same<T, float>::value ? "float" : "double") << ">" <<
			"(" << hamon::setw(3) << integer_part_length <<
			", " << hamon::setw(3) << fraction_part_length << "): " <<
			elapsed.count() << " ms" << hamon::endl;
	}
}

template <typename T>
inline void performance_test()
{
	std::default_random_engine rng;

	int const integer_length_tbl[]  = {0, 7, 8, 9, 16, 17, 18, 32, 64, 128, 256};
	int const fraction_length_tbl[] = {0, 4, 16, 32, 64, 128, 256, 512, 800};

	for (auto const& i : integer_length_tbl)
	{
		for (auto const& j : fraction_length_tbl)
		{
			performance_test_sub<T>(i, j, 10000, rng);
		}
	}

	std::cout << hamon::endl;
}

#endif

GTEST_TEST(CharConvTest, FromCharsFloatingPointTest)
{
	inf_test<float, hamon::chars_format::scientific>();
	inf_test<float, hamon::chars_format::fixed>();
	inf_test<float, hamon::chars_format::hex>();
	inf_test<float, hamon::chars_format::general>();

	inf_test<double, hamon::chars_format::scientific>();
	inf_test<double, hamon::chars_format::fixed>();
	inf_test<double, hamon::chars_format::hex>();
	inf_test<double, hamon::chars_format::general>();

	nan_test<float, hamon::chars_format::scientific>();
	nan_test<float, hamon::chars_format::fixed>();
	nan_test<float, hamon::chars_format::hex>();
	nan_test<float, hamon::chars_format::general>();

	nan_test<double, hamon::chars_format::scientific>();
	nan_test<double, hamon::chars_format::fixed>();
	nan_test<double, hamon::chars_format::hex>();
	nan_test<double, hamon::chars_format::general>();

	invalid_argument_test<float, hamon::chars_format::scientific>();
	invalid_argument_test<float, hamon::chars_format::fixed>();
	invalid_argument_test<float, hamon::chars_format::hex>();
	invalid_argument_test<float, hamon::chars_format::general>();

	invalid_argument_test<double, hamon::chars_format::scientific>();
	invalid_argument_test<double, hamon::chars_format::fixed>();
	invalid_argument_test<double, hamon::chars_format::hex>();
	invalid_argument_test<double, hamon::chars_format::general>();
	
	fixed_test<float>();
	fixed_test<double>();

	scientific_test<float>();
	scientific_test<double>();

	general_test<float>();
	general_test<double>();

	hex_test<float>();
	hex_test<double>();

	float_test();
	double_test();

#if defined(RANDOM_TEST)
	random_test<float, 100, 500, 3>();
	random_test<double, 500, 1000, 4>();
#endif

#if defined(PERFORMANCE_TEST)
	performance_test<float>();
	performance_test<double>();
#endif
}

}	// namespace from_chars_floating_point_test

}	// namespace hamon_charconv_test
