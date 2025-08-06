/**
 *	@file	unit_test_hive_block_capacity_limits.cpp
 *
 *	@brief	block_capacity_limits のテスト
 *
 *	constexpr hive_limits block_capacity_limits() const noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace block_capacity_limits_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().block_capacity_limits()), hamon::hive_limits>::value, "");
	static_assert(noexcept(hamon::declval<Hive>().block_capacity_limits()), "");

	{
		Hive const v;
		VERIFY(v.block_capacity_limits().min == v.block_capacity_default_limits().min);
		VERIFY(v.block_capacity_limits().max == v.block_capacity_default_limits().max);
	}
	{
		Hive const v{hamon::hive_limits{10, 100}};
		VERIFY(v.block_capacity_limits().min == 10);
		VERIFY(v.block_capacity_limits().max == 100);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, BlockCapacityLimitsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace block_capacity_limits_test

}	// namespace hamon_hive_test
