/**
 *	@file	unit_test_thread_id.cpp
 *
 *	@brief	thread::id のテスト
 */

#include <hamon/thread/thread.hpp>
#include <hamon/compare.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace id_test
{

GTEST_TEST(ThreadTest, IDTest)
{
	hamon::thread t1;
	hamon::thread t2([](){});
	hamon::thread t3([](){});

	EXPECT_TRUE (t1.get_id() == hamon::thread::id{});
	EXPECT_FALSE(t2.get_id() == hamon::thread::id{});
	EXPECT_FALSE(t3.get_id() == hamon::thread::id{});
	EXPECT_FALSE(t1.get_id() == t2.get_id());
	EXPECT_FALSE(t2.get_id() == t3.get_id());

	EXPECT_FALSE(t1.get_id() != hamon::thread::id{});
	EXPECT_TRUE (t2.get_id() != hamon::thread::id{});
	EXPECT_TRUE (t3.get_id() != hamon::thread::id{});
	EXPECT_TRUE (t1.get_id() != t2.get_id());
	EXPECT_TRUE (t2.get_id() != t3.get_id());

	if (t2.get_id() < t3.get_id())
	{
		EXPECT_TRUE (t2.get_id() <= t3.get_id());
		EXPECT_FALSE(t2.get_id() >  t3.get_id());
		EXPECT_FALSE(t2.get_id() >= t3.get_id());
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		EXPECT_TRUE(hamon::is_lt(t2.get_id() <=> t3.get_id()));
#endif
	}
	else
	{
		EXPECT_FALSE(t2.get_id() <= t3.get_id());
		EXPECT_TRUE (t2.get_id() >  t3.get_id());
		EXPECT_TRUE (t2.get_id() >= t3.get_id());
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		EXPECT_TRUE(hamon::is_gt(t2.get_id() <=> t3.get_id()));
#endif
	}

	//t1.join();
	t2.join();
	t3.join();
}

}	// namespace id_test

}	// namespace hamon_thread_test
