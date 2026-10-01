/**
 *	@file	unit_test_thread_thread_join.cpp
 *
 *	@brief	join のテスト
 *
 *	void join();
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace join_test
{

GTEST_TEST(ThreadTest, JoinTest)
{
	int x = 0;
	hamon::thread t([&] { ++x; });

	static_assert(!noexcept(t.join()), "");
	static_assert(hamon::is_same_v<decltype(t.join()), void>, "");

	t.join();

	// [thread.thread.member]/5
	EXPECT_TRUE(t.get_id() == hamon::thread::id());

	// TODO: Test throwing system_error
}

}	// namespace join_test

}	// namespace hamon_thread_test
