/**
 *	@file	unit_test_mutex_unique_lock_try_lock_until.cpp
 *
 *	@brief	try_lock_until のテスト
 *
 *	template<class Clock, class Duration>
 *	bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time);
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/mutex/defer_lock_t.hpp>
#include <hamon/chrono.hpp>
#include <hamon/system_error.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace try_lock_until_test
{

using Clock = std::chrono::system_clock;

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::unique_lock<checking_mutex>>().try_lock_until(Clock::now())), bool>, "");
static_assert(!noexcept(hamon::declval<hamon::unique_lock<checking_mutex>>().try_lock_until(Clock::now())), "");

GTEST_TEST(UniqueLockTest, TryLockUntilTest)
{
	checking_mutex mux;

	hamon::unique_lock<checking_mutex> lock(mux, hamon::defer_lock_t());

	EXPECT_TRUE(lock.try_lock_until(Clock::now()));
	EXPECT_TRUE(mux.current_state == checking_mutex::locked_via_try_lock_until);
	EXPECT_TRUE(lock.owns_lock());

#if !defined(HAMON_NO_EXCEPTIONS)
	try
	{
		mux.last_try = checking_mutex::none;
		(void)lock.try_lock_until(Clock::now());
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
#endif

	lock.unlock();
	mux.reject = true;
	EXPECT_TRUE(!lock.try_lock_until(Clock::now()));
	EXPECT_TRUE(mux.last_try == checking_mutex::locked_via_try_lock_until);
	EXPECT_TRUE(lock.owns_lock() == false);
	lock.release();

#if !defined(HAMON_NO_EXCEPTIONS)
	try
	{
		mux.last_try = checking_mutex::none;
		(void)lock.try_lock_until(Clock::now());
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

}	// namespace try_lock_until_test

}	// namespace hamon_unique_lock_test
