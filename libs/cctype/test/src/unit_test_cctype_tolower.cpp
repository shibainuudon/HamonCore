/**
 *	@file	unit_test_cctype_tolower.cpp
 *
 *	@brief	tolower のテスト
 */

#include <hamon/cctype/tolower.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace cctype_test {
namespace tolower_test {

template <typename T>
void test()
{
	// control codes (NUL, etc.)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00), hamon::tolower(T(0x00)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x01), hamon::tolower(T(0x01)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x02), hamon::tolower(T(0x02)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x03), hamon::tolower(T(0x03)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x04), hamon::tolower(T(0x04)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x05), hamon::tolower(T(0x05)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x06), hamon::tolower(T(0x06)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x07), hamon::tolower(T(0x07)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x08), hamon::tolower(T(0x08)));

	// tab (\t)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x09), hamon::tolower(T(0x09)));

	// whitespaces (\n, \v, \f, \r)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0A), hamon::tolower(T(0x0A)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0B), hamon::tolower(T(0x0B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0C), hamon::tolower(T(0x0C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0D), hamon::tolower(T(0x0D)));

	// control codes
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0E), hamon::tolower(T(0x0E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0F), hamon::tolower(T(0x0F)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x10), hamon::tolower(T(0x10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x11), hamon::tolower(T(0x11)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x12), hamon::tolower(T(0x12)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x13), hamon::tolower(T(0x13)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x14), hamon::tolower(T(0x14)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x15), hamon::tolower(T(0x15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x16), hamon::tolower(T(0x16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x17), hamon::tolower(T(0x17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x18), hamon::tolower(T(0x18)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x19), hamon::tolower(T(0x19)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1A), hamon::tolower(T(0x1A)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1B), hamon::tolower(T(0x1B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1C), hamon::tolower(T(0x1C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1D), hamon::tolower(T(0x1D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1E), hamon::tolower(T(0x1E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1F), hamon::tolower(T(0x1F)));

	// space
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x20), hamon::tolower(T(0x20)));

	// !"#$%&'()*+,-./
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x21), hamon::tolower(T(0x21)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x22), hamon::tolower(T(0x22)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x23), hamon::tolower(T(0x23)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x24), hamon::tolower(T(0x24)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x25), hamon::tolower(T(0x25)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x26), hamon::tolower(T(0x26)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x27), hamon::tolower(T(0x27)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x28), hamon::tolower(T(0x28)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x29), hamon::tolower(T(0x29)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2A), hamon::tolower(T(0x2A)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2B), hamon::tolower(T(0x2B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2C), hamon::tolower(T(0x2C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2D), hamon::tolower(T(0x2D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2E), hamon::tolower(T(0x2E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2F), hamon::tolower(T(0x2F)));

	// 0123456789
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x30), hamon::tolower(T(0x30)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x31), hamon::tolower(T(0x31)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x32), hamon::tolower(T(0x32)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x33), hamon::tolower(T(0x33)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x34), hamon::tolower(T(0x34)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x35), hamon::tolower(T(0x35)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x36), hamon::tolower(T(0x36)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x37), hamon::tolower(T(0x37)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x38), hamon::tolower(T(0x38)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x39), hamon::tolower(T(0x39)));

	// :;<=>?@
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x3A), hamon::tolower(T(0x3A)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x3B), hamon::tolower(T(0x3B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x3C), hamon::tolower(T(0x3C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x3D), hamon::tolower(T(0x3D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x3E), hamon::tolower(T(0x3E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x3F), hamon::tolower(T(0x3F)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x40), hamon::tolower(T(0x40)));

	// ABCDEF
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x61), hamon::tolower(T(0x41)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x62), hamon::tolower(T(0x42)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x63), hamon::tolower(T(0x43)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x64), hamon::tolower(T(0x44)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x65), hamon::tolower(T(0x45)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x66), hamon::tolower(T(0x46)));

	// GHIJKLMNOPQRSTUVWXYZ
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x67), hamon::tolower(T(0x47)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x68), hamon::tolower(T(0x48)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x69), hamon::tolower(T(0x49)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x6A), hamon::tolower(T(0x4A)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x6B), hamon::tolower(T(0x4B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x6C), hamon::tolower(T(0x4C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x6D), hamon::tolower(T(0x4D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x6E), hamon::tolower(T(0x4E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x6F), hamon::tolower(T(0x4F)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x70), hamon::tolower(T(0x50)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x71), hamon::tolower(T(0x51)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x72), hamon::tolower(T(0x52)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x73), hamon::tolower(T(0x53)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x74), hamon::tolower(T(0x54)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x75), hamon::tolower(T(0x55)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x76), hamon::tolower(T(0x56)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x77), hamon::tolower(T(0x57)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x78), hamon::tolower(T(0x58)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x79), hamon::tolower(T(0x59)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x7A), hamon::tolower(T(0x5A)));

	// [\]^_`
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x5B), hamon::tolower(T(0x5B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x5C), hamon::tolower(T(0x5C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x5D), hamon::tolower(T(0x5D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x5E), hamon::tolower(T(0x5E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x5F), hamon::tolower(T(0x5F)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x60), hamon::tolower(T(0x60)));

	// abcdef
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x61), hamon::tolower(T(0x61)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x62), hamon::tolower(T(0x62)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x63), hamon::tolower(T(0x63)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x64), hamon::tolower(T(0x64)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x65), hamon::tolower(T(0x65)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x66), hamon::tolower(T(0x66)));

	// ghijklmnopqrstuvwxyz
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x67), hamon::tolower(T(0x67)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x68), hamon::tolower(T(0x68)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x69), hamon::tolower(T(0x69)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x6A), hamon::tolower(T(0x6A)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x6B), hamon::tolower(T(0x6B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x6C), hamon::tolower(T(0x6C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x6D), hamon::tolower(T(0x6D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x6E), hamon::tolower(T(0x6E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x6F), hamon::tolower(T(0x6F)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x70), hamon::tolower(T(0x70)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x71), hamon::tolower(T(0x71)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x72), hamon::tolower(T(0x72)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x73), hamon::tolower(T(0x73)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x74), hamon::tolower(T(0x74)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x75), hamon::tolower(T(0x75)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x76), hamon::tolower(T(0x76)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x77), hamon::tolower(T(0x77)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x78), hamon::tolower(T(0x78)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x79), hamon::tolower(T(0x79)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x7A), hamon::tolower(T(0x7A)));

	// {|}~
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x7B), hamon::tolower(T(0x7B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x7C), hamon::tolower(T(0x7C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x7D), hamon::tolower(T(0x7D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x7E), hamon::tolower(T(0x7E)));

	// backspace character (DEL)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x7F), hamon::tolower(T(0x7F)));

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4310)	// キャストによって定数値が切り捨てられました。
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x80), hamon::tolower(T(0x80)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0xFF), hamon::tolower(T(0xFF)));
HAMON_WARNING_POP()
}

GTEST_TEST(CCTypeTest, ToLowerTest)
{
	test<char>();
	test<wchar_t>();
#if defined(HAMON_HAS_CXX20_CHAR8_T)
	test<char8_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	test<char16_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	test<char32_t>();
#endif
}

}	// namespace tolower_test
}	// namespace cctype_test
