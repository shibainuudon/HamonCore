/**
 *	@file	unit_test_hive_block_capacity_hard_limits.cpp
 *
 *	@brief	block_capacity_hard_limits のテスト
 *
 *	static constexpr hive_limits block_capacity_hard_limits() noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace block_capacity_hard_limits_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using Allocator = typename Hive::allocator_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().block_capacity_hard_limits()), hamon::hive_limits>::value, "");
	static_assert(noexcept(hamon::declval<Hive>().block_capacity_hard_limits()), "");

	auto hard_limits = Hive::block_capacity_hard_limits();
	VERIFY(hard_limits.min <= hard_limits.max);
	VERIFY(hard_limits.max <= hamon::allocator_traits<Allocator>::max_size(Allocator{}));

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, BlockCapacityHardLimitsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace block_capacity_hard_limits_test

}	// namespace hamon_hive_test
