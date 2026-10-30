/**
 *	@file	unit_test_mutex_unique_lock_op_bool.cpp
 *
 *	@brief	operator bool() のテスト
 *
 *	explicit operator bool() const noexcept;
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace op_bool_test
{

static_assert(hamon::is_same_v<decltype(static_cast<bool>(hamon::declval<hamon::unique_lock<checking_mutex>>())), bool>, "");
static_assert(noexcept(static_cast<bool>(hamon::declval<hamon::unique_lock<checking_mutex>>())), "");

static_assert(hamon::is_constructible_v<bool, hamon::unique_lock<checking_mutex>>, "");
static_assert(!hamon::is_convertible_v<hamon::unique_lock<checking_mutex>, bool>, "");

GTEST_TEST(UniqueLockTest, OpBoolTest)
{
	checking_mutex mux;
	const hamon::unique_lock<checking_mutex> lk0; // Make sure `operator bool()` is `const`
	EXPECT_TRUE(!static_cast<bool>(lk0));
	hamon::unique_lock<checking_mutex> lk1(mux);
	EXPECT_TRUE(static_cast<bool>(lk1));
	lk1.unlock();
	EXPECT_TRUE(!static_cast<bool>(lk1));
}

}	// namespace op_bool_test

}	// namespace hamon_unique_lock_test
