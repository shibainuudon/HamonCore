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
#include <hamon/cstring.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

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

	if (ret.ec == hamon::errc{})
	{
		hamon::ieee754::binary<T> const bits1(dest);
		hamon::ieee754::binary<T> const bits2(expected_value);
		if (bits2.is_nan())
		{
			VERIFY(bits1.is_nan());
#if !(defined(HAMON_USE_STD_CHARCONV) && defined(HAMON_STDLIB_LIBSTDCPP3))	// libstdc++ で chars_format::hex のときテストが通らない
			VERIFY(bits1.sign() == bits2.sign());
#endif
		}
		else
		{
			VERIFY(bits1.uint() == bits2.uint());
		}
	}
	else if (ret.ec == hamon::errc::result_out_of_range)
	{
#if !(defined(HAMON_USE_STD_CHARCONV) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL でテストが通らない
		// TODO
		//VERIFY(dest == unmodified_value);
#endif
	}
	else
	{
		VERIFY(dest == unmodified_value);
	}

	return true;
}

template <typename T>
inline /*HAMON_CXX14_CONSTEXPR*/ bool inf_test(hamon::chars_format fmt)
{
	T const infinity = hamon::numeric_limits<T>::infinity();

	using hamon::errc;

	struct test_data
	{
		const char* input;
		hamon::size_t expected_idx;
		errc expected_ec;
		T expected_value;
	};

	const test_data data[] =
	{
		{"I",          0, errc::invalid_argument, T{0}},
		{"II",         0, errc::invalid_argument, T{0}},
		{"IN",         0, errc::invalid_argument, T{0}},
		{"INT",        0, errc::invalid_argument, T{0}},
		{"INF",        3, errc{}, infinity},
		{"INFI",       3, errc{}, infinity},
		{"INFIN",      3, errc{}, infinity},
		{"INFINI",     3, errc{}, infinity},
		{"INFINIT",    3, errc{}, infinity},
		{"INFINITX",   3, errc{}, infinity},
		{"INFINITY",   8, errc{}, infinity},
		{"INFINITYX",  8, errc{}, infinity},
		{"INFINITYXX", 8, errc{}, infinity},

		{"-I",          0, errc::invalid_argument, T{0}},
		{"-II",         0, errc::invalid_argument, T{0}},
		{"-IN",         0, errc::invalid_argument, T{0}},
		{"-INT",        0, errc::invalid_argument, T{0}},
		{"-INF",        4, errc{}, -infinity},
		{"-INFI",       4, errc{}, -infinity},
		{"-INFIN",      4, errc{}, -infinity},
		{"-INFINI",     4, errc{}, -infinity},
		{"-INFINIT",    4, errc{}, -infinity},
		{"-INFINITX",   4, errc{}, -infinity},
		{"-INFINITY",   9, errc{}, -infinity},
		{"-INFINITYX",  9, errc{}, -infinity},
		{"-INFINITYXX", 9, errc{}, -infinity},

		{"i",          0, errc::invalid_argument, T{0}},
		{"ii",         0, errc::invalid_argument, T{0}},
		{"in",         0, errc::invalid_argument, T{0}},
		{"int",        0, errc::invalid_argument, T{0}},
		{"inf",        3, errc{}, infinity},
		{"infi",       3, errc{}, infinity},
		{"infin",      3, errc{}, infinity},
		{"infini",     3, errc{}, infinity},
		{"infinit",    3, errc{}, infinity},
		{"infinitx",   3, errc{}, infinity},
		{"infinity",   8, errc{}, infinity},
		{"infinityx",  8, errc{}, infinity},
		{"infinityxx", 8, errc{}, infinity},

		{"-i",          0, errc::invalid_argument, T{0}},
		{"-ii",         0, errc::invalid_argument, T{0}},
		{"-in",         0, errc::invalid_argument, T{0}},
		{"-int",        0, errc::invalid_argument, T{0}},
		{"-inf",        4, errc{}, -infinity},
		{"-infi",       4, errc{}, -infinity},
		{"-infin",      4, errc{}, -infinity},
		{"-infini",     4, errc{}, -infinity},
		{"-infinit",    4, errc{}, -infinity},
		{"-infinitx",   4, errc{}, -infinity},
		{"-infinity",   9, errc{}, -infinity},
		{"-infinityx",  9, errc{}, -infinity},
		{"-infinityxx", 9, errc{}, -infinity},
	};

	for (auto const& x : data)
	{
		VERIFY(test(x.input, fmt, x.expected_idx, x.expected_ec, x.expected_value));
	}

	return true;
}

template <typename T>
inline /*HAMON_CXX14_CONSTEXPR*/ bool nan_test(hamon::chars_format fmt)
{
	T const nan = hamon::numeric_limits<T>::quiet_NaN();

	using hamon::errc;

	struct test_data
	{
		const char* input;
		hamon::size_t expected_idx;
		errc expected_ec;
		T expected_value;
	};

	const test_data data[] =
	{
		{"N",          0, errc::invalid_argument, T{0}},
		{"NA",         0, errc::invalid_argument, T{0}},
		{"NAM",        0, errc::invalid_argument, T{0}},
		{"NAN",        3, errc{}, nan},
		{"NAN(",       3, errc{}, nan},
		{"NAN(!)",     3, errc{}, nan},
		{"NAN(1",      3, errc{}, nan},
		{"NAN(1_",     3, errc{}, nan},
		{"NAN(1_A",    3, errc{}, nan},
		{"NAN(1_A)",   8, errc{}, nan},
		{"NAN(1_A)X",  8, errc{}, nan},
		{"NAN(1_A)XX", 8, errc{}, nan},

		{"-N",          0, errc::invalid_argument, T{0}},
		{"-NA",         0, errc::invalid_argument, T{0}},
		{"-NAM",        0, errc::invalid_argument, T{0}},
		{"-NAN",        4, errc{}, -nan},
		{"-NAN(",       4, errc{}, -nan},
		{"-NAN(!)",     4, errc{}, -nan},
		{"-NAN(1",      4, errc{}, -nan},
		{"-NAN(1_",     4, errc{}, -nan},
		{"-NAN(1_A",    4, errc{}, -nan},
		{"-NAN(1_A)",   9, errc{}, -nan},
		{"-NAN(1_A)X",  9, errc{}, -nan},
		{"-NAN(1_A)XX", 9, errc{}, -nan},

		{"n",          0, errc::invalid_argument, T{0}},
		{"na",         0, errc::invalid_argument, T{0}},
		{"nam",        0, errc::invalid_argument, T{0}},
		{"nan",        3, errc{}, nan},
		{"nan(",       3, errc{}, nan},
		{"nan(!)",     3, errc{}, nan},
		{"nan(1",      3, errc{}, nan},
		{"nan(1_",     3, errc{}, nan},
		{"nan(1_a",    3, errc{}, nan},
		{"nan(1_a)",   8, errc{}, nan},
		{"nan(1_a)x",  8, errc{}, nan},
		{"nan(1_a)xx", 8, errc{}, nan},

		{"-n",          0, errc::invalid_argument, T{0}},
		{"-na",         0, errc::invalid_argument, T{0}},
		{"-nam",        0, errc::invalid_argument, T{0}},
		{"-nan",        4, errc{}, -nan},
		{"-nan(",       4, errc{}, -nan},
		{"-nan(!)",     4, errc{}, -nan},
		{"-nan(1",      4, errc{}, -nan},
		{"-nan(1_",     4, errc{}, -nan},
		{"-nan(1_a",    4, errc{}, -nan},
		{"-nan(1_a)",   9, errc{}, -nan},
		{"-nan(1_a)x",  9, errc{}, -nan},
		{"-nan(1_a)xx", 9, errc{}, -nan},
	};

	for (auto const& x : data)
	{
		VERIFY(test(x.input, fmt, x.expected_idx, x.expected_ec, x.expected_value));
	}

	return true;
}

template <typename T>
inline /*HAMON_CXX14_CONSTEXPR*/ bool invalid_argument_test(hamon::chars_format fmt)
{
	using hamon::errc;

	struct test_data
	{
		const char* input;
		hamon::size_t expected_idx;
		errc expected_ec;
		T expected_value;
	};

	const test_data data[] =
	{
		{"", 0, errc::invalid_argument, T{0}},
		{"-", 0, errc::invalid_argument, T{0}},
		{".", 0, errc::invalid_argument, T{0}},
		{"-.", 0, errc::invalid_argument, T{0}},
		{"+0.25", 0, errc::invalid_argument, T{0}},
		{"`1", 0, errc::invalid_argument, T{0}},
		{"~1", 0, errc::invalid_argument, T{0}},
		{"!1", 0, errc::invalid_argument, T{0}},
		{"@1", 0, errc::invalid_argument, T{0}},
		{"#1", 0, errc::invalid_argument, T{0}},
		{"$1", 0, errc::invalid_argument, T{0}},
		{"%1", 0, errc::invalid_argument, T{0}},
		{"^1", 0, errc::invalid_argument, T{0}},
		{"&1", 0, errc::invalid_argument, T{0}},
		{"*1", 0, errc::invalid_argument, T{0}},
		{"(1", 0, errc::invalid_argument, T{0}},
		{")1", 0, errc::invalid_argument, T{0}},
		{"_1", 0, errc::invalid_argument, T{0}},
		{"=1", 0, errc::invalid_argument, T{0}},
		{"[1", 0, errc::invalid_argument, T{0}},
		{"]1", 0, errc::invalid_argument, T{0}},
		{"{1", 0, errc::invalid_argument, T{0}},
		{"}1", 0, errc::invalid_argument, T{0}},
		{"\\1", 0, errc::invalid_argument, T{0}},
		{"|1", 0, errc::invalid_argument, T{0}},
		{";1", 0, errc::invalid_argument, T{0}},
		{":1", 0, errc::invalid_argument, T{0}},
		{"'1", 0, errc::invalid_argument, T{0}},
		{"\"1", 0, errc::invalid_argument, T{0}},
		{",1", 0, errc::invalid_argument, T{0}},
		{"/1", 0, errc::invalid_argument, T{0}},
		{"<1", 0, errc::invalid_argument, T{0}},
		{">1", 0, errc::invalid_argument, T{0}},
		{"?1", 0, errc::invalid_argument, T{0}},
		{" 1", 0, errc::invalid_argument, T{0}},
		{"\t1", 0, errc::invalid_argument, T{0}},
		{"\v1", 0, errc::invalid_argument, T{0}},
		{"\r1", 0, errc::invalid_argument, T{0}},
		{"\n1", 0, errc::invalid_argument, T{0}},
	};

	for (auto const& x : data)
	{
		VERIFY(test(x.input, fmt, x.expected_idx, x.expected_ec, x.expected_value));
	}

	return true;
}

