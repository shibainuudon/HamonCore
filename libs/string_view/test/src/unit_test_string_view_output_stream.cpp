/**
 *	@file	unit_test_string_view_output_stream.cpp
 *
 *	@brief
 */

#include <hamon/string_view.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_test
{
namespace string_view_test
{

GTEST_TEST(StringViewTest, OutputStreamTest)
{
	{
		hamon::string_view sv{"aababc", 6};
		std::stringstream ss;
		ss << sv;
		EXPECT_TRUE(ss.str() == "aababc");
	}
	{
		hamon::wstring_view sv{L"abcde", 5};
		std::wstringstream ss;
		ss << sv;
		EXPECT_TRUE(ss.str() == L"abcde");
	}
}

}	// namespace string_view_test
}	// namespace hamon_test
