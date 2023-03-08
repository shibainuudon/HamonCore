/**
 *	@file	unit_test_base64_xml_name.cpp
 *
 *	@brief	base64_xml_name のテスト
 */

#include <hamon/base64/base64_xml_name.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uint16_t.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "get_random_value.hpp"
#include "constexpr_test.hpp"

namespace hamon_base64_xml_name_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

GTEST_TEST(Base64XmlNameTest, GetEncodedSizeTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0u, hamon::base64_xml_name::get_encoded_size(0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2u, hamon::base64_xml_name::get_encoded_size(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3u, hamon::base64_xml_name::get_encoded_size(2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4u, hamon::base64_xml_name::get_encoded_size(3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6u, hamon::base64_xml_name::get_encoded_size(4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7u, hamon::base64_xml_name::get_encoded_size(5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8u, hamon::base64_xml_name::get_encoded_size(6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10u, hamon::base64_xml_name::get_encoded_size(7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11u, hamon::base64_xml_name::get_encoded_size(8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12u, hamon::base64_xml_name::get_encoded_size(9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14u, hamon::base64_xml_name::get_encoded_size(10));
}

GTEST_TEST(Base64XmlNameTest, GetDecodedSizeTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0u, hamon::base64_xml_name::get_decoded_size(0));
	//HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::base64_xml_name::get_decoded_size(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1u, hamon::base64_xml_name::get_decoded_size(2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2u, hamon::base64_xml_name::get_decoded_size(3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3u, hamon::base64_xml_name::get_decoded_size(4));
	//HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::base64_xml_name::get_decoded_size(5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4u, hamon::base64_xml_name::get_decoded_size(6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5u, hamon::base64_xml_name::get_decoded_size(7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6u, hamon::base64_xml_name::get_decoded_size(8));
	//HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::base64_xml_name::get_decoded_size(9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7u, hamon::base64_xml_name::get_decoded_size(10));
}

template <typename T, hamon::size_t N, typename U, hamon::size_t M>
inline HAMON_CXX14_CONSTEXPR bool ArrayTest1(T const (&src)[N], U const (&expected)[M])
{
	U encoded[M] {};
	hamon::base64_xml_name::encode(src, src + N, encoded);

	for (hamon::size_t i = 0; i < M; ++i)
	{
		VERIFY(encoded[i] == expected[i]);
	}

	T decoded[hamon::base64_xml_name::get_decoded_size(M)] {};
	auto size = hamon::base64_xml_name::decode(encoded, encoded + M, decoded);
	VERIFY(size == sizeof(src));
	for (hamon::size_t i = 0; i < N; ++i)
	{
		VERIFY(decoded[i] == src[i]);
	}

	return true;
}

template <typename T, hamon::size_t N, typename U, hamon::size_t M>
inline HAMON_CXX14_CONSTEXPR bool ArrayTest2(T const (&src)[N], U const (&expected)[M])
{
	U encoded[M] {};
	hamon::base64_xml_name::encode(src, encoded);

	for (hamon::size_t i = 0; i < M; ++i)
	{
		VERIFY(encoded[i] == expected[i]);
	}

	T decoded[hamon::base64_xml_name::get_decoded_size(M)] {};
	auto size = hamon::base64_xml_name::decode(encoded, decoded);
	VERIFY(size == sizeof(src));
	for (hamon::size_t i = 0; i < N; ++i)
	{
		VERIFY(decoded[i] == src[i]);
	}

	return true;
}

template <typename T, hamon::size_t N, typename U, hamon::size_t M>
inline HAMON_CXX14_CONSTEXPR bool ArrayTest(T const (&src)[N], U const (&expected)[M])
{
	VERIFY(hamon::base64_xml_name::get_encoded_size(sizeof(src)) == M);
	VERIFY(hamon::base64_xml_name::get_decoded_size(M) >= N);

	VERIFY(ArrayTest1(src, expected));
	VERIFY(ArrayTest2(src, expected));

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool ArrayConstexprTest()
{
	{
		char const src[] { 'f' };
		char const expected[] { 'Z', 'g' };
		VERIFY(ArrayTest(src, expected));
	}
	{
		char const src[] { 'f', 'o' };
		wchar_t const expected[] { 'Z', 'm', '8' };
		VERIFY(ArrayTest(src, expected));
	}
	{
		char const src[] { 'f', 'o', 'o' };
		char const expected[] { 'Z', 'm', '9', 'v' };
		VERIFY(ArrayTest(src, expected));
	}
	{
		char const src[] { 'f', 'o', 'o', 'b' };
		wchar_t const expected[] { 'Z', 'm', '9', 'v', 'Y', 'g' };
		VERIFY(ArrayTest(src, expected));
	}
	{
		char const src[] { 'f', 'o', 'o', 'b', 'a' };
		char const expected[] { 'Z', 'm', '9', 'v', 'Y', 'm', 'E' };
		VERIFY(ArrayTest(src, expected));
	}
	{
		char const src[] { 'f', 'o', 'o', 'b', 'a', 'r' };
		wchar_t const expected[] { 'Z', 'm', '9', 'v', 'Y', 'm', 'F', 'y' };
		VERIFY(ArrayTest(src, expected));
	}
	{
		unsigned char const src[] { 1 };
		char const expected[] { 'A', 'Q' };
		VERIFY(ArrayTest(src, expected));
	}
	{
		unsigned char const src[] { 1, 2 };
		wchar_t const expected[] { 'A', 'Q', 'I' };
		VERIFY(ArrayTest(src, expected));
	}
	{
		unsigned char const src[] { 1, 2, 3 };
		char const expected[] { 'A', 'Q', 'I', 'D' };
		VERIFY(ArrayTest(src, expected));
	}
	{
		unsigned char const src[] { 1, 2, 3, 255 };
		wchar_t const expected[] { 'A', 'Q', 'I', 'D', ':', 'w' };
		VERIFY(ArrayTest(src, expected));
	}
	{
		unsigned char const src[] { 1, 2, 3, 255, 255, 254 };
		char const expected[] { 'A', 'Q', 'I', 'D', ':', ':', ':', '_' };
		VERIFY(ArrayTest(src, expected));
	}
	return true;
}

inline bool ArrayNonConstexprTest()
{
	{
		hamon::uint16_t const src[] { 1 };
		char const expected[] {'A', 'Q', 'A'};
		VERIFY(ArrayTest(src, expected));
	}
	{
		hamon::uint16_t const src[] { 1, 2 };
		char const expected[] {'A', 'Q', 'A', 'C', 'A', 'A'};
		VERIFY(ArrayTest(src, expected));
	}
	{
		hamon::uint16_t const src[] { 1, 2, 3 };
		char const expected[] {'A', 'Q', 'A', 'C', 'A', 'A', 'M', 'A'};
		VERIFY(ArrayTest(src, expected));
	}
	{
		hamon::uint32_t const src[] { 1 };
		char const expected[] {'A', 'Q', 'A', 'A', 'A', 'A'};
		VERIFY(ArrayTest(src, expected));
	}
	{
		hamon::uint32_t const src[] { 1, 2 };
		char const expected[] {'A', 'Q', 'A', 'A', 'A', 'A', 'I', 'A', 'A', 'A', 'A'};
		VERIFY(ArrayTest(src, expected));
	}
	{
		hamon::uint32_t const src[] { 1, 2, 3 };
		char const expected[] {'A', 'Q', 'A', 'A', 'A', 'A', 'I', 'A', 'A', 'A', 'A', 'D', 'A', 'A', 'A', 'A'};
		VERIFY(ArrayTest(src, expected));
	}
	return true;
}

GTEST_TEST(Base64XmlNameTest, ArrayTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ArrayConstexprTest());
	EXPECT_TRUE(ArrayNonConstexprTest());
}

template <typename CharT1, typename CharT2>
void Base64XmlNameStringTest(CharT1 const* src, CharT2 const* expected)
{
	using String1 = std::basic_string<CharT1>;
	using String2 = std::basic_string<CharT2>;

	String1 const src_str(src);
	{
		auto const encoded = hamon::base64_xml_name::encode<String2>(src_str.begin(), src_str.end());
		EXPECT_EQ(expected, encoded);
		auto const decoded = hamon::base64_xml_name::decode<String1>(encoded.begin(), encoded.end());
		EXPECT_EQ(src_str, decoded);
	}
	{
		auto const encoded = hamon::base64_xml_name::encode<String2>(src_str);
		EXPECT_EQ(expected, encoded);
		auto const decoded = hamon::base64_xml_name::decode<String1>(encoded);
		EXPECT_EQ(src_str, decoded);
	}
}

GTEST_TEST(Base64XmlNameTest, StringTest)
{
	Base64XmlNameStringTest("", "");
	Base64XmlNameStringTest("f",      "Zg");
	Base64XmlNameStringTest("fo",     "Zm8");
	Base64XmlNameStringTest("foo",    "Zm9v");
	Base64XmlNameStringTest("foob",   "Zm9vYg");
	Base64XmlNameStringTest("fooba",  "Zm9vYmE");
	Base64XmlNameStringTest("foobar", "Zm9vYmFy");
	Base64XmlNameStringTest("M",   "TQ");
	Base64XmlNameStringTest("Ma",  "TWE");
	Base64XmlNameStringTest("Man", "TWFu");
	Base64XmlNameStringTest("ABCDEFG", "QUJDREVGRw");
	Base64XmlNameStringTest("abcdefg", "YWJjZGVmZw");
	Base64XmlNameStringTest("Hello World", "SGVsbG8gV29ybGQ");
	Base64XmlNameStringTest("Many hands make light work.", "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");
	Base64XmlNameStringTest("1",    "MQ");
	Base64XmlNameStringTest("12",   "MTI");
	Base64XmlNameStringTest("123",  "MTIz");
	Base64XmlNameStringTest("1234", "MTIzNA");
	Base64XmlNameStringTest("\1",       "AQ");
	Base64XmlNameStringTest("\1\2",     "AQI");
	Base64XmlNameStringTest("\1\2\3",   "AQID");
	Base64XmlNameStringTest("\1\2\3\4", "AQIDBA");
	Base64XmlNameStringTest("\xFF",         ":w");
	Base64XmlNameStringTest("\xFF\xFF",     "::8");
	Base64XmlNameStringTest("\xFF\xFF\xFE", ":::_");
	Base64XmlNameStringTest("\xFF\xFF\xFF", "::::");
	Base64XmlNameStringTest("\xFB\xEF\xBE", "____");

	Base64XmlNameStringTest("light work.",  "bGlnaHQgd29yay4");
	Base64XmlNameStringTest("light work",   "bGlnaHQgd29yaw");
	Base64XmlNameStringTest("light wor",    "bGlnaHQgd29y");
	Base64XmlNameStringTest("light wo",     "bGlnaHQgd28");
	Base64XmlNameStringTest("light w",      "bGlnaHQgdw");

	Base64XmlNameStringTest("light work.", L"bGlnaHQgd29yay4");
	Base64XmlNameStringTest("light work",  L"bGlnaHQgd29yaw");
	Base64XmlNameStringTest("light wor",   L"bGlnaHQgd29y");
	Base64XmlNameStringTest("light wo",    L"bGlnaHQgd28");
	Base64XmlNameStringTest("light w",     L"bGlnaHQgdw");
}

template <typename T, typename CharT>
void Base64XmlNameVectorTest()
{
	using Vector = std::vector<T>;
	using String = std::basic_string<CharT>;

	Vector vec(get_random_value<hamon::size_t>(0, 100));
	for (auto& x : vec)
	{
		x = get_random_value<T>();
	}

	{
		auto const encoded = hamon::base64_xml_name::encode<String>(vec.begin(), vec.end());
		auto const decoded = hamon::base64_xml_name::decode<Vector>(encoded.begin(), encoded.end());
		EXPECT_EQ(vec, decoded);
	}
	{
		auto const encoded = hamon::base64_xml_name::encode<String>(vec);
		auto const decoded = hamon::base64_xml_name::decode<Vector>(encoded);
		EXPECT_EQ(vec, decoded);
	}
}

GTEST_TEST(Base64XmlNameTest, VectorTest)
{
	Base64XmlNameVectorTest<signed   char,  char>();
	Base64XmlNameVectorTest<unsigned char,  char>();
	Base64XmlNameVectorTest<signed   short, char>();
	Base64XmlNameVectorTest<unsigned short, char>();
	Base64XmlNameVectorTest<signed   int,   char>();
	Base64XmlNameVectorTest<unsigned int,   char>();
	Base64XmlNameVectorTest<signed   long,  char>();
	Base64XmlNameVectorTest<unsigned long,  char>();
	Base64XmlNameVectorTest<float,          char>();
	Base64XmlNameVectorTest<double,         char>();

	Base64XmlNameVectorTest<signed   char,  wchar_t>();
	Base64XmlNameVectorTest<unsigned char,  wchar_t>();
	Base64XmlNameVectorTest<signed   short, wchar_t>();
	Base64XmlNameVectorTest<unsigned short, wchar_t>();
	Base64XmlNameVectorTest<signed   int,   wchar_t>();
	Base64XmlNameVectorTest<unsigned int,   wchar_t>();
	Base64XmlNameVectorTest<signed   long,  wchar_t>();
	Base64XmlNameVectorTest<unsigned long,  wchar_t>();
	Base64XmlNameVectorTest<float,          wchar_t>();
	Base64XmlNameVectorTest<double,         wchar_t>();
}

#undef VERIFY

}	// namespace hamon_base64_xml_name_test
