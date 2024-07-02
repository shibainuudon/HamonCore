/**
 *	@file	unit_test_deque_get_allocator.cpp
 *
 *	@brief	get_allocator のテスト
 *
 *	allocator_type get_allocator() const noexcept;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace get_allocator_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Allocator = std::allocator<T>;
	using Deque = hamon::deque<T, Allocator>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque>().get_allocator()),
		Allocator
	>::value, "");
	static_assert(noexcept(
		hamon::declval<Deque>().get_allocator()), "");

	Allocator alloc;
	Deque v(alloc);
	VERIFY(v.get_allocator() == alloc);

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, GetAllocatorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace get_allocator_test

}	// namespace hamon_deque_test
