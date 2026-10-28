/**
 *	@file	unit_test_thread_jthread_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	jthread(jthread&&) noexcept;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace ctor_move_test
{

static_assert( hamon::is_move_constructible_v<hamon::jthread>, "");
static_assert( hamon::is_nothrow_move_constructible_v<hamon::jthread>, "");
static_assert(!hamon::is_trivially_move_constructible_v<hamon::jthread>, "");
static_assert( hamon::is_implicitly_move_constructible_v<hamon::jthread>, "");

GTEST_TEST(JThreadTest, CtorMoveTest)
{
	{
		// x.get_id() == id() and get_id() returns the value of x.get_id() prior
		// to the start of construction.
		hamon::jthread j1([] {});
		auto id1 = j1.get_id();

		hamon::jthread j2(hamon::move(j1));
		EXPECT_TRUE(j1.get_id() == hamon::jthread::id());
		EXPECT_TRUE(j2.get_id() == id1);
	}

	{
		// ssource has the value of x.ssource prior to the start of construction
		// and x.ssource.stop_possible() is false.
		hamon::jthread j1([] {});
		auto ss1 = j1.get_stop_source();

		hamon::jthread j2(hamon::move(j1));
		EXPECT_TRUE(ss1 == j2.get_stop_source());
		EXPECT_FALSE(j1.get_stop_source().stop_possible());
		EXPECT_TRUE(j2.get_stop_source().stop_possible());
	}
}

}	// namespace ctor_move_test

}	// namespace hamon_jthread_test