template <typename T>
inline /*HAMON_CXX14_CONSTEXPR*/ bool fixed_test()
{
	auto const infinity = hamon::numeric_limits<T>::infinity();

	using hamon::errc;

	struct test_data
	{
		const char* input;
		hamon::size_t expected_idx;
		errc expected_ec;
		T expected_value;
	};

	const test_data data[] =
	{
		{"a123", 0, errc::invalid_argument, T{0}},
		{"b123", 0, errc::invalid_argument, T{0}},
		{"c123", 0, errc::invalid_argument, T{0}},
		{"d123", 0, errc::invalid_argument, T{0}},
		{"e123", 0, errc::invalid_argument, T{0}},
		{"f123", 0, errc::invalid_argument, T{0}},
		{"g123", 0, errc::invalid_argument, T{0}},
		{"h123", 0, errc::invalid_argument, T{0}},
		{"i123", 0, errc::invalid_argument, T{0}},
		{"j123", 0, errc::invalid_argument, T{0}},
		{"k123", 0, errc::invalid_argument, T{0}},
		{"l123", 0, errc::invalid_argument, T{0}},
		{"m123", 0, errc::invalid_argument, T{0}},
		{"n123", 0, errc::invalid_argument, T{0}},
		{"o123", 0, errc::invalid_argument, T{0}},
		{"p123", 0, errc::invalid_argument, T{0}},
		{"q123", 0, errc::invalid_argument, T{0}},
		{"r123", 0, errc::invalid_argument, T{0}},
		{"s123", 0, errc::invalid_argument, T{0}},
		{"t123", 0, errc::invalid_argument, T{0}},
		{"u123", 0, errc::invalid_argument, T{0}},
		{"v123", 0, errc::invalid_argument, T{0}},
		{"w123", 0, errc::invalid_argument, T{0}},
		{"x123", 0, errc::invalid_argument, T{0}},
		{"y123", 0, errc::invalid_argument, T{0}},
		{"z123", 0, errc::invalid_argument, T{0}},
		{"A123", 0, errc::invalid_argument, T{0}},
		{"B123", 0, errc::invalid_argument, T{0}},
		{"C123", 0, errc::invalid_argument, T{0}},
		{"D123", 0, errc::invalid_argument, T{0}},
		{"E123", 0, errc::invalid_argument, T{0}},
		{"F123", 0, errc::invalid_argument, T{0}},
		{"G123", 0, errc::invalid_argument, T{0}},
		{"H123", 0, errc::invalid_argument, T{0}},
		{"I123", 0, errc::invalid_argument, T{0}},
		{"J123", 0, errc::invalid_argument, T{0}},
		{"K123", 0, errc::invalid_argument, T{0}},
		{"L123", 0, errc::invalid_argument, T{0}},
		{"M123", 0, errc::invalid_argument, T{0}},
		{"N123", 0, errc::invalid_argument, T{0}},
		{"O123", 0, errc::invalid_argument, T{0}},
		{"P123", 0, errc::invalid_argument, T{0}},
		{"Q123", 0, errc::invalid_argument, T{0}},
		{"R123", 0, errc::invalid_argument, T{0}},
		{"S123", 0, errc::invalid_argument, T{0}},
		{"T123", 0, errc::invalid_argument, T{0}},
		{"U123", 0, errc::invalid_argument, T{0}},
		{"V123", 0, errc::invalid_argument, T{0}},
		{"W123", 0, errc::invalid_argument, T{0}},
		{"X123", 0, errc::invalid_argument, T{0}},
		{"Y123", 0, errc::invalid_argument, T{0}},
		{"Z123", 0, errc::invalid_argument, T{0}},

		{"0",         1, errc{}, T( 0.0)},
		{"-0",        2, errc{}, T(-0.0)},
		{"0.0",       3, errc{}, T( 0.0)},
		{"-0.0",      4, errc{}, T(-0.0)},
		{"0.000",     5, errc{}, T( 0.0)},
		{"-0.000",    6, errc{}, T(-0.0)},
		{"000.000",   7, errc{}, T( 0.0)},
		{"-00.000",   7, errc{}, T(-0.0)},
		{"0e0",       1, errc{}, T( 0.0)},
		{"-0e0",      2, errc{}, T(-0.0)},
		{"00e00",     2, errc{}, T( 0.0)},
		{"-00e00",    3, errc{}, T(-0.0)},
		{"0p0",       1, errc{}, T( 0.0)},
		{"-0p0",      2, errc{}, T(-0.0)},
		{"0.0p0",     3, errc{}, T( 0.0)},
		{"-0.0p0",    4, errc{}, T(-0.0)},

		{"123",       3, errc{}, T( 123)},
		{"-123",      4, errc{}, T(-123)},
		{"0.25",      4, errc{}, T( 0.25)},
		{"-0.25",     5, errc{}, T(-0.25)},
		{"001x",      3, errc{}, T( 1.0)},
		{".5",        2, errc{}, T( 0.5)},
		{"-.5",       3, errc{}, T(-0.5)},
		{"1.25.78",   4, errc{}, T(1.25)},
		{"1.5e10",    3, errc{}, T(1.5)},
		{"1.5E10",    3, errc{}, T(1.5)},
		{"1.5e+10",   3, errc{}, T(1.5)},
		{"1.5e-10",   3, errc{}, T(1.5)},
		{"1.5e",      3, errc{}, T(1.5)},
		{"1.5e+",     3, errc{}, T(1.5)},
		{"1.5e-",     3, errc{}, T(1.5)},
		{"1.5e +1",   3, errc{}, T(1.5)},
		{"1.5e+ 1",   3, errc{}, T(1.5)},
		{"1.5e -1",   3, errc{}, T(1.5)},
		{"1.5e- 1",   3, errc{}, T(1.5)},
		{"1.25e0e12", 4, errc{}, T(1.25)},
		{"1.25e++12", 4, errc{}, T(1.25)},
		{"1.25e+-12", 4, errc{}, T(1.25)},
		{"1.25e-+12", 4, errc{}, T(1.25)},
		{"1.25e--12", 4, errc{}, T(1.25)},
		{"1.25e0x12", 4, errc{}, T(1.25)},
		{"20040229",  8, errc{}, T(20040229)},
		{"123.456",   7, errc{}, T(1.23456e2)},
		{"123.456e3", 7, errc{}, T(1.23456e2)},
		{"0.111111111111111111111111111111111111111111", 44, errc{}, T(0.111111111111111111111111111111111111111111)},
		{"111111111111.111111111111111111111111111111111111111111", 55, errc{}, T(111111111111.111111111111111111111111111111111111111111)},
		{"1"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		 801, errc::result_out_of_range, infinity},
		{"-1"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
		 "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001",
		 802, errc::result_out_of_range, -infinity},
	};

	for (auto const& x : data)
	{
		VERIFY(test(x.input, hamon::chars_format::fixed, x.expected_idx, x.expected_ec, x.expected_value));
	}

	return true;
}

