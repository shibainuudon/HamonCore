/**
 *	@file	unit_test_bigint_sub.cpp
 *
 *	@brief	operator-のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_sub_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SubTest()
{
	{
		auto x = BigInt{0} - BigInt{0};
		VERIFY(x == BigInt(0));
	}
	{
		auto x = BigInt{1} - BigInt{0};
		VERIFY(x == BigInt(1));
	}
	{
		auto x = BigInt{5} - BigInt{2};
		VERIFY(x == BigInt(3));
	}
	{
		auto x = BigInt{1000} - BigInt{1};
		VERIFY(x == BigInt(999));
	}
	{
		auto x = BigInt{1000} - BigInt{999};
		VERIFY(x == BigInt(1));
	}
	{
		auto x = BigInt{1000} - BigInt{1000};
		VERIFY(x == BigInt(0));
	}
	{
		auto x = BigInt{1000} - BigInt{1001};
		VERIFY(x == BigInt(-1));
	}
	{
		auto x = BigInt( 2) - BigInt( 5);
		VERIFY(x == BigInt(-3));
	}
	{
		auto x = BigInt( 2) - BigInt(-5);
		VERIFY(x == BigInt(7));
	}
	{
		auto x = BigInt(-2) - BigInt( 5);
		VERIFY(x == BigInt(-7));
	}
	{
		auto x = BigInt(-2) - BigInt(-5);
		VERIFY(x == BigInt(3));
	}
	{
		auto x = BigInt{256} - BigInt{1};
		VERIFY(x == BigInt(255));
	}
	{
		auto x = BigInt{0x10000} - BigInt{1};
		VERIFY(x == BigInt(0xffff));
	}
	{
		auto x = BigInt{0x1000000} - BigInt{1};
		VERIFY(x == BigInt(0xffffff));
	}
	{
		auto x = BigInt{0x1000000} - BigInt{0xffffff};
		VERIFY(x == BigInt(1));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SubTest2()
{
	{
		auto x =
			BigInt{"8427663852327746832635939785432364562824"} -
			BigInt{"7567723894568827633575594573939298395955"};
		VERIFY(x == BigInt{"859939957758919199060345211493066166869"});
	}
	{
		auto x =
			BigInt{"4831358420296681146974351689067644777329"} -
			BigInt{"8250655382930189933211483422173351786903"};
		VERIFY(x == BigInt{"-3419296962633508786237131733105707009574"});
	}
	{
		auto x =
			BigInt{"100000000000000000000000000000000000000"} -
			BigInt{1};
		VERIFY(x == BigInt{"99999999999999999999999999999999999999"});
	}
	return true;
}

GTEST_TEST(BigIntTest, SubTest)
{
	EXPECT_TRUE(SubTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest<hamon::uint2048_t>());

	EXPECT_TRUE(SubTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SubTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_sub_test

}	// namespace hamon_bigint_test

