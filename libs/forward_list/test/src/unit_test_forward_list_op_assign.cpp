/**
 *	@file	unit_test_forward_list_op_assign.cpp
 *
 *	@brief	代入演算子のテスト
 *
 *	forward_list& operator=(const forward_list& x);
 *	forward_list& operator=(forward_list&& x)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value);
 *	forward_list& operator=(initializer_list<T>);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace op_assign_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, OpAssignTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace op_assign_test

}	// namespace hamon_forward_list_test
