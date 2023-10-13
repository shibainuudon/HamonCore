/**
 *	@file	string_test_helper.hpp
 *
 *	@brief	
 */

#ifndef UNIT_TEST_STRING_STRING_TEST_HELPER_HPP
#define UNIT_TEST_STRING_STRING_TEST_HELPER_HPP

#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_test
{
namespace string_test
{

template <typename String>
constexpr bool GeneralCheck(String const& s)
{
	using CharT = typename String::value_type;
	// [basic.string.general]/3
	return
		s.size() <= s.capacity() &&
		*(s.data() + s.size()) == CharT{} &&
		s[s.size()] == CharT{};
}

template <typename T>
class StringTest : public ::testing::Test {};

using StringTestTypes =
::testing::Types<
	  char
	, wchar_t
#if defined(HAMON_HAS_CXX20_CHAR8_T) && !defined(HAMON_PLATFORM_MACOS)
	, char8_t
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	, char16_t
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	, char32_t
#endif
>;

TYPED_TEST_SUITE(StringTest, StringTestTypes);

template <typename CharT>
struct StringTestHelper;

template <>
struct StringTestHelper<char>
{
	HAMON_CONSTEXPR static const char* aababc() { return "aababc"; }
	HAMON_CONSTEXPR static const char* abcd() { return "abcd"; }
	HAMON_CONSTEXPR static const char* abc() { return "abc"; }
	HAMON_CONSTEXPR static const char* ab() { return "ab"; }
	HAMON_CONSTEXPR static const char* abbccc() { return "abbccc"; }
	HAMON_CONSTEXPR static const char* abcde() { return "abcde"; }
	HAMON_CONSTEXPR static const char* abb() { return "abb"; }
	HAMON_CONSTEXPR static const char* bcde() { return "bcde"; }
	HAMON_CONSTEXPR static const char* bcd() { return "bcd"; }
	HAMON_CONSTEXPR static const char* edcba() { return "edcba"; }
	HAMON_CONSTEXPR static const char* ABCDE() { return "ABCDE"; }
	HAMON_CONSTEXPR static const char* long_str() { return "The quick brown fox jumps over the lazy dog"; }
};

template <>
struct StringTestHelper<wchar_t>
{
	HAMON_CONSTEXPR static const wchar_t* aababc() { return L"aababc"; }
	HAMON_CONSTEXPR static const wchar_t* abcd() { return L"abcd"; }
	HAMON_CONSTEXPR static const wchar_t* abc() { return L"abc"; }
	HAMON_CONSTEXPR static const wchar_t* ab() { return L"ab"; }
	HAMON_CONSTEXPR static const wchar_t* abbccc() { return L"abbccc"; }
	HAMON_CONSTEXPR static const wchar_t* abcde() { return L"abcde"; }
	HAMON_CONSTEXPR static const wchar_t* abb() { return L"abb"; }
	HAMON_CONSTEXPR static const wchar_t* bcde() { return L"bcde"; }
	HAMON_CONSTEXPR static const wchar_t* bcd() { return L"bcd"; }
	HAMON_CONSTEXPR static const wchar_t* edcba() { return L"edcba"; }
	HAMON_CONSTEXPR static const wchar_t* ABCDE() { return L"ABCDE"; }
	HAMON_CONSTEXPR static const wchar_t* long_str() { return L"The quick brown fox jumps over the lazy dog"; }
};

#if defined(HAMON_HAS_CXX20_CHAR8_T)
template <>
struct StringTestHelper<char8_t>
{
	HAMON_CONSTEXPR static const char8_t* aababc() { return u8"aababc"; }
	HAMON_CONSTEXPR static const char8_t* abcd() { return u8"abcd"; }
	HAMON_CONSTEXPR static const char8_t* abc() { return u8"abc"; }
	HAMON_CONSTEXPR static const char8_t* ab() { return u8"ab"; }
	HAMON_CONSTEXPR static const char8_t* abbccc() { return u8"abbccc"; }
	HAMON_CONSTEXPR static const char8_t* abcde() { return u8"abcde"; }
	HAMON_CONSTEXPR static const char8_t* abb() { return u8"abb"; }
	HAMON_CONSTEXPR static const char8_t* bcde() { return u8"bcde"; }
	HAMON_CONSTEXPR static const char8_t* bcd() { return u8"bcd"; }
	HAMON_CONSTEXPR static const char8_t* edcba() { return u8"edcba"; }
	HAMON_CONSTEXPR static const char8_t* ABCDE() { return u8"ABCDE"; }
	HAMON_CONSTEXPR static const char8_t* long_str() { return u8"The quick brown fox jumps over the lazy dog"; }
};
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
template <>
struct StringTestHelper<char16_t>
{
	HAMON_CONSTEXPR static const char16_t* aababc() { return u"aababc"; }
	HAMON_CONSTEXPR static const char16_t* abcd() { return u"abcd"; }
	HAMON_CONSTEXPR static const char16_t* abc() { return u"abc"; }
	HAMON_CONSTEXPR static const char16_t* ab() { return u"ab"; }
	HAMON_CONSTEXPR static const char16_t* abbccc() { return u"abbccc"; }
	HAMON_CONSTEXPR static const char16_t* abcde() { return u"abcde"; }
	HAMON_CONSTEXPR static const char16_t* abb() { return u"abb"; }
	HAMON_CONSTEXPR static const char16_t* bcde() { return u"bcde"; }
	HAMON_CONSTEXPR static const char16_t* bcd() { return u"bcd"; }
	HAMON_CONSTEXPR static const char16_t* edcba() { return u"edcba"; }
	HAMON_CONSTEXPR static const char16_t* ABCDE() { return u"ABCDE"; }
	HAMON_CONSTEXPR static const char16_t* long_str() { return u"The quick brown fox jumps over the lazy dog"; }
};
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
template <>
struct StringTestHelper<char32_t>
{
	HAMON_CONSTEXPR static const char32_t* aababc() { return U"aababc"; }
	HAMON_CONSTEXPR static const char32_t* abcd() { return U"abcd"; }
	HAMON_CONSTEXPR static const char32_t* abc() { return U"abc"; }
	HAMON_CONSTEXPR static const char32_t* ab() { return U"ab"; }
	HAMON_CONSTEXPR static const char32_t* abbccc() { return U"abbccc"; }
	HAMON_CONSTEXPR static const char32_t* abcde() { return U"abcde"; }
	HAMON_CONSTEXPR static const char32_t* abb() { return U"abb"; }
	HAMON_CONSTEXPR static const char32_t* bcde() { return U"bcde"; }
	HAMON_CONSTEXPR static const char32_t* bcd() { return U"bcd"; }
	HAMON_CONSTEXPR static const char32_t* edcba() { return U"edcba"; }
	HAMON_CONSTEXPR static const char32_t* ABCDE() { return U"ABCDE"; }
	HAMON_CONSTEXPR static const char32_t* long_str() { return U"The quick brown fox jumps over the lazy dog"; }
};
#endif

}	// namespace string_test
}	// namespace hamon_test

#endif // UNIT_TEST_STRING_STRING_TEST_HELPER_HPP
