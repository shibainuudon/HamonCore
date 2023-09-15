/**
 *	@file	unit_test_base64_xml_nmtoken.cpp
 *
 *	@brief	base64_xml_nmtoken のテスト
 */

#include <hamon/base64/base64_xml_nmtoken.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uint16_t.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <hamon/string.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "get_random_value.hpp"
#include "constexpr_test.hpp"

namespace hamon_base64_xml_nmtoken_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

GTEST_TEST(Base64XmlNmTokenTest, GetEncodedSizeTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0u, hamon::base64_xml_nmtoken::get_encoded_size(0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2u, hamon::base64_xml_nmtoken::get_encoded_size(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3u, hamon::base64_xml_nmtoken::get_encoded_size(2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4u, hamon::base64_xml_nmtoken::get_encoded_size(3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6u, hamon::base64_xml_nmtoken::get_encoded_size(4));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7u, hamon::base64_xml_nmtoken::get_encoded_size(5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 8u, hamon::base64_xml_nmtoken::get_encoded_size(6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10u, hamon::base64_xml_nmtoken::get_encoded_size(7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11u, hamon::base64_xml_nmtoken::get_encoded_size(8));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12u, hamon::base64_xml_nmtoken::get_encoded_size(9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14u, hamon::base64_xml_nmtoken::get_encoded_size(10));
}

GTEST_TEST(Base64XmlNmTokenTest, GetDecodedSizeTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0u, hamon::base64_xml_nmtoken::get_decoded_size(0));
	//HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1, hamon::base64_xml_nmtoken::get_decoded_size(1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1u, hamon::base64_xml_nmtoken::get_decoded_size(2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 2u, hamon::base64_xml_nmtoken::get_decoded_size(3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3u, hamon::base64_xml_nmtoken::get_decoded_size(4));
	//HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4, hamon::base64_xml_nmtoken::get_decoded_size(5));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4u, hamon::base64_xml_nmtoken::get_decoded_size(6));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5u, hamon::base64_xml_nmtoken::get_decoded_size(7));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6u, hamon::base64_xml_nmtoken::get_decoded_size(8));
	//HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7, hamon::base64_xml_nmtoken::get_decoded_size(9));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 7u, hamon::base64_xml_nmtoken::get_decoded_size(10));
}

template <typename T, hamon::size_t N, typename U, hamon::size_t M>
inline HAMON_CXX14_CONSTEXPR bool ArrayTest1(T const (&src)[N], U const (&expected)[M])
{
	U encoded[M] {};
	hamon::base64_xml_nmtoken::encode(src, src + N, encoded);

	for (hamon::size_t i = 0; i < M; ++i)
	{
		VERIFY(encoded[i] == expected[i]);
	}

	T decoded[hamon::base64_xml_nmtoken::get_decoded_size(M)] {};
	auto size = hamon::base64_xml_nmtoken::decode(encoded, encoded + M, decoded);
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
	hamon::base64_xml_nmtoken::encode(src, encoded);

	for (hamon::size_t i = 0; i < M; ++i)
	{
		VERIFY(encoded[i] == expected[i]);
	}

	T decoded[hamon::base64_xml_nmtoken::get_decoded_size(M)] {};
	auto size = hamon::base64_xml_nmtoken::decode(encoded, decoded);
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
	VERIFY(hamon::base64_xml_nmtoken::get_encoded_size(sizeof(src)) == M);
	VERIFY(hamon::base64_xml_nmtoken::get_decoded_size(M) >= N);

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
		wchar_t const expected[] { 'A', 'Q', 'I', 'D', '-', 'w' };
		VERIFY(ArrayTest(src, expected));
	}
	{
		unsigned char const src[] { 1, 2, 3, 255, 255, 254 };
		char const expected[] { 'A', 'Q', 'I', 'D', '-', '-', '-', '.' };
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

GTEST_TEST(Base64XmlNmTokenTest, ArrayTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ArrayConstexprTest());
	EXPECT_TRUE(ArrayNonConstexprTest());
}

template <typename CharT1, typename CharT2>
void Base64XmlNmTokenStringTest(CharT1 const* src, CharT2 const* expected)
{
	using String1 = hamon::basic_string<CharT1>;
	using String2 = hamon::basic_string<CharT2>;

	String1 const src_str(src);
	{
		auto const encoded = hamon::base64_xml_nmtoken::encode<String2>(src_str.begin(), src_str.end());
		EXPECT_EQ(expected, encoded);
		auto const decoded = hamon::base64_xml_nmtoken::decode<String1>(encoded.begin(), encoded.end());
		EXPECT_EQ(src_str, decoded);
	}
	{
		auto const encoded = hamon::base64_xml_nmtoken::encode<String2>(src_str);
		EXPECT_EQ(expected, encoded);
		auto const decoded = hamon::base64_xml_nmtoken::decode<String1>(encoded);
		EXPECT_EQ(src_str, decoded);
	}
}

GTEST_TEST(Base64XmlNmTokenTest, StringTest)
{
	Base64XmlNmTokenStringTest("", "");
	Base64XmlNmTokenStringTest("f",      "Zg");
	Base64XmlNmTokenStringTest("fo",     "Zm8");
	Base64XmlNmTokenStringTest("foo",    "Zm9v");
	Base64XmlNmTokenStringTest("foob",   "Zm9vYg");
	Base64XmlNmTokenStringTest("fooba",  "Zm9vYmE");
	Base64XmlNmTokenStringTest("foobar", "Zm9vYmFy");
	Base64XmlNmTokenStringTest("M",   "TQ");
	Base64XmlNmTokenStringTest("Ma",  "TWE");
	Base64XmlNmTokenStringTest("Man", "TWFu");
	Base64XmlNmTokenStringTest("ABCDEFG", "QUJDREVGRw");
	Base64XmlNmTokenStringTest("abcdefg", "YWJjZGVmZw");
	Base64XmlNmTokenStringTest("Hello World", "SGVsbG8gV29ybGQ");
	Base64XmlNmTokenStringTest("Many hands make light work.", "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");
	Base64XmlNmTokenStringTest("1",    "MQ");
	Base64XmlNmTokenStringTest("12",   "MTI");
	Base64XmlNmTokenStringTest("123",  "MTIz");
	Base64XmlNmTokenStringTest("1234", "MTIzNA");
	Base64XmlNmTokenStringTest("\1",       "AQ");
	Base64XmlNmTokenStringTest("\1\2",     "AQI");
	Base64XmlNmTokenStringTest("\1\2\3",   "AQID");
	Base64XmlNmTokenStringTest("\1\2\3\4", "AQIDBA");
	Base64XmlNmTokenStringTest("\xFF",         "-w");
	Base64XmlNmTokenStringTest("\xFF\xFF",     "--8");
	Base64XmlNmTokenStringTest("\xFF\xFF\xFE", "---.");
	Base64XmlNmTokenStringTest("\xFF\xFF\xFF", "----");
	Base64XmlNmTokenStringTest("\xFB\xEF\xBE", "....");

	Base64XmlNmTokenStringTest("light work.",  "bGlnaHQgd29yay4");
	Base64XmlNmTokenStringTest("light work",   "bGlnaHQgd29yaw");
	Base64XmlNmTokenStringTest("light wor",    "bGlnaHQgd29y");
	Base64XmlNmTokenStringTest("light wo",     "bGlnaHQgd28");
	Base64XmlNmTokenStringTest("light w",      "bGlnaHQgdw");

	Base64XmlNmTokenStringTest("light work.", L"bGlnaHQgd29yay4");
	Base64XmlNmTokenStringTest("light work",  L"bGlnaHQgd29yaw");
	Base64XmlNmTokenStringTest("light wor",   L"bGlnaHQgd29y");
	Base64XmlNmTokenStringTest("light wo",    L"bGlnaHQgd28");
	Base64XmlNmTokenStringTest("light w",     L"bGlnaHQgdw");
}

template <typename T, typename CharT>
void Base64XmlNmTokenVectorTest()
{
	using Vector = hamon::vector<T>;
	using String = hamon::basic_string<CharT>;

	Vector vec(get_random_value<hamon::size_t>(0, 100));
	for (auto& x : vec)
	{
		x = get_random_value<T>();
	}

	{
		auto const encoded = hamon::base64_xml_nmtoken::encode<String>(vec.begin(), vec.end());
		auto const decoded = hamon::base64_xml_nmtoken::decode<Vector>(encoded.begin(), encoded.end());
		EXPECT_EQ(vec, decoded);
	}
	{
		auto const encoded = hamon::base64_xml_nmtoken::encode<String>(vec);
		auto const decoded = hamon::base64_xml_nmtoken::decode<Vector>(encoded);
		EXPECT_EQ(vec, decoded);
	}
}

GTEST_TEST(Base64XmlNmTokenTest, VectorTest)
{
	Base64XmlNmTokenVectorTest<signed   char,  char>();
	Base64XmlNmTokenVectorTest<unsigned char,  char>();
	Base64XmlNmTokenVectorTest<signed   short, char>();
	Base64XmlNmTokenVectorTest<unsigned short, char>();
	Base64XmlNmTokenVectorTest<signed   int,   char>();
	Base64XmlNmTokenVectorTest<unsigned int,   char>();
	Base64XmlNmTokenVectorTest<signed   long,  char>();
	Base64XmlNmTokenVectorTest<unsigned long,  char>();
	Base64XmlNmTokenVectorTest<float,          char>();
	Base64XmlNmTokenVectorTest<double,         char>();

	Base64XmlNmTokenVectorTest<signed   char,  wchar_t>();
	Base64XmlNmTokenVectorTest<unsigned char,  wchar_t>();
	Base64XmlNmTokenVectorTest<signed   short, wchar_t>();
	Base64XmlNmTokenVectorTest<unsigned short, wchar_t>();
	Base64XmlNmTokenVectorTest<signed   int,   wchar_t>();
	Base64XmlNmTokenVectorTest<unsigned int,   wchar_t>();
	Base64XmlNmTokenVectorTest<signed   long,  wchar_t>();
	Base64XmlNmTokenVectorTest<unsigned long,  wchar_t>();
	Base64XmlNmTokenVectorTest<float,          wchar_t>();
	Base64XmlNmTokenVectorTest<double,         wchar_t>();
}

#undef VERIFY

}	// namespace hamon_base64_xml_nmtoken_test
