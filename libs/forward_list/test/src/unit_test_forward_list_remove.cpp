/**
 *	@file	unit_test_forward_list_remove.cpp
 *
 *	@brief	remove のテスト
 *
 *	size_type remove(const T& value);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace remove_test
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

GTEST_TEST(ForwardListTest, RemoveTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<int>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<char>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<float>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<S1>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<S2>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<S3>());
}

}	// namespace remove_test

}	// namespace hamon_forward_list_test
