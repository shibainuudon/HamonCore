/**
 *	@file	bitflags_test.hpp
 *
 *	@brief
 */

#ifndef UNIT_TEST_BITFLAGS_BITFLAGS_TEST_HPP
#define UNIT_TEST_BITFLAGS_BITFLAGS_TEST_HPP

#include <hamon/bitflags.hpp>
#include <cstdint>

namespace hamon_bitflags_test
{

enum Enum1
{
	kOption1,
	kOption2,
	kOption3,
};

enum class Enum2 : std::uint8_t
{
	kOption4,
	kOption5,
	kOption6,
	kOption7,
	kOption8,
};

enum class Enum3 : std::uint16_t
{
	kOption7 = 1,
	kOption8 = 4,
	kOption9 = 5,
};

using Bitflag1 = hamon::bitflags<Enum1>;
using Bitflag2 = hamon::bitflags<Enum2, 5, true>;
using Bitflag3 = hamon::bitflags<Enum3, 16>;

}	// namespace hamon_bitflags_test

#endif // UNIT_TEST_BITFLAGS_BITFLAGS_TEST_HPP
