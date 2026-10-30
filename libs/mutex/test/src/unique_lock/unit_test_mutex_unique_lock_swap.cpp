/**
 *	@file	unit_test_mutex_unique_lock_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	void swap(unique_lock& u) noexcept;
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace swap_test
{

GTEST_TEST(UniqueLockTest, SwapTest)
{
	checking_mutex mux;
	hamon::unique_lock<checking_mutex> lock1(mux);
	hamon::unique_lock<checking_mutex> lock2;

	static_assert(hamon::is_same_v<decltype(lock1.swap(lock2)), void>, "");
	static_assert(noexcept(lock1.swap(lock2)), "");

	lock1.swap(lock2);

	EXPECT_TRUE(lock1.mutex() == nullptr);
	EXPECT_TRUE(!lock1.owns_lock());
	EXPECT_TRUE(lock2.mutex() == hamon::addressof(mux));
	EXPECT_TRUE(lock2.owns_lock() == true);

	static_assert(hamon::is_same_v<decltype(swap(lock1, lock2)), void>, "");
	static_assert(noexcept(swap(lock1, lock2)), "");

	swap(lock1, lock2);

	EXPECT_TRUE(lock1.mutex() == hamon::addressof(mux));
	EXPECT_TRUE(lock1.owns_lock() == true);
	EXPECT_TRUE(lock2.mutex() == nullptr);
	EXPECT_TRUE(!lock2.owns_lock());
}

}	// namespace swap_test

}	// namespace hamon_unique_lock_test
