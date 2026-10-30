/**
 *	@file	unit_test_mutex_try_to_lock_t.cpp
 *
 *	@brief	try_to_lock_t のテスト
 *
 *	struct try_to_lock_t  { };
 *	inline constexpr try_to_lock_t  try_to_lock { };
 */

#include <hamon/mutex/try_to_lock_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_try_to_lock_t_test
{

static_assert( hamon::is_default_constructible_v<hamon::try_to_lock_t>, "");
static_assert( hamon::is_nothrow_default_constructible_v<hamon::try_to_lock_t>, "");
static_assert( hamon::is_trivially_default_constructible_v<hamon::try_to_lock_t>, "");
static_assert(!hamon::is_implicitly_default_constructible_v<hamon::try_to_lock_t>, "");

static_assert( hamon::is_copy_constructible_v<hamon::try_to_lock_t>, "");
static_assert( hamon::is_nothrow_copy_constructible_v<hamon::try_to_lock_t>, "");
static_assert( hamon::is_trivially_copy_constructible_v<hamon::try_to_lock_t>, "");
static_assert( hamon::is_implicitly_copy_constructible_v<hamon::try_to_lock_t>, "");

static_assert( hamon::is_move_constructible_v<hamon::try_to_lock_t>, "");
static_assert( hamon::is_nothrow_move_constructible_v<hamon::try_to_lock_t>, "");
static_assert( hamon::is_trivially_move_constructible_v<hamon::try_to_lock_t>, "");
static_assert( hamon::is_implicitly_move_constructible_v<hamon::try_to_lock_t>, "");

static_assert( hamon::is_copy_assignable_v<hamon::try_to_lock_t>, "");
static_assert( hamon::is_nothrow_copy_assignable_v<hamon::try_to_lock_t>, "");
static_assert( hamon::is_trivially_copy_assignable_v<hamon::try_to_lock_t>, "");

static_assert( hamon::is_move_assignable_v<hamon::try_to_lock_t>, "");
static_assert( hamon::is_nothrow_move_assignable_v<hamon::try_to_lock_t>, "");
static_assert( hamon::is_trivially_move_assignable_v<hamon::try_to_lock_t>, "");

static_assert(hamon::is_same_v<decltype(hamon::try_to_lock), hamon::try_to_lock_t const>, "");

GTEST_TEST(TryToLockTTest, TryToLockTTest)
{
	constexpr hamon::try_to_lock_t f;
	(void)f;
}

}	// namespace hamon_try_to_lock_t_test
