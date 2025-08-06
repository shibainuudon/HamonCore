/**
 *	@file	unit_test_hive_capacity.cpp
 *
 *	@brief	capacity のテスト
 *
 *	size_type capacity() const noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace capacity_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using SizeType = typename Hive::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().capacity()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<Hive>().capacity()), "");

	Hive v;
	VERIFY(v.capacity() == 0u);

	v.emplace(T{1});
	VERIFY(v.capacity() >= 1u);

	v.emplace(T{1});
	VERIFY(v.capacity() >= 2u);

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, CapacityTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace capacity_test

}	// namespace hamon_hive_test
