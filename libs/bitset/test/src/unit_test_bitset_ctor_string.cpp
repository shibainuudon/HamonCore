/**
 *	@file	unit_test_bitset_ctor_string.cpp
 *
 *	@brief	文字列を受け取るコンストラクタのテスト
 *
 *	template<class charT, class traits, class Allocator>
 *	constexpr explicit bitset(
 *		const basic_string<charT, traits, Allocator>& str,
 *		typename basic_string<charT, traits, Allocator>::size_type pos = 0,
 *		typename basic_string<charT, traits, Allocator>::size_type n = basic_string<charT, traits, Allocator>::npos,
 *		charT zero = charT('0'),
 *		charT one = charT('1'));
 */

#include <hamon/bitset.hpp>
#include <hamon/stdexcept/invalid_argument.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace ctor_string_test
{

GTEST_TEST(BitsetTest, CtorStringTest)
{
	{
		const hamon::string s = "10101100111000111100001111100000";

		const hamon::bitset< 0> b0(s);
		const hamon::bitset< 1> b1(s);
		const hamon::bitset< 7> b2(s);
		const hamon::bitset< 8> b3(s);
		const hamon::bitset< 9> b4(s);
		const hamon::bitset<15> b5(s);
		const hamon::bitset<16> b6(s);
		const hamon::bitset<17> b7(s);
		const hamon::bitset<31> b8(s);
		const hamon::bitset<32> b9(s);
		const hamon::bitset<33> b10(s);
		const hamon::bitset<63> b11(s);
		const hamon::bitset<64> b12(s);
		const hamon::bitset<65> b13(s);

		EXPECT_EQ("", b0.to_string());
		EXPECT_EQ("1", b1.to_string());
		EXPECT_EQ("1010110", b2.to_string());
		EXPECT_EQ("10101100", b3.to_string());
		EXPECT_EQ("101011001", b4.to_string());
		EXPECT_EQ("101011001110001", b5.to_string());
		EXPECT_EQ("1010110011100011", b6.to_string());
		EXPECT_EQ("10101100111000111", b7.to_string());
		EXPECT_EQ("1010110011100011110000111110000", b8.to_string());
		EXPECT_EQ("10101100111000111100001111100000", b9.to_string());
		EXPECT_EQ("010101100111000111100001111100000", b10.to_string());
		EXPECT_EQ("000000000000000000000000000000010101100111000111100001111100000", b11.to_string());
		EXPECT_EQ("0000000000000000000000000000000010101100111000111100001111100000", b12.to_string());
		EXPECT_EQ("00000000000000000000000000000000010101100111000111100001111100000", b13.to_string());

		EXPECT_EQ(0u, b0.count());
		EXPECT_EQ(1u, b1.count());
		EXPECT_EQ(4u, b2.count());
		EXPECT_EQ(4u, b3.count());
		EXPECT_EQ(5u, b4.count());
		EXPECT_EQ(8u, b5.count());
		EXPECT_EQ(9u, b6.count());
		EXPECT_EQ(10u, b7.count());
		EXPECT_EQ(16u, b8.count());
		EXPECT_EQ(16u, b9.count());
		EXPECT_EQ(16u, b10.count());
		EXPECT_EQ(16u, b11.count());
		EXPECT_EQ(16u, b12.count());
		EXPECT_EQ(16u, b13.count());
	}
	{
		const hamon::string s = "10101100111000111100001111100000";

		const hamon::bitset< 7> b0(s, 0);
		const hamon::bitset< 7> b1(s, 1);
		const hamon::bitset< 7> b2(s, 2);
		const hamon::bitset< 7> b3(s, 3);
		const hamon::bitset< 7> b4(s, 4);
		const hamon::bitset< 7> b5(s, 5);
		const hamon::bitset< 7> b6(s, 6);
		const hamon::bitset< 7> b7(s, 7);
		const hamon::bitset< 7> b8(s, 8);

		EXPECT_EQ("1010110", b0.to_string());
		EXPECT_EQ("0101100", b1.to_string());
		EXPECT_EQ("1011001", b2.to_string());
		EXPECT_EQ("0110011", b3.to_string());
		EXPECT_EQ("1100111", b4.to_string());
		EXPECT_EQ("1001110", b5.to_string());
		EXPECT_EQ("0011100", b6.to_string());
		EXPECT_EQ("0111000", b7.to_string());
		EXPECT_EQ("1110001", b8.to_string());

		EXPECT_EQ(4u, b0.count());
		EXPECT_EQ(3u, b1.count());
		EXPECT_EQ(4u, b2.count());
		EXPECT_EQ(4u, b3.count());
		EXPECT_EQ(5u, b4.count());
		EXPECT_EQ(4u, b5.count());
		EXPECT_EQ(3u, b6.count());
		EXPECT_EQ(3u, b7.count());
		EXPECT_EQ(4u, b8.count());
	}
	{
		const hamon::string s = "10101100111000111100001111100000";

		const hamon::bitset<17> b0(s, 0);
		const hamon::bitset<17> b1(s, 1);
		const hamon::bitset<17> b2(s, 2);
		const hamon::bitset<17> b3(s, 3);
		const hamon::bitset<17> b4(s, 4);
		const hamon::bitset<17> b5(s, 5);
		const hamon::bitset<17> b6(s, 6);
		const hamon::bitset<17> b7(s, 7);
		const hamon::bitset<17> b8(s, 8);

		EXPECT_EQ("10101100111000111", b0.to_string());
		EXPECT_EQ("01011001110001111", b1.to_string());
		EXPECT_EQ("10110011100011110", b2.to_string());
		EXPECT_EQ("01100111000111100", b3.to_string());
		EXPECT_EQ("11001110001111000", b4.to_string());
		EXPECT_EQ("10011100011110000", b5.to_string());
		EXPECT_EQ("00111000111100001", b6.to_string());
		EXPECT_EQ("01110001111000011", b7.to_string());
		EXPECT_EQ("11100011110000111", b8.to_string());

		EXPECT_EQ(10u, b0.count());
		EXPECT_EQ(10u, b1.count());
		EXPECT_EQ(10u, b2.count());
		EXPECT_EQ( 9u, b3.count());
		EXPECT_EQ( 9u, b4.count());
		EXPECT_EQ( 8u, b5.count());
		EXPECT_EQ( 8u, b6.count());
		EXPECT_EQ( 9u, b7.count());
		EXPECT_EQ(10u, b8.count());
	}
	{
		const hamon::string s = "10101100111000111100001111100000";

		const hamon::bitset< 7> b0(s, 0, 0);
		const hamon::bitset< 7> b1(s, 0, 1);
		const hamon::bitset< 7> b2(s, 0, 2);
		const hamon::bitset< 7> b3(s, 0, 3);
		const hamon::bitset< 7> b4(s, 0, 4);
		const hamon::bitset< 7> b5(s, 0, 5);
		const hamon::bitset< 7> b6(s, 0, 6);
		const hamon::bitset< 7> b7(s, 0, 7);
		const hamon::bitset< 7> b8(s, 0, 8);

		EXPECT_EQ("0000000", b0.to_string());
		EXPECT_EQ("0000001", b1.to_string());
		EXPECT_EQ("0000010", b2.to_string());
		EXPECT_EQ("0000101", b3.to_string());
		EXPECT_EQ("0001010", b4.to_string());
		EXPECT_EQ("0010101", b5.to_string());
		EXPECT_EQ("0101011", b6.to_string());
		EXPECT_EQ("1010110", b7.to_string());
		EXPECT_EQ("1010110", b8.to_string());

		EXPECT_EQ(0u, b0.count());
		EXPECT_EQ(1u, b1.count());
		EXPECT_EQ(1u, b2.count());
		EXPECT_EQ(2u, b3.count());
		EXPECT_EQ(2u, b4.count());
		EXPECT_EQ(3u, b5.count());
		EXPECT_EQ(4u, b6.count());
		EXPECT_EQ(4u, b7.count());
		EXPECT_EQ(4u, b8.count());
	}
	{
		const hamon::string s = "10101100111000111100001111100000";

		const hamon::bitset< 7> b0(s, 1, 0);
		const hamon::bitset< 7> b1(s, 1, 1);
		const hamon::bitset< 7> b2(s, 1, 2);
		const hamon::bitset< 7> b3(s, 1, 3);
		const hamon::bitset< 7> b4(s, 1, 4);
		const hamon::bitset< 7> b5(s, 1, 5);
		const hamon::bitset< 7> b6(s, 1, 6);
		const hamon::bitset< 7> b7(s, 1, 7);
		const hamon::bitset< 7> b8(s, 1, 8);

		EXPECT_EQ("0000000", b0.to_string());
		EXPECT_EQ("0000000", b1.to_string());
		EXPECT_EQ("0000001", b2.to_string());
		EXPECT_EQ("0000010", b3.to_string());
		EXPECT_EQ("0000101", b4.to_string());
		EXPECT_EQ("0001011", b5.to_string());
		EXPECT_EQ("0010110", b6.to_string());
		EXPECT_EQ("0101100", b7.to_string());
		EXPECT_EQ("0101100", b8.to_string());

		EXPECT_EQ(0u, b0.count());
		EXPECT_EQ(0u, b1.count());
		EXPECT_EQ(1u, b2.count());
		EXPECT_EQ(1u, b3.count());
		EXPECT_EQ(2u, b4.count());
		EXPECT_EQ(3u, b5.count());
		EXPECT_EQ(3u, b6.count());
		EXPECT_EQ(3u, b7.count());
		EXPECT_EQ(3u, b8.count());
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		const hamon::string s = "..111...";
		EXPECT_NO_THROW(hamon::bitset<0> b(s, 8));
		EXPECT_NO_THROW(hamon::bitset<0> b(s, 8, 0));
		EXPECT_NO_THROW(hamon::bitset<0> b(s, 8, 1));
		EXPECT_NO_THROW(hamon::bitset<0> b(s, 8, 2));
		EXPECT_THROW   (hamon::bitset<0> b(s, 9), hamon::out_of_range);
		EXPECT_THROW   (hamon::bitset<0> b(s, 9, 0), hamon::out_of_range);
		EXPECT_THROW   (hamon::bitset<0> b(s, 9, 1), hamon::out_of_range);
		EXPECT_THROW   (hamon::bitset<0> b(s, 9, 2), hamon::out_of_range);
		EXPECT_THROW   (hamon::bitset<0> b(s, 0, 2), hamon::invalid_argument);
		EXPECT_THROW   (hamon::bitset<0> b(s, 1, 2), hamon::invalid_argument);
		EXPECT_NO_THROW(hamon::bitset<0> b(s, 2, 2));
		EXPECT_NO_THROW(hamon::bitset<0> b(s, 3, 2));
		EXPECT_THROW   (hamon::bitset<0> b(s, 0, 3), hamon::invalid_argument);
		EXPECT_THROW   (hamon::bitset<0> b(s, 1, 3), hamon::invalid_argument);
		EXPECT_NO_THROW(hamon::bitset<0> b(s, 2, 3));
		EXPECT_THROW   (hamon::bitset<0> b(s, 3, 3), hamon::invalid_argument);
		EXPECT_THROW   (hamon::bitset<0> b(s, 0, 4), hamon::invalid_argument);
		EXPECT_THROW   (hamon::bitset<0> b(s, 1, 4), hamon::invalid_argument);
		EXPECT_THROW   (hamon::bitset<0> b(s, 2, 4), hamon::invalid_argument);
		EXPECT_THROW   (hamon::bitset<0> b(s, 3, 4), hamon::invalid_argument);
	}
#endif
	{
		const hamon::string s1 = "110010";
		const hamon::string s2 = ".1...1.1";
		const hamon::string s3 = "AABABBBA";

		const hamon::bitset< 0> b0(s1);
		const hamon::bitset< 1> b1(s1);
		const hamon::bitset< 8> b2(s1);
		const hamon::bitset<64> b3(s1);
		const hamon::bitset< 0> b4(s1, 2);
		const hamon::bitset< 8> b5(s1, 2);
		const hamon::bitset< 8> b6(s1, 6);
		const hamon::bitset<64> b7(s1, 6);
		const hamon::bitset< 0> b8(s1, 2, 3);
		const hamon::bitset< 8> b9(s1, 2, 3);
		const hamon::bitset<64> b10(s1, 2, 3);
		const hamon::bitset< 0> b11(s2, 0, 8, '.');
		const hamon::bitset< 8> b12(s2, 0, 8, '.');
		const hamon::bitset<64> b13(s2, 0, 8, '.');
		const hamon::bitset< 0> b14(s3, 0, 8, 'A', 'B');
		const hamon::bitset< 0> b15(s3, 0, 8, 'B', 'A');
		const hamon::bitset< 8> b16(s3, 0, 8, 'A', 'B');
		const hamon::bitset< 8> b17(s3, 0, 8, 'B', 'A');
		const hamon::bitset<64> b18(s3, 0, 8, 'A', 'B');
		const hamon::bitset<64> b19(s3, 0, 8, 'B', 'A');

		EXPECT_EQ("", b0.to_string());
		EXPECT_EQ("1", b1.to_string());
		EXPECT_EQ("00110010", b2.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000110010", b3.to_string());
		EXPECT_EQ("", b4.to_string());
		EXPECT_EQ("00000010", b5.to_string());
		EXPECT_EQ("00000000", b6.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000000", b7.to_string());
		EXPECT_EQ("", b8.to_string());
		EXPECT_EQ("00000001", b9.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000001", b10.to_string());
		EXPECT_EQ("", b11.to_string());
		EXPECT_EQ("01000101", b12.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000001000101", b13.to_string());
		EXPECT_EQ("", b14.to_string());
		EXPECT_EQ("", b15.to_string());
		EXPECT_EQ("00101110", b16.to_string());
		EXPECT_EQ("11010001", b17.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000101110", b18.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000011010001", b19.to_string());

		EXPECT_EQ(  0u, b0.to_ulong());
		EXPECT_EQ(  1u, b1.to_ulong());
		EXPECT_EQ( 50u, b2.to_ulong());
		EXPECT_EQ( 50u, b3.to_ulong());
		EXPECT_EQ(  0u, b4.to_ulong());
		EXPECT_EQ(  2u, b5.to_ulong());
		EXPECT_EQ(  0u, b6.to_ulong());
		EXPECT_EQ(  0u, b7.to_ulong());
		EXPECT_EQ(  0u, b8.to_ulong());
		EXPECT_EQ(  1u, b9.to_ulong());
		EXPECT_EQ(  1u, b10.to_ulong());
		EXPECT_EQ(  0u, b11.to_ulong());
		EXPECT_EQ( 69u, b12.to_ulong());
		EXPECT_EQ( 69u, b13.to_ulong());
		EXPECT_EQ(  0u, b14.to_ulong());
		EXPECT_EQ(  0u, b15.to_ulong());
		EXPECT_EQ( 46u, b16.to_ulong());
		EXPECT_EQ(209u, b17.to_ulong());
		EXPECT_EQ( 46u, b18.to_ulong());
		EXPECT_EQ(209u, b19.to_ulong());

		EXPECT_EQ(0u, b0.count());
		EXPECT_EQ(1u, b1.count());
		EXPECT_EQ(3u, b2.count());
		EXPECT_EQ(3u, b3.count());
		EXPECT_EQ(0u, b4.count());
		EXPECT_EQ(1u, b5.count());
		EXPECT_EQ(0u, b6.count());
		EXPECT_EQ(0u, b7.count());
		EXPECT_EQ(0u, b8.count());
		EXPECT_EQ(1u, b9.count());
		EXPECT_EQ(1u, b10.count());
		EXPECT_EQ(0u, b11.count());
		EXPECT_EQ(3u, b12.count());
		EXPECT_EQ(3u, b13.count());
		EXPECT_EQ(0u, b14.count());
		EXPECT_EQ(0u, b15.count());
		EXPECT_EQ(4u, b16.count());
		EXPECT_EQ(4u, b17.count());
		EXPECT_EQ(4u, b18.count());
		EXPECT_EQ(4u, b19.count());

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW(hamon::bitset<0> b(s1, 7), hamon::out_of_range);
		EXPECT_THROW(hamon::bitset<0> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<0> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<0> b(s3, 0, 8, 'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<0> b(s3, 0, 8, 'A', 'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s1, 7), hamon::out_of_range);
		EXPECT_THROW(hamon::bitset<1> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 0, 8, 'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 0, 8, 'B'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 0, 8, 'A', 'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 0, 8, 'B', 'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s1, 7), hamon::out_of_range);
		EXPECT_THROW(hamon::bitset<8> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s3, 0, 8, 'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s3, 0, 8, 'A', 'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s1, 7), hamon::out_of_range);
		EXPECT_THROW(hamon::bitset<64> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s3, 0, 8, 'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s3, 0, 8, 'A', 'C'), hamon::invalid_argument);
#endif
	}
	{
		const hamon::wstring s = L"10101100111000111100001111100000";

		const hamon::bitset< 0> b0(s);
		const hamon::bitset< 1> b1(s);
		const hamon::bitset< 7> b2(s);
		const hamon::bitset< 8> b3(s);
		const hamon::bitset< 9> b4(s);
		const hamon::bitset<15> b5(s);
		const hamon::bitset<16> b6(s);
		const hamon::bitset<17> b7(s);
		const hamon::bitset<31> b8(s);
		const hamon::bitset<32> b9(s);
		const hamon::bitset<33> b10(s);
		const hamon::bitset<63> b11(s);
		const hamon::bitset<64> b12(s);
		const hamon::bitset<65> b13(s);

		EXPECT_EQ("", b0.to_string());
		EXPECT_EQ("1", b1.to_string());
		EXPECT_EQ("1010110", b2.to_string());
		EXPECT_EQ("10101100", b3.to_string());
		EXPECT_EQ("101011001", b4.to_string());
		EXPECT_EQ("101011001110001", b5.to_string());
		EXPECT_EQ("1010110011100011", b6.to_string());
		EXPECT_EQ("10101100111000111", b7.to_string());
		EXPECT_EQ("1010110011100011110000111110000", b8.to_string());
		EXPECT_EQ("10101100111000111100001111100000", b9.to_string());
		EXPECT_EQ("010101100111000111100001111100000", b10.to_string());
		EXPECT_EQ("000000000000000000000000000000010101100111000111100001111100000", b11.to_string());
		EXPECT_EQ("0000000000000000000000000000000010101100111000111100001111100000", b12.to_string());
		EXPECT_EQ("00000000000000000000000000000000010101100111000111100001111100000", b13.to_string());

		EXPECT_EQ(0u, b0.count());
		EXPECT_EQ(1u, b1.count());
		EXPECT_EQ(4u, b2.count());
		EXPECT_EQ(4u, b3.count());
		EXPECT_EQ(5u, b4.count());
		EXPECT_EQ(8u, b5.count());
		EXPECT_EQ(9u, b6.count());
		EXPECT_EQ(10u, b7.count());
		EXPECT_EQ(16u, b8.count());
		EXPECT_EQ(16u, b9.count());
		EXPECT_EQ(16u, b10.count());
		EXPECT_EQ(16u, b11.count());
		EXPECT_EQ(16u, b12.count());
		EXPECT_EQ(16u, b13.count());
	}
	{
		const hamon::wstring s1 = L"110010";
		const hamon::wstring s2 = L".1...1.1";
		const hamon::wstring s3 = L"AABABBBA";

		const hamon::bitset< 0> b0(s1);
		const hamon::bitset< 1> b1(s1);
		const hamon::bitset< 8> b2(s1);
		const hamon::bitset<64> b3(s1);
		const hamon::bitset< 0> b4(s1, 2);
		const hamon::bitset< 8> b5(s1, 2);
		const hamon::bitset< 8> b6(s1, 6);
		const hamon::bitset<64> b7(s1, 6);
		const hamon::bitset< 0> b8(s1, 2, 3);
		const hamon::bitset< 8> b9(s1, 2, 3);
		const hamon::bitset<64> b10(s1, 2, 3);
		const hamon::bitset< 0> b11(s2, 0, 8, L'.');
		const hamon::bitset< 8> b12(s2, 0, 8, L'.');
		const hamon::bitset<64> b13(s2, 0, 8, L'.');
		const hamon::bitset< 0> b14(s3, 0, 8, L'A', L'B');
		const hamon::bitset< 0> b15(s3, 0, 8, L'B', L'A');
		const hamon::bitset< 8> b16(s3, 0, 8, L'A', L'B');
		const hamon::bitset< 8> b17(s3, 0, 8, L'B', L'A');
		const hamon::bitset<64> b18(s3, 0, 8, L'A', L'B');
		const hamon::bitset<64> b19(s3, 0, 8, L'B', L'A');

		EXPECT_EQ("", b0.to_string());
		EXPECT_EQ("1", b1.to_string());
		EXPECT_EQ("00110010", b2.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000110010", b3.to_string());
		EXPECT_EQ("", b4.to_string());
		EXPECT_EQ("00000010", b5.to_string());
		EXPECT_EQ("00000000", b6.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000000", b7.to_string());
		EXPECT_EQ("", b8.to_string());
		EXPECT_EQ("00000001", b9.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000001", b10.to_string());
		EXPECT_EQ("", b11.to_string());
		EXPECT_EQ("01000101", b12.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000001000101", b13.to_string());
		EXPECT_EQ("", b14.to_string());
		EXPECT_EQ("", b15.to_string());
		EXPECT_EQ("00101110", b16.to_string());
		EXPECT_EQ("11010001", b17.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000101110", b18.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000011010001", b19.to_string());

		EXPECT_EQ(  0u, b0.to_ulong());
		EXPECT_EQ(  1u, b1.to_ulong());
		EXPECT_EQ( 50u, b2.to_ulong());
		EXPECT_EQ( 50u, b3.to_ulong());
		EXPECT_EQ(  0u, b4.to_ulong());
		EXPECT_EQ(  2u, b5.to_ulong());
		EXPECT_EQ(  0u, b6.to_ulong());
		EXPECT_EQ(  0u, b7.to_ulong());
		EXPECT_EQ(  0u, b8.to_ulong());
		EXPECT_EQ(  1u, b9.to_ulong());
		EXPECT_EQ(  1u, b10.to_ulong());
		EXPECT_EQ(  0u, b11.to_ulong());
		EXPECT_EQ( 69u, b12.to_ulong());
		EXPECT_EQ( 69u, b13.to_ulong());
		EXPECT_EQ(  0u, b14.to_ulong());
		EXPECT_EQ(  0u, b15.to_ulong());
		EXPECT_EQ( 46u, b16.to_ulong());
		EXPECT_EQ(209u, b17.to_ulong());
		EXPECT_EQ( 46u, b18.to_ulong());
		EXPECT_EQ(209u, b19.to_ulong());

		EXPECT_EQ(0u, b0.count());
		EXPECT_EQ(1u, b1.count());
		EXPECT_EQ(3u, b2.count());
		EXPECT_EQ(3u, b3.count());
		EXPECT_EQ(0u, b4.count());
		EXPECT_EQ(1u, b5.count());
		EXPECT_EQ(0u, b6.count());
		EXPECT_EQ(0u, b7.count());
		EXPECT_EQ(0u, b8.count());
		EXPECT_EQ(1u, b9.count());
		EXPECT_EQ(1u, b10.count());
		EXPECT_EQ(0u, b11.count());
		EXPECT_EQ(3u, b12.count());
		EXPECT_EQ(3u, b13.count());
		EXPECT_EQ(0u, b14.count());
		EXPECT_EQ(0u, b15.count());
		EXPECT_EQ(4u, b16.count());
		EXPECT_EQ(4u, b17.count());
		EXPECT_EQ(4u, b18.count());
		EXPECT_EQ(4u, b19.count());

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW(hamon::bitset<0> b(s1, 7), hamon::out_of_range);
		EXPECT_THROW(hamon::bitset<0> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<0> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<0> b(s3, 0, 8, L'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<0> b(s3, 0, 8, L'A', L'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s1, 7), hamon::out_of_range);
		EXPECT_THROW(hamon::bitset<1> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 0, 8, L'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 0, 8, L'B'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 0, 8, L'A', L'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 0, 8, L'B', L'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s1, 7), hamon::out_of_range);
		EXPECT_THROW(hamon::bitset<8> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s3, 0, 8, L'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s3, 0, 8, L'A', L'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s1, 7), hamon::out_of_range);
		EXPECT_THROW(hamon::bitset<64> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s3, 0, 8, L'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s3, 0, 8, L'A', L'C'), hamon::invalid_argument);
#endif
	}
}

}	// namespace ctor_string_test

}	// namespace hamon_bitset_test
