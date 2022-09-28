/**
 *	@file	unit_test_base64.cpp
 *
 *	@brief	base64 のテスト
 */

#include <hamon/base64.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "get_random_value.hpp"
#include "constexpr_test.hpp"

namespace hamon_base64_test
{

template <typename CharT1, typename CharT2>
void Base64StringTest(CharT1 const* src, CharT2 const* expected)
{
	using String1 = std::basic_string<CharT1>;
	using String2 = std::basic_string<CharT2>;

	String1 src_str(src);

	auto const encoded = hamon::base64::encode<String2>(src_str.data(), src_str.size() * sizeof(CharT1));
	EXPECT_EQ(expected, encoded);
	auto const decoded = hamon::base64::decode<String1>(encoded.begin(), encoded.end());
	EXPECT_EQ(src_str, decoded);
}

GTEST_TEST(Base64Test, StringTest)
{
	Base64StringTest("", "");
	Base64StringTest("f",      "Zg==");
	Base64StringTest("fo",     "Zm8=");
	Base64StringTest("foo",    "Zm9v");
	Base64StringTest("foob",   "Zm9vYg==");
	Base64StringTest("fooba",  "Zm9vYmE=");
	Base64StringTest("foobar", "Zm9vYmFy");
	Base64StringTest("M",   "TQ==");
	Base64StringTest("Ma",  "TWE=");
	Base64StringTest("Man", "TWFu");
	Base64StringTest("ABCDEFG", "QUJDREVGRw==");
	Base64StringTest("abcdefg", "YWJjZGVmZw==");
	Base64StringTest("Hello World", "SGVsbG8gV29ybGQ=");
	Base64StringTest("Many hands make light work.", "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");
	Base64StringTest("1",    "MQ==");
	Base64StringTest("12",   "MTI=");
	Base64StringTest("123",  "MTIz");
	Base64StringTest("1234", "MTIzNA==");
	Base64StringTest("\1",       "AQ==");
	Base64StringTest("\1\2",     "AQI=");
	Base64StringTest("\1\2\3",   "AQID");
	Base64StringTest("\1\2\3\4", "AQIDBA==");
	Base64StringTest("\xFF",         "/w==");
	Base64StringTest("\xFF\xFF",     "//8=");
	Base64StringTest("\xFF\xFF\xFE", "///+");
	Base64StringTest("\xFF\xFF\xFF", "////");
	Base64StringTest("\xFB\xEF\xBE", "++++");

	Base64StringTest("light work.",  "bGlnaHQgd29yay4=");
	Base64StringTest("light work",   "bGlnaHQgd29yaw==");
	Base64StringTest("light wor",    "bGlnaHQgd29y");
	Base64StringTest("light wo",     "bGlnaHQgd28=");
	Base64StringTest("light w",      "bGlnaHQgdw==");

	Base64StringTest("light work.", L"bGlnaHQgd29yay4=");
	Base64StringTest("light work",  L"bGlnaHQgd29yaw==");
	Base64StringTest("light wor",   L"bGlnaHQgd29y");
	Base64StringTest("light wo",    L"bGlnaHQgd28=");
	Base64StringTest("light w",     L"bGlnaHQgdw==");
}

template <typename T, typename CharT>
void Base64VectorTest()
{
	using Vector = std::vector<T>;
	using String = std::basic_string<CharT>;

	Vector vec(get_random_value<std::size_t>(0, 100));
	for (auto& x : vec)
	{
		x = get_random_value<T>();
	}

	auto const encoded = hamon::base64::encode<String>(vec.data(), vec.size() * sizeof(T));
	auto const decoded = hamon::base64::decode<Vector>(encoded.begin(), encoded.end());
	EXPECT_EQ(vec, decoded);
}

GTEST_TEST(Base64Test, VectorTest)
{
	Base64VectorTest<signed   char,  char>();
	Base64VectorTest<unsigned char,  char>();
	Base64VectorTest<signed   short, char>();
	Base64VectorTest<unsigned short, char>();
	Base64VectorTest<signed   int,   char>();
	Base64VectorTest<unsigned int,   char>();
	Base64VectorTest<signed   long,  char>();
	Base64VectorTest<unsigned long,  char>();
	Base64VectorTest<float,          char>();
	Base64VectorTest<double,         char>();

	Base64VectorTest<signed   char,  wchar_t>();
	Base64VectorTest<unsigned char,  wchar_t>();
	Base64VectorTest<signed   short, wchar_t>();
	Base64VectorTest<unsigned short, wchar_t>();
	Base64VectorTest<signed   int,   wchar_t>();
	Base64VectorTest<unsigned int,   wchar_t>();
	Base64VectorTest<signed   long,  wchar_t>();
	Base64VectorTest<unsigned long,  wchar_t>();
	Base64VectorTest<float,          wchar_t>();
	Base64VectorTest<double,         wchar_t>();
}

}	// namespace hamon_base64_test
