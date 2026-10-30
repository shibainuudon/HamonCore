/**
 *	@file	unit_test_mutex_unique_lock_release.cpp
 *
 *	@brief	release のテスト
 *
 *	mutex_type* release() noexcept;
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace release_test
{

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::unique_lock<checking_mutex>>().release()), checking_mutex*>, "");
static_assert(noexcept(hamon::declval<hamon::unique_lock<checking_mutex>>().release()), "");

GTEST_TEST(UniqueLockTest, ReleaseTest)
{
	checking_mutex mux;
	hamon::unique_lock<checking_mutex> lock(mux);
	EXPECT_TRUE(lock.mutex() == hamon::addressof(mux));
	EXPECT_TRUE(lock.owns_lock());

	EXPECT_TRUE(mux.current_state == checking_mutex::locked_via_lock);

	EXPECT_TRUE(lock.release() == hamon::addressof(mux));
	EXPECT_TRUE(lock.mutex() == nullptr);
	EXPECT_TRUE(!lock.owns_lock());
	EXPECT_TRUE(mux.last_try == checking_mutex::locked_via_lock);
	EXPECT_TRUE(mux.current_state == checking_mutex::locked_via_lock);
	mux.unlock();
}

}	// namespace release_test

}	// namespace hamon_unique_lock_test
