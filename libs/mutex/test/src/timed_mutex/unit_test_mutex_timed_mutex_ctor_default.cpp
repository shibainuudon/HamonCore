/**
 *	@file	unit_test_mutex_timed_mutex_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	timed_mutex();
 */

#include <hamon/mutex/timed_mutex.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_timed_mutex_test
{

namespace ctor_default_test
{

static_assert( hamon::is_default_constructible_v<hamon::timed_mutex>, "");
//static_assert(!hamon::is_nothrow_default_constructible_v<hamon::timed_mutex>, "");	// TODO
static_assert(!hamon::is_trivially_default_constructible_v<hamon::timed_mutex>, "");
static_assert( hamon::is_implicitly_default_constructible_v<hamon::timed_mutex>, "");

GTEST_TEST(TimedMutexTest, CtorDefaultTest)
{
	// The mutex is unlocked after default construction
	{
		hamon::timed_mutex m;
		EXPECT_TRUE(m.try_lock());
		m.unlock();
	}
}

}	// namespace ctor_default_test

}	// namespace hamon_timed_mutex_test
