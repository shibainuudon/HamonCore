/**
 *	@file	unit_test_hive_block_capacity_default_limits.cpp
 *
 *	@brief	block_capacity_default_limits のテスト
 *
 *	static constexpr hive_limits block_capacity_default_limits() noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace block_capacity_default_limits_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().block_capacity_default_limits()), hamon::hive_limits>::value, "");
	static_assert(noexcept(hamon::declval<Hive>().block_capacity_default_limits()), "");

	auto default_limits = Hive::block_capacity_default_limits();
	auto hard_limits = Hive::block_capacity_hard_limits();
	VERIFY(default_limits.min <= default_limits.max);
	VERIFY(default_limits.min >= hard_limits.min);
	VERIFY(default_limits.max <= hard_limits.max);

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, BlockCapacityDefaultLimitsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace block_capacity_default_limits_test

}	// namespace hamon_hive_test
