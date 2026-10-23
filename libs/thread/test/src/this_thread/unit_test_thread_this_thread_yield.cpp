/**
 *	@file	unit_test_thread_this_thread_yield.cpp
 *
 *	@brief	this_thread::yield のテスト
 *
 *	thread::id yield() noexcept;
 */

#include <hamon/thread/this_thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/atomic.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace this_thread_yield_test
{

GTEST_TEST(ThisThreadTest, YieldTest)
{
	static_assert(noexcept(hamon::this_thread::yield()), "");
	static_assert(hamon::is_same_v<decltype(hamon::this_thread::yield()), void>, "");

	hamon::atomic<bool> done(false);
	int result;

	hamon::thread t([&] {
		// 別スレッド上での処理...
		result = 42;
		done = true;
	});

	// ビジーループによる待機
	while (!done)
	{
		// yield()呼出により待機側スレッドのCPUリソース占有を避ける
		hamon::this_thread::yield();
	}

	EXPECT_EQ(42, result);

	t.join();
}

}	// namespace this_thread_yield_test

}	// namespace hamon_thread_test
