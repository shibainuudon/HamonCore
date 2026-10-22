/**
 *	@file	unit_test_thread_ctor_args.cpp
 *
 *	@brief	コンストラクタのテスト
 *
 *	template<class... Args> explicit thread(Args&&... args);
 */

#include <hamon/thread/thread.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace ctor_args_test
{

GTEST_TEST(ThreadTest, CtorArgsTest)
{
	int x = 0;
	hamon::thread t([&] { x = 42; });

	// [thread.thread.constr]/8
	EXPECT_TRUE(t.get_id() != hamon::thread::id());

	t.join();

	EXPECT_EQ(42, x);
}

}	// namespace ctor_args_test

}	// namespace hamon_thread_test
