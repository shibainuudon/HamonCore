/**
 *	@file	unit_test_format_basic_format_string.cpp
 *
 *	@brief	basic_format_string のテスト
 */

#include <hamon/format/basic_format_string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_format_test
{

namespace basic_format_string_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
HAMON_CXX20_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(FormatTest, BasicFormatStringTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<wchar_t>());
}

}	// namespace basic_format_string_test

}	// namespace hamon_format_test
