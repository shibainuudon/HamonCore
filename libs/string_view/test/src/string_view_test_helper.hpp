/**
 *	@file	string_view_test_helper.hpp
 *
 *	@brief	
 */

#ifndef UNIT_TEST_STRING_VIEW_STRING_VIEW_TEST_HELPER_HPP
#define UNIT_TEST_STRING_VIEW_STRING_VIEW_TEST_HELPER_HPP

#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_test
{
namespace string_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
class StringViewTest : public ::testing::Test {};

using StringViewTestTypes =
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

TYPED_TEST_SUITE(StringViewTest, StringViewTestTypes);

template <typename CharT>
struct StringViewTestHelper;

template <>
struct StringViewTestHelper<char>
{
	
	HAMON_CONSTEXPR static const char* foo_bar()    { return "foo bar"; }
	HAMON_CONSTEXPR static const char* with_nulls() { return "This contains \0 a zero byte."; }
	HAMON_CONSTEXPR static const char* aababc()     { return "aababc"; }
	HAMON_CONSTEXPR static const char* abcd()       { return "abcd"; }
	HAMON_CONSTEXPR static const char* ab()         { return "ab"; }
	HAMON_CONSTEXPR static const char* cd()         { return "cd"; }
};

template <>
struct StringViewTestHelper<wchar_t>
{
	HAMON_CONSTEXPR static const wchar_t* foo_bar()    { return L"foo bar"; }
	HAMON_CONSTEXPR static const wchar_t* with_nulls() { return L"This contains \0 a zero byte."; }
	HAMON_CONSTEXPR static const wchar_t* aababc()     { return L"aababc"; }
	HAMON_CONSTEXPR static const wchar_t* abcd()       { return L"abcd"; }
	HAMON_CONSTEXPR static const wchar_t* ab()         { return L"ab"; }
	HAMON_CONSTEXPR static const wchar_t* cd()         { return L"cd"; }
};

#if defined(HAMON_HAS_CXX20_CHAR8_T)
template <>
struct StringViewTestHelper<char8_t>
{
	HAMON_CONSTEXPR static const char8_t* foo_bar()    { return u8"foo bar"; }
	HAMON_CONSTEXPR static const char8_t* with_nulls() { return u8"This contains \0 a zero byte."; }
	HAMON_CONSTEXPR static const char8_t* aababc()     { return u8"aababc"; }
	HAMON_CONSTEXPR static const char8_t* abcd()       { return u8"abcd"; }
	HAMON_CONSTEXPR static const char8_t* ab()         { return u8"ab"; }
	HAMON_CONSTEXPR static const char8_t* cd()         { return u8"cd"; }
};
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
template <>
struct StringViewTestHelper<char16_t>
{
	HAMON_CONSTEXPR static const char16_t* foo_bar()    { return u"foo bar"; }
	HAMON_CONSTEXPR static const char16_t* with_nulls() { return u"This contains \0 a zero byte."; }
	HAMON_CONSTEXPR static const char16_t* aababc()     { return u"aababc"; }
	HAMON_CONSTEXPR static const char16_t* abcd()       { return u"abcd"; }
	HAMON_CONSTEXPR static const char16_t* ab()         { return u"ab"; }
	HAMON_CONSTEXPR static const char16_t* cd()         { return u"cd"; }
};
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
template <>
struct StringViewTestHelper<char32_t>
{
	HAMON_CONSTEXPR static const char32_t* foo_bar()    { return U"foo bar"; }
	HAMON_CONSTEXPR static const char32_t* with_nulls() { return U"This contains \0 a zero byte."; }
	HAMON_CONSTEXPR static const char32_t* aababc()     { return U"aababc"; }
	HAMON_CONSTEXPR static const char32_t* abcd()       { return U"abcd"; }
	HAMON_CONSTEXPR static const char32_t* ab()         { return U"ab"; }
	HAMON_CONSTEXPR static const char32_t* cd()         { return U"cd"; }
};
#endif

}	// namespace string_view_test
}	// namespace hamon_test

#endif // UNIT_TEST_STRING_VIEW_STRING_VIEW_TEST_HELPER_HPP
