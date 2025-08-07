/**
 *	@file	unit_test_format_format_error.cpp
 *
 *	@brief	format_error のテスト
 *
 *	class format_error;
 */

#include <hamon/format/format_error.hpp>
#include <hamon/type_traits/is_base_of.hpp>
#include <hamon/type_traits/is_polymorphic.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

namespace hamon_format_test
{

namespace format_error_test
{


GTEST_TEST(FormatTest, FormatErrorTest)
{
	static_assert(hamon::is_base_of_v<std::runtime_error, hamon::format_error>);
	static_assert(hamon::is_polymorphic_v<hamon::format_error>);

	{
		const char* msg = "format_error message c-string";
		hamon::format_error e(msg);
		EXPECT_STREQ(e.what(), msg);
		hamon::format_error e2(e);
		EXPECT_STREQ(e2.what(), msg);
		e2 = e;
		EXPECT_STREQ(e2.what(), msg);
	}
	{
		std::string msg("format_error message std::string");
		hamon::format_error e(msg);
		EXPECT_EQ(e.what(), msg);
		hamon::format_error e2(e);
		EXPECT_EQ(e2.what(), msg);
		e2 = e;
		EXPECT_EQ(e2.what(), msg);
	}
}

}	// namespace format_error_test

}	// namespace hamon_format_test
