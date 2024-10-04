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

struct S1
{
	S1() = delete;
};

struct S2
{
	S2() {}
};

struct S3
{
	int x;
	float y;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, CtadTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<int>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<char>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<float>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<S1>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<S2>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<S3>());
}

}	// namespace ctad_test

}	// namespace hamon_forward_list_test
