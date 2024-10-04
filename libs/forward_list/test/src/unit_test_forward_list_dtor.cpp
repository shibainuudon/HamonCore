/**
 *	@file	unit_test_forward_list_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~forward_list();
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace dtor_test
{

struct S
{
	~S()
	{
		++s_dtor_count;
	}

	static int s_dtor_count;
};

int S::s_dtor_count = 0;

GTEST_TEST(ForwardListTest, DtorTest)
{
	S::s_dtor_count = 0;
	{
		hamon::forward_list<S> v;
	}
	EXPECT_EQ(0, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::forward_list<S> v(1);
	}
	EXPECT_EQ(1, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::forward_list<S> v(3);
	}
	EXPECT_EQ(3, S::s_dtor_count);
}

}	// namespace dtor_test

}	// namespace hamon_forward_list_test
