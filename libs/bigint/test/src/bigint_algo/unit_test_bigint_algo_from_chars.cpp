/**
 *	@file	unit_test_bigint_algo_from_chars.cpp
 *
 *	@brief	bigint_algo::from_chars のテスト
 */

#include <hamon/bigint/bigint_algo/from_chars.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/string_view.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_from_chars_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool
FromCharsTest(hamon::string_view sv, int base, T const& expected, hamon::size_t length = hamon::string_view::npos, hamon::errc ec = {})
{
	if (length == hamon::string_view::npos)
	{
		length = sv.length();
	}

	T value{0};
	auto ret = hamon::bigint_algo::from_chars(sv.data(), sv.data() + sv.size(), value, base);
	VERIFY(value == expected);
	VERIFY(ret.ptr == sv.data() + length);
	VERIFY(ret.ec == ec);

	return true;
}

GTEST_TEST(BigIntAlgoTest, FromCharsTest)
{
	{
		using Vector = hamon::vector<hamon::uint8_t>;
		EXPECT_TRUE(FromCharsTest("0",                             10, Vector{0x00}));
		EXPECT_TRUE(FromCharsTest("1",                             10, Vector{0x01}));
		EXPECT_TRUE(FromCharsTest("12",                            10, Vector{0x0C}));
		EXPECT_TRUE(FromCharsTest("123",                           10, Vector{0x7B}));
		EXPECT_TRUE(FromCharsTest("1234",                          10, Vector{0xD2, 0x04}));
		EXPECT_TRUE(FromCharsTest("12345",                         10, Vector{0x39, 0x30}));
		EXPECT_TRUE(FromCharsTest("123456",                        10, Vector{0x40, 0xE2, 0x01}));
		EXPECT_TRUE(FromCharsTest("1234567",                       10, Vector{0x87, 0xD6, 0x12}));
		EXPECT_TRUE(FromCharsTest("12345678",                      10, Vector{0x4E, 0x61, 0xBC}));
		EXPECT_TRUE(FromCharsTest("123456789",                     10, Vector{0x15, 0xCD, 0x5B, 0x07}));
		EXPECT_TRUE(FromCharsTest("1234567890",                    10, Vector{0xD2, 0x02, 0x96, 0x49}));
		EXPECT_TRUE(FromCharsTest("12345678901",                   10, Vector{0x35, 0x1C, 0xDC, 0xDF, 0x02}));
		EXPECT_TRUE(FromCharsTest("123456789012",                  10, Vector{0x14, 0x1A, 0x99, 0xBE, 0x1C}));
		EXPECT_TRUE(FromCharsTest("1234567890123",                 10, Vector{0xCB, 0x04, 0xFB, 0x71, 0x1F, 0x01}));
		EXPECT_TRUE(FromCharsTest("12345678901234",                10, Vector{0xF2, 0x2F, 0xCE, 0x73, 0x3A, 0x0B}));
		EXPECT_TRUE(FromCharsTest("123456789012345",               10, Vector{0x79, 0xDF, 0x0D, 0x86, 0x48, 0x70}));
		EXPECT_TRUE(FromCharsTest("1234567890123456",              10, Vector{0xC0, 0xBA, 0x8A, 0x3C, 0xD5, 0x62, 0x04}));
		EXPECT_TRUE(FromCharsTest("12345678901234567",             10, Vector{0x87, 0x4B, 0x6B, 0x5D, 0x54, 0xDC, 0x2B}));
		EXPECT_TRUE(FromCharsTest("123456789012345678",            10, Vector{0x4E, 0xF3, 0x30, 0xA6, 0x4B, 0x9B, 0xB6, 0x01}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789",           10, Vector{0x15, 0x81, 0xE9, 0x7D, 0xF4, 0x10, 0x22, 0x11}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890",          10, Vector{0xD2, 0x0A, 0x1F, 0xEB, 0x8C, 0xA9, 0x54, 0xAB}));
		EXPECT_TRUE(FromCharsTest("123456789012345678901",         10, Vector{0x35, 0x6C, 0x36, 0x2F, 0x81, 0x9F, 0x4E, 0xB1, 0x06}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789012",        10, Vector{0x14, 0x3A, 0x20, 0xD8, 0x0B, 0x3B, 0x12, 0xED, 0x42}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890123",       10, Vector{0xCB, 0x44, 0x42, 0x71, 0x76, 0x4E, 0xB6, 0x42, 0x9D, 0x02}));
		EXPECT_TRUE(FromCharsTest("123456789012345678901234",      10, Vector{0xF2, 0xAF, 0x96, 0x6C, 0xA0, 0x10, 0x1F, 0x9B, 0x24, 0x1A}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789012345",     10, Vector{0x79, 0xDF, 0xE2, 0x3D, 0x44, 0xA6, 0x36, 0x0F, 0x6E, 0x05, 0x01}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890123456",    10, Vector{0xC0, 0xBA, 0xDC, 0x6A, 0xAA, 0x7E, 0x22, 0x98, 0x4C, 0x36, 0x0A}));
		EXPECT_TRUE(FromCharsTest("123456789012345678901234567",   10, Vector{0x87, 0x4B, 0x9F, 0x2C, 0xA8, 0xF2, 0x58, 0xF1, 0xFD, 0x1E, 0x66}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789012345678",  10, Vector{0x4E, 0xF3, 0x38, 0xBE, 0x91, 0x7A, 0x79, 0x6D, 0xEB, 0x35, 0xFD, 0x03}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890123456789", 10, Vector{0x15, 0x81, 0x39, 0x6E, 0xB1, 0xC9, 0xBE, 0x46, 0x32, 0x1B, 0xE4, 0x27}));
	}
	{
		using Vector = hamon::vector<hamon::uint16_t>;
		EXPECT_TRUE(FromCharsTest("0",                             10, Vector{0x0000}));
		EXPECT_TRUE(FromCharsTest("1",                             10, Vector{0x0001}));
		EXPECT_TRUE(FromCharsTest("12",                            10, Vector{0x000C}));
		EXPECT_TRUE(FromCharsTest("123",                           10, Vector{0x007B}));
		EXPECT_TRUE(FromCharsTest("1234",                          10, Vector{0x04D2}));
		EXPECT_TRUE(FromCharsTest("12345",                         10, Vector{0x3039}));
		EXPECT_TRUE(FromCharsTest("123456",                        10, Vector{0xE240, 0x0001}));
		EXPECT_TRUE(FromCharsTest("1234567",                       10, Vector{0xD687, 0x0012}));
		EXPECT_TRUE(FromCharsTest("12345678",                      10, Vector{0x614E, 0x00BC}));
		EXPECT_TRUE(FromCharsTest("123456789",                     10, Vector{0xCD15, 0x075B}));
		EXPECT_TRUE(FromCharsTest("1234567890",                    10, Vector{0x02D2, 0x4996}));
		EXPECT_TRUE(FromCharsTest("12345678901",                   10, Vector{0x1C35, 0xDFDC, 0x0002}));
		EXPECT_TRUE(FromCharsTest("123456789012",                  10, Vector{0x1A14, 0xBE99, 0x001C}));
		EXPECT_TRUE(FromCharsTest("1234567890123",                 10, Vector{0x04CB, 0x71FB, 0x011F}));
		EXPECT_TRUE(FromCharsTest("12345678901234",                10, Vector{0x2FF2, 0x73CE, 0x0B3A}));
		EXPECT_TRUE(FromCharsTest("123456789012345",               10, Vector{0xDF79, 0x860D, 0x7048}));
		EXPECT_TRUE(FromCharsTest("1234567890123456",              10, Vector{0xBAC0, 0x3C8A, 0x62D5, 0x0004}));
		EXPECT_TRUE(FromCharsTest("12345678901234567",             10, Vector{0x4B87, 0x5D6B, 0xDC54, 0x002B}));
		EXPECT_TRUE(FromCharsTest("123456789012345678",            10, Vector{0xF34E, 0xA630, 0x9B4B, 0x01B6}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789",           10, Vector{0x8115, 0x7DE9, 0x10F4, 0x1122}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890",          10, Vector{0x0AD2, 0xEB1F, 0xA98C, 0xAB54}));
		EXPECT_TRUE(FromCharsTest("123456789012345678901",         10, Vector{0x6C35, 0x2F36, 0x9F81, 0xB14E, 0x0006}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789012",        10, Vector{0x3A14, 0xD820, 0x3B0B, 0xED12, 0x0042}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890123",       10, Vector{0x44CB, 0x7142, 0x4E76, 0x42B6, 0x029D}));
		EXPECT_TRUE(FromCharsTest("123456789012345678901234",      10, Vector{0xAFF2, 0x6C96, 0x10A0, 0x9B1F, 0x1A24}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789012345",     10, Vector{0xDF79, 0x3DE2, 0xA644, 0x0F36, 0x056E, 0x0001}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890123456",    10, Vector{0xBAC0, 0x6ADC, 0x7EAA, 0x9822, 0x364C, 0x000A}));
		EXPECT_TRUE(FromCharsTest("123456789012345678901234567",   10, Vector{0x4B87, 0x2C9F, 0xF2A8, 0xF158, 0x1EFD, 0x0066}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789012345678",  10, Vector{0xF34E, 0xBE38, 0x7A91, 0x6D79, 0x35EB, 0x03FD}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890123456789", 10, Vector{0x8115, 0x6E39, 0xC9B1, 0x46BE, 0x1B32, 0x27E4}));
	}
	{
		using Vector = hamon::vector<hamon::uint32_t>;
		EXPECT_TRUE(FromCharsTest("0",                             10, Vector{0x00000000}));
		EXPECT_TRUE(FromCharsTest("1",                             10, Vector{0x00000001}));
		EXPECT_TRUE(FromCharsTest("12",                            10, Vector{0x0000000C}));
		EXPECT_TRUE(FromCharsTest("123",                           10, Vector{0x0000007B}));
		EXPECT_TRUE(FromCharsTest("1234",                          10, Vector{0x000004D2}));
		EXPECT_TRUE(FromCharsTest("12345",                         10, Vector{0x00003039}));
		EXPECT_TRUE(FromCharsTest("123456",                        10, Vector{0x0001E240}));
		EXPECT_TRUE(FromCharsTest("1234567",                       10, Vector{0x0012D687}));
		EXPECT_TRUE(FromCharsTest("12345678",                      10, Vector{0x00BC614E}));
		EXPECT_TRUE(FromCharsTest("123456789",                     10, Vector{0x075BCD15}));
		EXPECT_TRUE(FromCharsTest("1234567890",                    10, Vector{0x499602D2}));
		EXPECT_TRUE(FromCharsTest("12345678901",                   10, Vector{0xDFDC1C35, 0x00000002}));
		EXPECT_TRUE(FromCharsTest("123456789012",                  10, Vector{0xBE991A14, 0x0000001C}));
		EXPECT_TRUE(FromCharsTest("1234567890123",                 10, Vector{0x71FB04CB, 0x0000011F}));
		EXPECT_TRUE(FromCharsTest("12345678901234",                10, Vector{0x73CE2FF2, 0x00000B3A}));
		EXPECT_TRUE(FromCharsTest("123456789012345",               10, Vector{0x860DDF79, 0x00007048}));
		EXPECT_TRUE(FromCharsTest("1234567890123456",              10, Vector{0x3C8ABAC0, 0x000462D5}));
		EXPECT_TRUE(FromCharsTest("12345678901234567",             10, Vector{0x5D6B4B87, 0x002BDC54}));
		EXPECT_TRUE(FromCharsTest("123456789012345678",            10, Vector{0xA630F34E, 0x01B69B4B}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789",           10, Vector{0x7DE98115, 0x112210F4}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890",          10, Vector{0xEB1F0AD2, 0xAB54A98C}));
		EXPECT_TRUE(FromCharsTest("123456789012345678901",         10, Vector{0x2F366C35, 0xB14E9F81, 0x00000006}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789012",        10, Vector{0xD8203A14, 0xED123B0B, 0x00000042}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890123",       10, Vector{0x714244CB, 0x42B64E76, 0x0000029D}));
		EXPECT_TRUE(FromCharsTest("123456789012345678901234",      10, Vector{0x6C96AFF2, 0x9B1F10A0, 0x00001A24}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789012345",     10, Vector{0x3DE2DF79, 0x0F36A644, 0x0001056E}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890123456",    10, Vector{0x6ADCBAC0, 0x98227EAA, 0x000A364C}));
		EXPECT_TRUE(FromCharsTest("123456789012345678901234567",   10, Vector{0x2C9F4B87, 0xF158F2A8, 0x00661EFD}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789012345678",  10, Vector{0xBE38F34E, 0x6D797A91, 0x03FD35EB}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890123456789", 10, Vector{0x6E398115, 0x46BEC9B1, 0x27E41B32}));
	}
	{
		using Vector = hamon::vector<hamon::uint64_t>;
		EXPECT_TRUE(FromCharsTest("0",                             10, Vector{0x0000000000000000}));
		EXPECT_TRUE(FromCharsTest("1",                             10, Vector{0x0000000000000001}));
		EXPECT_TRUE(FromCharsTest("12",                            10, Vector{0x000000000000000C}));
		EXPECT_TRUE(FromCharsTest("123",                           10, Vector{0x000000000000007B}));
		EXPECT_TRUE(FromCharsTest("1234",                          10, Vector{0x00000000000004D2}));
		EXPECT_TRUE(FromCharsTest("12345",                         10, Vector{0x0000000000003039}));
		EXPECT_TRUE(FromCharsTest("123456",                        10, Vector{0x000000000001E240}));
		EXPECT_TRUE(FromCharsTest("1234567",                       10, Vector{0x000000000012D687}));
		EXPECT_TRUE(FromCharsTest("12345678",                      10, Vector{0x0000000000BC614E}));
		EXPECT_TRUE(FromCharsTest("123456789",                     10, Vector{0x00000000075BCD15}));
		EXPECT_TRUE(FromCharsTest("1234567890",                    10, Vector{0x00000000499602D2}));
		EXPECT_TRUE(FromCharsTest("12345678901",                   10, Vector{0x00000002DFDC1C35}));
		EXPECT_TRUE(FromCharsTest("123456789012",                  10, Vector{0x0000001CBE991A14}));
		EXPECT_TRUE(FromCharsTest("1234567890123",                 10, Vector{0x0000011F71FB04CB}));
		EXPECT_TRUE(FromCharsTest("12345678901234",                10, Vector{0x00000B3A73CE2FF2}));
		EXPECT_TRUE(FromCharsTest("123456789012345",               10, Vector{0x00007048860DDF79}));
		EXPECT_TRUE(FromCharsTest("1234567890123456",              10, Vector{0x000462D53C8ABAC0}));
		EXPECT_TRUE(FromCharsTest("12345678901234567",             10, Vector{0x002BDC545D6B4B87}));
		EXPECT_TRUE(FromCharsTest("123456789012345678",            10, Vector{0x01B69B4BA630F34E}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789",           10, Vector{0x112210F47DE98115}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890",          10, Vector{0xAB54A98CEB1F0AD2}));
		EXPECT_TRUE(FromCharsTest("123456789012345678901",         10, Vector{0xB14E9F812F366C35, 0x0000000000000006}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789012",        10, Vector{0xED123B0BD8203A14, 0x0000000000000042}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890123",       10, Vector{0x42B64E76714244CB, 0x000000000000029D}));
		EXPECT_TRUE(FromCharsTest("123456789012345678901234",      10, Vector{0x9B1F10A06C96AFF2, 0x0000000000001A24}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789012345",     10, Vector{0x0F36A6443DE2DF79, 0x000000000001056E}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890123456",    10, Vector{0x98227EAA6ADCBAC0, 0x00000000000A364C}));
		EXPECT_TRUE(FromCharsTest("123456789012345678901234567",   10, Vector{0xF158F2A82C9F4B87, 0x0000000000661EFD}));
		EXPECT_TRUE(FromCharsTest("1234567890123456789012345678",  10, Vector{0x6D797A91BE38F34E, 0x0000000003FD35EB}));
		EXPECT_TRUE(FromCharsTest("12345678901234567890123456789", 10, Vector{0x46BEC9B16E398115, 0x0000000027E41B32}));
	}
	{
		using Vector = hamon::vector<hamon::uint8_t>;
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  2, Vector{0x01}, 2));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  3, Vector{0x05}, 3));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  4, Vector{0x1B}, 4));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  5, Vector{0xC2}, 5));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  6, Vector{0x49, 0x07}, 6));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  7, Vector{0x5B, 0x59}, 7));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  8, Vector{0x77, 0x39, 0x05}, 8));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  9, Vector{0x44, 0x5E, 0x5c}, 9));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 10, Vector{0x15, 0xCD, 0x5B, 0x07}, 10));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 11, Vector{0x21, 0x1B, 0x0F, 0xAA}, 11));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 12, Vector{0x93, 0x0A, 0x13, 0x28, 0x11}, 12));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 13, Vector{0x26, 0x23, 0x69, 0xB6, 0xE9, 0x01}, 13));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 14, Vector{0xA1, 0x4D, 0xF9, 0xF7, 0xCC, 0x3B}, 14));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 15, Vector{0x77, 0x9B, 0x40, 0x2A, 0xF3, 0xEF, 0x07}, 15));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 16, Vector{0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01}, 16));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 17, Vector{0x08, 0x37, 0x64, 0x47, 0xCB, 0x43, 0xD8, 0x2C}, 17));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 18, Vector{0x2D, 0x4C, 0x2E, 0x07, 0x5F, 0x63, 0x6A, 0x61, 0x07}, 18));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 19, Vector{0x7D, 0xAB, 0xB8, 0xF1, 0xB2, 0x4C, 0x03, 0x05, 0x4B, 0x01}, 19));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 20, Vector{0x0B, 0x97, 0x73, 0xD5, 0xDB, 0xC3, 0x72, 0x19, 0x82, 0x3D}, 20));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 21, Vector{0x8A, 0x6A, 0x73, 0x58, 0x5A, 0x81, 0x39, 0x31, 0x0A, 0x15, 0x0C}, 21));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 22, Vector{0x39, 0x7C, 0xBA, 0x41, 0x3B, 0x18, 0x41, 0xFD, 0xF3, 0x69, 0x80, 0x02}, 22));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 23, Vector{0x53, 0xCB, 0xB3, 0x58, 0x0E, 0x1C, 0x64, 0x1E, 0x19, 0xC8, 0x65, 0x8B}, 23));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 24, Vector{0x67, 0x99, 0x93, 0xDF, 0x12, 0x49, 0xD9, 0x4F, 0xAB, 0x8F, 0x90, 0xD2, 0x1F}, 24));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 25, Vector{0x4C, 0xE3, 0x05, 0x1D, 0x6B, 0x17, 0x0F, 0xB6, 0x2C, 0x38, 0x74, 0x3F, 0x9A, 0x07}, 25));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 26, Vector{0x45, 0x25, 0x75, 0x66, 0xD6, 0xCA, 0x1A, 0x1F, 0x1C, 0x7D, 0x48, 0xD8, 0xA1, 0xE5, 0x01}, 26));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 27, Vector{0x19, 0x9E, 0x3B, 0x9E, 0x62, 0xB2, 0xAA, 0xF5, 0xF3, 0xB1, 0x15, 0x0A, 0x25, 0x55, 0x7E}, 27));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 28, Vector{0x83, 0xC8, 0xCD, 0xA6, 0x2D, 0xAE, 0x90, 0x0D, 0x67, 0x25, 0x65, 0x82, 0x97, 0xA5, 0x34, 0x22}, 28));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 29, Vector{0xEE, 0x27, 0x11, 0x08, 0xB9, 0xA0, 0x3D, 0x79, 0x75, 0x8A, 0x2E, 0xBD, 0x7E, 0x38, 0xEB, 0x9F, 0x09}, 29));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 30, Vector{0xD1, 0xDE, 0x04, 0xB0, 0xD6, 0xA3, 0x72, 0x53, 0xB7, 0x88, 0xA3, 0x4F, 0x06, 0x28, 0xDF, 0x73, 0xCF, 0x02}, 30));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 31, Vector{0xEF, 0xDD, 0x69, 0xA5, 0xE5, 0x06, 0xBF, 0x48, 0x4E, 0x9D, 0xB6, 0x9B, 0xFC, 0x41, 0xBE, 0x53, 0xB7, 0xD9}, 31));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 32, Vector{0xDF, 0x77, 0xBE, 0x75, 0xC6, 0xD7, 0x56, 0x3A, 0x65, 0x84, 0xCF, 0x35, 0xB6, 0x54, 0x42, 0xC7, 0x14, 0x32, 0x44}, 32));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 33, Vector{0x10, 0x0C, 0x0E, 0x99, 0x0E, 0xF0, 0xF1, 0xC3, 0x6F, 0x34, 0x77, 0xD7, 0xB2, 0x58, 0x80, 0x73, 0x9B, 0xCD, 0x15, 0x16}, 33));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 34, Vector{0x5D, 0x70, 0xA2, 0x0D, 0xCA, 0x31, 0x6D, 0x66, 0x6D, 0x50, 0x4E, 0xC7, 0x5E, 0x68, 0xC7, 0xC3, 0x1B, 0xF0, 0x04, 0x63, 0x7}, 34));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 35, Vector{0xF5, 0x0F, 0x85, 0x53, 0x5F, 0x72, 0x6A, 0x45, 0x3C, 0x86, 0x15, 0x42, 0x70, 0xA2, 0x0F, 0xCC, 0xAD, 0x5F, 0xE2, 0x90, 0x8C, 0x02}, 35));
		EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 36, Vector{0xFB, 0xFA, 0x57, 0x03, 0x70, 0xA8, 0x0A, 0xE5, 0xF8, 0x2A, 0x61, 0x11, 0xC6, 0x72, 0xE2, 0xCC, 0xFA, 0xD9, 0x11, 0x02, 0x1F, 0xE8}, 36));
	}
	{
		using Vector = hamon::vector<hamon::uint8_t>;
		Vector const expected {0xF0, 0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12}; 
		EXPECT_TRUE(FromCharsTest("1001000110100010101100111100010011010101111001101111011110000", 2, expected));
		EXPECT_TRUE(FromCharsTest("22201222011201200202210002220221122120",                        3, expected));
		EXPECT_TRUE(FromCharsTest("1020310111213202122233031323300",                               4, expected));
		EXPECT_TRUE(FromCharsTest("42000442104032331212242240",                                    5, expected));
		EXPECT_TRUE(FromCharsTest("135444110402414144034240",                                      6, expected));
		EXPECT_TRUE(FromCharsTest("2230356425160551126205",                                        7, expected));
		EXPECT_TRUE(FromCharsTest("110642547423257157360",                                         8, expected));
		EXPECT_TRUE(FromCharsTest("8658151622702827576",                                           9, expected));
		EXPECT_TRUE(FromCharsTest("1311768467463790320",                                          10, expected));
		EXPECT_TRUE(FromCharsTest("26603294a9a89a7456",                                           11, expected));
		EXPECT_TRUE(FromCharsTest("7118369118a902980",                                            12, expected));
		EXPECT_TRUE(FromCharsTest("1c82091a91c94389a",                                            13, expected));
		EXPECT_TRUE(FromCharsTest("8609a3282abbdcac",                                             14, expected));
		EXPECT_TRUE(FromCharsTest("2ee03c32ad644ad0",                                             15, expected));
		EXPECT_TRUE(FromCharsTest("123456789abcdef0",                                             16, expected));
		EXPECT_TRUE(FromCharsTest("7d785d21d122679",                                              17, expected));
		EXPECT_TRUE(FromCharsTest("38hge12hbcg8eh6",                                              18, expected));
		EXPECT_TRUE(FromCharsTest("1c3ce7389162864",                                              19, expected));
		EXPECT_TRUE(FromCharsTest("g0527ff428dfg0",                                               20, expected));
		EXPECT_TRUE(FromCharsTest("8a6jfhgje8c8gc",                                               21, expected));
		EXPECT_TRUE(FromCharsTest("4e0l080f20eej6",                                               22, expected));
		EXPECT_TRUE(FromCharsTest("2djglk7e9hk71g",                                               23, expected));
		EXPECT_TRUE(FromCharsTest("1bm160eim0i8a0",                                               24, expected));
		EXPECT_TRUE(FromCharsTest("m04m5khi77eck",                                                25, expected));
		EXPECT_TRUE(FromCharsTest("dja81l3gogiba",                                                26, expected));
		EXPECT_TRUE(FromCharsTest("8jq4jikl2ophf",                                                27, expected));
		EXPECT_TRUE(FromCharsTest("5i4jlj7grodjc",                                                28, expected));
		EXPECT_TRUE(FromCharsTest("3kf06i3d918p3",                                                29, expected));
		EXPECT_TRUE(FromCharsTest("2e1em88jcdle0",                                                30, expected));
		EXPECT_TRUE(FromCharsTest("1kjdmqg2jplbf",                                                31, expected));
		EXPECT_TRUE(FromCharsTest("14d2mf2dbpnng",                                                32, expected));
		EXPECT_TRUE(FromCharsTest("pvfsujwmda96",                                                 33, expected));
		EXPECT_TRUE(FromCharsTest("inelk2b6ha3q",                                                 34, expected));
		EXPECT_TRUE(FromCharsTest("dkihnh24hce5",                                                 35, expected));
		EXPECT_TRUE(FromCharsTest("9ys742pps3qo",                                                 36, expected));
	}
	{
		using Vector = hamon::vector<hamon::uint32_t>;
		Vector const expected {0x9ABCDEF0, 0x12345678}; 
		EXPECT_TRUE(FromCharsTest("1001000110100010101100111100010011010101111001101111011110000", 2, expected));
		EXPECT_TRUE(FromCharsTest("22201222011201200202210002220221122120",                        3, expected));
		EXPECT_TRUE(FromCharsTest("1020310111213202122233031323300",                               4, expected));
		EXPECT_TRUE(FromCharsTest("42000442104032331212242240",                                    5, expected));
		EXPECT_TRUE(FromCharsTest("135444110402414144034240",                                      6, expected));
		EXPECT_TRUE(FromCharsTest("2230356425160551126205",                                        7, expected));
		EXPECT_TRUE(FromCharsTest("110642547423257157360",                                         8, expected));
		EXPECT_TRUE(FromCharsTest("8658151622702827576",                                           9, expected));
		EXPECT_TRUE(FromCharsTest("1311768467463790320",                                          10, expected));
		EXPECT_TRUE(FromCharsTest("26603294a9a89a7456",                                           11, expected));
		EXPECT_TRUE(FromCharsTest("7118369118a902980",                                            12, expected));
		EXPECT_TRUE(FromCharsTest("1c82091a91c94389a",                                            13, expected));
		EXPECT_TRUE(FromCharsTest("8609a3282abbdcac",                                             14, expected));
		EXPECT_TRUE(FromCharsTest("2ee03c32ad644ad0",                                             15, expected));
		EXPECT_TRUE(FromCharsTest("123456789abcdef0",                                             16, expected));
		EXPECT_TRUE(FromCharsTest("7d785d21d122679",                                              17, expected));
		EXPECT_TRUE(FromCharsTest("38hge12hbcg8eh6",                                              18, expected));
		EXPECT_TRUE(FromCharsTest("1c3ce7389162864",                                              19, expected));
		EXPECT_TRUE(FromCharsTest("g0527ff428dfg0",                                               20, expected));
		EXPECT_TRUE(FromCharsTest("8a6jfhgje8c8gc",                                               21, expected));
		EXPECT_TRUE(FromCharsTest("4e0l080f20eej6",                                               22, expected));
		EXPECT_TRUE(FromCharsTest("2djglk7e9hk71g",                                               23, expected));
		EXPECT_TRUE(FromCharsTest("1bm160eim0i8a0",                                               24, expected));
		EXPECT_TRUE(FromCharsTest("m04m5khi77eck",                                                25, expected));
		EXPECT_TRUE(FromCharsTest("dja81l3gogiba",                                                26, expected));
		EXPECT_TRUE(FromCharsTest("8jq4jikl2ophf",                                                27, expected));
		EXPECT_TRUE(FromCharsTest("5i4jlj7grodjc",                                                28, expected));
		EXPECT_TRUE(FromCharsTest("3kf06i3d918p3",                                                29, expected));
		EXPECT_TRUE(FromCharsTest("2e1em88jcdle0",                                                30, expected));
		EXPECT_TRUE(FromCharsTest("1kjdmqg2jplbf",                                                31, expected));
		EXPECT_TRUE(FromCharsTest("14d2mf2dbpnng",                                                32, expected));
		EXPECT_TRUE(FromCharsTest("pvfsujwmda96",                                                 33, expected));
		EXPECT_TRUE(FromCharsTest("inelk2b6ha3q",                                                 34, expected));
		EXPECT_TRUE(FromCharsTest("dkihnh24hce5",                                                 35, expected));
		EXPECT_TRUE(FromCharsTest("9ys742pps3qo",                                                 36, expected));
	}
	{
		using Vector = hamon::vector<hamon::uint64_t>;
		Vector const expected {0x123456789ABCDEF0}; 
		EXPECT_TRUE(FromCharsTest("1001000110100010101100111100010011010101111001101111011110000", 2, expected));
		EXPECT_TRUE(FromCharsTest("22201222011201200202210002220221122120",                        3, expected));
		EXPECT_TRUE(FromCharsTest("1020310111213202122233031323300",                               4, expected));
		EXPECT_TRUE(FromCharsTest("42000442104032331212242240",                                    5, expected));
		EXPECT_TRUE(FromCharsTest("135444110402414144034240",                                      6, expected));
		EXPECT_TRUE(FromCharsTest("2230356425160551126205",                                        7, expected));
		EXPECT_TRUE(FromCharsTest("110642547423257157360",                                         8, expected));
		EXPECT_TRUE(FromCharsTest("8658151622702827576",                                           9, expected));
		EXPECT_TRUE(FromCharsTest("1311768467463790320",                                          10, expected));
		EXPECT_TRUE(FromCharsTest("26603294a9a89a7456",                                           11, expected));
		EXPECT_TRUE(FromCharsTest("7118369118a902980",                                            12, expected));
		EXPECT_TRUE(FromCharsTest("1c82091a91c94389a",                                            13, expected));
		EXPECT_TRUE(FromCharsTest("8609a3282abbdcac",                                             14, expected));
		EXPECT_TRUE(FromCharsTest("2ee03c32ad644ad0",                                             15, expected));
		EXPECT_TRUE(FromCharsTest("123456789abcdef0",                                             16, expected));
		EXPECT_TRUE(FromCharsTest("7d785d21d122679",                                              17, expected));
		EXPECT_TRUE(FromCharsTest("38hge12hbcg8eh6",                                              18, expected));
		EXPECT_TRUE(FromCharsTest("1c3ce7389162864",                                              19, expected));
		EXPECT_TRUE(FromCharsTest("g0527ff428dfg0",                                               20, expected));
		EXPECT_TRUE(FromCharsTest("8a6jfhgje8c8gc",                                               21, expected));
		EXPECT_TRUE(FromCharsTest("4e0l080f20eej6",                                               22, expected));
		EXPECT_TRUE(FromCharsTest("2djglk7e9hk71g",                                               23, expected));
		EXPECT_TRUE(FromCharsTest("1bm160eim0i8a0",                                               24, expected));
		EXPECT_TRUE(FromCharsTest("m04m5khi77eck",                                                25, expected));
		EXPECT_TRUE(FromCharsTest("dja81l3gogiba",                                                26, expected));
		EXPECT_TRUE(FromCharsTest("8jq4jikl2ophf",                                                27, expected));
		EXPECT_TRUE(FromCharsTest("5i4jlj7grodjc",                                                28, expected));
		EXPECT_TRUE(FromCharsTest("3kf06i3d918p3",                                                29, expected));
		EXPECT_TRUE(FromCharsTest("2e1em88jcdle0",                                                30, expected));
		EXPECT_TRUE(FromCharsTest("1kjdmqg2jplbf",                                                31, expected));
		EXPECT_TRUE(FromCharsTest("14d2mf2dbpnng",                                                32, expected));
		EXPECT_TRUE(FromCharsTest("pvfsujwmda96",                                                 33, expected));
		EXPECT_TRUE(FromCharsTest("inelk2b6ha3q",                                                 34, expected));
		EXPECT_TRUE(FromCharsTest("dkihnh24hce5",                                                 35, expected));
		EXPECT_TRUE(FromCharsTest("9ys742pps3qo",                                                 36, expected));
	}

	{
		using Vector = hamon::array<hamon::uint8_t, 12>;
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0",                             10, Vector{0x00}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1",                             10, Vector{0x01}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12",                            10, Vector{0x0C}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123",                           10, Vector{0x7B}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234",                          10, Vector{0xD2, 0x04}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345",                         10, Vector{0x39, 0x30}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456",                        10, Vector{0x40, 0xE2, 0x01}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567",                       10, Vector{0x87, 0xD6, 0x12}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678",                      10, Vector{0x4E, 0x61, 0xBC}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789",                     10, Vector{0x15, 0xCD, 0x5B, 0x07}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890",                    10, Vector{0xD2, 0x02, 0x96, 0x49}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901",                   10, Vector{0x35, 0x1C, 0xDC, 0xDF, 0x02}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012",                  10, Vector{0x14, 0x1A, 0x99, 0xBE, 0x1C}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123",                 10, Vector{0xCB, 0x04, 0xFB, 0x71, 0x1F, 0x01}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234",                10, Vector{0xF2, 0x2F, 0xCE, 0x73, 0x3A, 0x0B}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345",               10, Vector{0x79, 0xDF, 0x0D, 0x86, 0x48, 0x70}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456",              10, Vector{0xC0, 0xBA, 0x8A, 0x3C, 0xD5, 0x62, 0x04}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567",             10, Vector{0x87, 0x4B, 0x6B, 0x5D, 0x54, 0xDC, 0x2B}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678",            10, Vector{0x4E, 0xF3, 0x30, 0xA6, 0x4B, 0x9B, 0xB6, 0x01}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789",           10, Vector{0x15, 0x81, 0xE9, 0x7D, 0xF4, 0x10, 0x22, 0x11}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890",          10, Vector{0xD2, 0x0A, 0x1F, 0xEB, 0x8C, 0xA9, 0x54, 0xAB}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678901",         10, Vector{0x35, 0x6C, 0x36, 0x2F, 0x81, 0x9F, 0x4E, 0xB1, 0x06}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789012",        10, Vector{0x14, 0x3A, 0x20, 0xD8, 0x0B, 0x3B, 0x12, 0xED, 0x42}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890123",       10, Vector{0xCB, 0x44, 0x42, 0x71, 0x76, 0x4E, 0xB6, 0x42, 0x9D, 0x02}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678901234",      10, Vector{0xF2, 0xAF, 0x96, 0x6C, 0xA0, 0x10, 0x1F, 0x9B, 0x24, 0x1A}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789012345",     10, Vector{0x79, 0xDF, 0xE2, 0x3D, 0x44, 0xA6, 0x36, 0x0F, 0x6E, 0x05, 0x01}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890123456",    10, Vector{0xC0, 0xBA, 0xDC, 0x6A, 0xAA, 0x7E, 0x22, 0x98, 0x4C, 0x36, 0x0A}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678901234567",   10, Vector{0x87, 0x4B, 0x9F, 0x2C, 0xA8, 0xF2, 0x58, 0xF1, 0xFD, 0x1E, 0x66}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789012345678",  10, Vector{0x4E, 0xF3, 0x38, 0xBE, 0x91, 0x7A, 0x79, 0x6D, 0xEB, 0x35, 0xFD, 0x03}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890123456789", 10, Vector{0x15, 0x81, 0x39, 0x6E, 0xB1, 0xC9, 0xBE, 0x46, 0x32, 0x1B, 0xE4, 0x27}));
	}
	{
		using Vector = hamon::array<hamon::uint16_t, 6>;
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0",                             10, Vector{0x0000}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1",                             10, Vector{0x0001}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12",                            10, Vector{0x000C}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123",                           10, Vector{0x007B}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234",                          10, Vector{0x04D2}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345",                         10, Vector{0x3039}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456",                        10, Vector{0xE240, 0x0001}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567",                       10, Vector{0xD687, 0x0012}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678",                      10, Vector{0x614E, 0x00BC}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789",                     10, Vector{0xCD15, 0x075B}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890",                    10, Vector{0x02D2, 0x4996}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901",                   10, Vector{0x1C35, 0xDFDC, 0x0002}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012",                  10, Vector{0x1A14, 0xBE99, 0x001C}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123",                 10, Vector{0x04CB, 0x71FB, 0x011F}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234",                10, Vector{0x2FF2, 0x73CE, 0x0B3A}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345",               10, Vector{0xDF79, 0x860D, 0x7048}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456",              10, Vector{0xBAC0, 0x3C8A, 0x62D5, 0x0004}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567",             10, Vector{0x4B87, 0x5D6B, 0xDC54, 0x002B}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678",            10, Vector{0xF34E, 0xA630, 0x9B4B, 0x01B6}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789",           10, Vector{0x8115, 0x7DE9, 0x10F4, 0x1122}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890",          10, Vector{0x0AD2, 0xEB1F, 0xA98C, 0xAB54}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678901",         10, Vector{0x6C35, 0x2F36, 0x9F81, 0xB14E, 0x0006}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789012",        10, Vector{0x3A14, 0xD820, 0x3B0B, 0xED12, 0x0042}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890123",       10, Vector{0x44CB, 0x7142, 0x4E76, 0x42B6, 0x029D}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678901234",      10, Vector{0xAFF2, 0x6C96, 0x10A0, 0x9B1F, 0x1A24}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789012345",     10, Vector{0xDF79, 0x3DE2, 0xA644, 0x0F36, 0x056E, 0x0001}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890123456",    10, Vector{0xBAC0, 0x6ADC, 0x7EAA, 0x9822, 0x364C, 0x000A}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678901234567",   10, Vector{0x4B87, 0x2C9F, 0xF2A8, 0xF158, 0x1EFD, 0x0066}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789012345678",  10, Vector{0xF34E, 0xBE38, 0x7A91, 0x6D79, 0x35EB, 0x03FD}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890123456789", 10, Vector{0x8115, 0x6E39, 0xC9B1, 0x46BE, 0x1B32, 0x27E4}));
	}
	{
		using Vector = hamon::array<hamon::uint32_t, 3>;
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0",                             10, Vector{0x00000000}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1",                             10, Vector{0x00000001}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12",                            10, Vector{0x0000000C}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123",                           10, Vector{0x0000007B}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234",                          10, Vector{0x000004D2}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345",                         10, Vector{0x00003039}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456",                        10, Vector{0x0001E240}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567",                       10, Vector{0x0012D687}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678",                      10, Vector{0x00BC614E}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789",                     10, Vector{0x075BCD15}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890",                    10, Vector{0x499602D2}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901",                   10, Vector{0xDFDC1C35, 0x00000002}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012",                  10, Vector{0xBE991A14, 0x0000001C}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123",                 10, Vector{0x71FB04CB, 0x0000011F}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234",                10, Vector{0x73CE2FF2, 0x00000B3A}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345",               10, Vector{0x860DDF79, 0x00007048}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456",              10, Vector{0x3C8ABAC0, 0x000462D5}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567",             10, Vector{0x5D6B4B87, 0x002BDC54}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678",            10, Vector{0xA630F34E, 0x01B69B4B}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789",           10, Vector{0x7DE98115, 0x112210F4}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890",          10, Vector{0xEB1F0AD2, 0xAB54A98C}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678901",         10, Vector{0x2F366C35, 0xB14E9F81, 0x00000006}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789012",        10, Vector{0xD8203A14, 0xED123B0B, 0x00000042}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890123",       10, Vector{0x714244CB, 0x42B64E76, 0x0000029D}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678901234",      10, Vector{0x6C96AFF2, 0x9B1F10A0, 0x00001A24}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789012345",     10, Vector{0x3DE2DF79, 0x0F36A644, 0x0001056E}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890123456",    10, Vector{0x6ADCBAC0, 0x98227EAA, 0x000A364C}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678901234567",   10, Vector{0x2C9F4B87, 0xF158F2A8, 0x00661EFD}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789012345678",  10, Vector{0xBE38F34E, 0x6D797A91, 0x03FD35EB}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890123456789", 10, Vector{0x6E398115, 0x46BEC9B1, 0x27E41B32}));
	}
	{
		using Vector = hamon::array<hamon::uint64_t, 2>;
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0",                             10, Vector{0x0000000000000000}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1",                             10, Vector{0x0000000000000001}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12",                            10, Vector{0x000000000000000C}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123",                           10, Vector{0x000000000000007B}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234",                          10, Vector{0x00000000000004D2}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345",                         10, Vector{0x0000000000003039}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456",                        10, Vector{0x000000000001E240}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567",                       10, Vector{0x000000000012D687}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678",                      10, Vector{0x0000000000BC614E}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789",                     10, Vector{0x00000000075BCD15}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890",                    10, Vector{0x00000000499602D2}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901",                   10, Vector{0x00000002DFDC1C35}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012",                  10, Vector{0x0000001CBE991A14}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123",                 10, Vector{0x0000011F71FB04CB}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234",                10, Vector{0x00000B3A73CE2FF2}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345",               10, Vector{0x00007048860DDF79}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456",              10, Vector{0x000462D53C8ABAC0}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567",             10, Vector{0x002BDC545D6B4B87}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678",            10, Vector{0x01B69B4BA630F34E}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789",           10, Vector{0x112210F47DE98115}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890",          10, Vector{0xAB54A98CEB1F0AD2}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678901",         10, Vector{0xB14E9F812F366C35, 0x0000000000000006}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789012",        10, Vector{0xED123B0BD8203A14, 0x0000000000000042}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890123",       10, Vector{0x42B64E76714244CB, 0x000000000000029D}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678901234",      10, Vector{0x9B1F10A06C96AFF2, 0x0000000000001A24}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789012345",     10, Vector{0x0F36A6443DE2DF79, 0x000000000001056E}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890123456",    10, Vector{0x98227EAA6ADCBAC0, 0x00000000000A364C}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789012345678901234567",   10, Vector{0xF158F2A82C9F4B87, 0x0000000000661EFD}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1234567890123456789012345678",  10, Vector{0x6D797A91BE38F34E, 0x0000000003FD35EB}));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("12345678901234567890123456789", 10, Vector{0x46BEC9B16E398115, 0x0000000027E41B32}));
	}
	{
		using Vector = hamon::array<hamon::uint8_t, 32>;
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  2, Vector{0x01}, 2));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  3, Vector{0x05}, 3));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  4, Vector{0x1B}, 4));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  5, Vector{0xC2}, 5));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  6, Vector{0x49, 0x07}, 6));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  7, Vector{0x5B, 0x59}, 7));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  8, Vector{0x77, 0x39, 0x05}, 8));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz",  9, Vector{0x44, 0x5E, 0x5c}, 9));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 10, Vector{0x15, 0xCD, 0x5B, 0x07}, 10));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 11, Vector{0x21, 0x1B, 0x0F, 0xAA}, 11));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 12, Vector{0x93, 0x0A, 0x13, 0x28, 0x11}, 12));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 13, Vector{0x26, 0x23, 0x69, 0xB6, 0xE9, 0x01}, 13));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 14, Vector{0xA1, 0x4D, 0xF9, 0xF7, 0xCC, 0x3B}, 14));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 15, Vector{0x77, 0x9B, 0x40, 0x2A, 0xF3, 0xEF, 0x07}, 15));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 16, Vector{0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01}, 16));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 17, Vector{0x08, 0x37, 0x64, 0x47, 0xCB, 0x43, 0xD8, 0x2C}, 17));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 18, Vector{0x2D, 0x4C, 0x2E, 0x07, 0x5F, 0x63, 0x6A, 0x61, 0x07}, 18));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 19, Vector{0x7D, 0xAB, 0xB8, 0xF1, 0xB2, 0x4C, 0x03, 0x05, 0x4B, 0x01}, 19));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 20, Vector{0x0B, 0x97, 0x73, 0xD5, 0xDB, 0xC3, 0x72, 0x19, 0x82, 0x3D}, 20));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 21, Vector{0x8A, 0x6A, 0x73, 0x58, 0x5A, 0x81, 0x39, 0x31, 0x0A, 0x15, 0x0C}, 21));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 22, Vector{0x39, 0x7C, 0xBA, 0x41, 0x3B, 0x18, 0x41, 0xFD, 0xF3, 0x69, 0x80, 0x02}, 22));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 23, Vector{0x53, 0xCB, 0xB3, 0x58, 0x0E, 0x1C, 0x64, 0x1E, 0x19, 0xC8, 0x65, 0x8B}, 23));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 24, Vector{0x67, 0x99, 0x93, 0xDF, 0x12, 0x49, 0xD9, 0x4F, 0xAB, 0x8F, 0x90, 0xD2, 0x1F}, 24));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 25, Vector{0x4C, 0xE3, 0x05, 0x1D, 0x6B, 0x17, 0x0F, 0xB6, 0x2C, 0x38, 0x74, 0x3F, 0x9A, 0x07}, 25));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 26, Vector{0x45, 0x25, 0x75, 0x66, 0xD6, 0xCA, 0x1A, 0x1F, 0x1C, 0x7D, 0x48, 0xD8, 0xA1, 0xE5, 0x01}, 26));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 27, Vector{0x19, 0x9E, 0x3B, 0x9E, 0x62, 0xB2, 0xAA, 0xF5, 0xF3, 0xB1, 0x15, 0x0A, 0x25, 0x55, 0x7E}, 27));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 28, Vector{0x83, 0xC8, 0xCD, 0xA6, 0x2D, 0xAE, 0x90, 0x0D, 0x67, 0x25, 0x65, 0x82, 0x97, 0xA5, 0x34, 0x22}, 28));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 29, Vector{0xEE, 0x27, 0x11, 0x08, 0xB9, 0xA0, 0x3D, 0x79, 0x75, 0x8A, 0x2E, 0xBD, 0x7E, 0x38, 0xEB, 0x9F, 0x09}, 29));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 30, Vector{0xD1, 0xDE, 0x04, 0xB0, 0xD6, 0xA3, 0x72, 0x53, 0xB7, 0x88, 0xA3, 0x4F, 0x06, 0x28, 0xDF, 0x73, 0xCF, 0x02}, 30));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 31, Vector{0xEF, 0xDD, 0x69, 0xA5, 0xE5, 0x06, 0xBF, 0x48, 0x4E, 0x9D, 0xB6, 0x9B, 0xFC, 0x41, 0xBE, 0x53, 0xB7, 0xD9}, 31));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 32, Vector{0xDF, 0x77, 0xBE, 0x75, 0xC6, 0xD7, 0x56, 0x3A, 0x65, 0x84, 0xCF, 0x35, 0xB6, 0x54, 0x42, 0xC7, 0x14, 0x32, 0x44}, 32));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 33, Vector{0x10, 0x0C, 0x0E, 0x99, 0x0E, 0xF0, 0xF1, 0xC3, 0x6F, 0x34, 0x77, 0xD7, 0xB2, 0x58, 0x80, 0x73, 0x9B, 0xCD, 0x15, 0x16}, 33));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 34, Vector{0x5D, 0x70, 0xA2, 0x0D, 0xCA, 0x31, 0x6D, 0x66, 0x6D, 0x50, 0x4E, 0xC7, 0x5E, 0x68, 0xC7, 0xC3, 0x1B, 0xF0, 0x04, 0x63, 0x7}, 34));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 35, Vector{0xF5, 0x0F, 0x85, 0x53, 0x5F, 0x72, 0x6A, 0x45, 0x3C, 0x86, 0x15, 0x42, 0x70, 0xA2, 0x0F, 0xCC, 0xAD, 0x5F, 0xE2, 0x90, 0x8C, 0x02}, 35));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("0123456789abcdefghijklmnopqrstuvwxyz", 36, Vector{0xFB, 0xFA, 0x57, 0x03, 0x70, 0xA8, 0x0A, 0xE5, 0xF8, 0x2A, 0x61, 0x11, 0xC6, 0x72, 0xE2, 0xCC, 0xFA, 0xD9, 0x11, 0x02, 0x1F, 0xE8}, 36));
	}
	{
		using Vector = hamon::array<hamon::uint8_t, 8>;
		HAMON_CXX14_CONSTEXPR Vector expected {0xF0, 0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12}; 
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1001000110100010101100111100010011010101111001101111011110000", 2, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("22201222011201200202210002220221122120",                        3, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1020310111213202122233031323300",                               4, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("42000442104032331212242240",                                    5, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("135444110402414144034240",                                      6, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("2230356425160551126205",                                        7, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("110642547423257157360",                                         8, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("8658151622702827576",                                           9, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1311768467463790320",                                          10, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("26603294a9a89a7456",                                           11, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("7118369118a902980",                                            12, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1c82091a91c94389a",                                            13, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("8609a3282abbdcac",                                             14, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("2ee03c32ad644ad0",                                             15, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789abcdef0",                                             16, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("7d785d21d122679",                                              17, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("38hge12hbcg8eh6",                                              18, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1c3ce7389162864",                                              19, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("g0527ff428dfg0",                                               20, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("8a6jfhgje8c8gc",                                               21, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("4e0l080f20eej6",                                               22, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("2djglk7e9hk71g",                                               23, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1bm160eim0i8a0",                                               24, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("m04m5khi77eck",                                                25, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("dja81l3gogiba",                                                26, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("8jq4jikl2ophf",                                                27, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("5i4jlj7grodjc",                                                28, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("3kf06i3d918p3",                                                29, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("2e1em88jcdle0",                                                30, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1kjdmqg2jplbf",                                                31, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("14d2mf2dbpnng",                                                32, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("pvfsujwmda96",                                                 33, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("inelk2b6ha3q",                                                 34, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("dkihnh24hce5",                                                 35, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("9ys742pps3qo",                                                 36, expected));
	}
	{
		using Vector = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR Vector expected {0x9ABCDEF0, 0x12345678}; 
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1001000110100010101100111100010011010101111001101111011110000", 2, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("22201222011201200202210002220221122120",                        3, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1020310111213202122233031323300",                               4, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("42000442104032331212242240",                                    5, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("135444110402414144034240",                                      6, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("2230356425160551126205",                                        7, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("110642547423257157360",                                         8, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("8658151622702827576",                                           9, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1311768467463790320",                                          10, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("26603294a9a89a7456",                                           11, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("7118369118a902980",                                            12, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1c82091a91c94389a",                                            13, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("8609a3282abbdcac",                                             14, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("2ee03c32ad644ad0",                                             15, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789abcdef0",                                             16, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("7d785d21d122679",                                              17, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("38hge12hbcg8eh6",                                              18, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1c3ce7389162864",                                              19, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("g0527ff428dfg0",                                               20, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("8a6jfhgje8c8gc",                                               21, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("4e0l080f20eej6",                                               22, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("2djglk7e9hk71g",                                               23, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1bm160eim0i8a0",                                               24, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("m04m5khi77eck",                                                25, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("dja81l3gogiba",                                                26, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("8jq4jikl2ophf",                                                27, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("5i4jlj7grodjc",                                                28, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("3kf06i3d918p3",                                                29, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("2e1em88jcdle0",                                                30, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1kjdmqg2jplbf",                                                31, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("14d2mf2dbpnng",                                                32, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("pvfsujwmda96",                                                 33, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("inelk2b6ha3q",                                                 34, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("dkihnh24hce5",                                                 35, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("9ys742pps3qo",                                                 36, expected));
	}
	{
		using Vector = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR Vector expected {0x123456789ABCDEF0}; 
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1001000110100010101100111100010011010101111001101111011110000", 2, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("22201222011201200202210002220221122120",                        3, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1020310111213202122233031323300",                               4, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("42000442104032331212242240",                                    5, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("135444110402414144034240",                                      6, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("2230356425160551126205",                                        7, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("110642547423257157360",                                         8, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("8658151622702827576",                                           9, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1311768467463790320",                                          10, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("26603294a9a89a7456",                                           11, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("7118369118a902980",                                            12, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1c82091a91c94389a",                                            13, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("8609a3282abbdcac",                                             14, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("2ee03c32ad644ad0",                                             15, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("123456789abcdef0",                                             16, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("7d785d21d122679",                                              17, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("38hge12hbcg8eh6",                                              18, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1c3ce7389162864",                                              19, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("g0527ff428dfg0",                                               20, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("8a6jfhgje8c8gc",                                               21, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("4e0l080f20eej6",                                               22, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("2djglk7e9hk71g",                                               23, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1bm160eim0i8a0",                                               24, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("m04m5khi77eck",                                                25, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("dja81l3gogiba",                                                26, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("8jq4jikl2ophf",                                                27, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("5i4jlj7grodjc",                                                28, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("3kf06i3d918p3",                                                29, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("2e1em88jcdle0",                                                30, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("1kjdmqg2jplbf",                                                31, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("14d2mf2dbpnng",                                                32, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("pvfsujwmda96",                                                 33, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("inelk2b6ha3q",                                                 34, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("dkihnh24hce5",                                                 35, expected));
		/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromCharsTest("9ys742pps3qo",                                                 36, expected));
	}

	// オーバーフローに関するテスト
	{
		using Vector = hamon::array<hamon::uint8_t, 1>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("255", 10, Vector{0xFF}, 3, hamon::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("256", 10, Vector{0x00}, 3, hamon::errc::result_out_of_range));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("11111111",  2, Vector{0xFF}, 8, hamon::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("100000000", 2, Vector{0x00}, 9, hamon::errc::result_out_of_range));
	}
	{
		using Vector = hamon::array<hamon::uint8_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("65535", 10, Vector{0xFF, 0xFF}, 5, hamon::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("65536", 10, Vector{0x00, 0x00}, 5, hamon::errc::result_out_of_range));
	}
	{
		using Vector = hamon::array<hamon::uint8_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("ffffff",  16, Vector{0xFF, 0xFF, 0xFF}, 6, hamon::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("1000000", 16, Vector{0x00, 0x00, 0x00}, 7, hamon::errc::result_out_of_range));
	}
	{
		using Vector = hamon::array<hamon::uint8_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("ffffffff",  16, Vector{0xFF, 0xFF, 0xFF, 0xFF}, 8, hamon::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("100000000", 16, Vector{0x00, 0x00, 0x00, 0x00}, 9, hamon::errc::result_out_of_range));
	}
	{
		using Vector = hamon::array<hamon::uint16_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("ffffffff",  16, Vector{0xFFFF, 0xFFFF}, 8, hamon::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("100000000", 16, Vector{0x0000, 0x0000}, 9, hamon::errc::result_out_of_range));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("ffffffffff 012", 16, Vector{0x0000, 0x0000}, 10, hamon::errc::result_out_of_range));
	}
	{
		using Vector = hamon::array<hamon::uint32_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("ffffffffffffffffffffffff",  16, Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 24, hamon::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("1000000000000000000000000", 16, Vector{0x00000000, 0x00000000, 0x00000000}, 25, hamon::errc::result_out_of_range));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromCharsTest("ffffffffffffffffffffffffffff", 16, Vector{0x00000000, 0x00000000, 0x00000000}, 28, hamon::errc::result_out_of_range));
	}
}

#undef VERIFY

}	// namespace bigint_algo_from_chars_test

}	// namespace hamon_bigint_test
