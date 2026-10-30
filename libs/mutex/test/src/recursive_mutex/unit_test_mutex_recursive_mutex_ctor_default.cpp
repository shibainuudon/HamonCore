/**
 *	@file	unit_test_mutex_recursive_mutex_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	recursive_mutex();
 */

#include <hamon/mutex/recursive_mutex.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_recursive_mutex_test
{

namespace ctor_default_test
{

static_assert( hamon::is_default_constructible_v<hamon::recursive_mutex>, "");
//static_assert(!hamon::is_nothrow_default_constructible_v<hamon::recursive_mutex>, "");	// TODO
static_assert(!hamon::is_trivially_default_constructible_v<hamon::recursive_mutex>, "");
static_assert( hamon::is_implicitly_default_constructible_v<hamon::recursive_mutex>, "");

GTEST_TEST(RecursiveMutexTest, CtorDefaultTest)
{
	// The mutex is unlocked after default construction
	{
		hamon::recursive_mutex m;
		EXPECT_TRUE(m.try_lock());
		m.unlock();
	}
}

}	// namespace ctor_default_test

}	// namespace hamon_recursive_mutex_test
