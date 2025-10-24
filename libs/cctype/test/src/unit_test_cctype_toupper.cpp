/**
 *	@file	unit_test_cctype_toupper.cpp
 *
 *	@brief	toupper のテスト
 */

#include <hamon/cctype/toupper.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace cctype_test {
namespace toupper_test {

template <typename T>
void test()
{
	// control codes (NUL, etc.)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x00), hamon::toupper(T(0x00)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x01), hamon::toupper(T(0x01)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x02), hamon::toupper(T(0x02)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x03), hamon::toupper(T(0x03)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x04), hamon::toupper(T(0x04)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x05), hamon::toupper(T(0x05)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x06), hamon::toupper(T(0x06)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x07), hamon::toupper(T(0x07)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x08), hamon::toupper(T(0x08)));

	// tab (\t)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x09), hamon::toupper(T(0x09)));

	// whitespaces (\n, \v, \f, \r)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0A), hamon::toupper(T(0x0A)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0B), hamon::toupper(T(0x0B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0C), hamon::toupper(T(0x0C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0D), hamon::toupper(T(0x0D)));

	// control codes
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0E), hamon::toupper(T(0x0E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x0F), hamon::toupper(T(0x0F)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x10), hamon::toupper(T(0x10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x11), hamon::toupper(T(0x11)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x12), hamon::toupper(T(0x12)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x13), hamon::toupper(T(0x13)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x14), hamon::toupper(T(0x14)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x15), hamon::toupper(T(0x15)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x16), hamon::toupper(T(0x16)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x17), hamon::toupper(T(0x17)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x18), hamon::toupper(T(0x18)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x19), hamon::toupper(T(0x19)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1A), hamon::toupper(T(0x1A)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1B), hamon::toupper(T(0x1B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1C), hamon::toupper(T(0x1C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1D), hamon::toupper(T(0x1D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1E), hamon::toupper(T(0x1E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x1F), hamon::toupper(T(0x1F)));

	// space
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x20), hamon::toupper(T(0x20)));

	// !"#$%&'()*+,-./
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x21), hamon::toupper(T(0x21)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x22), hamon::toupper(T(0x22)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x23), hamon::toupper(T(0x23)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x24), hamon::toupper(T(0x24)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x25), hamon::toupper(T(0x25)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x26), hamon::toupper(T(0x26)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x27), hamon::toupper(T(0x27)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x28), hamon::toupper(T(0x28)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x29), hamon::toupper(T(0x29)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2A), hamon::toupper(T(0x2A)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2B), hamon::toupper(T(0x2B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2C), hamon::toupper(T(0x2C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2D), hamon::toupper(T(0x2D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2E), hamon::toupper(T(0x2E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x2F), hamon::toupper(T(0x2F)));

	// 0123456789
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x30), hamon::toupper(T(0x30)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x31), hamon::toupper(T(0x31)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x32), hamon::toupper(T(0x32)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x33), hamon::toupper(T(0x33)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x34), hamon::toupper(T(0x34)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x35), hamon::toupper(T(0x35)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x36), hamon::toupper(T(0x36)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x37), hamon::toupper(T(0x37)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x38), hamon::toupper(T(0x38)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x39), hamon::toupper(T(0x39)));

	// :;<=>?@
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x3A), hamon::toupper(T(0x3A)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x3B), hamon::toupper(T(0x3B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x3C), hamon::toupper(T(0x3C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x3D), hamon::toupper(T(0x3D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x3E), hamon::toupper(T(0x3E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x3F), hamon::toupper(T(0x3F)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x40), hamon::toupper(T(0x40)));

	// ABCDEF
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x41), hamon::toupper(T(0x41)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x42), hamon::toupper(T(0x42)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x43), hamon::toupper(T(0x43)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x44), hamon::toupper(T(0x44)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x45), hamon::toupper(T(0x45)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x46), hamon::toupper(T(0x46)));

	// GHIJKLMNOPQRSTUVWXYZ
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x47), hamon::toupper(T(0x47)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x48), hamon::toupper(T(0x48)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x49), hamon::toupper(T(0x49)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4A), hamon::toupper(T(0x4A)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4B), hamon::toupper(T(0x4B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4C), hamon::toupper(T(0x4C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4D), hamon::toupper(T(0x4D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4E), hamon::toupper(T(0x4E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4F), hamon::toupper(T(0x4F)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x50), hamon::toupper(T(0x50)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x51), hamon::toupper(T(0x51)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x52), hamon::toupper(T(0x52)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x53), hamon::toupper(T(0x53)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x54), hamon::toupper(T(0x54)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x55), hamon::toupper(T(0x55)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x56), hamon::toupper(T(0x56)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x57), hamon::toupper(T(0x57)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x58), hamon::toupper(T(0x58)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x59), hamon::toupper(T(0x59)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x5A), hamon::toupper(T(0x5A)));

	// [\]^_`
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x5B), hamon::toupper(T(0x5B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x5C), hamon::toupper(T(0x5C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x5D), hamon::toupper(T(0x5D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x5E), hamon::toupper(T(0x5E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x5F), hamon::toupper(T(0x5F)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x60), hamon::toupper(T(0x60)));

	// abcdef
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x41), hamon::toupper(T(0x61)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x42), hamon::toupper(T(0x62)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x43), hamon::toupper(T(0x63)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x44), hamon::toupper(T(0x64)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x45), hamon::toupper(T(0x65)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x46), hamon::toupper(T(0x66)));

	// ghijklmnopqrstuvwxyz
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x47), hamon::toupper(T(0x67)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x48), hamon::toupper(T(0x68)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x49), hamon::toupper(T(0x69)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4A), hamon::toupper(T(0x6A)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4B), hamon::toupper(T(0x6B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4C), hamon::toupper(T(0x6C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4D), hamon::toupper(T(0x6D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4E), hamon::toupper(T(0x6E)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x4F), hamon::toupper(T(0x6F)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x50), hamon::toupper(T(0x70)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x51), hamon::toupper(T(0x71)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x52), hamon::toupper(T(0x72)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x53), hamon::toupper(T(0x73)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x54), hamon::toupper(T(0x74)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x55), hamon::toupper(T(0x75)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x56), hamon::toupper(T(0x76)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x57), hamon::toupper(T(0x77)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x58), hamon::toupper(T(0x78)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x59), hamon::toupper(T(0x79)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x5A), hamon::toupper(T(0x7A)));

	// {|}~
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x7B), hamon::toupper(T(0x7B)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x7C), hamon::toupper(T(0x7C)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x7D), hamon::toupper(T(0x7D)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x7E), hamon::toupper(T(0x7E)));

	// backspace character (DEL)
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x7F), hamon::toupper(T(0x7F)));

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4310)	// キャストによって定数値が切り捨てられました。
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0x80), hamon::toupper(T(0x80)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0xFF), hamon::toupper(T(0xFF)));
HAMON_WARNING_POP()
}

GTEST_TEST(CCTypeTest, ToUpperTest)
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

}	// namespace toupper_test
}	// namespace cctype_test
