/**
 *	@file	unit_test_thread_thread_stack_size_hint.cpp
 *
 *	@brief	thread::stack_size_hint のテスト
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits.hpp>
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
	static_assert(!hamon::is_default_constructible_v<hamon::thread::stack_size_hint>, "");
	static_assert( hamon::is_copy_constructible_v<hamon::thread::stack_size_hint>, "");
	static_assert( hamon::is_move_constructible_v<hamon::thread::stack_size_hint>, "");
	static_assert( hamon::is_constructible_v<hamon::thread::stack_size_hint, hamon::size_t>, "");
	static_assert( hamon::is_nothrow_constructible_v<hamon::thread::stack_size_hint, hamon::size_t>, "");
	static_assert(!hamon::is_implicitly_constructible_v<hamon::thread::stack_size_hint, hamon::size_t>, "");
	static_assert( hamon::is_copy_assignable_v<hamon::thread::stack_size_hint>, "");
	static_assert( hamon::is_move_assignable_v<hamon::thread::stack_size_hint>, "");

	// スタックサイズ512KiBのヒントを指定してスレッドを生成する
	hamon::thread t{ hamon::thread::stack_size_hint(512 * 1024), work, 42 };

	t.join();
}

}	// namespace stack_size_hint_test

}	// namespace hamon_thread_test
