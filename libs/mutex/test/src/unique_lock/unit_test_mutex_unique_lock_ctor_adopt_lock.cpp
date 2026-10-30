/**
 *	@file	unit_test_mutex_unique_lock_ctor_adopt_lock.cpp
 *
 *	@brief	mutex_type と adopt_lock_t を引数に取るコンストラクタのテスト
 *
 *	unique_lock(mutex_type& m, adopt_lock_t);
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/mutex/adopt_lock_t.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace ctor_adopt_lock_test
{

static_assert( hamon::is_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, hamon::adopt_lock_t>, "");
//static_assert(!hamon::is_nothrow_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, hamon::adopt_lock_t>, "");	// TODO
static_assert(!hamon::is_trivially_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, hamon::adopt_lock_t>, "");
static_assert( hamon::is_implicitly_constructible_v<hamon::unique_lock<checking_mutex>, checking_mutex&, hamon::adopt_lock_t>, "");

GTEST_TEST(UniqueLockTest, CtorAdoptLockTest)
{
	checking_mutex m;
	m.lock();
	m.last_try = checking_mutex::none;
	hamon::unique_lock<checking_mutex> lk(m, hamon::adopt_lock);
	EXPECT_TRUE(m.last_try == checking_mutex::none);
	EXPECT_TRUE(lk.mutex() == hamon::addressof(m));
	EXPECT_TRUE(lk.owns_lock());
}

}	// namespace ctor_adopt_lock_test

}	// namespace hamon_unique_lock_test
