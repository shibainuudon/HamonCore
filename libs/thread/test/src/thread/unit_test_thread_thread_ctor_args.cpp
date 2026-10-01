/**
 *	@file	unit_test_thread_thread_ctor_args.cpp
 *
 *	@brief	argsを引数に取るコンストラクタのテスト
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
	{
		int x = 0;
		hamon::thread t1([&] { x = 42; });
		int y = 0;
		hamon::thread t2([&](int i) { y = i * 2; }, 13);
		int z = 0;
		hamon::thread t3([&](int a, int b) { z = a + b; }, 2, 3);

		// [thread.thread.constr]/8
		EXPECT_TRUE(t1.get_id() != hamon::thread::id());
		EXPECT_TRUE(t2.get_id() != hamon::thread::id());
		EXPECT_TRUE(t3.get_id() != hamon::thread::id());

		t1.join();
		t2.join();
		t3.join();

		EXPECT_EQ(42, x);
		EXPECT_EQ(26, y);
		EXPECT_EQ( 5, z);
	}
	{
		int x = 0;
		hamon::thread t{
			hamon::thread::stack_size_hint(1234),
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::thread::name_hint("TestThread"),
#else
			hamon::thread::name_hint<char>("TestThread"),
#endif
			[&](int a, int b) { x = a * b; },
			3,
			13
		};
		t.join();
		EXPECT_EQ(39, x);
	}
}

}	// namespace ctor_args_test

}	// namespace hamon_thread_test
