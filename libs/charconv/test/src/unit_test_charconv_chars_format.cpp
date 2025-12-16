/**
 *	@file	unit_test_charconv_chars_format.cpp
 *
 *	@brief	chars_format のテスト
 */

#include <hamon/charconv/chars_format.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_charconv_test
{

namespace chars_format_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	using hamon::chars_format;
	{
		auto f = chars_format::fixed;
		f |= chars_format::scientific;
		VERIFY(f == chars_format::general);
	}
	{
		auto f = chars_format::general;
		f &= ~chars_format::fixed;
		VERIFY(f == chars_format::scientific);
	}
	{
		auto f = chars_format::general;
		f ^= chars_format::scientific;
		VERIFY(f == chars_format::fixed);
		f ^= chars_format::scientific;
		VERIFY(f == chars_format::general);
	}
	VERIFY((chars_format::general & chars_format::scientific) == chars_format::scientific);
	VERIFY((chars_format::general & chars_format::fixed)      == chars_format::fixed);
	VERIFY((chars_format::general & chars_format::hex)        != chars_format::hex);

	return true;
}

#undef VERIFY

GTEST_TEST(CharConvTest, CharsFormatTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace chars_format_test

}	// namespace hamon_charconv_test
