/**
 *	@file	unit_test_vector_get_allocator.cpp
 *
 *	@brief	get_allocator のテスト
 *
 *	constexpr allocator_type get_allocator() const noexcept;
 */

#include <hamon/vector.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace get_allocator_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test()
{
	using T = int;
	using Allocator = hamon::allocator<T>;
	using Vector = hamon::vector<T, Allocator>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector>().get_allocator()),
		Allocator
	>::value, "");
	static_assert(noexcept(
		hamon::declval<Vector>().get_allocator()), "");

	Allocator alloc;
	Vector v(alloc);
	VERIFY(v.get_allocator() == alloc);

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, GetAllocatorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace get_allocator_test

}	// namespace hamon_vector_test