template <typename T>
inline /*HAMON_CXX14_CONSTEXPR*/ bool scientific_test()
{
	auto const infinity = hamon::numeric_limits<T>::infinity();

	using hamon::errc;

	struct test_data
	{
		const char* input;
		hamon::size_t expected_idx;
		errc expected_ec;
		T expected_value;
	};

	const test_data data[] =
	{
		{"a1e0", 0, errc::invalid_argument, T{0}},
		{"b1e0", 0, errc::invalid_argument, T{0}},
		{"c1e0", 0, errc::invalid_argument, T{0}},
		{"d1e0", 0, errc::invalid_argument, T{0}},
		{"e1e0", 0, errc::invalid_argument, T{0}},
		{"f1e0", 0, errc::invalid_argument, T{0}},
		{"g1e0", 0, errc::invalid_argument, T{0}},
		{"h1e0", 0, errc::invalid_argument, T{0}},
		{"i1e0", 0, errc::invalid_argument, T{0}},
		{"j1e0", 0, errc::invalid_argument, T{0}},
		{"k1e0", 0, errc::invalid_argument, T{0}},
		{"l1e0", 0, errc::invalid_argument, T{0}},
		{"m1e0", 0, errc::invalid_argument, T{0}},
		{"n1e0", 0, errc::invalid_argument, T{0}},
		{"o1e0", 0, errc::invalid_argument, T{0}},
		{"p1e0", 0, errc::invalid_argument, T{0}},
		{"q1e0", 0, errc::invalid_argument, T{0}},
		{"r1e0", 0, errc::invalid_argument, T{0}},
		{"s1e0", 0, errc::invalid_argument, T{0}},
		{"t1e0", 0, errc::invalid_argument, T{0}},
		{"u1e0", 0, errc::invalid_argument, T{0}},
		{"v1e0", 0, errc::invalid_argument, T{0}},
		{"w1e0", 0, errc::invalid_argument, T{0}},
		{"x1e0", 0, errc::invalid_argument, T{0}},
		{"y1e0", 0, errc::invalid_argument, T{0}},
		{"z1e0", 0, errc::invalid_argument, T{0}},
		{"A1e0", 0, errc::invalid_argument, T{0}},
		{"B1e0", 0, errc::invalid_argument, T{0}},
		{"C1e0", 0, errc::invalid_argument, T{0}},
		{"D1e0", 0, errc::invalid_argument, T{0}},
		{"E1e0", 0, errc::invalid_argument, T{0}},
		{"F1e0", 0, errc::invalid_argument, T{0}},
		{"G1e0", 0, errc::invalid_argument, T{0}},
		{"H1e0", 0, errc::invalid_argument, T{0}},
		{"I1e0", 0, errc::invalid_argument, T{0}},
		{"J1e0", 0, errc::invalid_argument, T{0}},
		{"K1e0", 0, errc::invalid_argument, T{0}},
		{"L1e0", 0, errc::invalid_argument, T{0}},
		{"M1e0", 0, errc::invalid_argument, T{0}},
		{"N1e0", 0, errc::invalid_argument, T{0}},
		{"O1e0", 0, errc::invalid_argument, T{0}},
		{"P1e0", 0, errc::invalid_argument, T{0}},
		{"Q1e0", 0, errc::invalid_argument, T{0}},
		{"R1e0", 0, errc::invalid_argument, T{0}},
		{"S1e0", 0, errc::invalid_argument, T{0}},
		{"T1e0", 0, errc::invalid_argument, T{0}},
		{"U1e0", 0, errc::invalid_argument, T{0}},
		{"V1e0", 0, errc::invalid_argument, T{0}},
		{"W1e0", 0, errc::invalid_argument, T{0}},
		{"X1e0", 0, errc::invalid_argument, T{0}},
		{"Y1e0", 0, errc::invalid_argument, T{0}},
		{"Z1e0", 0, errc::invalid_argument, T{0}},

		{"1.23",      0, errc::invalid_argument, T{0}},
		{"1.23e",     0, errc::invalid_argument, T{0}},
		{"1.5e+",     0, errc::invalid_argument, T{0}},
		{"1.5e-",     0, errc::invalid_argument, T{0}},
		{"1.5e +1",   0, errc::invalid_argument, T{0}},
		{"1.5e+ 1",   0, errc::invalid_argument, T{0}},
		{"1.5e -1",   0, errc::invalid_argument, T{0}},
		{"1.5e- 1",   0, errc::invalid_argument, T{0}},
		{"1.25e++12", 0, errc::invalid_argument, T{0}},
		{"1.25e+-12", 0, errc::invalid_argument, T{0}},
		{"1.25e-+12", 0, errc::invalid_argument, T{0}},
		{"1.25e--12", 0, errc::invalid_argument, T{0}},

		{"0",         0, errc::invalid_argument, T{0}},
		{"-0",        0, errc::invalid_argument, T{0}},
		{"0.0",       0, errc::invalid_argument, T{0}},
		{"-0.0",      0, errc::invalid_argument, T{0}},
		{"0.000",     0, errc::invalid_argument, T{0}},
		{"-0.000",    0, errc::invalid_argument, T{0}},
		{"000.000",   0, errc::invalid_argument, T{0}},
		{"-00.000",   0, errc::invalid_argument, T{0}},
		{"0e0",       3, errc{}, T( 0.0)},
		{"-0e0",      4, errc{}, T(-0.0)},
		{"00e00",     5, errc{}, T( 0.0)},
		{"-00e00",    6, errc{}, T(-0.0)},
		{"0p0",       0, errc::invalid_argument, T{0}},
		{"-0p0",      0, errc::invalid_argument, T{0}},
		{"0.0p0",     0, errc::invalid_argument, T{0}},
		{"-0.0p0",    0, errc::invalid_argument, T{0}},

		{"0.25e0",      6, errc{}, T( 0.25)},
		{"-0.25e0",     7, errc{}, T(-0.25)},
		{"001e0x",      5, errc{}, T(1.0)},
		{"1.25e0.78",   6, errc{}, T(1.25)},
		{"1.5e10",      6, errc{}, T(1.5e10)},
		{"1.5E10",      6, errc{}, T(1.5e10)},
		{"1.5e+10",     7, errc{}, T(1.5e10)},
		{"1.5e-10",     7, errc{}, T(1.5e-10)},
		{"0.001e5",     7, errc{}, T(1.0e2)},
		{"0.001e-5",    8, errc{}, T(1.0e-8)},
		{"1.25e0x12",   6, errc{}, T(1.25)},
		{"20040229e0", 10, errc{}, T(20040229)},
		{"123.456e3",   9, errc{}, T(1.23456e5)},
		{"0.111111111111111111111111111111111111111111e0", 46, errc{}, T(0.111111111111111111111111111111111111111111)},
		{"111111111111.111111111111111111111111111111111111111111e0", 57, errc{}, T(111111111111.111111111111111111111111111111111111111111)},

		{"1e9999999999999999999999999999999999999999",   42, errc::result_out_of_range,  infinity},
		{"-1e9999999999999999999999999999999999999999",  43, errc::result_out_of_range, -infinity},
		{"1e-9999999999999999999999999999999999999999",  43, errc::result_out_of_range, T{ 0.0}},
		{"-1e-9999999999999999999999999999999999999999", 44, errc::result_out_of_range, T{-0.0}},
	};

	for (auto const& x : data)
	{
		VERIFY(test(x.input, hamon::chars_format::scientific, x.expected_idx, x.expected_ec, x.expected_value));
	}

	return true;
}

template <typename T>
inline /*HAMON_CXX14_CONSTEXPR*/ bool general_test()
{
	auto const infinity = hamon::numeric_limits<T>::infinity();

	using hamon::errc;

	struct test_data
	{
		const char* input;
		hamon::size_t expected_idx;
		errc expected_ec;
		T expected_value;
	};

	const test_data data[] =
	{
		{"a1", 0, errc::invalid_argument, T{0}},
		{"b1", 0, errc::invalid_argument, T{0}},
		{"c1", 0, errc::invalid_argument, T{0}},
		{"d1", 0, errc::invalid_argument, T{0}},
		{"e1", 0, errc::invalid_argument, T{0}},
		{"f1", 0, errc::invalid_argument, T{0}},
		{"g1", 0, errc::invalid_argument, T{0}},
		{"h1", 0, errc::invalid_argument, T{0}},
		{"i1", 0, errc::invalid_argument, T{0}},
		{"j1", 0, errc::invalid_argument, T{0}},
		{"k1", 0, errc::invalid_argument, T{0}},
		{"l1", 0, errc::invalid_argument, T{0}},
		{"m1", 0, errc::invalid_argument, T{0}},
		{"n1", 0, errc::invalid_argument, T{0}},
		{"o1", 0, errc::invalid_argument, T{0}},
		{"p1", 0, errc::invalid_argument, T{0}},
		{"q1", 0, errc::invalid_argument, T{0}},
		{"r1", 0, errc::invalid_argument, T{0}},
		{"s1", 0, errc::invalid_argument, T{0}},
		{"t1", 0, errc::invalid_argument, T{0}},
		{"u1", 0, errc::invalid_argument, T{0}},
		{"v1", 0, errc::invalid_argument, T{0}},
		{"w1", 0, errc::invalid_argument, T{0}},
		{"x1", 0, errc::invalid_argument, T{0}},
		{"y1", 0, errc::invalid_argument, T{0}},
		{"z1", 0, errc::invalid_argument, T{0}},
		{"A1", 0, errc::invalid_argument, T{0}},
		{"B1", 0, errc::invalid_argument, T{0}},
		{"C1", 0, errc::invalid_argument, T{0}},
		{"D1", 0, errc::invalid_argument, T{0}},
		{"E1", 0, errc::invalid_argument, T{0}},
		{"F1", 0, errc::invalid_argument, T{0}},
		{"G1", 0, errc::invalid_argument, T{0}},
		{"H1", 0, errc::invalid_argument, T{0}},
		{"I1", 0, errc::invalid_argument, T{0}},
		{"J1", 0, errc::invalid_argument, T{0}},
		{"K1", 0, errc::invalid_argument, T{0}},
		{"L1", 0, errc::invalid_argument, T{0}},
		{"M1", 0, errc::invalid_argument, T{0}},
		{"N1", 0, errc::invalid_argument, T{0}},
		{"O1", 0, errc::invalid_argument, T{0}},
		{"P1", 0, errc::invalid_argument, T{0}},
		{"Q1", 0, errc::invalid_argument, T{0}},
		{"R1", 0, errc::invalid_argument, T{0}},
		{"S1", 0, errc::invalid_argument, T{0}},
		{"T1", 0, errc::invalid_argument, T{0}},
		{"U1", 0, errc::invalid_argument, T{0}},
		{"V1", 0, errc::invalid_argument, T{0}},
		{"W1", 0, errc::invalid_argument, T{0}},
		{"X1", 0, errc::invalid_argument, T{0}},
		{"Y1", 0, errc::invalid_argument, T{0}},
		{"Z1", 0, errc::invalid_argument, T{0}},

		{"0",         1, errc{}, T( 0.0)},
		{"-0",        2, errc{}, T(-0.0)},
		{"0.0",       3, errc{}, T( 0.0)},
		{"-0.0",      4, errc{}, T(-0.0)},
		{"0.000",     5, errc{}, T( 0.0)},
		{"-0.000",    6, errc{}, T(-0.0)},
		{"000.000",   7, errc{}, T( 0.0)},
		{"-00.000",   7, errc{}, T(-0.0)},
		{"0e0",       3, errc{}, T( 0.0)},
		{"-0e0",      4, errc{}, T(-0.0)},
		{"00e00",     5, errc{}, T( 0.0)},
		{"-00e00",    6, errc{}, T(-0.0)},
		{"0p0",       1, errc{}, T( 0.0)},
		{"-0p0",      2, errc{}, T(-0.0)},
		{"0.0p0",     3, errc{}, T( 0.0)},
		{"-0.0p0",    4, errc{}, T(-0.0)},

		{"0.25",      4, errc{}, T( 0.25)},
		{"-0.25",     5, errc{}, T(-0.25)},
		{"001x",      3, errc{}, T( 1.0)},
		{".5e0",      4, errc{}, T( 0.5)},
		{"-.5e0",     5, errc{}, T(-0.5)},
		{".5",        2, errc{}, T( 0.5)},
		{"-.5",       3, errc{}, T(-0.5)},
		{"1.25.78",   4, errc{}, T(1.25)},
		{"1.5e10",    6, errc{}, T(1.5e10)},
		{"1.5E10",    6, errc{}, T(1.5e10)},
		{"1.5e+10",   7, errc{}, T(1.5e10)},
		{"1.5e-10",   7, errc{}, T(1.5e-10)},
		{"1.5e",      3, errc{}, T(1.5)},
		{"1.5e+",     3, errc{}, T(1.5)},
		{"1.5e-",     3, errc{}, T(1.5)},
		{"1.5e +1",   3, errc{}, T(1.5)},
		{"1.5e+ 1",   3, errc{}, T(1.5)},
		{"1.5e -1",   3, errc{}, T(1.5)},
		{"1.5e- 1",   3, errc{}, T(1.5)},
		{"1.25e++12", 4, errc{}, T(1.25)},
		{"1.25e+-12", 4, errc{}, T(1.25)},
		{"1.25e-+12", 4, errc{}, T(1.25)},
		{"1.25e--12", 4, errc{}, T(1.25)},
		{"1.25e0x12", 6, errc{}, T(1.25)},
		{"1.25e0e12", 6, errc{}, T(1.25)},
		{"20040229",  8, errc{}, T(20040229)},
		{"123.456",   7, errc{}, T(1.23456e2)},
		{"123.456e3", 9, errc{}, T(1.23456e5)},
		{"0.111111111111111111111111111111111111111111", 44, errc{}, T(0.111111111111111111111111111111111111111111)},
		{"111111111111.111111111111111111111111111111111111111111", 55, errc{}, T(111111111111.111111111111111111111111111111111111111111)},

		{"1e9999999999999999999999999999999999999999",   42, errc::result_out_of_range,  infinity},
		{"-1e9999999999999999999999999999999999999999",  43, errc::result_out_of_range, -infinity},
		{"1e-9999999999999999999999999999999999999999",  43, errc::result_out_of_range, T{ 0.0}},
		{"-1e-9999999999999999999999999999999999999999", 44, errc::result_out_of_range, T{-0.0}},
	};

	for (auto const& x : data)
	{
		VERIFY(test(x.input, hamon::chars_format::general, x.expected_idx, x.expected_ec, x.expected_value));
	}

	return true;
}

