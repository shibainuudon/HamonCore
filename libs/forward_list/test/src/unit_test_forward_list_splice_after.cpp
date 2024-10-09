/**
 *	@file	unit_test_forward_list_splice_after.cpp
 *
 *	@brief	splice_after のテスト
 *
 *	void splice_after(const_iterator position, forward_list& x);
 *	void splice_after(const_iterator position, forward_list&& x);
 *	void splice_after(const_iterator position, forward_list& x, const_iterator i);
 *	void splice_after(const_iterator position, forward_list&& x, const_iterator i);
 *	void splice_after(const_iterator position, forward_list& x, const_iterator first, const_iterator last);
 *	void splice_after(const_iterator position, forward_list&& x, const_iterator first, const_iterator last);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace splice_after_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, SpliceAfterTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace splice_after_test

}	// namespace hamon_forward_list_test
