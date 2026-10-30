/**
 *	@file	unit_test_mutex_unique_lock_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	unique_lock() noexcept;
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace ctor_default_test
{

static_assert( hamon::is_default_constructible_v<hamon::unique_lock<checking_mutex>>, "");
static_assert( hamon::is_nothrow_default_constructible_v<hamon::unique_lock<checking_mutex>>, "");
static_assert(!hamon::is_trivially_default_constructible_v<hamon::unique_lock<checking_mutex>>, "");
static_assert( hamon::is_implicitly_default_constructible_v<hamon::unique_lock<checking_mutex>>, "");

GTEST_TEST(UniqueLockTest, CtorDefaultTest)
{
	hamon::unique_lock<checking_mutex> ul;
	EXPECT_FALSE(ul.owns_lock());
	EXPECT_TRUE(ul.mutex() == nullptr);
}

}	// namespace ctor_default_test

}	// namespace hamon_unique_lock_test
