/**
 *	@file	unit_test_forward_list_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	void swap(forward_list&)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value);
 *
 *	template<class T, class Allocator>
 *	void swap(forward_list<T, Allocator>& x, forward_list<T, Allocator>& y)
 *		noexcept(noexcept(x.swap(y)));
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, SwapTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace swap_test

}	// namespace hamon_forward_list_test
