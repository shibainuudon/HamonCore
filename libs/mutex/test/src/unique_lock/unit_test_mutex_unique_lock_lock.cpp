/**
 *	@file	unit_test_mutex_unique_lock_lock.cpp
 *
 *	@brief	lock のテスト
 *
 *	void lock();
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/mutex/defer_lock_t.hpp>
#include <hamon/system_error.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace lock_test
{

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::unique_lock<checking_mutex>>().lock()), void>, "");
static_assert(!noexcept(hamon::declval<hamon::unique_lock<checking_mutex>>().lock()), "");

GTEST_TEST(UniqueLockTest, LockTest)
{
	checking_mutex mux;
	hamon::unique_lock<checking_mutex> lk(mux, hamon::defer_lock_t());
	EXPECT_TRUE(mux.last_try == checking_mutex::none);
	lk.lock();
	EXPECT_TRUE(mux.current_state == checking_mutex::locked_via_lock);
	mux.last_try = checking_mutex::none;

#if !defined(HAMON_NO_EXCEPTIONS)
	try
	{
		mux.last_try = checking_mutex::none;
		lk.lock();
		EXPECT_TRUE(false);
	}
	catch (hamon::system_error& e)
	{
		EXPECT_TRUE(mux.last_try == checking_mutex::none);
		EXPECT_TRUE(e.code() == hamon::errc::resource_deadlock_would_occur);
	}
	catch (...)
	{
		EXPECT_TRUE(false);
	}

	lk.unlock();
	lk.release();

	try
	{
		mux.last_try = checking_mutex::none;
		lk.lock();
		EXPECT_TRUE(false);
	}
	catch (hamon::system_error& e)
	{
		EXPECT_TRUE(mux.last_try == checking_mutex::none);
		EXPECT_TRUE(e.code() == hamon::errc::operation_not_permitted);
	}
	catch (...)
	{
		EXPECT_TRUE(false);
	}
#endif
}

}	// namespace lock_test

}	// namespace hamon_unique_lock_test
