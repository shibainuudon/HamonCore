/**
 *	@file	unit_test_thread_joinable.cpp
 *
 *	@brief	joinable のテスト
 *
 *	bool joinable() const noexcept;
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace joinable_test
{

GTEST_TEST(ThreadTest, JoinableTest)
{
	int x = 0;
	hamon::thread t1([&] { ++x; });
	hamon::thread t2;

	static_assert(noexcept(t1.joinable()), "");
	static_assert(hamon::is_same_v<decltype(t1.joinable()), bool>, "");

	EXPECT_TRUE (t1.joinable());
	EXPECT_FALSE(t2.joinable());

	t1.join();

	EXPECT_FALSE(t1.joinable());
	EXPECT_FALSE(t2.joinable());
}

}	// namespace joinable_test

}	// namespace hamon_thread_test
