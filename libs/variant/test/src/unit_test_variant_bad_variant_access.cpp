/**
 *	@file	unit_test_variant_bad_variant_access.cpp
 *
 *	@brief	bad_variant_access のテスト
 */

#include <hamon/variant/bad_variant_access.hpp>
#include <hamon/type_traits/is_base_of.hpp>
#include <gtest/gtest.h>
#include <exception>

GTEST_TEST(VariantTest, BadVariantAccessTest)
{
	static_assert(hamon::is_base_of<std::exception, hamon::bad_variant_access>::value, "");
	static_assert(noexcept(hamon::bad_variant_access{}), "must be noexcept");
	static_assert(noexcept(hamon::bad_variant_access{}.what()), "must be noexcept");
	hamon::bad_variant_access ex;
	EXPECT_TRUE(ex.what() != nullptr);
}
