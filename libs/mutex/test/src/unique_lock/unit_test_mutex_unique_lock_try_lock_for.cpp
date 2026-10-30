/**
 *	@file	unit_test_mutex_unique_lock_try_lock_for.cpp
 *
 *	@brief	try_lock_for のテスト
 *
 *	template<class Rep, class Period>
 *	bool try_lock_for(const chrono::duration<Rep, Period>& rel_time);
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

namespace try_lock_for_test
{

using ms = std::chrono::milliseconds;

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::unique_lock<checking_mutex>>().try_lock_for(ms())), bool>, "");
static_assert(!noexcept(hamon::declval<hamon::unique_lock<checking_mutex>>().try_lock_for(ms())), "");

GTEST_TEST(UniqueLockTest, TryLockForTest)
{
	checking_mutex mux;

	hamon::unique_lock<checking_mutex> lock(mux, hamon::defer_lock_t());

	EXPECT_TRUE(lock.try_lock_for(ms(5)));
	EXPECT_TRUE(mux.current_state == checking_mutex::locked_via_try_lock_for);
	EXPECT_TRUE(lock.owns_lock());

#if !defined(HAMON_NO_EXCEPTIONS)
	try
	{
		mux.last_try = checking_mutex::none;
		(void)lock.try_lock_for(ms(5));

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
	EXPECT_TRUE(!lock.try_lock_for(ms(5)));
	EXPECT_TRUE(mux.last_try == checking_mutex::locked_via_try_lock_for);
	EXPECT_TRUE(!lock.owns_lock());

	lock.release();

#if !defined(HAMON_NO_EXCEPTIONS)
	try
	{
		mux.last_try = checking_mutex::none;
		(void)lock.try_lock_for(ms(5));

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

}	// namespace try_lock_for_test

}	// namespace hamon_unique_lock_test
