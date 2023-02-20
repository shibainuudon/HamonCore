/**
 *	@file	unit_test_variant_monostate.cpp
 *
 *	@brief	monostate のテスト
 */

#include <hamon/variant/monostate.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_move_assignable.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

static_assert(hamon::is_trivially_default_constructible<hamon::monostate>::value, "");
static_assert(hamon::is_trivially_copy_constructible<hamon::monostate>::value, "");
static_assert(hamon::is_trivially_copy_assignable<hamon::monostate>::value, "");
static_assert(hamon::is_trivially_move_constructible<hamon::monostate>::value, "");
static_assert(hamon::is_trivially_move_assignable<hamon::monostate>::value, "");
static_assert(hamon::is_trivially_destructible<hamon::monostate>::value, "");

GTEST_TEST(VariantTest, MonostateTest)
{
	HAMON_CXX11_CONSTEXPR hamon::monostate m1{};
	HAMON_CXX11_CONSTEXPR hamon::monostate m2{};
	{
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 < m2);
		HAMON_ASSERT_NOEXCEPT_TRUE(m1 < m2);
	}
	{
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 > m2);
		HAMON_ASSERT_NOEXCEPT_TRUE(m1 > m2);
	}
	{
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(m1 <= m2);
		HAMON_ASSERT_NOEXCEPT_TRUE(m1 <= m2);
	}
	{
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(m1 >= m2);
		HAMON_ASSERT_NOEXCEPT_TRUE(m1 >= m2);
	}
	{
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(m1 == m2);
		HAMON_ASSERT_NOEXCEPT_TRUE(m1 == m2);
	}
	{
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(m1 != m2);
		HAMON_ASSERT_NOEXCEPT_TRUE(m1 != m2);
	}
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	{
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE((m1 <=> m2) == 0);
		HAMON_ASSERT_NOEXCEPT_TRUE(m1 <=> m2);
	}
#endif
}
