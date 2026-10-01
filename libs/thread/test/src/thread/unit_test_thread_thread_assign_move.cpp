/**
 *	@file	unit_test_thread_thread_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 *
 *	thread& operator=(thread&& x) noexcept;
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace assign_move_test
{

static_assert( hamon::is_move_assignable_v<hamon::thread>, "");
static_assert( hamon::is_nothrow_move_assignable_v<hamon::thread>, "");
static_assert(!hamon::is_trivially_move_assignable_v<hamon::thread>, "");

GTEST_TEST(ThreadTest, AssignMoveTest)
{
	int x = 0;
	int y = 0;
	hamon::thread t1([&] { ++x; });
	auto id1 = t1.get_id();
	hamon::thread t2([&] { ++y; });
	auto id2 = t2.get_id();

	t2.join();
	auto& r = (t2 = hamon::move(t1));

	EXPECT_TRUE(&r == &t2);
	EXPECT_TRUE(&r != &t1);

	// [thread.thread.assign]/2
	EXPECT_TRUE(t1.get_id() == hamon::thread::id());
	EXPECT_TRUE(t1.get_id() != id1);
	EXPECT_TRUE(t1.get_id() != id2);
	EXPECT_TRUE(t2.get_id() == id1);
	EXPECT_TRUE(t2.get_id() != id2);
	EXPECT_TRUE(t2.get_id() != hamon::thread::id());

	t2.join();

	EXPECT_EQ(1, x);
	EXPECT_EQ(1, y);
}

}	// namespace assign_move_test

}	// namespace hamon_thread_test
