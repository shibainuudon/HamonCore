/**
 *	@file	unit_test_mutex_unique_lock_owns_lock.cpp
 *
 *	@brief	owns_lock のテスト
 *
 *	bool owns_lock() const noexcept;
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace owns_lock_test
{

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::unique_lock<checking_mutex>>().owns_lock()), bool>, "");
static_assert(noexcept(hamon::declval<hamon::unique_lock<checking_mutex>>().owns_lock()), "");

GTEST_TEST(UniqueLockTest, OwnsLockTest)
{
	checking_mutex mux;
	const hamon::unique_lock<checking_mutex> lock0; // Make sure `owns_lock()` is `const`
	EXPECT_TRUE(!lock0.owns_lock());
	hamon::unique_lock<checking_mutex> lock1(mux);
	EXPECT_TRUE(lock1.owns_lock());
	lock1.unlock();
	EXPECT_TRUE(!lock1.owns_lock());
}

}	// namespace owns_lock_test

}	// namespace hamon_unique_lock_test
