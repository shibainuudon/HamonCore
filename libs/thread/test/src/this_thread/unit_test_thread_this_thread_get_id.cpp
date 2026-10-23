/**
 *	@file	unit_test_thread_this_thread_get_id.cpp
 *
 *	@brief	this_thread::get_id のテスト
 *
 *	thread::id get_id() noexcept;
 */

#include <hamon/thread/this_thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace this_thread_get_id_test
{

GTEST_TEST(ThisThreadTest, GetIdTest)
{
	static_assert(noexcept(hamon::this_thread::get_id()), "");
	static_assert(hamon::is_same_v<decltype(hamon::this_thread::get_id()), hamon::thread::id>, "");

	hamon::thread t([](){});

	auto id1 = hamon::this_thread::get_id();
	auto id2 = hamon::this_thread::get_id();
	auto id3 = t.get_id();

	EXPECT_TRUE(id1 == id2);
	EXPECT_TRUE(id1 != id3);
	EXPECT_TRUE(id1 != hamon::thread::id{});

	t.join();
}

}	// namespace this_thread_get_id_test

}	// namespace hamon_thread_test
