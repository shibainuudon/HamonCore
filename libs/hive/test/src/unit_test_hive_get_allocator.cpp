/**
 *	@file	unit_test_hive_get_allocator.cpp
 *
 *	@brief	get_allocator のテスト
 *
 *	allocator_type get_allocator() const noexcept;
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "hive_test_helper.hpp"

namespace hamon_hive_test
{

namespace get_allocator_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T, TestAllocator2<T>>;
	using Allocator = typename Hive::allocator_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().get_allocator()), Allocator>::value, "");
	static_assert(noexcept(hamon::declval<Hive>().get_allocator()), "");

	Allocator a1{10};
	Allocator a2{20};

	Hive v1(a1);
	VERIFY(v1.get_allocator() == a1);
	VERIFY(v1.get_allocator() != a2);

	Hive v2(a2);
	VERIFY(v2.get_allocator() != a1);
	VERIFY(v2.get_allocator() == a2);

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, GetAllocatorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace get_allocator_test

}	// namespace hamon_hive_test
