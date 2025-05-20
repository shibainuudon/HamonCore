/**
 *	@file	unit_test_bad_expected_access_void.cpp
 *
 *	@brief	bad_expected_access<void> のテスト
 */

#include <hamon/expected/bad_expected_access.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bad_expected_access_test
{

namespace void_test
{

static_assert(!hamon::is_constructible<hamon::bad_expected_access<void>, int>::value, "");
static_assert(!hamon::is_default_constructible<hamon::bad_expected_access<void>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::bad_expected_access<void>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::bad_expected_access<void>>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::bad_expected_access<void>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::bad_expected_access<void>>::value, "");

struct Inherit : hamon::bad_expected_access<void> {};

static_assert(!hamon::is_constructible<Inherit, int>::value, "");

static_assert( hamon::is_default_constructible<Inherit>::value, "");
static_assert( hamon::is_nothrow_default_constructible<Inherit>::value, "");
static_assert(!hamon::is_trivially_default_constructible<Inherit>::value, "");
static_assert( hamon::is_implicitly_default_constructible<Inherit>::value, "");

static_assert( hamon::is_copy_constructible<Inherit>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<Inherit>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<Inherit>::value, "");
static_assert( hamon::is_implicitly_copy_constructible<Inherit>::value, "");

static_assert( hamon::is_move_constructible<Inherit>::value, "");
static_assert( hamon::is_nothrow_move_constructible<Inherit>::value, "");
static_assert(!hamon::is_trivially_move_constructible<Inherit>::value, "");
static_assert( hamon::is_implicitly_move_constructible<Inherit>::value, "");

static_assert( hamon::is_copy_assignable<Inherit>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<Inherit>::value, "");
static_assert(!hamon::is_trivially_copy_assignable<Inherit>::value, "");

static_assert( hamon::is_move_assignable<Inherit>::value, "");
static_assert( hamon::is_nothrow_move_assignable<Inherit>::value, "");
static_assert(!hamon::is_trivially_move_assignable<Inherit>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

/*HAMON_CXX20_CONSTEXPR*/ bool test()
{
	Inherit unex;
	VERIFY(unex.what() != nullptr);
	static_assert(noexcept(unex.what()), "");
	return true;
}

#undef VERIFY

GTEST_TEST(BadExpectedAccessTest, VoidTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE((test()));
}

}	// namespace void_test

}	// namespace hamon_bad_expected_access_test
