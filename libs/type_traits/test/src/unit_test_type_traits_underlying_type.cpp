/**
 *	@file	unit_test_type_traits_underlying_type.cpp
 *
 *	@brief	underlying_type のテスト
 */

#include <hamon/type_traits/underlying_type.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <cstddef>
#include <type_traits>
#include "type_traits_test_utility.hpp"

namespace hamon_type_traits_test
{

namespace underlying_type_test
{

#define HAMON_UNDERLYING_TYPE_TEST(T1, T2)	\
	static_assert(std::is_same<hamon::underlying_type<T1>::type, T2>::value, "");	\
	static_assert(std::is_same<hamon::underlying_type_t<T1>, T2>::value, "")

enum       E1 : char {};
enum class E2 : signed char {};
enum       E3 : unsigned char {};
enum class E4 : wchar_t {};
enum       E5 : int {};
enum class E6 : short {};
enum       E7 : long {};
enum class E8 : long long {};
enum       E9 : unsigned int {};
enum class E10 : unsigned short {};
enum       E11 : unsigned long {};
enum class E12 : unsigned long long {};
enum       E13 : std::size_t {};

//HAMON_UNDERLYING_TYPE_TEST(enum_UDT, unsigned int);	// 実装依存
HAMON_UNDERLYING_TYPE_TEST(enum_uint32_t_UDT, std::uint32_t);
HAMON_UNDERLYING_TYPE_TEST(enum_uint16_t_UDT, std::uint16_t);
HAMON_UNDERLYING_TYPE_TEST(enum_uint8_t_UDT,  std::uint8_t);
HAMON_UNDERLYING_TYPE_TEST(enum_int32_t_UDT,  std::int32_t);
HAMON_UNDERLYING_TYPE_TEST(enum_int16_t_UDT,  std::int16_t);
HAMON_UNDERLYING_TYPE_TEST(enum_int8_t_UDT,   std::int8_t);
HAMON_UNDERLYING_TYPE_TEST(enum_class_UDT, int);
HAMON_UNDERLYING_TYPE_TEST(enum_class_uint32_t_UDT, std::uint32_t);
HAMON_UNDERLYING_TYPE_TEST(enum_class_uint16_t_UDT, std::uint16_t);
HAMON_UNDERLYING_TYPE_TEST(enum_class_uint8_t_UDT,  std::uint8_t);
HAMON_UNDERLYING_TYPE_TEST(enum_class_int32_t_UDT,  std::int32_t);
HAMON_UNDERLYING_TYPE_TEST(enum_class_int16_t_UDT,  std::int16_t);
HAMON_UNDERLYING_TYPE_TEST(enum_class_int8_t_UDT,   std::int8_t);

HAMON_UNDERLYING_TYPE_TEST(E1, char);
HAMON_UNDERLYING_TYPE_TEST(E2, signed char);
HAMON_UNDERLYING_TYPE_TEST(E3, unsigned char);
HAMON_UNDERLYING_TYPE_TEST(E4, wchar_t);
HAMON_UNDERLYING_TYPE_TEST(E5, int);
HAMON_UNDERLYING_TYPE_TEST(E6, short);
HAMON_UNDERLYING_TYPE_TEST(E7, long);
HAMON_UNDERLYING_TYPE_TEST(E8, long long);
HAMON_UNDERLYING_TYPE_TEST(E9, unsigned int);
HAMON_UNDERLYING_TYPE_TEST(E10, unsigned short);
HAMON_UNDERLYING_TYPE_TEST(E11, unsigned long);
HAMON_UNDERLYING_TYPE_TEST(E12, unsigned long long);
HAMON_UNDERLYING_TYPE_TEST(E13, std::size_t);

#undef HAMON_UNDERLYING_TYPE_TEST

}	// namespace underlying_type_test

}	// namespace hamon_type_traits_test
