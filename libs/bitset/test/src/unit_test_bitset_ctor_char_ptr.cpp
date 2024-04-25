/**
 *	@file	unit_test_bitset_ctor_char_ptr.cpp
 *
 *	@brief	文字配列を受け取るコンストラクタのテスト
 *
 *	template<class charT>
 *	constexpr explicit bitset(
 *		const charT* str,
 *		typename basic_string_view<charT>::size_type n = basic_string_view<charT>::npos,
 *		charT zero = charT('0'),
 *		charT one = charT('1'));
 */

#include <hamon/bitset.hpp>
#include <hamon/stdexcept/invalid_argument.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace ctor_char_ptr_test
{

GTEST_TEST(BitsetTest, CtorCharPtrTest)
{
	{
		HAMON_CXX11_CONSTEXPR const char* s = "10101100111000111100001111100000";

		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b0(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 1> b1(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 7> b2(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b3(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 9> b4(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<15> b5(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<16> b6(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<17> b7(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<31> b8(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<32> b9(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<33> b10(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<63> b11(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b12(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<65> b13(s);

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

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b0.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b1.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b2.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b3.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5u, b4.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, b5.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(9u, b6.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10u, b7.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b8.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b9.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b10.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b11.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b12.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b13.count());
	}
	{
		HAMON_CXX11_CONSTEXPR const char* s = "10101100111000111100001111100000";

		HAMON_CXX11_CONSTEXPR hamon::bitset< 7> b0(s, 0);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 7> b1(s, 1);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 7> b2(s, 2);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 7> b3(s, 3);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 7> b4(s, 4);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 7> b5(s, 5);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 7> b6(s, 6);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 7> b7(s, 7);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 7> b8(s, 8);

		EXPECT_EQ("0000000", b0.to_string());
		EXPECT_EQ("0000001", b1.to_string());
		EXPECT_EQ("0000010", b2.to_string());
		EXPECT_EQ("0000101", b3.to_string());
		EXPECT_EQ("0001010", b4.to_string());
		EXPECT_EQ("0010101", b5.to_string());
		EXPECT_EQ("0101011", b6.to_string());
		EXPECT_EQ("1010110", b7.to_string());
		EXPECT_EQ("1010110", b8.to_string());

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b0.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b1.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b2.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, b3.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, b4.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, b5.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b6.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b7.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b8.count());
	}
	{
		HAMON_CXX11_CONSTEXPR const char* s = "10101100111000111100001111100000";

		HAMON_CXX11_CONSTEXPR hamon::bitset<17> b0(s, 0);
		HAMON_CXX11_CONSTEXPR hamon::bitset<17> b1(s, 1);
		HAMON_CXX11_CONSTEXPR hamon::bitset<17> b2(s, 2);
		HAMON_CXX11_CONSTEXPR hamon::bitset<17> b3(s, 3);
		HAMON_CXX11_CONSTEXPR hamon::bitset<17> b4(s, 4);
		HAMON_CXX11_CONSTEXPR hamon::bitset<17> b5(s, 5);
		HAMON_CXX11_CONSTEXPR hamon::bitset<17> b6(s, 16);
		HAMON_CXX11_CONSTEXPR hamon::bitset<17> b7(s, 17);
		HAMON_CXX11_CONSTEXPR hamon::bitset<17> b8(s, 18);

		EXPECT_EQ("00000000000000000", b0.to_string());
		EXPECT_EQ("00000000000000001", b1.to_string());
		EXPECT_EQ("00000000000000010", b2.to_string());
		EXPECT_EQ("00000000000000101", b3.to_string());
		EXPECT_EQ("00000000000001010", b4.to_string());
		EXPECT_EQ("00000000000010101", b5.to_string());
		EXPECT_EQ("01010110011100011", b6.to_string());
		EXPECT_EQ("10101100111000111", b7.to_string());
		EXPECT_EQ("10101100111000111", b8.to_string());

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b0.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b1.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b2.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, b3.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, b4.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, b5.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(9u, b6.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10u, b7.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10u, b8.count());
	}
	{
		HAMON_CXX11_CONSTEXPR const char s1[] = "110010";
		HAMON_CXX11_CONSTEXPR const char s2[] = ".1...1.1";
		HAMON_CXX11_CONSTEXPR const char s3[] = "AABABBBA";

		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b0(s1);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 1> b1(s1);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b2(s1);
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b3(s1);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b4(s1, 2);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b5(s1, 2);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b6(s1, 6);
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b7(s1, 6);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b11(s2, 8, '.');
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b12(s2, 8, '.');
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b13(s2, 8, '.');
		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b14(s3, 8, 'A', 'B');
		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b15(s3, 8, 'B', 'A');
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b16(s3, 8, 'A', 'B');
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b17(s3, 8, 'B', 'A');
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b18(s3, 8, 'A', 'B');
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b19(s3, 8, 'B', 'A');

		EXPECT_EQ("", b0.to_string());
		EXPECT_EQ("1", b1.to_string());
		EXPECT_EQ("00110010", b2.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000110010", b3.to_string());
		EXPECT_EQ("", b4.to_string());
		EXPECT_EQ("00000011", b5.to_string());
		EXPECT_EQ("00110010", b6.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000110010", b7.to_string());
		EXPECT_EQ("", b11.to_string());
		EXPECT_EQ("01000101", b12.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000001000101", b13.to_string());
		EXPECT_EQ("", b14.to_string());
		EXPECT_EQ("", b15.to_string());
		EXPECT_EQ("00101110", b16.to_string());
		EXPECT_EQ("11010001", b17.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000101110", b18.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000011010001", b19.to_string());

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0u, b0.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1u, b1.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 50u, b2.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 50u, b3.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0u, b4.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  3u, b5.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 50u, b6.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 50u, b7.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0u, b11.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 69u, b12.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 69u, b13.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0u, b14.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0u, b15.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 46u, b16.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(209u, b17.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 46u, b18.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(209u, b19.to_ulong());

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW(hamon::bitset<0> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<0> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<0> b(s3, 8, 'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<0> b(s3, 8, 'A', 'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 8, 'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 8, 'B'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 8, 'A', 'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 8, 'B', 'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s3, 8, 'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s3, 8, 'A', 'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s3, 8, 'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s3, 8, 'A', 'C'), hamon::invalid_argument);
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR const wchar_t* s = L"10101100111000111100001111100000";

		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b0(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 1> b1(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 7> b2(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b3(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 9> b4(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<15> b5(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<16> b6(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<17> b7(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<31> b8(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<32> b9(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<33> b10(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<63> b11(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b12(s);
		HAMON_CXX11_CONSTEXPR hamon::bitset<65> b13(s);

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

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b0.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b1.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b2.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b3.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(5u, b4.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, b5.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(9u, b6.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10u, b7.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b8.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b9.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b10.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b11.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b12.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b13.count());
	}
	{
		HAMON_CXX11_CONSTEXPR const wchar_t s1[] = L"110010";
		HAMON_CXX11_CONSTEXPR const wchar_t s2[] = L".1...1.1";
		HAMON_CXX11_CONSTEXPR const wchar_t s3[] = L"AABABBBA";

		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b0(s1);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 1> b1(s1);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b2(s1);
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b3(s1);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b4(s1, 2);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b5(s1, 2);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b6(s1, 6);
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b7(s1, 6);
		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b11(s2, 8, L'.');
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b12(s2, 8, L'.');
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b13(s2, 8, L'.');
		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b14(s3, 8, L'A', L'B');
		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b15(s3, 8, L'B', L'A');
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b16(s3, 8, L'A', L'B');
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b17(s3, 8, L'B', L'A');
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b18(s3, 8, L'A', L'B');
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b19(s3, 8, L'B', L'A');

		EXPECT_EQ("", b0.to_string());
		EXPECT_EQ("1", b1.to_string());
		EXPECT_EQ("00110010", b2.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000110010", b3.to_string());
		EXPECT_EQ("", b4.to_string());
		EXPECT_EQ("00000011", b5.to_string());
		EXPECT_EQ("00110010", b6.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000110010", b7.to_string());
		EXPECT_EQ("", b11.to_string());
		EXPECT_EQ("01000101", b12.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000001000101", b13.to_string());
		EXPECT_EQ("", b14.to_string());
		EXPECT_EQ("", b15.to_string());
		EXPECT_EQ("00101110", b16.to_string());
		EXPECT_EQ("11010001", b17.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000101110", b18.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000011010001", b19.to_string());

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0u, b0.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  1u, b1.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 50u, b2.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 50u, b3.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0u, b4.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  3u, b5.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 50u, b6.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 50u, b7.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0u, b11.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 69u, b12.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 69u, b13.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0u, b14.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  0u, b15.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 46u, b16.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(209u, b17.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 46u, b18.to_ulong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(209u, b19.to_ulong());

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW(hamon::bitset<0> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<0> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<0> b(s3, 8, L'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<0> b(s3, 8, L'A', L'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 8, L'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 8, L'B'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 8, L'A', L'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<1> b(s3, 8, L'B', L'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s3, 8, L'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<8> b(s3, 8, L'A', L'C'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s2), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s3), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s3, 8, L'A'), hamon::invalid_argument);
		EXPECT_THROW(hamon::bitset<64> b(s3, 8, L'A', L'C'), hamon::invalid_argument);
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<7> b("1");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("0000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<7> b("01");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("0000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<7> b("10");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("0000010", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<7> b("0000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("0000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<9> b("1");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<9> b("01");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<9> b("10");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("000000010", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<9> b("000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<32> b("0");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.count());
		EXPECT_EQ("00000000000000000000000000000000", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<32> b("1");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<32> b("10");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000010", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<32> b("11");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, b.count());
		EXPECT_EQ("00000000000000000000000000000011", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<32> b("100");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000100", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<32> b("001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<32> b("00000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<32> b("10000000000000000000000000000000");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("10000000000000000000000000000000", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<32> b("10110011100011110000111110000000");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15u, b.count());
		EXPECT_EQ("10110011100011110000111110000000", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b("1");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b("01");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b("0000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b("00000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b("000000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b("000000000000000000000000000000000000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b("0000000000000000000000000000000000000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b("1");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b("01");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b("0000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b("00000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b("000000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b("000000000000000000000000000000000000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b("0000000000000000000000000000000000000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b.count());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", b.to_string());
	}
}

}	// namespace ctor_char_ptr_test

}	// namespace hamon_bitset_test
