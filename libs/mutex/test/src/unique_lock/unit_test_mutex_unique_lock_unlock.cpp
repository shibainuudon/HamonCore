/**
 *	@file	unit_test_mutex_unique_lock_unlock.cpp
 *
 *	@brief	unlock のテスト
 *
 *	void unlock();
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/system_error.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace unlock_test
{

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::unique_lock<checking_mutex>>().unlock()), void>, "");
static_assert(!noexcept(hamon::declval<hamon::unique_lock<checking_mutex>>().unlock()), "");

GTEST_TEST(UniqueLockTest, UnlockTest)
{
	checking_mutex mux;
	hamon::unique_lock<checking_mutex> lock(mux);
	EXPECT_TRUE(mux.current_state == checking_mutex::locked_via_lock);
	lock.unlock();
	EXPECT_TRUE(mux.current_state == checking_mutex::unlocked);
	EXPECT_TRUE(!lock.owns_lock());

#if !defined(HAMON_NO_EXCEPTIONS)
	try
	{
		mux.last_try = checking_mutex::none;
		lock.unlock();
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

	lock.release();

#if !defined(HAMON_NO_EXCEPTIONS)
	try
	{
		mux.last_try = checking_mutex::none;
		lock.unlock();
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

}	// namespace unlock_test

}	// namespace hamon_unique_lock_test
