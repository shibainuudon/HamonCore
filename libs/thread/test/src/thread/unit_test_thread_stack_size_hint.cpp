/**
 *	@file	unit_test_thread_stack_size_hint.cpp
 *
 *	@brief	thread::stack_size_hint のテスト
 */

#include <hamon/thread/thread.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace stack_size_hint_test
{

void work(int n)
{
	(void)n;
}

GTEST_TEST(ThreadTest, StackSizeHintTest)
{
	// スタックサイズ512KiBのヒントを指定してスレッドを生成する
	hamon::thread t{ hamon::thread::stack_size_hint(512 * 1024), work, 42 };

	t.join();
}

}	// namespace stack_size_hint_test

}	// namespace hamon_thread_test
