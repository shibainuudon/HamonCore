/**
 *	@file	unit_test_mutex_lock_guard_ctor_adopt_lock.cpp
 *
 *	@brief	mutex_typeとadopt_lock_tを引数に取るコンストラクタのテスト
 *
 *	lock_guard(mutex_type& m, adopt_lock_t);
 */

#include <hamon/mutex/lock_guard.hpp>
#include <hamon/mutex/adopt_lock_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "lock_guard_test_helper.hpp"

namespace hamon_lock_guard_test
{

namespace ctor_adopt_lock_test
{

static_assert( hamon::is_constructible_v<hamon::lock_guard<MyMutex>, MyMutex&, hamon::adopt_lock_t>, "");
//static_assert(!hamon::is_nothrow_constructible_v<hamon::lock_guard<MyMutex>, MyMutex&, hamon::adopt_lock_t>, "");	// TODO
static_assert(!hamon::is_trivially_constructible_v<hamon::lock_guard<MyMutex>, MyMutex&, hamon::adopt_lock_t>, "");
static_assert( hamon::is_implicitly_constructible_v<hamon::lock_guard<MyMutex>, MyMutex&, hamon::adopt_lock_t>, "");

GTEST_TEST(LockGuardTest, CtorAdoptLockTest)
{
	MyMutex m;
	{
		m.lock();
		hamon::lock_guard<MyMutex> lg(m, hamon::adopt_lock);
		EXPECT_TRUE(m.locked);
	}
	EXPECT_FALSE(m.locked);
}

}	// namespace ctor_adopt_lock_test

}	// namespace hamon_lock_guard_test
