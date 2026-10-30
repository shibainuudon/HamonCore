/**
 *	@file	unit_test_mutex_unique_lock_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	unique_lock(unique_lock&& u) noexcept;
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace ctor_move_test
{

static_assert( hamon::is_move_constructible_v<hamon::unique_lock<checking_mutex>>, "");
static_assert( hamon::is_nothrow_move_constructible_v<hamon::unique_lock<checking_mutex>>, "");
static_assert(!hamon::is_trivially_move_constructible_v<hamon::unique_lock<checking_mutex>>, "");
static_assert( hamon::is_implicitly_move_constructible_v<hamon::unique_lock<checking_mutex>>, "");

GTEST_TEST(UniqueLockTest, CtorMoveTest)
{
	checking_mutex m;
	hamon::unique_lock<checking_mutex> lk0(m);
	hamon::unique_lock<checking_mutex> lk = hamon::move(lk0);

	EXPECT_TRUE(lk.mutex() == hamon::addressof(m));
	EXPECT_TRUE(lk.owns_lock());
	EXPECT_TRUE(lk0.mutex() == nullptr);
	EXPECT_FALSE(lk0.owns_lock());
}

}	// namespace ctor_move_test

}	// namespace hamon_unique_lock_test
