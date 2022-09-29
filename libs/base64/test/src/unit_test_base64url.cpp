/**
 *	@file	unit_test_base64url.cpp
 *
 *	@brief	base64url のテスト
 */

#include <hamon/base64/base64url.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "get_random_value.hpp"

namespace hamon_base64url_test
{

template <typename CharT1, typename CharT2>
void Base64UrlStringTest(CharT1 const* src, CharT2 const* expected)
{
	using String1 = std::basic_string<CharT1>;
	using String2 = std::basic_string<CharT2>;

	String1 src_str(src);

	auto const encoded = hamon::base64url::encode<String2>(src_str.data(), src_str.size() * sizeof(CharT1));
	EXPECT_EQ(expected, encoded);
	auto const decoded = hamon::base64url::decode<String1>(encoded.begin(), encoded.end());
	EXPECT_EQ(src_str, decoded);
}

GTEST_TEST(Base64UrlTest, StringTest)
{
	Base64UrlStringTest("", "");
	Base64UrlStringTest("f",      "Zg");
	Base64UrlStringTest("fo",     "Zm8");
	Base64UrlStringTest("foo",    "Zm9v");
	Base64UrlStringTest("foob",   "Zm9vYg");
	Base64UrlStringTest("fooba",  "Zm9vYmE");
	Base64UrlStringTest("foobar", "Zm9vYmFy");
	Base64UrlStringTest("M",   "TQ");
	Base64UrlStringTest("Ma",  "TWE");
	Base64UrlStringTest("Man", "TWFu");
	Base64UrlStringTest("ABCDEFG", "QUJDREVGRw");
	Base64UrlStringTest("abcdefg", "YWJjZGVmZw");
	Base64UrlStringTest("Hello World", "SGVsbG8gV29ybGQ");
	Base64UrlStringTest("Many hands make light work.", "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");
	Base64UrlStringTest("1",    "MQ");
	Base64UrlStringTest("12",   "MTI");
	Base64UrlStringTest("123",  "MTIz");
	Base64UrlStringTest("1234", "MTIzNA");
	Base64UrlStringTest("\1",       "AQ");
	Base64UrlStringTest("\1\2",     "AQI");
	Base64UrlStringTest("\1\2\3",   "AQID");
	Base64UrlStringTest("\1\2\3\4", "AQIDBA");
	Base64UrlStringTest("\xFF",         "_w");
	Base64UrlStringTest("\xFF\xFF",     "__8");
	Base64UrlStringTest("\xFF\xFF\xFE", "___-");
	Base64UrlStringTest("\xFF\xFF\xFF", "____");
	Base64UrlStringTest("\xFB\xEF\xBE", "----");

	Base64UrlStringTest("light work.",  "bGlnaHQgd29yay4");
	Base64UrlStringTest("light work",   "bGlnaHQgd29yaw");
	Base64UrlStringTest("light wor",    "bGlnaHQgd29y");
	Base64UrlStringTest("light wo",     "bGlnaHQgd28");
	Base64UrlStringTest("light w",      "bGlnaHQgdw");

	Base64UrlStringTest("light work.", L"bGlnaHQgd29yay4");
	Base64UrlStringTest("light work",  L"bGlnaHQgd29yaw");
	Base64UrlStringTest("light wor",   L"bGlnaHQgd29y");
	Base64UrlStringTest("light wo",    L"bGlnaHQgd28");
	Base64UrlStringTest("light w",     L"bGlnaHQgdw");
}

template <typename T, typename CharT>
void Base64UrlVectorTest()
{
	using Vector = std::vector<T>;
	using String = std::basic_string<CharT>;

	Vector vec(get_random_value<std::size_t>(0, 100));
	for (auto& x : vec)
	{
		x = get_random_value<T>();
	}

	auto const encoded = hamon::base64url::encode<String>(vec.data(), vec.size() * sizeof(T));
	auto const decoded = hamon::base64url::decode<Vector>(encoded.begin(), encoded.end());
	EXPECT_EQ(vec, decoded);
}

GTEST_TEST(Base64UrlTest, VectorTest)
{
	Base64UrlVectorTest<signed   char,  char>();
	Base64UrlVectorTest<unsigned char,  char>();
	Base64UrlVectorTest<signed   short, char>();
	Base64UrlVectorTest<unsigned short, char>();
	Base64UrlVectorTest<signed   int,   char>();
	Base64UrlVectorTest<unsigned int,   char>();
	Base64UrlVectorTest<signed   long,  char>();
	Base64UrlVectorTest<unsigned long,  char>();
	Base64UrlVectorTest<float,          char>();
	Base64UrlVectorTest<double,         char>();

	Base64UrlVectorTest<signed   char,  wchar_t>();
	Base64UrlVectorTest<unsigned char,  wchar_t>();
	Base64UrlVectorTest<signed   short, wchar_t>();
	Base64UrlVectorTest<unsigned short, wchar_t>();
	Base64UrlVectorTest<signed   int,   wchar_t>();
	Base64UrlVectorTest<unsigned int,   wchar_t>();
	Base64UrlVectorTest<signed   long,  wchar_t>();
	Base64UrlVectorTest<unsigned long,  wchar_t>();
	Base64UrlVectorTest<float,          wchar_t>();
	Base64UrlVectorTest<double,         wchar_t>();
}

}	// namespace hamon_base64url_test
