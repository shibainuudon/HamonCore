/**
 *	@file	unit_test_thread_thread_get_id.cpp
 *
 *	@brief	get_id のテスト
 *
 *	id get_id() const noexcept;
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace get_id_test
{

GTEST_TEST(ThreadTest, GetIdTest)
{
	int x = 0;
	hamon::thread t1([&] { ++x; });
	hamon::thread t2;

	static_assert(noexcept(t1.get_id()), "");
	static_assert(hamon::is_same_v<decltype(t1.get_id()), hamon::thread::id>, "");

	EXPECT_TRUE(t1.get_id() != hamon::thread::id());
	EXPECT_TRUE(t2.get_id() == hamon::thread::id());

	t1.join();
}

}	// namespace get_id_test

}	// namespace hamon_thread_test
