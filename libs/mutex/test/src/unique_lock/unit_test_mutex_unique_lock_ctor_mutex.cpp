/**
 *	@file	unit_test_mutex_unique_lock_ctor_mutex.cpp
 *
 *	@brief	mutex_type を引数に取るコンストラクタのテスト
 *
 *	explicit unique_lock(mutex_type& m);
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace ctor_mutex_test
{

static_assert( hamon::is_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&>, "");
static_assert(!hamon::is_nothrow_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&>, "");
static_assert(!hamon::is_trivially_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&>, "");
static_assert(!hamon::is_implicitly_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&>, "");

GTEST_TEST(UniqueLockTest, CtorMutexTest)
{
	checking_mutex mux;
	{
		hamon::unique_lock<checking_mutex> lock(mux);
		EXPECT_TRUE(mux.current_state == checking_mutex::locked_via_lock);
	}
	EXPECT_TRUE(mux.current_state == checking_mutex::unlocked);
}

}	// namespace ctor_mutex_test

}	// namespace hamon_unique_lock_test
