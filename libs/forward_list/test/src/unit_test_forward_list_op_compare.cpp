/**
 *	@file	unit_test_forward_list_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class T, class Allocator>
 *	bool operator==(const forward_list<T, Allocator>& x, const forward_list<T, Allocator>& y);
 *
 *	template<class T, class Allocator>
 *	synth-three-way-result<T>
 *	operator<=>(const forward_list<T, Allocator>& x, const forward_list<T, Allocator>& y);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace op_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, OpCompareTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace op_compare_test

}	// namespace hamon_forward_list_test
