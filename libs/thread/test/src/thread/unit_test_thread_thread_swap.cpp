/**
 *	@file	unit_test_thread_thread_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	void swap(thread& x) noexcept;
 *	void swap(thread& x, thread& y) noexcept;
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace swap_test
{

GTEST_TEST(ThreadTest, SwapTest)
{
	int x = 0;
	int y = 0;
	hamon::thread t1([&] { ++x; });
	auto id1 = t1.get_id();
	hamon::thread t2([&] { y+=2; });
	auto id2 = t2.get_id();

	static_assert(noexcept(t1.swap(t2)), "");
	static_assert(hamon::is_same_v<decltype(t1.swap(t2)), void>, "");
	t1.swap(t2);

	EXPECT_TRUE(t1.get_id() != id1);
	EXPECT_TRUE(t1.get_id() == id2);
	EXPECT_TRUE(t1.get_id() != hamon::thread::id());
	EXPECT_TRUE(t2.get_id() == id1);
	EXPECT_TRUE(t2.get_id() != id2);
	EXPECT_TRUE(t2.get_id() != hamon::thread::id());

	static_assert(noexcept(swap(t1, t2)), "");
	static_assert(hamon::is_same_v<decltype(swap(t1, t2)), void>, "");
	swap(t1, t2);

	EXPECT_TRUE(t1.get_id() == id1);
	EXPECT_TRUE(t1.get_id() != id2);
	EXPECT_TRUE(t1.get_id() != hamon::thread::id());
	EXPECT_TRUE(t2.get_id() != id1);
	EXPECT_TRUE(t2.get_id() == id2);
	EXPECT_TRUE(t2.get_id() != hamon::thread::id());

	t1.join();
	t2.join();

	EXPECT_EQ(1, x);
	EXPECT_EQ(2, y);
}

}	// namespace swap_test

}	// namespace hamon_thread_test
