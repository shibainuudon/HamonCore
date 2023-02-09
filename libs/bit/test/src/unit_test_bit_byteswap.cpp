/**
 *	@file	unit_test_bit_byteswap.cpp
 *
 *	@brief	byteswap のテスト
 */

#include <hamon/bit/byteswap.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>
#include <utility>
#include "constexpr_test.hpp"

namespace hamon_bit_test
{
namespace byteswap_test
{

template <typename T>
struct has_byteswap_impl
{
private:
	template <typename U, typename = decltype(hamon::byteswap(std::declval<U>()))>
	static auto test(int) -> std::true_type;

	template <typename>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_byteswap = typename has_byteswap_impl<T>::type;

static_assert( has_byteswap<signed char>::value, "");
static_assert( has_byteswap<signed char>::value, "");
static_assert( has_byteswap<signed short>::value, "");
static_assert( has_byteswap<signed int>::value, "");
static_assert( has_byteswap<signed long>::value, "");
static_assert( has_byteswap<signed long long>::value, "");
static_assert( has_byteswap<unsigned char>::value, "");
static_assert( has_byteswap<unsigned short>::value, "");
static_assert( has_byteswap<unsigned int>::value, "");
static_assert( has_byteswap<unsigned long>::value, "");
static_assert( has_byteswap<unsigned long long>::value, "");
static_assert( has_byteswap<bool>::value, "");
static_assert( has_byteswap<char>::value, "");
static_assert( has_byteswap<wchar_t>::value, "");
#if defined(HAMON_HAS_CXX11_CHAR16_T)
static_assert( has_byteswap<char16_t>::value, "");
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
static_assert( has_byteswap<char32_t>::value, "");
#endif
#if defined(HAMON_HAS_CXX20_CHAR8_T)
static_assert( has_byteswap<char8_t>::value, "");
#endif

static_assert(!has_byteswap<int *>::value, "");
static_assert(!has_byteswap<int const*>::value, "");
static_assert( has_byteswap<int &>::value, "");
static_assert( has_byteswap<int const &>::value, "");
static_assert( has_byteswap<int &&>::value, "");
static_assert( has_byteswap<int const &&>::value, "");
static_assert(!has_byteswap<int[]>::value, "");
static_assert(!has_byteswap<int[2]>::value, "");
static_assert(!has_byteswap<void>::value, "");
static_assert(!has_byteswap<void*>::value, "");
static_assert(!has_byteswap<float>::value, "");
static_assert(!has_byteswap<double>::value, "");
static_assert(!has_byteswap<long double>::value, "");

template <typename T>
HAMON_CXX11_CONSTEXPR bool ByteswapTest(T x, T y)
{
	static_assert(std::is_same<decltype(hamon::byteswap(x)), decltype(x)>::value, "");
	static_assert(noexcept(hamon::byteswap(x)), "");
	return hamon::byteswap(x) == y;
}

GTEST_TEST(BitTest, ByteswapTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::uint8_t>(0x12, 0x12)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::uint8_t>(0xAB, 0xAB)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::uint16_t>(0x1234, 0x3412)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::uint16_t>(0xABCD, 0xCDAB)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::uint32_t>(0x12345678, 0x78563412)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::uint32_t>(0x01234567, 0x67452301)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::uint64_t>(0x123456789ABCDEF0, 0xF0DEBC9A78563412)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::uint64_t>(0x0123456789ABCDEF, 0xEFCDAB8967452301)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::int8_t>(0x12, 0x12)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::int8_t>(0x34, 0x34)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::int16_t>(0x1234, 0x3412)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::int16_t>(0x7654, 0x5476)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::int32_t>(0x12345678, 0x78563412)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::int32_t>(0x01234567, 0x67452301)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::int64_t>(std::int64_t(0x123456789ABCDEF0), std::int64_t(0xF0DEBC9A78563412))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<std::int64_t>(std::int64_t(0x0123456789ABCDEF), std::int64_t(0xEFCDAB8967452301))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<bool>(true,  true)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<bool>(false, false)));

#if defined(HAMON_HAS_CXX20_CHAR8_T)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<char8_t>(0xAB, 0xAB)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<char8_t>(0xBA, 0xBA)));
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<char16_t>(0xABCD, 0xCDAB)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<char16_t>(0x3210, 0x1032)));
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<char32_t>(0xABCDEF01, 0x01EFCDAB)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((ByteswapTest<char32_t>(0x87654321, 0x21436587)));
#endif
}

}	// namespace byteswap_test
}	// namespace hamon_bit_test
