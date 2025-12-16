/**
 *	@file	unit_test_charconv_to_chars_result.cpp
 *
 *	@brief	to_chars_result のテスト
 */

#include <hamon/charconv/to_chars_result.hpp>
#include <hamon/system_error/errc.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_charconv_test
{

namespace to_chars_result_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool
test()
{
	char buf[128]{};

	hamon::to_chars_result res1{buf, hamon::errc{}};
	hamon::to_chars_result res2{buf, hamon::errc{}};
	hamon::to_chars_result res3{buf, hamon::errc::value_too_large};
	hamon::to_chars_result res4{buf+1, hamon::errc{}};
	hamon::to_chars_result res5{buf+1, hamon::errc::value_too_large};

	VERIFY( (res1 == res1));
	VERIFY( (res1 == res2));
	VERIFY(!(res1 == res3));
	VERIFY(!(res1 == res4));
	VERIFY(!(res1 == res5));

	VERIFY(!(res1 != res1));
	VERIFY(!(res1 != res2));
	VERIFY( (res1 != res3));
	VERIFY( (res1 != res4));
	VERIFY( (res1 != res5));

	return true;
}

GTEST_TEST(CharConvTest, ToCharsResultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

#undef VERIFY

}	// namespace to_chars_result_test

}	// namespace hamon_charconv_test
