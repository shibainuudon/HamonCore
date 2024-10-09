/**
 *	@file	unit_test_forward_list_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator, class Allocator = allocator<iter-value-type<InputIterator>>>
 *	forward_list(InputIterator, InputIterator, Allocator = Allocator())
 *		-> forward_list<iter-value-type<InputIterator>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator = allocator<ranges::range_value_t<R>>>
 *	forward_list(from_range_t, R&&, Allocator = Allocator())
 *		-> forward_list<ranges::range_value_t<R>, Allocator>;
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace ctad_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, CtadTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace ctad_test

}	// namespace hamon_forward_list_test
