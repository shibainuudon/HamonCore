/**
 *	@file	unit_test_mutex_defer_lock_t.cpp
 *
 *	@brief	defer_lock_t のテスト
 *
 *	struct defer_lock_t  { };
 *	inline constexpr defer_lock_t  defer_lock { };
 */

#include <hamon/mutex/defer_lock_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_defer_lock_t_test
{

static_assert( hamon::is_default_constructible_v<hamon::defer_lock_t>, "");
static_assert( hamon::is_nothrow_default_constructible_v<hamon::defer_lock_t>, "");
static_assert( hamon::is_trivially_default_constructible_v<hamon::defer_lock_t>, "");
static_assert(!hamon::is_implicitly_default_constructible_v<hamon::defer_lock_t>, "");

static_assert( hamon::is_copy_constructible_v<hamon::defer_lock_t>, "");
static_assert( hamon::is_nothrow_copy_constructible_v<hamon::defer_lock_t>, "");
static_assert( hamon::is_trivially_copy_constructible_v<hamon::defer_lock_t>, "");
static_assert( hamon::is_implicitly_copy_constructible_v<hamon::defer_lock_t>, "");

static_assert( hamon::is_move_constructible_v<hamon::defer_lock_t>, "");
static_assert( hamon::is_nothrow_move_constructible_v<hamon::defer_lock_t>, "");
static_assert( hamon::is_trivially_move_constructible_v<hamon::defer_lock_t>, "");
static_assert( hamon::is_implicitly_move_constructible_v<hamon::defer_lock_t>, "");

static_assert( hamon::is_copy_assignable_v<hamon::defer_lock_t>, "");
static_assert( hamon::is_nothrow_copy_assignable_v<hamon::defer_lock_t>, "");
static_assert( hamon::is_trivially_copy_assignable_v<hamon::defer_lock_t>, "");

static_assert( hamon::is_move_assignable_v<hamon::defer_lock_t>, "");
static_assert( hamon::is_nothrow_move_assignable_v<hamon::defer_lock_t>, "");
static_assert( hamon::is_trivially_move_assignable_v<hamon::defer_lock_t>, "");

static_assert(hamon::is_same_v<decltype(hamon::defer_lock), hamon::defer_lock_t const>, "");

GTEST_TEST(DeferLockTTest, DeferLockTTest)
{
	constexpr hamon::defer_lock_t f;
	(void)f;
}

}	// namespace hamon_defer_lock_t_test
