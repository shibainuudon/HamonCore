/**
 *	@file	unit_test_mutex_unique_lock_ctor_try_to_lock.cpp
 *
 *	@brief	mutex_type と try_to_lock_t を引数に取るコンストラクタのテスト
 *
 *	unique_lock(mutex_type& m, try_to_lock_t);
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/mutex/try_to_lock_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace ctor_try_to_lock_test
{

static_assert( hamon::is_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, hamon::try_to_lock_t>, "");
static_assert(!hamon::is_nothrow_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, hamon::try_to_lock_t>, "");	// TODO
static_assert(!hamon::is_trivially_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, hamon::try_to_lock_t>, "");
static_assert( hamon::is_implicitly_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, hamon::try_to_lock_t>, "");

GTEST_TEST(UniqueLockTest, CtorTryToLockTest)
{
	checking_mutex mux;

	{ // check successful lock
		mux.reject = false;
		hamon::unique_lock<checking_mutex> lock(mux, hamon::try_to_lock);
		EXPECT_TRUE(mux.current_state == checking_mutex::locked_via_try_lock);
		EXPECT_TRUE(lock.owns_lock());
	}
	EXPECT_TRUE(mux.current_state == checking_mutex::unlocked);

	{ // check successful lock
		mux.reject = true;
		hamon::unique_lock<checking_mutex> lock(mux, hamon::try_to_lock);
		EXPECT_TRUE(mux.last_try == checking_mutex::locked_via_try_lock);
		EXPECT_TRUE(mux.current_state == checking_mutex::unlocked);
		EXPECT_FALSE(lock.owns_lock());
	}
	EXPECT_TRUE(mux.current_state == checking_mutex::unlocked);
}

}	// namespace ctor_try_to_lock_test

}	// namespace hamon_unique_lock_test
