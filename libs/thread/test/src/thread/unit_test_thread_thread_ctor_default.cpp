/**
 *	@file	unit_test_thread_thread_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	thread() noexcept;
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace ctor_default_test
{

static_assert( hamon::is_default_constructible_v<hamon::thread>, "");
static_assert( hamon::is_nothrow_default_constructible_v<hamon::thread>, "");
static_assert(!hamon::is_trivially_default_constructible_v<hamon::thread>, "");
static_assert( hamon::is_implicitly_default_constructible_v<hamon::thread>, "");

GTEST_TEST(ThreadTest, CtorDefaultTest)
{
	hamon::thread t;
	EXPECT_TRUE(t.get_id() == hamon::thread::id());	// [thread.thread.constr]/2
}

}	// namespace ctor_default_test

}	// namespace hamon_thread_test
