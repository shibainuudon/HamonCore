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

	{
		hamon::string_view sv{"abc"};
		std::stringstream ss;
		ss << std::setfill('-');
		ss << std::left;
		ss << std::setw(5);
		ss << sv;
		EXPECT_EQ(ss.str(), "abc--");

		// width is reset after each call
		ss << sv;
		EXPECT_EQ(ss.str(), "abc--abc");

		ss << std::setw(6);
		ss << sv;
		EXPECT_EQ(ss.str(), "abc--abcabc---");
	}
	{
		hamon::wstring_view sv{L"abcd"};
		std::wstringstream ss;
		ss << std::setfill(L'+');
		ss << std::right;
		ss << std::setw(6);
		ss << sv;
		EXPECT_EQ(ss.str(), L"++abcd");

		// width is reset after each call
		ss << sv;
		EXPECT_EQ(ss.str(), L"++abcdabcd");

		ss << std::setw(5);
		ss << sv;
		EXPECT_EQ(ss.str(), L"++abcdabcd+abcd");
	}
}

}	// namespace string_view_test
}	// namespace hamon_test
