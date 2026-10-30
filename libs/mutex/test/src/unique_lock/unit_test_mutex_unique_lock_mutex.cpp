/**
 *	@file	unit_test_mutex_unique_lock_mutex.cpp
 *
 *	@brief	mutex のテスト
 *
 *	mutex_type* mutex() const noexcept;
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace mutex_test
{

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::unique_lock<checking_mutex>>().mutex()), checking_mutex*>, "");
static_assert(noexcept(hamon::declval<hamon::unique_lock<checking_mutex>>().mutex()), "");

GTEST_TEST(UniqueLockTest, MutexTest)
{
	checking_mutex mux;
	const hamon::unique_lock<checking_mutex> lock0; // Make sure `mutex()` is `const`
	EXPECT_TRUE(lock0.mutex() == nullptr);
	hamon::unique_lock<checking_mutex> lock1(mux);
	EXPECT_TRUE(lock1.mutex() == hamon::addressof(mux));
	lock1.unlock();
	EXPECT_TRUE(lock1.mutex() == hamon::addressof(mux));
}

}	// namespace mutex_test

}	// namespace hamon_unique_lock_test
