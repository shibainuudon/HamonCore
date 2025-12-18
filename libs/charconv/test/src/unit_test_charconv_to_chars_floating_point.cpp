/**
 *	@file	unit_test_charconv_to_chars_floating_point.cpp
 *
 *	@brief	to_chars のテスト
 *
 *	to_chars_result to_chars(char* first, char* last, floating-point-type value);
 */

#include <hamon/charconv/to_chars.hpp>
#include <hamon/cmath/nan.hpp>
#include <hamon/string_view.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_charconv_test
{

namespace to_chars_floating_point_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
test(T val, const char* expected)
{
	char buf[128]{};
	auto ret = hamon::to_chars(buf, buf+sizeof(buf), val);
	//if (hamon::string_view(buf, ret.ptr) != expected)
	//{
	//	std::cout << "!!!  actual: \"" << hamon::string_view(buf, ret.ptr) << "\", expected: \"" << expected << "\"" << std::endl;
	//}
	VERIFY(hamon::string_view(buf, ret.ptr) == expected);
	VERIFY(ret.ec == hamon::errc{});

	return true;
}

inline /*HAMON_CXX14_CONSTEXPR*/ bool float_test()
{
	float const infinity = hamon::numeric_limits<float>::infinity();
	float const quiet_NaN = hamon::numeric_limits<float>::quiet_NaN();
	float const signaling_NaN = hamon::numeric_limits<float>::signaling_NaN();

	struct test_data
	{
		float val;
		const char* expected;
	};

	const test_data data[] =
	{
		{ 0.0f, "0"},
		{-0.0f, "-0"},
		{ infinity, "inf"},
		{-infinity, "-inf"},
#if !defined(HAMON_USE_STD_CHARCONV)
		{ quiet_NaN, "nan"},
		{-quiet_NaN, "-nan"},
		{ signaling_NaN, "nan(snan)"},
		{-signaling_NaN, "-nan(snan)"},
#elif defined(HAMON_MSVC)
		{ quiet_NaN, "nan"},
		{-quiet_NaN, "-nan(ind)"},
		{ signaling_NaN, "nan"},
		{-signaling_NaN, "-nan"},
#else
		{ quiet_NaN, "nan"},
		{-quiet_NaN, "-nan"},
		{ signaling_NaN, "nan"},
		{-signaling_NaN, "-nan"},
#endif
		{ 2.018f, "2.018"},
		{-2.018f, "-2.018"},
		{1e-6f, "1e-06"},
		{1e-5f, "1e-05"},
		{1e-4f, "1e-04"},
		{1e-3f, "0.001"},
		{1e-2f, "0.01"},
		{1e-1f, "0.1"},
		{1e0f, "1"},
		{1e1f, "10"},
		{1e2f, "100"},
		{1e3f, "1000"},
		{1e4f, "10000"},
		{1e5f, "1e+05"},
		{1e6f, "1e+06"},
		{1e7f, "1e+07"},
		{1.234e-6f, "1.234e-06"},
		{1.234e-5f, "1.234e-05"},
		{1.234e-4f, "0.0001234"},
		{1.234e-3f, "0.001234"},
		{1.234e-2f, "0.01234"},
		{1.234e-1f, "0.1234"},
		{1.234e0f, "1.234"},
		{1.234e1f, "12.34"},
		{1.234e2f, "123.4"},
		{1.234e3f, "1234"},
		{1.234e4f, "12340"},
		{1.234e5f, "123400"},
		{1.234e6f, "1234000"},
		{1.234e7f, "12340000"},
		{1.234e8f, "123400000"},
		{1.234e9f, "1.234e+09"},
		{1.234e10f, "1.234e+10"},
	};

	for (auto const& x : data)
	{
		VERIFY(test(x.val, x.expected));
	}

	return true;
}

inline /*HAMON_CXX14_CONSTEXPR*/ bool double_test()
{
	double const infinity = hamon::numeric_limits<double>::infinity();
	double const quiet_NaN = hamon::numeric_limits<double>::quiet_NaN();
	double const signaling_NaN = hamon::numeric_limits<double>::signaling_NaN();

	struct test_data
	{
		double val;
		const char* expected;
	};

	const test_data data[] =
	{
		{ 0.0, "0"},
		{-0.0, "-0"},
		{ infinity, "inf"},
		{-infinity, "-inf"},
#if !defined(HAMON_USE_STD_CHARCONV)
		{ quiet_NaN, "nan"},
		{-quiet_NaN, "-nan"},
		{ signaling_NaN, "nan(snan)"},
		{-signaling_NaN, "-nan(snan)"},
#elif defined(HAMON_MSVC)
		{ quiet_NaN, "nan"},
		{-quiet_NaN, "-nan(ind)"},
		{ signaling_NaN, "nan(snan)"},
		{-signaling_NaN, "-nan(snan)"},
#else
		{ quiet_NaN, "nan"},
		{-quiet_NaN, "-nan"},
		{ signaling_NaN, "nan"},
		{-signaling_NaN, "-nan"},
#endif
		{2.018, "2.018"},
		{-2.018, "-2.018"},
		{1e-6, "1e-06"},
		{1e-5, "1e-05"},
		{1e-4, "1e-04"},
		{1e-3, "0.001"},
		{1e-2, "0.01"},
		{1e-1, "0.1"},
		{1e0, "1"},
		{1e1, "10"},
		{1e2, "100"},
		{1e3, "1000"},
		{1e4, "10000"},
		{1e5, "1e+05"},
		{1e6, "1e+06"},
		{1e7, "1e+07"},
		{1.234e-6, "1.234e-06"},
		{1.234e-5, "1.234e-05"},
		{1.234e-4, "0.0001234"},
		{1.234e-3, "0.001234"},
		{1.234e-2, "0.01234"},
		{1.234e-1, "0.1234"},
		{1.234e0, "1.234"},
		{1.234e1, "12.34"},
		{1.234e2, "123.4"},
		{1.234e3, "1234"},
		{1.234e4, "12340"},
		{1.234e5, "123400"},
		{1.234e6, "1234000"},
		{1.234e7, "12340000"},
		{1.234e8, "123400000"},
		{1.234e9, "1.234e+09"},
		{1.234e10, "1.234e+10"},
	};

	for (auto const& x : data)
	{
		VERIFY(test(x.val, x.expected));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(CharConvTest, ToCharsFloatingPointTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(float_test());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(double_test());

	{
		float const nan_payload = hamon::nanf("1729");

#if !defined(HAMON_USE_STD_CHARCONV)
		EXPECT_TRUE(test( nan_payload, "nan"));
		EXPECT_TRUE(test(-nan_payload, "-nan"));
#elif defined(HAMON_MSVC)
		EXPECT_TRUE(test( nan_payload, "nan"));
		EXPECT_TRUE(test(-nan_payload, "-nan(ind)"));
#else
		EXPECT_TRUE(test( nan_payload, "nan"));
		EXPECT_TRUE(test(-nan_payload, "-nan"));
#endif
	}
	{
		double const nan_payload = hamon::nan("1729");

#if !defined(HAMON_USE_STD_CHARCONV)
		EXPECT_TRUE(test( nan_payload, "nan"));
		EXPECT_TRUE(test(-nan_payload, "-nan"));
#elif defined(HAMON_MSVC)
		EXPECT_TRUE(test( nan_payload, "nan"));
		EXPECT_TRUE(test(-nan_payload, "-nan(ind)"));
#else
		EXPECT_TRUE(test( nan_payload, "nan"));
		EXPECT_TRUE(test(-nan_payload, "-nan"));
#endif
	}
}

}	// namespace to_chars_floating_point_test

}	// namespace hamon_charconv_test
