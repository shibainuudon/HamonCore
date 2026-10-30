/**
 *	@file	unit_test_mutex_unique_lock_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 *
 *	unique_lock& operator=(unique_lock&& u) noexcept;
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace assign_move_test
{

static_assert( hamon::is_move_assignable_v<hamon::unique_lock<checking_mutex>>, "");
static_assert( hamon::is_nothrow_move_assignable_v<hamon::unique_lock<checking_mutex>>, "");

GTEST_TEST(UniqueLockTest, AssignMoveTest)
{
	{
		checking_mutex m0;
		checking_mutex m1;
		hamon::unique_lock<checking_mutex> lk0(m0);
		hamon::unique_lock<checking_mutex> lk1(m1);

		// Test self move assignment for lk0.
		lk0 = hamon::move(lk0);
		EXPECT_TRUE(lk0.mutex() == hamon::addressof(m0));
		EXPECT_TRUE(lk0.owns_lock() == true);

		auto& result = (lk1 = hamon::move(lk0));

		EXPECT_TRUE(&result == &lk1);
		EXPECT_TRUE(lk1.mutex() == hamon::addressof(m0));
		EXPECT_TRUE(lk1.owns_lock());
		EXPECT_TRUE(lk0.mutex() == nullptr);
		EXPECT_TRUE(lk0.owns_lock() == false);
	}

	{
		// Test self move-assignment (LWG4172)
		checking_mutex m0;
		hamon::unique_lock<checking_mutex> lk0(m0);
		lk0 = hamon::move(lk0);
		EXPECT_TRUE(lk0.mutex() == hamon::addressof(m0));
		EXPECT_TRUE(lk0.owns_lock() == true);
	}
}

}	// namespace assign_move_test

}	// namespace hamon_unique_lock_test
