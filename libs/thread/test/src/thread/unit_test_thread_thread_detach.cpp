/**
 *	@file	unit_test_thread_thread_detach.cpp
 *
 *	@brief	detach のテスト
 *
 *	void detach();
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace detach_test
{

GTEST_TEST(ThreadTest, DetachTest)
{
	int x = 0;
	hamon::thread t([&] { ++x; });

	static_assert(!noexcept(t.detach()), "");
	static_assert(hamon::is_same_v<decltype(t.detach()), void>, "");

	t.detach();

	// [thread.thread.member]/9
	EXPECT_TRUE(t.get_id() == hamon::thread::id());

	// TODO: Test throwing system_error
}

}	// namespace detach_test

}	// namespace hamon_thread_test
