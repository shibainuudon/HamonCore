/**
 *	@file	unit_test_list_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~list();
 */

#include <hamon/list/list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
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

GTEST_TEST(ListTest, DtorTest)
{
	S::s_dtor_count = 0;
	{
		hamon::list<S> v;
	}
	EXPECT_EQ(0, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::list<S> v(1);
	}
	EXPECT_EQ(1, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::list<S> v(3);
	}
	EXPECT_EQ(3, S::s_dtor_count);
}

}	// namespace dtor_test

}	// namespace hamon_list_test
