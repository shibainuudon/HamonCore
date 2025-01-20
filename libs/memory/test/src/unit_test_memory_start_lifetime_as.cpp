/**
 *	@file	unit_test_memory_start_lifetime_as.cpp
 *
 *	@brief	start_lifetime_as のテスト
 */

#include <hamon/memory/start_lifetime_as.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_memory_test
{

namespace start_lifetime_as_test
{

template <typename T>
struct Point
{
	T x;
	T y;
};

GTEST_TEST(MemoryTest, StartLifetimeAsTest)
{
	{
		alignas(Point<float>) unsigned char data[sizeof(Point<float>)]
		{
			0xcd, 0xcc, 0xcc, 0x3d, 0xcd, 0xcc, 0x4c, 0x3e,
		};
		auto* d = hamon::start_lifetime_as<Point<float>>(data);
		static_assert(hamon::is_same<decltype(d), Point<float>*>::value, "");
		EXPECT_EQ(0.1f, d->x);
		EXPECT_EQ(0.2f, d->y);
	}
	{
		alignas(Point<hamon::int32_t>) unsigned char const data[sizeof(Point<hamon::int32_t>)]
		{
			0xcd, 0xcc, 0xcc, 0x3d, 0xcd, 0xcc, 0x4c, 0x3e,
		};
		auto* d = hamon::start_lifetime_as<Point<hamon::int32_t>>(data);
		static_assert(hamon::is_same<decltype(d), Point<hamon::int32_t> const*>::value, "");
		EXPECT_EQ(0x3dcccccd, d->x);
		EXPECT_EQ(0x3e4ccccd, d->y);
	}
	{
		alignas(Point<hamon::uint64_t>) unsigned char volatile data[sizeof(Point<hamon::uint64_t>)]
		{
			0xcd, 0xcc, 0xcc, 0x3d, 0xcd, 0xcc, 0x4c, 0x3e,
		};
		auto* d = hamon::start_lifetime_as<Point<hamon::uint64_t>>(data);
		static_assert(hamon::is_same<decltype(d), Point<hamon::uint64_t> volatile*>::value, "");
		EXPECT_EQ(0x3e4ccccd3dcccccdu, d->x);
		EXPECT_EQ(0x0000000000000000u, d->y);
	}
	{
		alignas(Point<float>) unsigned char const volatile data[sizeof(Point<float>)]
		{
			0x9a, 0x99, 0x99, 0x3e, 0xcd, 0xcc, 0xcc, 0x3e,
		};
		auto* d = hamon::start_lifetime_as<Point<float>>(data);
		static_assert(hamon::is_same<decltype(d), Point<float> const volatile*>::value, "");
		EXPECT_EQ(0.3f, d->x);
		EXPECT_EQ(0.4f, d->y);
	}
}

}	// namespace start_lifetime_as_test

}	// namespace hamon_memory_test
