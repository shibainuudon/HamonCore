/**
 *	@file	unit_test_cstring_strlen.cpp
 *
 *	@brief	strlenのテスト
 */

#include <hamon/cstring/strlen.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(CStringTest, StrLenTest)
{
	// hamon::ct::strlen
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0u, hamon::ct::strlen(""));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3u, hamon::ct::strlen("abc"));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11u, hamon::ct::strlen("Hello World"));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4u, hamon::ct::strlen("Hell\0o World"));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0u, hamon::ct::strlen(L""));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3u, hamon::ct::strlen(L"abc"));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11u, hamon::ct::strlen(L"Hello World"));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4u, hamon::ct::strlen(L"Hell\0o World"));

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0u, hamon::ct::strlen(u8""));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3u, hamon::ct::strlen(u8"abc"));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11u, hamon::ct::strlen(u8"Hello World"));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4u, hamon::ct::strlen(u8"Hell\0o World"));
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0u, hamon::ct::strlen(u""));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3u, hamon::ct::strlen(u"abc"));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11u, hamon::ct::strlen(u"Hello World"));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4u, hamon::ct::strlen(u"Hell\0o World"));
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0u, hamon::ct::strlen(U""));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 3u, hamon::ct::strlen(U"abc"));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(11u, hamon::ct::strlen(U"Hello World"));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 4u, hamon::ct::strlen(U"Hell\0o World"));
#endif

	// hamon::strlen
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 0u, hamon::strlen(""));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 3u, hamon::strlen("abc"));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ(11u, hamon::strlen("Hello World"));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::strlen("Hell\0o World"));

	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 0u, hamon::strlen(L""));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 3u, hamon::strlen(L"abc"));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ(11u, hamon::strlen(L"Hello World"));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::strlen(L"Hell\0o World"));

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 0u, hamon::strlen(u8""));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 3u, hamon::strlen(u8"abc"));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ(11u, hamon::strlen(u8"Hello World"));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::strlen(u8"Hell\0o World"));
#endif

#if defined(HAMON_HAS_CXX11_CHAR16_T)
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 0u, hamon::strlen(u""));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 3u, hamon::strlen(u"abc"));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ(11u, hamon::strlen(u"Hello World"));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::strlen(u"Hell\0o World"));
#endif

#if defined(HAMON_HAS_CXX11_CHAR32_T)
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 0u, hamon::strlen(U""));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 3u, hamon::strlen(U"abc"));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ(11u, hamon::strlen(U"Hello World"));
	HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::strlen(U"Hell\0o World"));
#endif

	// long string
	{
		hamon::size_t const length = 1024 * 1024;
		hamon::string s(length, 42);
		EXPECT_EQ(length, hamon::strlen(s.c_str()));
	}
	{
		hamon::size_t const length = 1024 * 1024;
		hamon::wstring s(length, 42);
		EXPECT_EQ(length, hamon::strlen(s.c_str()));
	}
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	{
		hamon::size_t const length = 1024 * 1024;
		hamon::u8string s(length, 42);
		EXPECT_EQ(length, hamon::strlen(s.c_str()));
	}
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	{
		hamon::size_t const length = 1024 * 1024;
		hamon::u16string s(length, 42);
		EXPECT_EQ(length, hamon::strlen(s.c_str()));
	}
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	{
		hamon::size_t const length = 1024 * 1024;
		hamon::u32string s(length, 42);
		EXPECT_EQ(length, hamon::strlen(s.c_str()));
	}
#endif
}