template <typename T>
inline /*HAMON_CXX14_CONSTEXPR*/ bool hex_test()
{
	auto const infinity = hamon::numeric_limits<T>::infinity();

	using hamon::errc;

	struct test_data
	{
		const char* input;
		hamon::size_t expected_idx;
		errc expected_ec;
		T expected_value;
	};

	const test_data data[] =
	{
		{"a1", 2, errc{}, T{0xa1}},
		{"b1", 2, errc{}, T{0xb1}},
		{"c1", 2, errc{}, T{0xc1}},
		{"d1", 2, errc{}, T{0xd1}},
		{"e1", 2, errc{}, T{0xe1}},
		{"f1", 2, errc{}, T{0xf1}},
		{"g1", 0, errc::invalid_argument, T{0}},
		{"h1", 0, errc::invalid_argument, T{0}},
		{"i1", 0, errc::invalid_argument, T{0}},
		{"j1", 0, errc::invalid_argument, T{0}},
		{"k1", 0, errc::invalid_argument, T{0}},
		{"l1", 0, errc::invalid_argument, T{0}},
		{"m1", 0, errc::invalid_argument, T{0}},
		{"n1", 0, errc::invalid_argument, T{0}},
		{"o1", 0, errc::invalid_argument, T{0}},
		{"p1", 0, errc::invalid_argument, T{0}},
		{"q1", 0, errc::invalid_argument, T{0}},
		{"r1", 0, errc::invalid_argument, T{0}},
		{"s1", 0, errc::invalid_argument, T{0}},
		{"t1", 0, errc::invalid_argument, T{0}},
		{"u1", 0, errc::invalid_argument, T{0}},
		{"v1", 0, errc::invalid_argument, T{0}},
		{"w1", 0, errc::invalid_argument, T{0}},
		{"x1", 0, errc::invalid_argument, T{0}},
		{"y1", 0, errc::invalid_argument, T{0}},
		{"z1", 0, errc::invalid_argument, T{0}},
		{"A1", 2, errc{}, T{0xa1}},
		{"B1", 2, errc{}, T{0xb1}},
		{"C1", 2, errc{}, T{0xc1}},
		{"D1", 2, errc{}, T{0xd1}},
		{"E1", 2, errc{}, T{0xe1}},
		{"F1", 2, errc{}, T{0xf1}},
		{"G1", 0, errc::invalid_argument, T{0}},
		{"H1", 0, errc::invalid_argument, T{0}},
		{"I1", 0, errc::invalid_argument, T{0}},
		{"J1", 0, errc::invalid_argument, T{0}},
		{"K1", 0, errc::invalid_argument, T{0}},
		{"L1", 0, errc::invalid_argument, T{0}},
		{"M1", 0, errc::invalid_argument, T{0}},
		{"N1", 0, errc::invalid_argument, T{0}},
		{"O1", 0, errc::invalid_argument, T{0}},
		{"P1", 0, errc::invalid_argument, T{0}},
		{"Q1", 0, errc::invalid_argument, T{0}},
		{"R1", 0, errc::invalid_argument, T{0}},
		{"S1", 0, errc::invalid_argument, T{0}},
		{"T1", 0, errc::invalid_argument, T{0}},
		{"U1", 0, errc::invalid_argument, T{0}},
		{"V1", 0, errc::invalid_argument, T{0}},
		{"W1", 0, errc::invalid_argument, T{0}},
		{"X1", 0, errc::invalid_argument, T{0}},
		{"Y1", 0, errc::invalid_argument, T{0}},
		{"Z1", 0, errc::invalid_argument, T{0}},

		{"0",         1, errc{}, T( 0.0)},
		{"-0",        2, errc{}, T(-0.0)},
		{"0.0",       3, errc{}, T( 0.0)},
		{"-0.0",      4, errc{}, T(-0.0)},
		{"0.000",     5, errc{}, T( 0.0)},
		{"-0.000",    6, errc{}, T(-0.0)},
		{"000.000",   7, errc{}, T( 0.0)},
		{"-00.000",   7, errc{}, T(-0.0)},
		{"0e0",       3, errc{}, T(0xe0)},
		{"-0e0",      4, errc{}, T(-0xe0)},
		{"00e00",     5, errc{}, T( 0xe00)},
		{"-00e00",    6, errc{}, T(-0xe00)},
		{"0p0",       3, errc{}, T( 0.0)},
		{"-0p0",      4, errc{}, T(-0.0)},
		{"0.0p0",     5, errc{}, T( 0.0)},
		{"-0.0p0",    6, errc{}, T(-0.0)},

		{"0.25",      4, errc{}, T( 0.14453125)},	// 0x0.25p0
		{"-0.25",     5, errc{}, T(-0.14453125)},	// -0x0.25p0
		{"001x",      3, errc{}, T(1.0)},
		{".5p0",      4, errc{}, T( 0.3125)},		// 0x0.5p0
		{"-.5p0",     5, errc{}, T(-0.3125)},		// -0x0.5p0
		{".5",        2, errc{}, T( 0.3125)},		// 0x0.5p0
		{"-.5",       3, errc{}, T(-0.3125)},		// -0x0.5p0
		{"1.25.78",   4, errc{}, T(1.14453125)},	// 0x1.25p0
		{"1.5e",      4, errc{}, T(1.3671875)},		// 0x1.5ep0
		{"1.5p10",    6, errc{}, T(1344.0)},		// 0x1.5p10
		{"1.5P10",    6, errc{}, T(1344.0)},		// 0x1.5p10
		{"1.5p+10",   7, errc{}, T(1344.0)},		// 0x1.5p10
		{"1.5p-10",   7, errc{}, T(0.00128173828125)},	// 0x1.5p-10
		{"0.001p5",   7, errc{}, T(0.0078125)},		// 0x0.001p5
		{"0.001p-5",  8, errc{}, T(7.62939453125e-06)},	// 0x0.001p-5
		{"1.5p",      3, errc{}, T(1.3125)},		// 0x1.5p0
		{"1.5p+",     3, errc{}, T(1.3125)},		// 0x1.5p0
		{"1.5p-",     3, errc{}, T(1.3125)},		// 0x1.5p0
		{"1.5p +1",   3, errc{}, T(1.3125)},		// 0x1.5p0
		{"1.5p+ 1",   3, errc{}, T(1.3125)},		// 0x1.5p0
		{"1.5p -1",   3, errc{}, T(1.3125)},		// 0x1.5p0
		{"1.5p- 1",   3, errc{}, T(1.3125)},		// 0x1.5p0
		{"1.25p++12", 4, errc{}, T(1.14453125)},	// 0x1.25p0
#if !(defined(HAMON_USE_STD_CHARCONV) && defined(HAMON_STDLIB_LIBSTDCPP3))
		{"1.25p+-12", 4, errc{}, T(1.14453125)},	// 0x1.25p0
#endif
		{"1.25p-+12", 4, errc{}, T(1.14453125)},	// 0x1.25p0
		{"1.25p--12", 4, errc{}, T(1.14453125)},	// 0x1.25p0
		{"1.25p0x12", 6, errc{}, T(1.14453125)},	// 0x1.25p0
		{"1.25p0p12", 6, errc{}, T(1.14453125)},	// 0x1.25p0
		{"131CA25",   7, errc{}, T(0x131CA25)},
		{"123.456",   7, errc{}, T(291.27099609375)},	// 0x123.456p0
		{"123.456p3", 9, errc{}, T(2330.16796875)},	// 0x123.456p3
#if defined(HAMON_HAS_CXX17_HEX_FLOAT)
		{"0.111111111111111111111111111111111111111111", 44, errc{}, T(0x0.111111111111111111111111111111111111111111p0)},
		{"111111111111.111111111111111111111111111111111111111111", 55, errc{}, T(0x111111111111.111111111111111111111111111111111111111111p0)},
#endif
		{"1p9999999999999999999999999999999999999999",   42, errc::result_out_of_range,  infinity},
		{"-1p9999999999999999999999999999999999999999",  43, errc::result_out_of_range, -infinity},
		{"1p-9999999999999999999999999999999999999999",  43, errc::result_out_of_range, T{ 0.0}},
		{"-1p-9999999999999999999999999999999999999999", 44, errc::result_out_of_range, T{-0.0}},
	};

	for (auto const& x : data)
	{
		VERIFY(test(x.input, hamon::chars_format::hex, x.expected_idx, x.expected_ec, x.expected_value));
	}

	return true;
}

