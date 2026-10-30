/**
 *	@file	unit_test_mutex_unique_lock_ctor_time_point.cpp
 *
 *	@brief	mutex_type と time_point を引数に取るコンストラクタのテスト
 *
 *	template<class Clock, class Duration>
 *	unique_lock(mutex_type& m, const chrono::time_point<Clock, Duration>& abs_time);
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/chrono.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace ctor_time_point_test
{

namespace chrono = std::chrono;

static_assert( hamon::is_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, chrono::time_point<chrono::system_clock>>, "");
static_assert(!hamon::is_nothrow_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, chrono::time_point<chrono::system_clock>>, "");	// TODO
static_assert(!hamon::is_trivially_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, chrono::time_point<chrono::system_clock>>, "");
static_assert( hamon::is_implicitly_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, chrono::time_point<chrono::system_clock>>, "");

GTEST_TEST(UniqueLockTest, CtorTimePointTest)
{
	checking_mutex mux;

	{ // check successful lock
		mux.reject = false;
		hamon::unique_lock<checking_mutex> lock(mux, chrono::time_point<chrono::system_clock>());
		EXPECT_TRUE(mux.current_state == checking_mutex::locked_via_try_lock_until);
		EXPECT_TRUE(lock.owns_lock());
	}
	EXPECT_TRUE(mux.current_state == checking_mutex::unlocked);

	{ // check unsuccessful lock
		mux.reject = true;
		hamon::unique_lock<checking_mutex> lock(mux, chrono::time_point<chrono::system_clock>());
		EXPECT_TRUE(mux.current_state == checking_mutex::unlocked);
		EXPECT_TRUE(mux.last_try == checking_mutex::locked_via_try_lock_until);
		EXPECT_FALSE(lock.owns_lock());
	}
	EXPECT_TRUE(mux.current_state == checking_mutex::unlocked);
}

}	// namespace ctor_time_point_test

}	// namespace hamon_unique_lock_test
