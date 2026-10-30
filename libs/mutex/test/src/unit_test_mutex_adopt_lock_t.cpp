/**
 *	@file	unit_test_mutex_adopt_lock_t.cpp
 *
 *	@brief	adopt_lock_t のテスト
 *
 *	struct adopt_lock_t  { };
 *	inline constexpr adopt_lock_t  adopt_lock { };
 */

#include <hamon/mutex/adopt_lock_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_adopt_lock_t_test
{

static_assert( hamon::is_default_constructible_v<hamon::adopt_lock_t>, "");
static_assert( hamon::is_nothrow_default_constructible_v<hamon::adopt_lock_t>, "");
static_assert( hamon::is_trivially_default_constructible_v<hamon::adopt_lock_t>, "");
static_assert(!hamon::is_implicitly_default_constructible_v<hamon::adopt_lock_t>, "");

static_assert( hamon::is_copy_constructible_v<hamon::adopt_lock_t>, "");
static_assert( hamon::is_nothrow_copy_constructible_v<hamon::adopt_lock_t>, "");
static_assert( hamon::is_trivially_copy_constructible_v<hamon::adopt_lock_t>, "");
static_assert( hamon::is_implicitly_copy_constructible_v<hamon::adopt_lock_t>, "");

static_assert( hamon::is_move_constructible_v<hamon::adopt_lock_t>, "");
static_assert( hamon::is_nothrow_move_constructible_v<hamon::adopt_lock_t>, "");
static_assert( hamon::is_trivially_move_constructible_v<hamon::adopt_lock_t>, "");
static_assert( hamon::is_implicitly_move_constructible_v<hamon::adopt_lock_t>, "");

static_assert( hamon::is_copy_assignable_v<hamon::adopt_lock_t>, "");
static_assert( hamon::is_nothrow_copy_assignable_v<hamon::adopt_lock_t>, "");
static_assert( hamon::is_trivially_copy_assignable_v<hamon::adopt_lock_t>, "");

static_assert( hamon::is_move_assignable_v<hamon::adopt_lock_t>, "");
static_assert( hamon::is_nothrow_move_assignable_v<hamon::adopt_lock_t>, "");
static_assert( hamon::is_trivially_move_assignable_v<hamon::adopt_lock_t>, "");

static_assert(hamon::is_same_v<decltype(hamon::adopt_lock), hamon::adopt_lock_t const>, "");

GTEST_TEST(AdoptLockTTest, AdoptLockTTest)
{
	constexpr hamon::adopt_lock_t f;
	(void)f;
}

}	// namespace hamon_adopt_lock_t_test
