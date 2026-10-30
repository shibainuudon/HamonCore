/**
 *	@file	unit_test_mutex_mutex_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr mutex() noexcept;
 */

#include <hamon/mutex/mutex.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_mutex_test
{

namespace ctor_default_test
{

static_assert( hamon::is_default_constructible_v<hamon::mutex>, "");
static_assert( hamon::is_nothrow_default_constructible_v<hamon::mutex>, "");
static_assert(!hamon::is_trivially_default_constructible_v<hamon::mutex>, "");
static_assert( hamon::is_implicitly_default_constructible_v<hamon::mutex>, "");

GTEST_TEST(MutexTest, CtorDefaultTest)
{
	// The mutex is unlocked after default construction
	{
		hamon::mutex m;
		EXPECT_TRUE(m.try_lock());
		m.unlock();
	}
}

}	// namespace ctor_default_test

}	// namespace hamon_mutex_test
