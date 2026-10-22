/**
 *	@file	unit_test_thread_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	thread(thread&& x) noexcept;
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace ctor_move_test
{

static_assert( hamon::is_move_constructible_v<hamon::thread>, "");
static_assert( hamon::is_nothrow_move_constructible_v<hamon::thread>, "");
static_assert(!hamon::is_trivially_move_constructible_v<hamon::thread>, "");
static_assert( hamon::is_implicitly_move_constructible_v<hamon::thread>, "");

GTEST_TEST(ThreadTest, CtorMoveTest)
{
	int x = 0;
	hamon::thread t1([&] { ++x; });
	auto id1 = t1.get_id();
	hamon::thread t2(hamon::move(t1));

	// [thread.thread.constr]/11
	EXPECT_TRUE(t1.get_id() == hamon::thread::id());
	EXPECT_TRUE(t1.get_id() != id1);
	EXPECT_TRUE(t2.get_id() == id1);
	EXPECT_TRUE(t2.get_id() != hamon::thread::id());

	t2.join();

	EXPECT_EQ(1, x);
}

}	// namespace ctor_move_test

}	// namespace hamon_thread_test
