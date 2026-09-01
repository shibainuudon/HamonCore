/**
 *	@file	unit_test_string_view_output_stream.cpp
 *
 *	@brief
 */

#include <hamon/string_view.hpp>
#include <hamon/iomanip/setfill.hpp>
#include <hamon/iomanip/setw.hpp>
#include <hamon/ios.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <hamon/sstream/wstringstream.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_test
{
namespace string_view_test
{

GTEST_TEST(StringViewTest, OutputStreamTest)
{
	{
		hamon::string_view sv{"aababc", 6};
		hamon::stringstream ss;
		ss << sv;
		EXPECT_TRUE(ss.str() == "aababc");
	}
	{
		hamon::wstring_view sv{L"abcde", 5};
		hamon::wstringstream ss;
		ss << sv;
		EXPECT_TRUE(ss.str() == L"abcde");
	}

	{
		hamon::string_view sv{"abc"};
		hamon::stringstream ss;
		ss << hamon::setfill('-');
		ss << hamon::left;
		ss << hamon::setw(5);
		ss << sv;
		EXPECT_EQ(ss.str(), "abc--");

		// width is reset after each call
		ss << sv;
		EXPECT_EQ(ss.str(), "abc--abc");

		ss << hamon::setw(6);
		ss << sv;
		EXPECT_EQ(ss.str(), "abc--abcabc---");
	}
	{
		hamon::wstring_view sv{L"abcd"};
		hamon::wstringstream ss;
		ss << hamon::setfill(L'+');
		ss << hamon::right;
		ss << hamon::setw(6);
		ss << sv;
		EXPECT_EQ(ss.str(), L"++abcd");

		// width is reset after each call
		ss << sv;
		EXPECT_EQ(ss.str(), L"++abcdabcd");

		ss << hamon::setw(5);
		ss << sv;
		EXPECT_EQ(ss.str(), L"++abcdabcd+abcd");
	}
}

}	// namespace string_view_test
}	// namespace hamon_test