inline /*HAMON_CXX14_CONSTEXPR*/ bool float_test()
{
	float const infinity = hamon::numeric_limits<float>::infinity();

	using hamon::chars_format;
	using hamon::errc;

	struct test_data
	{
		const char* input;
		chars_format fmt;
		hamon::size_t expected_idx;
		errc expected_ec;
		float expected_value;
	};

	const test_data data[] =
	{
		{"3.40282347e+38", chars_format::scientific, 14, errc{}, hamon::numeric_limits<float>::max()},
		{"1.17549435e-38", chars_format::scientific, 14, errc{}, hamon::numeric_limits<float>::min()},
		{"-3.40282347e+38", chars_format::scientific, 15, errc{}, hamon::numeric_limits<float>::lowest()},
		{"1.401e-45", chars_format::scientific, 9, errc{}, hamon::numeric_limits<float>::denorm_min()},

		{"1.a0000400", chars_format::hex, 10, errc{}, 1.62500024f},	// 0x1.a00004p0f}, // exact
		{"1.a0000401", chars_format::hex, 10, errc{}, 1.62500024f},	// 0x1.a00004p0f}, // below midpoint, round down
		{"1.a0000500", chars_format::hex, 10, errc{}, 1.62500024f},	// 0x1.a00004p0f}, // midpoint, round down to even
		{"1.a0000501", chars_format::hex, 10, errc{}, 1.62500036f},	// 0x1.a00006p0f}, // above midpoint, round up
		{"1.a0000600", chars_format::hex, 10, errc{}, 1.62500036f},	// 0x1.a00006p0f}, // exact
		{"1.a0000601", chars_format::hex, 10, errc{}, 1.62500036f},	// 0x1.a00006p0f}, // below midpoint, round down
		{"1.a0000700", chars_format::hex, 10, errc{}, 1.62500048f},	// 0x1.a00008p0f}, // midpoint, round up to even
		{"1.a0000701", chars_format::hex, 10, errc{}, 1.62500048f},	// 0x1.a00008p0f}, // above midpoint, round up

		{"1.0000040", chars_format::hex, 9, errc{}, 1.00000024f},	// 0x1.000004p0f}, // exact
		{"1.0000041", chars_format::hex, 9, errc{}, 1.00000024f},	// 0x1.000004p0f}, // below midpoint, round down
		{"1.0000050", chars_format::hex, 9, errc{}, 1.00000024f},	// 0x1.000004p0f}, // midpoint, round down to even
		{"1.0000051", chars_format::hex, 9, errc{}, 1.00000036f},	// 0x1.000006p0f}, // above midpoint, round up
		{"1.0000060", chars_format::hex, 9, errc{}, 1.00000036f},	// 0x1.000006p0f}, // exact
		{"1.0000061", chars_format::hex, 9, errc{}, 1.00000036f},	// 0x1.000006p0f}, // below midpoint, round down
		{"1.0000070", chars_format::hex, 9, errc{}, 1.00000048f},	// 0x1.000008p0f}, // midpoint, round up to even
		{"1.0000071", chars_format::hex, 9, errc{}, 1.00000048f},	// 0x1.000008p0f}, // above midpoint, round up

		{"1.0000002384185791015625000000", chars_format::general, 30, errc{}, 1.00000024f},	// 0x1.000004p0f}, // exact
		{"1.0000002421438694000244140625", chars_format::general, 30, errc{}, 1.00000024f},	// 0x1.000004p0f}, // below midpoint, round down
		{"1.0000002980232238769531249999", chars_format::general, 30, errc{}, 1.00000024f},	// 0x1.000004p0f}, // below midpoint, round down
		{"1.0000002980232238769531250000", chars_format::general, 30, errc{}, 1.00000024f},	// 0x1.000004p0f}, // midpoint, round down to even
		{"1.0000002980232238769531250001", chars_format::general, 30, errc{}, 1.00000036f},	// 0x1.000006p0f}, // above midpoint, round up
		{"1.0000003017485141754150390625", chars_format::general, 30, errc{}, 1.00000036f},	// 0x1.000006p0f}, // above midpoint, round up
		{"1.0000003576278686523437500000", chars_format::general, 30, errc{}, 1.00000036f},	// 0x1.000006p0f}, // exact
		{"1.0000003613531589508056640625", chars_format::general, 30, errc{}, 1.00000036f},	// 0x1.000006p0f}, // below midpoint, round down
		{"1.0000004172325134277343749999", chars_format::general, 30, errc{}, 1.00000036f},	// 0x1.000006p0f}, // below midpoint, round down
		{"1.0000004172325134277343750000", chars_format::general, 30, errc{}, 1.00000048f},	// 0x1.000008p0f}, // midpoint, round up to even
		{"1.0000004172325134277343750001", chars_format::general, 30, errc{}, 1.00000048f},	// 0x1.000008p0f}, // above midpoint, round up
		{"1.0000004209578037261962890625", chars_format::general, 30, errc{}, 1.00000048f},	// 0x1.000008p0f}, // above midpoint, round up

		// VSO-838635 "<charconv>: from_chars() mishandles certain subnormals"
		// This bug didn't actually affect float, but we should have similar test cases.
		// These values change on half-ulp boundaries:
		// 1 * 2^-150 ~= 7.01e-46 (half-ulp between zero and min subnormal)
		// 2 * 2^-150 ~= 1.40e-45 (min subnormal)
		// 3 * 2^-150 ~= 2.10e-45 (half-ulp between min subnormal and next subnormal)
		// 4 * 2^-150 ~= 2.80e-45 (next subnormal)
		{"6."
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
			chars_format::scientific, 1006, errc::result_out_of_range, 0.0f},
		{"7."
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
			chars_format::scientific, 1006, errc{}, 1.401e-45f},	// 0x0.000002p-126f},
		{"8."
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
			chars_format::scientific, 1006, errc{}, 1.401e-45f},	// 0x0.000002p-126f},
		{"9."
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
			chars_format::scientific, 1006, errc{}, 1.401e-45f},	// 0x0.000002p-126f},
		{"1."
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
			chars_format::scientific, 1006, errc{}, 1.401e-45f},	// 0x0.000002p-126f},
		{"2."
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
			chars_format::scientific, 1006, errc{}, 2.803e-45f},	// 0x0.000004p-126f},

		// VSO-733765 "<charconv>: [Feedback] double std::from_chars behavior on exponent out of range"
		// LWG-3081 "Floating point from_chars API does not distinguish between overflow and underflow"
		// These test cases exercise every overflow/underflow codepath.
		{"1e+1000", chars_format::scientific, 7, errc::result_out_of_range, infinity},
		{"1e-1000", chars_format::scientific, 7, errc::result_out_of_range, 0.0f},
		{"1.ffffffp+127", chars_format::hex, 13, errc::result_out_of_range, infinity},
		{"1e+2000", chars_format::scientific, 7, errc::result_out_of_range, infinity},
		{"1e-2000", chars_format::scientific, 7, errc::result_out_of_range, 0.0f},
		{"1e+9999", chars_format::scientific, 7, errc::result_out_of_range, infinity},
		{"1e-9999", chars_format::scientific, 7, errc::result_out_of_range, 0.0f},
		{"10e+5199", chars_format::scientific, 8, errc::result_out_of_range, infinity},
		{"0.001e-5199", chars_format::scientific, 11, errc::result_out_of_range, 0.0f},
	};

	for (auto const& x : data)
	{
		VERIFY(test(x.input, x.fmt, x.expected_idx, x.expected_ec, x.expected_value));
	}

	{
		const char* s = "7.411412e-39U";
		const char* last = s + hamon::strlen(s) - 1;

		float value = 0.25;
		hamon::from_chars_result result = hamon::from_chars(s, last, value);

		VERIFY(result.ec == hamon::errc{});
		VERIFY(result.ptr == last);
		VERIFY(value == 7.411412e-39F);
	}

	return true;
}

