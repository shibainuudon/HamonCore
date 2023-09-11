/**
 *	@file	unit_test_bit_endian.cpp
 *
 *	@brief	endian のテスト
 */

#include <hamon/bit/endian.hpp>
#include <hamon/cstdint/uint8_t.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <hamon/cstring/memcpy.hpp>
#include <hamon/type_traits/underlying_type.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <gtest/gtest.h>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4127)	// conditional expression is constant

GTEST_TEST(BitTest, EndianTest)
{
	static_assert(hamon::is_enum<hamon::endian>::value, "");

	using UT = hamon::underlying_type_t<hamon::endian>;
	static_assert(!hamon::is_convertible<hamon::endian, UT>::value, "");

	// test that the enumeration values exist
	static_assert(hamon::endian::little == hamon::endian::little, "");
	static_assert(hamon::endian::big    == hamon::endian::big, "");
	static_assert(hamon::endian::native == hamon::endian::native, "");
	static_assert(hamon::endian::little != hamon::endian::big, "");

	//  Technically not required, but true on all existing machines
	static_assert(
		hamon::endian::native == hamon::endian::little ||
		hamon::endian::native == hamon::endian::big, "");

	//  Try to check at runtime
	{
		hamon::uint32_t i = 0x01020304;
		hamon::uint8_t c[4];
		hamon::memcpy(c, &i, sizeof(c));

		if (hamon::endian::native == hamon::endian::big)
		{
			EXPECT_EQ(1, c[0]);
			EXPECT_EQ(2, c[1]);
			EXPECT_EQ(3, c[2]);
			EXPECT_EQ(4, c[3]);
		}
		else
		{
			EXPECT_EQ(4, c[0]);
			EXPECT_EQ(3, c[1]);
			EXPECT_EQ(2, c[2]);
			EXPECT_EQ(1, c[3]);
		}
	}
}

HAMON_WARNING_POP()
