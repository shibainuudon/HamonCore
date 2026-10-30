/**
 *	@file	unit_test_mutex_once_flag.cpp
 *
 *	@brief	once_flag のテスト
 *
 *	struct once_flag {
 *		constexpr once_flag() noexcept;
 *
 *		once_flag(const once_flag&) = delete;
 *		once_flag& operator=(const once_flag&) = delete;
 *	};
 */

#include <hamon/mutex/once_flag.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_once_flag_test
{

static_assert( hamon::is_default_constructible_v<hamon::once_flag>, "");
static_assert( hamon::is_nothrow_default_constructible_v<hamon::once_flag>, "");
static_assert(!hamon::is_trivially_default_constructible_v<hamon::once_flag>, "");
static_assert( hamon::is_implicitly_default_constructible_v<hamon::once_flag>, "");

static_assert(!hamon::is_copy_constructible_v<hamon::once_flag>, "");
static_assert(!hamon::is_move_constructible_v<hamon::once_flag>, "");
static_assert(!hamon::is_copy_assignable_v<hamon::once_flag>, "");
static_assert(!hamon::is_move_assignable_v<hamon::once_flag>, "");

GTEST_TEST(OnceFlagTest, OnceFlagTest)
{
	constexpr hamon::once_flag f;
	(void)f;
}

}	// namespace hamon_once_flag_test