inline /*HAMON_CXX14_CONSTEXPR*/ bool double_test()
{
	double const infinity = hamon::numeric_limits<double>::infinity();

	using hamon::chars_format;
	using hamon::errc;

	struct test_data
	{
		const char* input;
		chars_format fmt;
		hamon::size_t expected_idx;
		errc expected_ec;
		double expected_value;
	};

	const test_data data[] =
	{
		{"1.7976931348623157e+308", chars_format::scientific, 23, errc{}, hamon::numeric_limits<double>::max()},
		{"2.2250738585072014e-308", chars_format::scientific, 23, errc{}, hamon::numeric_limits<double>::min()},
		{"-1.7976931348623157e+308", chars_format::scientific, 24, errc{}, hamon::numeric_limits<double>::lowest()},
		{"4.940656458412e-324", chars_format::scientific, 19, errc{}, hamon::numeric_limits<double>::denorm_min()},

		{"1.000000000000a000", chars_format::hex, 18, errc{}, 1.0000000000000022},	// 0x1.000000000000ap0}, // exact
		{"1.000000000000a001", chars_format::hex, 18, errc{}, 1.0000000000000022},	// 0x1.000000000000ap0}, // below midpoint, round down
		{"1.000000000000a800", chars_format::hex, 18, errc{}, 1.0000000000000022},	// 0x1.000000000000ap0}, // midpoint, round down to even
		{"1.000000000000a801", chars_format::hex, 18, errc{}, 1.0000000000000024},	// 0x1.000000000000bp0}, // above midpoint, round up
		{"1.000000000000b000", chars_format::hex, 18, errc{}, 1.0000000000000024},	// 0x1.000000000000bp0}, // exact
		{"1.000000000000b001", chars_format::hex, 18, errc{}, 1.0000000000000024},	// 0x1.000000000000bp0}, // below midpoint, round down
		{"1.000000000000b800", chars_format::hex, 18, errc{}, 1.0000000000000027},	// 0x1.000000000000cp0}, // midpoint, round up to even
		{"1.000000000000b801", chars_format::hex, 18, errc{}, 1.0000000000000027},	// 0x1.000000000000cp0}, // above midpoint, round up

		{"1.00000000000020", chars_format::hex, 16, errc{}, 1.0000000000000004},	// 0x1.0000000000002p0}, // exact
		{"1.00000000000021", chars_format::hex, 16, errc{}, 1.0000000000000004},	// 0x1.0000000000002p0}, // below midpoint, round down
		{"1.00000000000028", chars_format::hex, 16, errc{}, 1.0000000000000004},	// 0x1.0000000000002p0}, // midpoint, round down to even
		{"1.00000000000029", chars_format::hex, 16, errc{}, 1.0000000000000007},	// 0x1.0000000000003p0}, // above midpoint, round up
		{"1.00000000000030", chars_format::hex, 16, errc{}, 1.0000000000000007},	// 0x1.0000000000003p0}, // exact
		{"1.00000000000031", chars_format::hex, 16, errc{}, 1.0000000000000007},	// 0x1.0000000000003p0}, // below midpoint, round down
		{"1.00000000000038", chars_format::hex, 16, errc{}, 1.0000000000000009},	// 0x1.0000000000004p0}, // midpoint, round up to even
		{"1.00000000000039", chars_format::hex, 16, errc{}, 1.0000000000000009},	// 0x1.0000000000004p0}, // above midpoint, round up

		{"1.00000000000000044408920985006261616945266723632812500000", chars_format::general, 58, errc{}, 1.0000000000000004},	// 0x1.0000000000002p0}, // exact
		{"1.00000000000000045796699765787707292474806308746337890625", chars_format::general, 58, errc{}, 1.0000000000000004},	// 0x1.0000000000002p0}, // below midpoint, round down
		{"1.00000000000000055511151231257827021181583404541015624999", chars_format::general, 58, errc{}, 1.0000000000000004},	// 0x1.0000000000002p0}, // below midpoint, round down
		{"1.00000000000000055511151231257827021181583404541015625000", chars_format::general, 58, errc{}, 1.0000000000000004},	// 0x1.0000000000002p0}, // midpoint, round down to even
		{"1.00000000000000055511151231257827021181583404541015625001", chars_format::general, 58, errc{}, 1.0000000000000007},	// 0x1.0000000000003p0}, // above midpoint, round up
		{"1.00000000000000056898930012039272696711122989654541015625", chars_format::general, 58, errc{}, 1.0000000000000007},	// 0x1.0000000000003p0}, // above midpoint, round up
		{"1.00000000000000066613381477509392425417900085449218750000", chars_format::general, 58, errc{}, 1.0000000000000007},	// 0x1.0000000000003p0}, // exact
		{"1.00000000000000068001160258290838100947439670562744140625", chars_format::general, 58, errc{}, 1.0000000000000007},	// 0x1.0000000000003p0}, // below midpoint, round down
		{"1.00000000000000077715611723760957829654216766357421874999", chars_format::general, 58, errc{}, 1.0000000000000007},	// 0x1.0000000000003p0}, // below midpoint, round down
		{"1.00000000000000077715611723760957829654216766357421875000", chars_format::general, 58, errc{}, 1.0000000000000009},	// 0x1.0000000000004p0}, // midpoint, round up to even
		{"1.00000000000000077715611723760957829654216766357421875001", chars_format::general, 58, errc{}, 1.0000000000000009},	// 0x1.0000000000004p0}, // above midpoint, round up
		{"1.00000000000000079103390504542403505183756351470947265625", chars_format::general, 58, errc{}, 1.0000000000000009},	// 0x1.0000000000004p0}, // above midpoint, round up

		// https://www.exploringbinary.com/nondeterministic-floating-point-conversions-in-java/
		{"0.0000008p-1022", chars_format::hex, 15, errc{}, 6.631236846766e-316},	// 0x0.0000008p-1022},

		// VSO-838635 "<charconv>: from_chars() mishandles certain subnormals"
		// These values change on half-ulp boundaries:
		// 1 * 2^-1075 ~= 2.47e-324 (half-ulp between zero and min subnormal)
		// 2 * 2^-1075 ~= 4.94e-324 (min subnormal)
		// 3 * 2^-1075 ~= 7.41e-324 (half-ulp between min subnormal and next subnormal)
		// 4 * 2^-1075 ~= 9.88e-324 (next subnormal)
		{"1."
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
			chars_format::scientific, 1007, errc::result_out_of_range, 0.0},
		{"2."
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
			chars_format::scientific, 1007, errc::result_out_of_range, 0.0},
		{"3."
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
			chars_format::scientific, 1007, errc{}, 4.940656458412e-324},	// 0x0.0000000000001p-1022},
		{"4."
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
			chars_format::scientific, 1007, errc{}, 4.940656458412e-324},	// 0x0.0000000000001p-1022},
		{"5."
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
			chars_format::scientific, 1007, errc{}, 4.940656458412e-324},	// 0x0.0000000000001p-1022},
		{"6."
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
			chars_format::scientific, 1007, errc{}, 4.940656458412e-324},	// 0x0.0000000000001p-1022},
		{"7."
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
			chars_format::scientific, 1007, errc{}, 9.881312916825e-324},	// 0x0.0000000000002p-1022},
		{"8."
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
			chars_format::scientific, 1007, errc{}, 9.881312916825e-324},	// 0x0.0000000000002p-1022},
		{"9."
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
			chars_format::scientific, 1007, errc{}, 9.881312916825e-324},	// 0x0.0000000000002p-1022},

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
		{"0."
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
			chars_format::fixed, 1080, errc::result_out_of_range, 0.0},

		// (0 + 2^-53) * 2^-1022 exactly
		{"0."
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
			chars_format::fixed, 1077, errc::result_out_of_range, 0.0},

		// (0 + 2^-53) * 2^-1022 exactly, followed by a thousand 0 digits
		{"0."
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
			chars_format::fixed, 2077, errc::result_out_of_range, 0.0},

		// above (0 + 2^-53) * 2^-1022: appended a thousand 0 digits followed by a 1 digit
		{"0."
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
			chars_format::fixed, 2078, errc{}, 4.940656458412e-324},	// 0x0.0000000000001p-1022},

		// above (0 + 2^-53) * 2^-1022: appended a 1 digit
		{"0."
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
			chars_format::fixed, 1078, errc{}, 4.940656458412e-324},	// 0x0.0000000000001p-1022},

		// above (0 + 2^-53) * 2^-1022: incremented last digit
		{"0."
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
			chars_format::fixed, 1077, errc{}, 4.940656458412e-324},	// 0x0.0000000000001p-1022},

		// just below (0 + 1 - 3 * 2^-53) * 2^-1022: decremented last digit, then appended three 9 digits
		{"0."
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
			 chars_format::fixed, 1080, errc{}, 2.225073858507200395e-308},	// 0x0.ffffffffffffep-1022},

		// (0 + 1 - 3 * 2^-53) * 2^-1022 exactly
		{"0."
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
			chars_format::fixed, 1077, errc{}, 2.225073858507200395e-308},	// 0x0.ffffffffffffep-1022},

		// (0 + 1 - 3 * 2^-53) * 2^-1022 exactly, followed by a thousand 0 digits
		{"0."
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
			chars_format::fixed, 2077, errc{}, 2.225073858507200395e-308},	// 0x0.ffffffffffffep-1022},

		// above (0 + 1 - 3 * 2^-53) * 2^-1022: appended a thousand 0 digits followed by a 1 digit
		{"0."
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
			 chars_format::fixed, 2078, errc{}, 2.225073858507200889e-308},	// 0x0.fffffffffffffp-1022},

		// above (0 + 1 - 3 * 2^-53) * 2^-1022: appended a 1 digit
		{"0."
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
			chars_format::fixed, 1078, errc{}, 2.225073858507200889e-308},	// 0x0.fffffffffffffp-1022},

		// above (0 + 1 - 3 * 2^-53) * 2^-1022: incremented last digit
		{"0."
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
			chars_format::fixed, 1077, errc{}, 2.225073858507200889e-308},	// 0x0.fffffffffffffp-1022},

		// just below (1 + 2^-53) * 2^-1022: decremented last digit, then appended three 9 digits
		{"0."
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
			chars_format::fixed, 1080, errc{}, 2.225073858507201383e-308},	// 0x1.0000000000000p-1022},

		// (1 + 2^-53) * 2^-1022 exactly
		{"0."
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
			chars_format::fixed, 1077, errc{}, 2.225073858507201383e-308},	// 0x1.0000000000000p-1022},

		// (1 + 2^-53) * 2^-1022 exactly, followed by a thousand 0 digits
		{"0."
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
			chars_format::fixed, 2077, errc{}, 2.225073858507201383e-308},	// 0x1.0000000000000p-1022},

		// above (1 + 2^-53) * 2^-1022: appended a thousand 0 digits followed by a 1 digit
		{"0."
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
			chars_format::fixed, 2078, errc{}, 2.225073858507201877e-308},	// 0x1.0000000000001p-1022},

		// above (1 + 2^-53) * 2^-1022: appended a 1 digit
		{"0."
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
			chars_format::fixed, 1078, errc{}, 2.225073858507201877e-308},	// 0x1.0000000000001p-1022},

		// above (1 + 2^-53) * 2^-1022: incremented last digit
		{"0."
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
			chars_format::fixed, 1077, errc{}, 2.225073858507201877e-308},	// 0x1.0000000000001p-1022},

		// just below (1 + 1 - 3 * 2^-53) * 2^-1022: decremented last digit, then appended three 9 digits
		{"0."
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
			 chars_format::fixed, 1080, errc{}, 4.450147717014401778e-308},	// 0x1.ffffffffffffep-1022},

		// (1 + 1 - 3 * 2^-53) * 2^-1022 exactly
		{"0."
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
			chars_format::fixed, 1077, errc{}, 4.450147717014401778e-308},	// 0x1.ffffffffffffep-1022},

		// (1 + 1 - 3 * 2^-53) * 2^-1022 exactly, followed by a thousand 0 digits
		{"0."
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
			chars_format::fixed, 2077, errc{}, 4.450147717014401778e-308},	// 0x1.ffffffffffffep-1022},

		// above (1 + 1 - 3 * 2^-53) * 2^-1022: appended a thousand 0 digits followed by a 1 digit
		{"0."
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
			chars_format::fixed, 2078, errc{}, 4.450147717014402272e-308},	// 0x1.fffffffffffffp-1022},

		// above (1 + 1 - 3 * 2^-53) * 2^-1022: appended a 1 digit
		{"0."
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
			chars_format::fixed, 1078, errc{}, 4.450147717014402272e-308},	// 0x1.fffffffffffffp-1022},

		// above (1 + 1 - 3 * 2^-53) * 2^-1022: incremented last digit
		{"0."
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
			chars_format::fixed, 1077, errc{}, 4.450147717014402272e-308},	// 0x1.fffffffffffffp-1022},

		// just below (1 + 2^-53) * 2^-33: decremented last digit, then appended three 9 digits
		{"0.00000000011641532182693482737782207114105741986576081359316958696581423282623291015624999",
			 chars_format::fixed, 91, errc{}, 1.164153218269348145e-10},	// 0x1.0000000000000p-33},

		// (1 + 2^-53) * 2^-33 exactly
		{"0.00000000011641532182693482737782207114105741986576081359316958696581423282623291015625",
			 chars_format::fixed, 88, errc{}, 1.164153218269348145e-10},	// 0x1.0000000000000p-33},

		// (1 + 2^-53) * 2^-33 exactly, followed by a thousand 0 digits
		{"0."
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
			chars_format::fixed, 1088, errc{}, 1.164153218269348145e-10},	// 0x1.0000000000000p-33},

		// above (1 + 2^-53) * 2^-33: appended a thousand 0 digits followed by a 1 digit
		{"0."
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
			 chars_format::fixed, 1089, errc{}, 1.164153218269348403e-10},	// 0x1.0000000000001p-33},

		// above (1 + 2^-53) * 2^-33: appended a 1 digit
		{"0.000000000116415321826934827377822071141057419865760813593169586965814232826232910156251",
			chars_format::fixed, 89, errc{}, 1.164153218269348403e-10},	// 0x1.0000000000001p-33},

		// above (1 + 2^-53) * 2^-33: incremented last digit
		{"0.00000000011641532182693482737782207114105741986576081359316958696581423282623291015626",
			chars_format::fixed, 88, errc{}, 1.164153218269348403e-10},	// 0x1.0000000000001p-33},

		// just below (1 + 1 - 3 * 2^-53) * 2^-33: decremented last digit, then appended three 9 digits
		{"0.00000000023283064365386959013215878657682774040271755922049123910255730152130126953124999",
			chars_format::fixed, 91, errc{}, 2.328306436538695772e-10},	// 0x1.ffffffffffffep-33},

		// (1 + 1 - 3 * 2^-53) * 2^-33 exactly
		{"0.00000000023283064365386959013215878657682774040271755922049123910255730152130126953125",
			chars_format::fixed, 88, errc{}, 2.328306436538695772e-10},	// 0x1.ffffffffffffep-33},

		// (1 + 1 - 3 * 2^-53) * 2^-33 exactly, followed by a thousand 0 digits
		{"0."
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
			chars_format::fixed, 1088, errc{}, 2.328306436538695772e-10},	// 0x1.ffffffffffffep-33},

		// above (1 + 1 - 3 * 2^-53) * 2^-33: appended a thousand 0 digits followed by a 1 digit
		{"0."
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
			 chars_format::fixed, 1089, errc{}, 2.328306436538696031e-10},	// 0x1.fffffffffffffp-33},

		// above (1 + 1 - 3 * 2^-53) * 2^-33: appended a 1 digit
		{"0.000000000232830643653869590132158786576827740402717559220491239102557301521301269531251",
			 chars_format::fixed, 89, errc{}, 2.328306436538696031e-10},	// 0x1.fffffffffffffp-33},

		// above (1 + 1 - 3 * 2^-53) * 2^-33: incremented last digit
		{"0.00000000023283064365386959013215878657682774040271755922049123910255730152130126953126",
			chars_format::fixed, 88, errc{}, 2.328306436538696031e-10},	// 0x1.fffffffffffffp-33},

		// just below (1 + 2^-53) * 2^0: decremented last digit, then appended three 9 digits
		{"1.00000000000000011102230246251565404236316680908203124999", chars_format::fixed, 58, errc{}, 1.0},

		// (1 + 2^-53) * 2^0 exactly
		{"1.00000000000000011102230246251565404236316680908203125", chars_format::fixed, 55, errc{}, 1.0},

		// (1 + 2^-53) * 2^0 exactly, followed by a thousand 0 digits
		{"1."
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
			chars_format::fixed, 1055, errc{}, 1.0},

		// above (1 + 2^-53) * 2^0: appended a thousand 0 digits followed by a 1 digit
		{"1."
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
			chars_format::fixed, 1056, errc{}, 1.000000000000000222},	// 0x1.0000000000001p+0},

		// above (1 + 2^-53) * 2^0: appended a 1 digit
		{"1.000000000000000111022302462515654042363166809082031251", chars_format::fixed, 56, errc{}, 1.000000000000000222},	// 0x1.0000000000001p+0},

		// above (1 + 2^-53) * 2^0: incremented last digit
		{"1.00000000000000011102230246251565404236316680908203126", chars_format::fixed, 55, errc{}, 1.000000000000000222},	// 0x1.0000000000001p+0},

		// just below (1 + 1 - 3 * 2^-53) * 2^0: decremented last digit, then appended three 9 digits
		{"1.99999999999999966693309261245303787291049957275390624999", chars_format::fixed, 58, errc{}, 1.999999999999999556},	// 0x1.ffffffffffffep+0},

		// (1 + 1 - 3 * 2^-53) * 2^0 exactly
		{"1.99999999999999966693309261245303787291049957275390625", chars_format::fixed, 55, errc{}, 1.999999999999999556},	// 0x1.ffffffffffffep+0},

		// (1 + 1 - 3 * 2^-53) * 2^0 exactly, followed by a thousand 0 digits
		{"1."
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
			chars_format::fixed, 1055, errc{}, 1.999999999999999556},	// 0x1.ffffffffffffep+0},

		// above (1 + 1 - 3 * 2^-53) * 2^0: appended a thousand 0 digits followed by a 1 digit
		{"1."
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
			 chars_format::fixed, 1056, errc{}, 1.999999999999999778},	// 0x1.fffffffffffffp+0},

		// above (1 + 1 - 3 * 2^-53) * 2^0: appended a 1 digit
		{"1.999999999999999666933092612453037872910499572753906251", chars_format::fixed, 56, errc{}, 1.999999999999999778},	// 0x1.fffffffffffffp+0},

		// above (1 + 1 - 3 * 2^-53) * 2^0: incremented last digit
		{"1.99999999999999966693309261245303787291049957275390626", chars_format::fixed, 55, errc{}, 1.999999999999999778},	// 0x1.fffffffffffffp+0},

		// just below (1 + 2^-53) * 2^33: decremented last digit, then appended three 9 digits
		{"8589934592.00000095367431640624999", chars_format::fixed, 34, errc{}, 8589934592.0},	// 0x1.0000000000000p+33},

		// (1 + 2^-53) * 2^33 exactly
		{"8589934592.00000095367431640625", chars_format::fixed, 31, errc{}, 8589934592.0},	// 0x1.0000000000000p+33},

		// (1 + 2^-53) * 2^33 exactly, followed by a thousand 0 digits
		{"8589934592."
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
			chars_format::fixed, 1031, errc{}, 8589934592.0},	// 0x1.0000000000000p+33},

		// above (1 + 2^-53) * 2^33: appended a thousand 0 digits followed by a 1 digit
		{"8589934592."
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
			chars_format::fixed, 1032, errc{}, 8589934592.000001907},	// 0x1.0000000000001p+33},

		// above (1 + 2^-53) * 2^33: appended a 1 digit
		{"8589934592.000000953674316406251", chars_format::fixed, 32, errc{}, 8589934592.000001907},	// 0x1.0000000000001p+33},

		// above (1 + 2^-53) * 2^33: incremented last digit
		{"8589934592.00000095367431640626", chars_format::fixed, 31, errc{}, 8589934592.000001907},	// 0x1.0000000000001p+33},

		// just below (1 + 1 - 3 * 2^-53) * 2^33: decremented last digit, then appended three 9 digits
		{"17179869183.99999713897705078124999", chars_format::fixed, 35, errc{}, 17179869183.99999619},	// 0x1.ffffffffffffep+33},

		// (1 + 1 - 3 * 2^-53) * 2^33 exactly
		{"17179869183.99999713897705078125", chars_format::fixed, 32, errc{}, 17179869183.99999619},	// 0x1.ffffffffffffep+33},

		// (1 + 1 - 3 * 2^-53) * 2^33 exactly, followed by a thousand 0 digits
		{"17179869183."
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
			chars_format::fixed, 1032, errc{}, 17179869183.99999619},	// 0x1.ffffffffffffep+33},

		// above (1 + 1 - 3 * 2^-53) * 2^33: appended a thousand 0 digits followed by a 1 digit
		{"17179869183."
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
			 chars_format::fixed, 1033, errc{}, 17179869183.99999809},	// 0x1.fffffffffffffp+33},

		// above (1 + 1 - 3 * 2^-53) * 2^33: appended a 1 digit
		{"17179869183.999997138977050781251", chars_format::fixed, 33, errc{}, 17179869183.99999809},	// 0x1.fffffffffffffp+33},

		// above (1 + 1 - 3 * 2^-53) * 2^33: incremented last digit
		{"17179869183.99999713897705078126", chars_format::fixed, 32, errc{}, 17179869183.99999809},	// 0x1.fffffffffffffp+33},

		// just below (1 + 2^-53) * 2^77: decremented last digit, then appended three 9 digits
		{"151115727451828663615487.999", chars_format::fixed, 28, errc{}, 1.511157274518286468e+23},	// 0x1.0000000000000p+77},

		// (1 + 2^-53) * 2^77 exactly
		{"151115727451828663615488", chars_format::fixed, 24, errc{}, 1.511157274518286468e+23},	// 0x1.0000000000000p+77},

		// (1 + 2^-53) * 2^77 exactly, followed by a thousand 0 digits
		{"151115727451828663615488."
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
			chars_format::fixed, 1025, errc{}, 1.511157274518286468e+23},	// 0x1.0000000000000p+77},

		// above (1 + 2^-53) * 2^77: appended a thousand 0 digits followed by a 1 digit
		{"151115727451828663615488."
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
			chars_format::fixed, 1026, errc{}, 1.511157274518286804e+23},	// 0x1.0000000000001p+77},

		// above (1 + 2^-53) * 2^77: appended a 1 digit
		{"151115727451828663615488.1", chars_format::fixed, 26, errc{}, 1.511157274518286804e+23},	// 0x1.0000000000001p+77},

		// above (1 + 2^-53) * 2^77: incremented last digit
		{"151115727451828663615489", chars_format::fixed, 24, errc{}, 1.511157274518286804e+23},	// 0x1.0000000000001p+77},

		// just below (1 + 1 - 3 * 2^-53) * 2^77: decremented last digit, then appended three 9 digits
		{"302231454903657243344895.999", chars_format::fixed, 28, errc{}, 3.022314549036572266e+23},	// 0x1.ffffffffffffep+77},

		// (1 + 1 - 3 * 2^-53) * 2^77 exactly
		{"302231454903657243344896", chars_format::fixed, 24, errc{}, 3.022314549036572266e+23},	// 0x1.ffffffffffffep+77},

		// (1 + 1 - 3 * 2^-53) * 2^77 exactly, followed by a thousand 0 digits
		{"302231454903657243344896."
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
			chars_format::fixed, 1025, errc{}, 3.022314549036572266e+23},	// 0x1.ffffffffffffep+77},

		// above (1 + 1 - 3 * 2^-53) * 2^77: appended a thousand 0 digits followed by a 1 digit
		{"302231454903657243344896."
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
			chars_format::fixed, 1026, errc{}, 3.022314549036572601e+23},	// 0x1.fffffffffffffp+77},

		// above (1 + 1 - 3 * 2^-53) * 2^77: appended a 1 digit
		{"302231454903657243344896.1", chars_format::fixed, 26, errc{}, 3.022314549036572601e+23},	// 0x1.fffffffffffffp+77},

		// above (1 + 1 - 3 * 2^-53) * 2^77: incremented last digit
		{"302231454903657243344897", chars_format::fixed, 24, errc{}, 3.022314549036572601e+23},	// 0x1.fffffffffffffp+77},

		// just below (1 + 2^-53) * 2^1023: decremented last digit, then appended three 9 digits
		{"8988465674311580536566680721305029496276241413130815897397134275615404541548669375241369800602409693534988440"
		 "3114202125541629105369684531108613657287705365884742938136589844238179474556051429647415148697857438797685859"
		 "063890851407391008830874765563025951597582513936655578157348020066364210154316532161708031.999",
			 chars_format::fixed, 312, errc{}, 8.988465674311579539e+307},	// 0x1.0000000000000p+1023},

		// (1 + 2^-53) * 2^1023 exactly
		{"8988465674311580536566680721305029496276241413130815897397134275615404541548669375241369800602409693534988440"
		 "3114202125541629105369684531108613657287705365884742938136589844238179474556051429647415148697857438797685859"
		 "063890851407391008830874765563025951597582513936655578157348020066364210154316532161708032",
			chars_format::fixed, 308, errc{}, 8.988465674311579539e+307},	// 0x1.0000000000000p+1023},

		// (1 + 2^-53) * 2^1023 exactly, followed by a thousand 0 digits
		{"8988465674311580536566680721305029496276241413130815897397134275615404541548669375241369800602409693534988440"
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
			chars_format::fixed, 1309, errc{}, 8.988465674311579539e+307},	// 0x1.0000000000000p+1023},

		// above (1 + 2^-53) * 2^1023: appended a thousand 0 digits followed by a 1 digit
		{"8988465674311580536566680721305029496276241413130815897397134275615404541548669375241369800602409693534988440"
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
			chars_format::fixed, 1310, errc{}, 8.988465674311581534e+307},	// 0x1.0000000000001p+1023},

		// above (1 + 2^-53) * 2^1023: appended a 1 digit
		{"8988465674311580536566680721305029496276241413130815897397134275615404541548669375241369800602409693534988440"
		 "3114202125541629105369684531108613657287705365884742938136589844238179474556051429647415148697857438797685859"
		 "063890851407391008830874765563025951597582513936655578157348020066364210154316532161708032.1",
			chars_format::fixed, 310, errc{}, 8.988465674311581534e+307},	// 0x1.0000000000001p+1023},

		// above (1 + 2^-53) * 2^1023: incremented last digit
		{"8988465674311580536566680721305029496276241413130815897397134275615404541548669375241369800602409693534988440"
		 "3114202125541629105369684531108613657287705365884742938136589844238179474556051429647415148697857438797685859"
		 "063890851407391008830874765563025951597582513936655578157348020066364210154316532161708033",
			chars_format::fixed, 308, errc{}, 8.988465674311581534e+307},	// 0x1.0000000000001p+1023},

		// just below (1 + 1 - 3 * 2^-53) * 2^1023: decremented last digit, then appended three 9 digits
		{"1797693134862315608353258760581052985162070023416521662616611746258695532672923265745300992879465492467506314"
		 "9033587701752208710592698796290627760473556921329019091915239418047621712533496094635638726128664019802903779"
		 "9514183602981511756283727771403830521483963923935633133642802139091669457927874464075218943.999",
			chars_format::fixed, 313, errc{}, 1.797693134862315509e+308},	// 0x1.ffffffffffffep+1023},

		// (1 + 1 - 3 * 2^-53) * 2^1023 exactly
		{"1797693134862315608353258760581052985162070023416521662616611746258695532672923265745300992879465492467506314"
		 "9033587701752208710592698796290627760473556921329019091915239418047621712533496094635638726128664019802903779"
		 "9514183602981511756283727771403830521483963923935633133642802139091669457927874464075218944",
			chars_format::fixed, 309, errc{}, 1.797693134862315509e+308},	// 0x1.ffffffffffffep+1023},

		// (1 + 1 - 3 * 2^-53) * 2^1023 exactly, followed by a thousand 0 digits
		{"1797693134862315608353258760581052985162070023416521662616611746258695532672923265745300992879465492467506314"
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
			chars_format::fixed, 1310, errc{}, 1.797693134862315509e+308},	// 0x1.ffffffffffffep+1023},

		// above (1 + 1 - 3 * 2^-53) * 2^1023: appended a thousand 0 digits followed by a 1 digit
		{"1797693134862315608353258760581052985162070023416521662616611746258695532672923265745300992879465492467506314"
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
			chars_format::fixed, 1311, errc{}, 1.797693134862315708e+308},	// 0x1.fffffffffffffp+1023},

		// above (1 + 1 - 3 * 2^-53) * 2^1023: appended a 1 digit
		{"1797693134862315608353258760581052985162070023416521662616611746258695532672923265745300992879465492467506314"
		 "9033587701752208710592698796290627760473556921329019091915239418047621712533496094635638726128664019802903779"
		 "9514183602981511756283727771403830521483963923935633133642802139091669457927874464075218944.1",
			chars_format::fixed, 311, errc{}, 1.797693134862315708e+308},	// 0x1.fffffffffffffp+1023},

		// above (1 + 1 - 3 * 2^-53) * 2^1023: incremented last digit
		{"1797693134862315608353258760581052985162070023416521662616611746258695532672923265745300992879465492467506314"
		 "9033587701752208710592698796290627760473556921329019091915239418047621712533496094635638726128664019802903779"
		 "9514183602981511756283727771403830521483963923935633133642802139091669457927874464075218945",
			chars_format::fixed, 309, errc{}, 1.797693134862315708e+308},	// 0x1.fffffffffffffp+1023},

		// VSO-852024 also affected hexfloats.
		{"0.00000000000008p-1022", chars_format::hex, 22, errc::result_out_of_range, 0.0},
		{"0."
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
			chars_format::hex, 1023, errc{}, 4.940656458412e-324},	// 0x0.0000000000001p-1022},

		{"0.ffffffffffffe8p-1022", chars_format::hex, 22, errc{}, 2.225073858507200395e-308},	// 0x0.ffffffffffffep-1022},
		{"0."
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
			chars_format::hex, 1023, errc{}, 2.225073858507200889e-308},	// 0x0.fffffffffffffp-1022},

		{"1.00000000000008p+0", chars_format::hex, 19, errc{}, 1.0},
		{"1."
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
			 chars_format::hex, 1020, errc{}, 1.000000000000000222},	// 0x1.0000000000001p+0},

		{"1.ffffffffffffe8p+0", chars_format::hex, 19, errc{}, 1.999999999999999556},	// 0x1.ffffffffffffep+0},
		{"1."
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
			chars_format::hex, 1020, errc{}, 1.999999999999999778},	// 0x1.fffffffffffffp+0},

		{"1.00000000000008p+1023", chars_format::hex, 22, errc{}, 8.988465674311579539e+307},	// 0x1.0000000000000p+1023},
		{"1."
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
			chars_format::hex, 1023, errc{}, 8.988465674311581534e+307},	// 0x1.0000000000001p+1023},

		{"1.ffffffffffffe8p+1023", chars_format::hex, 22, errc{}, 1.797693134862315509e+308},	// 0x1.ffffffffffffep+1023},
		{"1."
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
			chars_format::hex, 1023, errc{}, 1.797693134862315708e+308},	// 0x1.fffffffffffffp+1023},

		// VSO-733765 "<charconv>: [Feedback] double std::from_chars behavior on exponent out of range"
		// LWG-3081 "Floating point from_chars API does not distinguish between overflow and underflow"
		// These test cases exercise every overflow/underflow codepath.
		{"1e+1000", chars_format::scientific, 7, errc::result_out_of_range, infinity},
		{"1e-1000", chars_format::scientific, 7, errc::result_out_of_range, 0.0},
		{"1.fffffffffffff8p+1023", chars_format::hex, 22, errc::result_out_of_range, infinity},
		{"1e+2000", chars_format::scientific, 7, errc::result_out_of_range, infinity},
		{"1e-2000", chars_format::scientific, 7, errc::result_out_of_range, 0.0},
		{"1e+9999", chars_format::scientific, 7, errc::result_out_of_range, infinity},
		{"1e-9999", chars_format::scientific, 7, errc::result_out_of_range, 0.0},
		{"10e+5199", chars_format::scientific, 8, errc::result_out_of_range, infinity},
		{"0.001e-5199", chars_format::scientific, 11, errc::result_out_of_range, 0.0},
	};

	for (auto const& x : data)
	{
		VERIFY(test(x.input, x.fmt, x.expected_idx, x.expected_ec, x.expected_value));
	}

	{
		const char* s = "4.219902180869891e-2788";
		const char* last = s + hamon::strlen(s) - 1;

		// last + 1 contains a digit. When that value is parsed the exponent is
		// e-2788 which returns std::errc::result_out_of_range and the value 0.
		// the proper exponent is e-278, which can be represented by a double.

		double value = 0.25;
		hamon::from_chars_result result = hamon::from_chars(s, last, value);

		VERIFY(result.ec == hamon::errc{});
		VERIFY(result.ptr == last);
		VERIFY(value == 4.219902180869891e-278);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(CharConvTest, FromCharsFloatingPointTest)
{
	EXPECT_TRUE(inf_test<float>(hamon::chars_format::scientific));
	EXPECT_TRUE(inf_test<float>(hamon::chars_format::fixed));
	EXPECT_TRUE(inf_test<float>(hamon::chars_format::hex));
	EXPECT_TRUE(inf_test<float>(hamon::chars_format::general));

	EXPECT_TRUE(inf_test<double>(hamon::chars_format::scientific));
	EXPECT_TRUE(inf_test<double>(hamon::chars_format::fixed));
	EXPECT_TRUE(inf_test<double>(hamon::chars_format::hex));
	EXPECT_TRUE(inf_test<double>(hamon::chars_format::general));

	EXPECT_TRUE(nan_test<float>(hamon::chars_format::scientific));
	EXPECT_TRUE(nan_test<float>(hamon::chars_format::fixed));
	EXPECT_TRUE(nan_test<float>(hamon::chars_format::hex));
	EXPECT_TRUE(nan_test<float>(hamon::chars_format::general));

	EXPECT_TRUE(nan_test<double>(hamon::chars_format::scientific));
	EXPECT_TRUE(nan_test<double>(hamon::chars_format::fixed));
	EXPECT_TRUE(nan_test<double>(hamon::chars_format::hex));
	EXPECT_TRUE(nan_test<double>(hamon::chars_format::general));

	EXPECT_TRUE(invalid_argument_test<float>(hamon::chars_format::scientific));
	EXPECT_TRUE(invalid_argument_test<float>(hamon::chars_format::fixed));
	EXPECT_TRUE(invalid_argument_test<float>(hamon::chars_format::hex));
	EXPECT_TRUE(invalid_argument_test<float>(hamon::chars_format::general));

	EXPECT_TRUE(invalid_argument_test<double>(hamon::chars_format::scientific));
	EXPECT_TRUE(invalid_argument_test<double>(hamon::chars_format::fixed));
	EXPECT_TRUE(invalid_argument_test<double>(hamon::chars_format::hex));
	EXPECT_TRUE(invalid_argument_test<double>(hamon::chars_format::general));

	EXPECT_TRUE(fixed_test<float>());
	EXPECT_TRUE(fixed_test<double>());

	EXPECT_TRUE(scientific_test<float>());
	EXPECT_TRUE(scientific_test<double>());

	EXPECT_TRUE(general_test<float>());
	EXPECT_TRUE(general_test<double>());

	EXPECT_TRUE(hex_test<float>());
	EXPECT_TRUE(hex_test<double>());

	EXPECT_TRUE(float_test());
	EXPECT_TRUE(double_test());
}

}	// namespace from_chars_floating_point_test

}	// namespace hamon_charconv_test
