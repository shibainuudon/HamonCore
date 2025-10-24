/**
 *	@file	unit_test_cctype.cpp
 *
 *	@brief	cctype のテスト
 */

#include <hamon/cctype.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(CCTypeTest, CCTypeTest)
{
	EXPECT_TRUE(hamon::isalnum('0'));
	EXPECT_TRUE(hamon::isalpha('A'));
	EXPECT_TRUE(hamon::isblank('\t'));
	EXPECT_TRUE(hamon::iscntrl('\n'));
	EXPECT_TRUE(hamon::isdigit('0'));
	EXPECT_TRUE(hamon::isgraph('!'));
	EXPECT_TRUE(hamon::islower('a'));
	EXPECT_TRUE(hamon::isprint(':'));
	EXPECT_TRUE(hamon::ispunct('['));
	EXPECT_TRUE(hamon::isspace(' '));
	EXPECT_TRUE(hamon::isupper('A'));
	EXPECT_TRUE(hamon::isxdigit('f'));

	{
		hamon::string s = "Hello, World!\t123\n";
		EXPECT_EQ(13, hamon::count_if(s.begin(), s.end(), hamon::isalnum));
		EXPECT_EQ(10, hamon::count_if(s.begin(), s.end(), hamon::isalpha));
		EXPECT_EQ( 2, hamon::count_if(s.begin(), s.end(), hamon::isblank));
		EXPECT_EQ( 2, hamon::count_if(s.begin(), s.end(), hamon::iscntrl));
		EXPECT_EQ( 3, hamon::count_if(s.begin(), s.end(), hamon::isdigit));
		EXPECT_EQ(15, hamon::count_if(s.begin(), s.end(), hamon::isgraph));
		EXPECT_EQ( 8, hamon::count_if(s.begin(), s.end(), hamon::islower));
		EXPECT_EQ(16, hamon::count_if(s.begin(), s.end(), hamon::isprint));
		EXPECT_EQ( 2, hamon::count_if(s.begin(), s.end(), hamon::ispunct));
		EXPECT_EQ( 3, hamon::count_if(s.begin(), s.end(), hamon::isspace));
		EXPECT_EQ( 2, hamon::count_if(s.begin(), s.end(), hamon::isupper));
		EXPECT_EQ( 5, hamon::count_if(s.begin(), s.end(), hamon::isxdigit));
		hamon::transform(s.begin(), s.end(), s.begin(), hamon::tolower);
		EXPECT_EQ("hello, world!\t123\n", s);
		hamon::transform(s.begin(), s.end(), s.begin(), hamon::toupper);
		EXPECT_EQ("HELLO, WORLD!\t123\n", s);
	}
	{
		hamon::wstring s = L"Hello, World!\t123\n";
		EXPECT_EQ(13, hamon::count_if(s.begin(), s.end(), hamon::isalnum));
		EXPECT_EQ(10, hamon::count_if(s.begin(), s.end(), hamon::isalpha));
		EXPECT_EQ( 2, hamon::count_if(s.begin(), s.end(), hamon::isblank));
		EXPECT_EQ( 2, hamon::count_if(s.begin(), s.end(), hamon::iscntrl));
		EXPECT_EQ( 3, hamon::count_if(s.begin(), s.end(), hamon::isdigit));
		EXPECT_EQ(15, hamon::count_if(s.begin(), s.end(), hamon::isgraph));
		EXPECT_EQ( 8, hamon::count_if(s.begin(), s.end(), hamon::islower));
		EXPECT_EQ(16, hamon::count_if(s.begin(), s.end(), hamon::isprint));
		EXPECT_EQ( 2, hamon::count_if(s.begin(), s.end(), hamon::ispunct));
		EXPECT_EQ( 3, hamon::count_if(s.begin(), s.end(), hamon::isspace));
		EXPECT_EQ( 2, hamon::count_if(s.begin(), s.end(), hamon::isupper));
		EXPECT_EQ( 5, hamon::count_if(s.begin(), s.end(), hamon::isxdigit));
		hamon::transform(s.begin(), s.end(), s.begin(), hamon::tolower);
		EXPECT_EQ(L"hello, world!\t123\n", s);
		hamon::transform(s.begin(), s.end(), s.begin(), hamon::toupper);
		EXPECT_EQ(L"HELLO, WORLD!\t123\n", s);
	}
}
