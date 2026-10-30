/**
 *	@file	unit_test_mutex_unique_lock_ctor_defer_lock.cpp
 *
 *	@brief	mutex_type と defer_lock_t を引数に取るコンストラクタのテスト
 *
 *	unique_lock(mutex_type& m, defer_lock_t) noexcept;
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/mutex/defer_lock_t.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace ctor_defer_lock_test
{

static_assert( hamon::is_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, hamon::defer_lock_t>, "");
static_assert( hamon::is_nothrow_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, hamon::defer_lock_t>, "");	// TODO
static_assert(!hamon::is_trivially_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, hamon::defer_lock_t>, "");
static_assert( hamon::is_implicitly_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, hamon::defer_lock_t>, "");

GTEST_TEST(UniqueLockTest, CtorDeferLockTest)
{
	checking_mutex m;
	hamon::unique_lock<checking_mutex> lk(m, hamon::defer_lock);
	EXPECT_TRUE(m.last_try == checking_mutex::none);
	EXPECT_TRUE(lk.mutex() == hamon::addressof(m));
	EXPECT_TRUE(lk.owns_lock() == false);
}

}	// namespace ctor_defer_lock_test

}	// namespace hamon_unique_lock_test
